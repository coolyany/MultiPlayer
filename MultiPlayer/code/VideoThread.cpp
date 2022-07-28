#include "VideoThread.h"
#include <QDebug>
#include <QImage>

VideoThread::VideoThread(Data *data, QObject* parent)
	: QThread(parent),
	  m_data(data)
{
}

void VideoThread::Start()
{
	this->start();
}

void VideoThread::Stop()
{

}

void VideoThread::setVideoCapture(cv::VideoCapture * cap)
{
	m_cap = cap;
}

void VideoThread::openMedia(QString &filePath)
{
	initDecode(filePath);

	Start();
}

QImage VideoThread::cvMat2QImage(const cv::Mat & mat)
{
	// 8-bits unsigned, NO. OF CHANNELS = 1
	if (mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		// Set the color table (used to translate colour indexes to qRgb values)
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		// Copy input Mat
		uchar *pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	// 8-bits unsigned, NO. OF CHANNELS = 3
	else if (mat.type() == CV_8UC3)
	{
		// Copy input Mat
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		qDebug() << "CV_8UC4";
		// Copy input Mat
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		qDebug() << "ERROR: Mat could not be converted to QImage.";
		return QImage();
	}
}

void VideoThread::initDecode(QString &filePath)
{
	/* alloc AvFormatContext memory */
	fctx = avformat_alloc_context();
	if (!fctx)
	{
		cout << "fctx is nullptr" << endl;
	}
	if (avformat_open_input(&fctx, filePath.toLocal8Bit(), NULL, NULL) != 0)
	{
		cout << "File open failed!" << endl;
		return;
	}
	if (avformat_find_stream_info(fctx, NULL) < 0)
	{
		cout << "Stream find failed!\n";
		return;
	}
	av_dump_format(fctx, -1, filePath.toLocal8Bit(), NULL);

	//找视频流
	/*for (int i = 0; i < fctx->nb_streams; i++)
	{
		if (fctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
			videoStream = i;
	}*/
	videoStream = av_find_best_stream(fctx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
	if (videoStream == -1)
	{
		cout << "Codec find failed!" << endl;
		return;
	}
	cctx = avcodec_alloc_context3(NULL);
	if (avcodec_parameters_to_context(cctx, fctx->streams[videoStream]->codecpar) < 0)
	{
		cout << "Copy stream failed!" << endl;
		return;
	}
	c = avcodec_find_decoder(cctx->codec_id);
	if (!c) {
		cout << "Find Decoder failed!" << endl;
		return;
	}
	if (avcodec_open2(cctx, c, NULL) != 0) {
		cout << "Open codec failed!" << endl;
		return;
	}
	cout << " avcodec_open2 success!" << endl;

	imgCtx = sws_getContext(cctx->width, cctx->height, cctx->pix_fmt, cctx->width, cctx->height, AV_PIX_FMT_BGR24,
		SWS_BICUBIC, NULL, NULL, NULL);
	if (!imgCtx) {
		cout << "Get swscale context failed!" << endl;
		return;
	}
	pkt = av_packet_alloc();
	fr = av_frame_alloc();
	yuv = av_frame_alloc();
	vsize = av_image_get_buffer_size(AV_PIX_FMT_BGR24, cctx->width, cctx->height, 1);
	buf = (uint8_t *)av_malloc(vsize);
	//通过av_image_fill_arrays和out_buffer来初始化pFrameRGB里的data指针和linesize指针.linesize是每个图像的宽大小(字节数)。
	int re = av_image_fill_arrays(yuv->data, yuv->linesize, buf, AV_PIX_FMT_BGR24, cctx->width, cctx->height, 1);
}

// 转换函数
QImage VideoThread::avFrame2QImage(AVFrame *frame)
{
	pFrmDst = av_frame_alloc();
	/*av_image_alloc(pFrmDst->data,
		pFrmDst->linesize,
		frame->width,
		frame->height,
		AV_PIX_FMT_YUV420P,
		1);*/
	if (img_convert_ctx == nullptr)
	{
		img_convert_ctx = sws_getContext(frame->width, frame->height, 
			(AVPixelFormat)frame->format, frame->width, frame->height,
			AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);

		pFrmDst->format = AV_PIX_FMT_YUV420P;
		pFrmDst->width = frame->width;
		pFrmDst->height = frame->height;

		if (av_frame_get_buffer(pFrmDst, 0) < 0)
		{
			return QImage();
		}

	}

	if (img_convert_ctx == nullptr)
	{

		return QImage();
	}

	sws_scale(img_convert_ctx, (const uint8_t *const *)frame->data,
		frame->linesize, 0, frame->height, pFrmDst->data,
		pFrmDst->linesize);

	QImage img(pFrmDst->width, pFrmDst->height, QImage::Format_RGB888);
	for (int y = 0; y < pFrmDst->height; ++y)
	{
		memcpy(img.scanLine(y), pFrmDst->data[0] + y * pFrmDst->linesize[0], pFrmDst->linesize[0]);
	}

	av_freep(&pFrmDst->data[0]);
	return img;
}


QImage *VideoThread::AVFrame2QImage(AVFrame *avframe)
{
	int w = avframe->width;
	int h = avframe->height;
	QImage *image = NULL;
	uchar *buf = new uchar[w*h * 4];
	image = new QImage(buf, w, h, QImage::Format_ARGB32);
	AVPixelFormat pixFormat;
	switch (avframe->format)
	{
	case AV_PIX_FMT_YUVJ420P:
		pixFormat = AV_PIX_FMT_YUV420P;
		break;
	case AV_PIX_FMT_YUVJ422P:
		pixFormat = AV_PIX_FMT_YUV422P;
		break;
	case AV_PIX_FMT_YUVJ444P:
		pixFormat = AV_PIX_FMT_YUV444P;
		break;
	case AV_PIX_FMT_YUVJ440P:
		pixFormat = AV_PIX_FMT_YUV440P;
		break;
	default:
		pixFormat = (AVPixelFormat)avframe->format;
	}

	struct SwsContext *sws_ctx = NULL;
	sws_ctx = sws_getContext(avframe->width, avframe->height, (enum AVPixelFormat)avframe->format,
		w, h, AV_PIX_FMT_BGRA, SWS_BICUBIC, NULL, NULL, NULL);
	if (!sws_ctx)
	{
		return NULL;
	}
	uint8_t *data[AV_NUM_DATA_POINTERS];
	data[0] = (uint8_t *)(char*)image->bits();
	int linesize[AV_NUM_DATA_POINTERS] = { 0 };
	linesize[0] = w * 4;//每一行的宽度
	int hii = sws_scale(sws_ctx, avframe->data, avframe->linesize, 0, avframe->height,
		data,
		linesize
	);
	sws_freeContext(sws_ctx);
	return image;
}

void VideoThread::setEnd()
{
	if (m_PlayWay == MEDIA)
	{
		av_free(buf);
		av_frame_free(&yuv);
		av_frame_free(&fr);
		av_packet_free(&pkt);
		sws_freeContext(imgCtx);

		avcodec_free_context(&cctx);
		avformat_close_input(&fctx);
		avformat_free_context(fctx);
	}
}

void VideoThread::run()
{
	while (isStart)
	{
		if (!m_data)
		{
			return;
		}
		if (m_data->getPlayWay() == CAMERA)
		{
			if (!m_cap)
			{
				return;
			}
			cv::Mat frame;
			m_cap->read(frame);

			QImage img = cvMat2QImage(frame);

			std::cout << "frame size :: " << img.width() << " " << img.height() << std::endl;
			m_data->addCamFrame(img);

			msleep(10);
			emit updateGL();
		}
		else if (m_data->getPlayWay() == MEDIA)
		{

			if (av_read_frame(fctx, pkt) < 0) {
				cout << "read frame failed" << endl;
				break;
			}
			//判断视频流
			if (pkt->stream_index == videoStream) {
				//多次读取帧
				while (avcodec_receive_frame(cctx, fr))
				{
					if (avcodec_send_packet(cctx, pkt) != 0)
					{
						cout << "Send video stream packet failed!" << endl;
						//av_strerror(iRes, errbuf, 256);
						return;
					}
				}
				//进行视频像素格式和分辨率的转换
				//sws_scale(imgCtx, (const unsigned char* const*)fr->data, fr->linesize, 0, cctx->height, yuv->data, yuv->linesize);
				//QImage img = avFrame2QImage(fr);
				//QImage mdiaImage((uchar*)yuv->data[0], cctx->width, cctx->height, QImage::Format_ARGB32);
				//AVFrame转QImage
				//QImage img(fr->width, fr->height, QImage::Format_RGB888);
				//uint8_t* dst[] = { img.bits() };
				//int dstStride[4];
				//av_image_fill_linesizes(dstStride, AV_PIX_FMT_RGB24, fr->width);
				////转换
				//sws_scale(imgCtx, fr->data, (const int*)fr->linesize, 0, cctx->height, dst, dstStride);

				//m_data->addFrame(yuv);

				QImage *img = AVFrame2QImage(fr);
				if (!img)
				{
					continue;
				}

				cout << "push success" << endl;

				m_data->addMediaFrame(img);

				msleep(80);
				emit updateGL();
			}
		}
		else
		{
			continue;
		}

		
	}
}

