#include "SDLVideo.h"
#include <QDebug>

using namespace std;

static double r2d(AVRational r)
{
	return r.num == 0 || r.den == 0 ? 0. : (double)r.num / (double)r.den;
}


SDLVideo::SDLVideo(const void* wid, const int winW, const int winH)
	:m_wid(wid),
	 m_winW(winW),
	 m_winH(winH)
{	
	connect(this, &QThread::finished, this, &SDLVideo::threadQuit);
}

SDLVideo::~SDLVideo()
{
	endPlay();
}

void SDLVideo::setPlayWay(PLAYWAY way)
{
	
}

bool SDLVideo::openVideo(const QString & path)
{
	m_playway = MEDIA;
	if (!openCodec(path)) {
		cout << "open codec failed " << endl;
		return false;
	}
	if (!initSDL()){
		cout << "init SDL failed" << endl;
		return false;
	}

	//alloc memory
	pkt = av_packet_alloc();
	frame = av_frame_alloc();
	yuv = av_frame_alloc();
	vsize = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, cctx->width, cctx->height, 1);
	buf = (uint8_t *)av_malloc(vsize);
	av_image_fill_arrays(yuv->data, yuv->linesize, buf, AV_PIX_FMT_YUV420P, cctx->width, cctx->height, 1);

	this->start();
	return true;
	
}

void SDLVideo::startPlay()
{
	
}

void SDLVideo::endPlay()
{
	if (this->isRunning())
	{
		isEnd = true;
		this->quit();
		this->wait();
	}	
}

void SDLVideo::threadQuit()
{
	if (m_playway == MEDIA)
	{
		if (buf)
		{
			av_free(buf);
		}
		if (yuv)
		{
			av_frame_free(&yuv);
		}
		if (frame)
		{
			av_frame_free(&frame);
		}
		if (pkt)
		{
			av_packet_free(&pkt);
		}
		if (imgCtx)
		{
			sws_freeContext(imgCtx);
		}
		if (cctx)
		{
			avcodec_free_context(&cctx);
		}
		if (fctx)
		{
			avformat_close_input(&fctx);
			avformat_free_context(fctx);
		}

	}
	if (bitmapTex)
	{
		SDL_DestroyTexture(bitmapTex);
	}
	if (render)
	{
		SDL_DestroyRenderer(render);
	}
	if (screen)
	{
		SDL_DestroyWindow(screen);
	}
	SDL_Quit();
}

void SDLVideo::updateSDLVideo()
{
	static int i = 0;
	std::cout << "frame :: " << i++ << std::endl;
	if (m_playway == MEDIA)
	{
		if (!bitmapTex || !frame)
		{
			cout << "11" << endl;
		}
		int re = SDL_UpdateTexture(bitmapTex, &srect, yuv->data[0], yuv->linesize[0]);
		if (!re)
		{
			cout << "re " << re << endl;
		}
		SDL_RenderClear(render);

		SDL_RenderCopy(render, bitmapTex, NULL, &srect);
		SDL_RenderPresent(render);
	}
}

bool SDLVideo::initSDL()
{
	if (m_playway == MEDIA)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			std::cout << "SDL_Init failed" << std::endl;
			return false;
		}
		if (!cctx)
		{
			return false;
		}
		screen = SDL_CreateWindowFrom(m_wid);
		render = SDL_CreateRenderer(screen, -1, 0);
		bitmapTex = SDL_CreateTexture(render, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, cctx->width, cctx->height);
		if (!screen || !render || !bitmapTex) {
			cout << "Create SDL windows failed!" << endl;
			return false;
		}
		srect.w = cctx->width;
		srect.h = cctx->height;
		return true;
	}
	
	/*screen = SDL_CreateWindowFrom(m_wid);
	if (!screen)
	{
		std::cout << "DL_CreateWindowFrom failed" << std::endl;
		return;
	}*/
	//render = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);//渲染器使用硬件加速
	//if (!render)
	//{
	//	std::cout << "SDL_CreateRenderer failed" << std::endl;
	//	return;
	//}
	//bitmapTex = SDL_CreateTexture(
	//	render, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, m_winW,
	//	m_winH);
	//if (!bitmapTex) {
	//	SDL_LogError(1, "SDL: SDL_CreateTexture failed.");
	//	return;
	//}
}

QImage SDLVideo::cvMat2QImage(const cv::Mat & mat)
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

bool SDLVideo::openCodec(const QString &path)
{
	/* alloc AvFormatContext memory */
	fctx = avformat_alloc_context();
	if (!fctx)
	{
		cout << "fctx is nullptr" << endl;
		return false;
	}
	if (avformat_open_input(&fctx, path.toLocal8Bit(), NULL, NULL) != 0)
	{
		cout << "File open failed!" << endl;
		return false;
	}
	if (avformat_find_stream_info(fctx, NULL) < 0)
	{
		cout << "Stream find failed!\n";
		return false;
	}
	av_dump_format(fctx, -1, path.toLocal8Bit(), NULL);

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
		return false;
	}
	cctx = avcodec_alloc_context3(NULL);
	if (avcodec_parameters_to_context(cctx, fctx->streams[videoStream]->codecpar) < 0)
	{
		cout << "Copy stream failed!" << endl;
		return false;
	}
	codec = avcodec_find_decoder(cctx->codec_id);
	if (!codec) {
		cout << "Find Decoder failed!" << endl;
		return false;
	}
	if (avcodec_open2(cctx, codec, NULL) != 0) {
		cout << "Open codec failed!" << endl;
		return false;
	}
	cout << " avcodec_open2 success!" << endl;
	return true;
}

void SDLVideo::run()
{
	while (!isEnd) {
		mutex.lock();
		if (m_playway == MEDIA)
		{
			if (av_read_frame(fctx, pkt) < 0) {
				cout << "read frame failed" << endl;
				break;
			}
			//判断视频流
			if (pkt->stream_index == videoStream) {
				//多次读取帧
				while (avcodec_receive_frame(cctx, frame))
				{
					if (avcodec_send_packet(cctx, pkt) != 0)
					{
						cout << "Send video stream packet failed!" << endl;
						//av_strerror(iRes, errbuf, 256);
						return;
					}
				}
				imgCtx = sws_getContext(cctx->width, cctx->height, cctx->pix_fmt, cctx->width, cctx->height, AV_PIX_FMT_YUV420P,
					SWS_BICUBIC, NULL, NULL, NULL);
				if (!imgCtx) {
					cout << "Get swscale context failed!" << endl;
					continue;
				}
				sws_scale(imgCtx, frame->data, frame->linesize, 0, cctx->height, yuv->data, yuv->linesize);
				sws_freeContext(imgCtx);
				updateSDLVideo();
			}
		}
		//QThread::sleep(10);
		_sleep(15);
		mutex.unlock();
	}
}
