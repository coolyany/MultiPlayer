#include "MyConvert.h"

extern "C" {
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavutil/samplefmt.h>
#include <libavcodec/avcodec.h>
}
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "avcodec.lib") 
#pragma comment(lib, "swscale.lib") 

MyConvert::MyConvert()
{

}
MyConvert::~MyConvert()
{
}

QImage *MyConvert::AVFrame2QImage(AVFrame *avframe)
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
	linesize[0] = w * 4;//ÿһ�еĿ��
	int hii = sws_scale(sws_ctx, avframe->data, avframe->linesize, 0, avframe->height,
		data,
		linesize
	);
	sws_freeContext(sws_ctx);
	return image;
}
cv::Mat MyConvert::AVFrameTocvMat(AVFrame *avframe)
{
	int w = avframe->width;
	int h = avframe->height;
	struct SwsContext *sws_ctx = NULL;
	sws_ctx = sws_getContext(avframe->width, avframe->height, (enum AVPixelFormat)avframe->format,
		w, h, AV_PIX_FMT_BGR24, SWS_BICUBIC, NULL, NULL, NULL);

	cv::Mat mat;
	mat.create(cv::Size(w, h), CV_8UC3);
	AVFrame *bgr24frame = av_frame_alloc();
	bgr24frame->data[0] = (uint8_t *)mat.data;
	avpicture_fill((AVPicture *)bgr24frame, bgr24frame->data[0], AV_PIX_FMT_BGR24, w, h);
	sws_scale(sws_ctx,
		(const uint8_t* const*)avframe->data, avframe->linesize,
		0, avframe->height, // from cols=0,all rows trans
		bgr24frame->data, bgr24frame->linesize);

	av_free(bgr24frame);
	sws_freeContext(sws_ctx);
	return mat;
}
QImage MyConvert::cvMat2QImage(const cv::Mat& mat)
{
	if (mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		uchar *pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	else if (mat.type() == CV_8UC3)
	{
		const uchar * pSrc = (const uchar*)mat.data;
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		const uchar * pSrc = (const uchar*)mat.data;
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB32);
		return image.copy();
	}
	else
	{
		return QImage();
	}
}
AVFrame *MyConvert::cvMatToAVFrame(cv::Mat &mat)
{
	AVFrame *avframe = av_frame_alloc();
	if (avframe && !mat.empty()) {
		avframe->format = AV_PIX_FMT_YUV420P;
		avframe->width = mat.cols;
		avframe->height = mat.rows;
		av_frame_get_buffer(avframe, 0);
		int width = mat.cols;
		int height = mat.rows;
		int cvLinesizes[1];
		cvLinesizes[0] = mat.step1();
		SwsContext* conversion = sws_getContext(width, height, AVPixelFormat::AV_PIX_FMT_BGR24, width, height, (AVPixelFormat)avframe->format, SWS_FAST_BILINEAR, NULL, NULL, NULL);
		sws_scale(conversion, &mat.data, cvLinesizes, 0, height, avframe->data, avframe->linesize);
		sws_freeContext(conversion);
		return avframe;
	}
	else
	{
		return NULL;
	}
}

AVFrame *MyConvert::YUV420_To_AVFrame(unsigned char* pYUV420, int width, int height)
{
	if (!pYUV420)
		return NULL;
	//AVFrame *avframe = av_frame_alloc();
	//if (avframe) {
	//	avframe->format = AV_PIX_FMT_YUV420P;
	//	avframe->width = width;
	//	avframe->height = height;
	//	av_frame_get_buffer(avframe, 0);
	//	int cvLinesizes[1];
	//	cvLinesizes[0] = width;
	//	int temp = (AVPixelFormat)avframe->format;
	//	//SwsContext* conversion = sws_getContext(width, height, AVPixelFormat::AV_PIX_FMT_BGR24, width, height, (AVPixelFormat)avframe->format, SWS_FAST_BILINEAR, NULL, NULL, NULL);
	//	SwsContext* conversion = sws_getContext(width, height, AVPixelFormat::AV_PIX_FMT_GRAY8, width, height, (AVPixelFormat)avframe->format, SWS_FAST_BILINEAR, NULL, NULL, NULL);
	//	//SwsContext* conversion = sws_getContext(width, height, AVPixelFormat::AV_PIX_FMT_YUV420P, width, height, (AVPixelFormat)avframe->format, SWS_BICUBIC, NULL, NULL, NULL);
	//	//SwsContext* conversion = sws_getContext(width, height, AVPixelFormat::AV_PIX_FMT_NV12, width, height, (AVPixelFormat)avframe->format, SWS_FAST_BILINEAR, NULL, NULL, NULL);
	//	
	//	sws_scale(conversion, (uint8_t **) & (pYUV420), cvLinesizes, 0, height, avframe->data, avframe->linesize);
	//	sws_freeContext(conversion);
	//	return avframe;
	//}
	//else
	//{
	//	return NULL;
	//}

	//��ʼ��AVFrame
	AVFrame *frame = av_frame_alloc();
	frame->width = width;
	frame->height = height;
	frame->format = AV_PIX_FMT_YUV420P;
	//��ʼ��frame-> linesize
	//avpicture_fill((AVPicture *)frame��NULL��frame->format��frame->width��frame->height);

	//�ֶ�����frame-> dataָ��
	//frame->data[0] = inputBufferY;
	//frame->data[1] = inputBufferU;
	//frame->data[2] = inputBufferV;

	//���ߣ��������Y��U��V�������������Ĳ��Ҿ�����ȷ�Ĵ�С����ֻ��ʹ�ã�
	//avpicture_fill����AVPicture *��frame��inputBufferYUV��frame-> format��frame-> width��frame-> height��;
	avpicture_fill((AVPicture *)frame, pYUV420, (AVPixelFormat)frame->format, frame->width, frame->height);
	return frame;
	////���Ҫ/��Ҫ�����������ݵĸ���������Ҫ��������Ļ�������С��Ȼ�������и����������ݡ�
	////��ʼ��AVFrame
	//AVFrame *��� = avcodec_alloc_frame����;
	//frame->width = width;
	//���->�߶� = �߶�;
	//frame->format = AV_PIX_FMT_YUV420P;

	////�����㹻��Ļ�������������������
	//int size = avpicture_get_size��frame->format��frame->width��frame->height��;
	//uint8_t *������ = ��uint8_t * ��av_malloc����С��;

	////��ʼ��frame-> linesize��frame-> dataָ��
	//avpicture_fill����AVPicture *��frame��buffer��frame->format��frame->width��frame->height��; ���ƴ���

	//	//��3�����뻺������������
	//	memcpy��frame->data[0]��inputBufferY��frame->linesize[0] * frame->height��;
	//memcpy��frame->data[1]��inputBufferU��frame->linesize[1] * frame->height / 2��;
	//memcpy��frame->data[2]��inputBufferV��frame->linesize[2] * frame->height / 2��;
}

IplImage *MyConvert::AVFrameToIplImage(AVFrame *frame)
{
	if (frame == NULL)
		return NULL;
	IplImage* image = cvCreateImage(cvSize(frame->width, frame->height), IPL_DEPTH_8U, 3);
	AVPixelFormat pixFormat;
	switch (frame->format)
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
		pixFormat = (AVPixelFormat)frame->format;
	}
	struct SwsContext *cCtx = NULL;
	cCtx = sws_getCachedContext(cCtx, frame->width,
		frame->height,
		pixFormat,
		image->width, image->height,
		AV_PIX_FMT_BGR24,
		SWS_BICUBIC,
		NULL, NULL, NULL
	);
	if (!cCtx)
	{
		printf("sws_getCachedContext failed\n");
		cvReleaseImage(&image);
		return NULL;
	}
	int linesize[4] = { image->widthStep, 0, 0, 0 };

	sws_scale(cCtx, frame->data, frame->linesize, 0, frame->height,
		(uint8_t **) & (image->imageData), linesize);
	sws_freeContext(cCtx);
	return image;
}
AVFrame *MyConvert::cvIplImageToAVFrame(IplImage *img)
{
	AVFrame *avframe = av_frame_alloc();
	if (avframe && img != NULL) {
		avframe->format = AV_PIX_FMT_YUV420P;
		avframe->width = img->width;
		avframe->height = img->height;
		av_frame_get_buffer(avframe, 0);
		int width = img->width;
		int height = img->height;
		int cvLinesizes[1];
		cvLinesizes[0] = img->widthStep;
		SwsContext* conversion = sws_getContext(width, height, AVPixelFormat::AV_PIX_FMT_BGR24, width, height, (AVPixelFormat)avframe->format, SWS_FAST_BILINEAR, NULL, NULL, NULL);
		sws_scale(conversion, (uint8_t **) & (img->imageData), cvLinesizes, 0, height, avframe->data, avframe->linesize);
		sws_freeContext(conversion);
		return avframe;
	}
	else
	{
		return NULL;
	}
}

/* NV12<--->YUV420P
 * NV12----->yyyyyyyy uvuv
 * YUV420P----->yyyyyyyy uu vv
 */

AVFrame *MyConvert::nv12_to_yuv420p(AVFrame *nv12_frame)
{
	int x, y;
	//1. yuv420p frame alloc
	AVFrame *frame = av_frame_alloc();
	if (!frame)
		return NULL;
	//2. must be set
	frame->format = AV_PIX_FMT_YUV420P;
	frame->width = nv12_frame->width;
	frame->height = nv12_frame->height;

	//2. 32Ϊ�ڴ������Ҫ���ͼ�����ڴ�洢��ʽ�йأ�Ŀǰһ���Ϊ32
	//alloc frame->data memory
	int ret = av_frame_get_buffer(frame, 32);
	if (ret < 0)
		return NULL;

	//3. make sure the frame data is writable
	ret = av_frame_make_writable(frame);
	if (ret < 0)
		return NULL;
	//4. copy data
	//y
	if (nv12_frame->linesize[0] == nv12_frame->width)
	{
		memcpy(frame->data[0], nv12_frame->data[0], nv12_frame->height*nv12_frame->linesize[0]);
	}
	else
	{
		for (y = 0; y < frame->height; y++)
		{
			for (x = 0; x < frame->width; x++)
			{
				frame->data[0][y*frame->linesize[0] + x] = nv12_frame->data[0][y*nv12_frame->linesize[0] + x];
			}
		}
	}
	//cb and cr
	for (y = 0; y < frame->height / 2; y++)
	{
		for (x = 0; x < frame->width / 2; x++)
		{
			frame->data[1][y * frame->linesize[1] + x] = nv12_frame->data[1][y*nv12_frame->linesize[1] + 2 * x];
			frame->data[2][y * frame->linesize[2] + x] = nv12_frame->data[1][y*nv12_frame->linesize[1] + 2 * x + 1];
		}
	}
	return frame;
}
AVFrame *MyConvert::yuv420p_to_nv12(AVFrame *yuv420p_frame)
{
	int x, y;
	//1. yuv420p frame alloc
	AVFrame *frame = av_frame_alloc();
	if (!frame)
		return NULL;
	//2. must be set
	frame->format = AV_PIX_FMT_NV12;
	frame->width = yuv420p_frame->width;
	frame->height = yuv420p_frame->height;

	//2. 32Ϊ�ڴ������Ҫ���ͼ�����ڴ�洢��ʽ�йأ�Ŀǰһ���Ϊ32
	//alloc frame->data memory
	int ret = av_frame_get_buffer(frame, 32);
	if (ret < 0)
		return NULL;

	//3. make sure the frame data is writable
	ret = av_frame_make_writable(frame);
	if (ret < 0)
		return NULL;

	//4. copy data
	//y
	if (yuv420p_frame->linesize[0] == yuv420p_frame->width)
	{
		memcpy(frame->data[0], yuv420p_frame->data[0], yuv420p_frame->height*yuv420p_frame->linesize[0]);
	}
	else
	{
		for (y = 0; y < frame->height; y++)
		{
			for (x = 0; x < frame->width; x++)
			{
				frame->data[0][y*frame->linesize[0] + x] = yuv420p_frame->data[0][y*yuv420p_frame->linesize[0] + x];
			}
		}
	}
	//cb and cr
	for (y = 0; y < frame->height / 2; y++)
	{
		for (x = 0; x < frame->width / 2; x++)
		{
			frame->data[1][y * frame->linesize[1] + 2 * x] = yuv420p_frame->data[1][y*yuv420p_frame->linesize[1] + x];
			frame->data[1][y * frame->linesize[1] + 2 * x + 1] = yuv420p_frame->data[2][y*yuv420p_frame->linesize[2] + x];
		}
	}
	return frame;
}