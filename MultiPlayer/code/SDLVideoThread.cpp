#include "SDLVideoThread.h"
#include <QImage>
#include <QDebug>
using namespace std;
SDLVideoThread::SDLVideoThread(Data *data, QObject *parent)
	:m_data(data)
{
	
}



QImage SDLVideoThread::cvMat2QImage(const cv::Mat & mat)
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

SDLVideoThread::~SDLVideoThread()
{

}

static double r2d(AVRational r)
{
	return r.num == 0 || r.den == 0 ? 0. : (double)r.num / (double)r.den;
}

void SDLVideoThread::initVideo()
{
	if (m_data->getPlayWay() == CAMERA)
	{
		cap.open(0);
		cap.set(cv::CAP_PROP_FRAME_WIDTH, m_data->m_width);
		cap.set(cv::CAP_PROP_FRAME_HEIGHT, m_data->m_height);
	}
	else if (m_data->getPlayWay() == MEDIA) 
	{
		//封装格式上下文
		ic = avformat_alloc_context();

		//参数设置
		AVDictionary *opts = NULL;
		//设置rtsp流以tcp协议打开
		av_dict_set(&opts, "rtsp_transport", "tcp", 0);

		//网络延迟时间
		av_dict_set(&opts, "max_delay", "500000", 0);
		//av_dict_set(&opts, "stimeout", "3000000", 0);  //设置超时断开连接时间
		//av_dict_set(&opts, "timeout", "3000000", 0);  //设置超时断开连接时间

		av_dict_set(&opts, "max_delay", "5000000", 0);
		av_dict_set(&opts, "buffer_size", "10240000", 0);

		av_dict_set(&opts, "protocol_whitelist", "file,tcp,udp,rtp", 0);

		if (avformat_open_input(&ic, path.toLocal8Bit(), 0, &opts) != 0)
		{
			qDebug() << "can not open video";
			avformat_close_input(&ic);
			return;
		}
		//获取流信息
		if (avformat_find_stream_info(ic, 0) != 0)
		{
			qDebug() << "can not get video stream info";

			return;
		}
		qDebug() << "msc ::" << ic->duration / (AV_TIME_BASE / 1000);

		//打印视频流详细信息
		av_dump_format(ic, 0, path.toLocal8Bit(), 0);

		//获取视频流
		videoStream = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
		AVStream *as = ic->streams[videoStream];

		cout << "===================================================" << endl;
		cout << "codec_id = " << as->codecpar->codec_id << endl;
		cout << "format = " << as->codecpar->format << endl;
		cout << videoStream << "视频信息" << endl;
		cout << "width = " << as->codecpar->width << endl;
		cout << "height = " << as->codecpar->height << endl;
		//帧率 fps 分数转换
		cout << "video fps = " << r2d(as->avg_frame_rate) << endl;

		//分配内存
		AVCodecParameters *param = avcodec_parameters_alloc();
		avcodec_parameters_copy(param, ic->streams[videoStream]->codecpar);

		//找到解码器
		AVCodec *vcodec = avcodec_find_decoder(param->codec_id);
		if (!vcodec)
		{
			avcodec_parameters_free(&param);
			cout << "can't find the codec id " << param->codec_id << endl;
			return;
		}
		cout << "find the AVCodec " << param->codec_id << endl;

		//申请AVCodecContext空间。需要传递一个编码器，也可以不传，但不会包含编码器。
		codec = avcodec_alloc_context3(vcodec);
		//该函数用于将流里面的参数，也就是AVStream里面的参数直接复制到AVCodecContext的上下文当中。
		avcodec_parameters_to_context(codec, param);
		avcodec_parameters_free(&param);
		//八线程解码器
		codec->thread_count = 8;

		//打开解码器上下文
		int re = avcodec_open2(codec, vcodec, 0);
		if (re != 0)
		{
			avcodec_free_context(&codec);
			char buf[1024] = { 0 };
			av_strerror(re, buf, sizeof(buf) - 1);
			cout << "avcodec_open2 failed! :" << buf << endl;
			return;
		}
		cout << " avcodec_open2 success!" << endl;
		//decodeStream();//解码
	}
}

void SDLVideoThread::setEnd(bool re)
{
	if (re)
	{
		isEnd = true;
		if (m_data->getPlayWay() == CAMERA)
		{
			cap.release();
		}
		
	}
	
}

void SDLVideoThread::run()
{
	initVideo();
	while (!isEnd) {
		if (m_data->getPlayWay() == CAMERA)
		{
			//std::cout << "111111111111111" << std::endl;
			if (!cap.isOpened())
			{
				return;
			}
			curFrame.release();
			cap >> curFrame;
			m_data->addFrame(curFrame);
			//cv::waitKey(30);
			emit UpdateSDL();
		}

		//QThread::sleep(10);
	}
}
