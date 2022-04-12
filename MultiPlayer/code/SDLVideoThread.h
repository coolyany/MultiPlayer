#pragma once
#include <QThread>
#include <QQueue>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/highgui.hpp>
#include "Data.h"
#include "pVideo.h"



class SDLVideoThread : public QThread
{
	Q_OBJECT
public:
	SDLVideoThread(Data *data, QObject *parent = NULL);
	~SDLVideoThread();
	void initVideo();
	void initDecode();
	void setEnd(bool re);
	
	QImage cvMat2QImage(const cv::Mat& mat);
protected:
	void run() override;
signals:
	void UpdateSDL();
private:
	Data *m_data = nullptr;
	bool isEnd = false;
	cv::VideoCapture cap;
	cv::Mat curFrame;

	//ffmpeg

	AVFormatContext *fctx = NULL;
	AVCodecContext *cctx = NULL;
	AVCodec *c = NULL;
	AVPacket *pkt = NULL;
	AVFrame *fr = NULL;
	AVFrame *yuv = NULL;
	uint8_t *buf = NULL;
	int vsize;
	int videoStream = -1;
	struct SwsContext *imgCtx = NULL;


	//pVideo* pvideo = NULL;
};