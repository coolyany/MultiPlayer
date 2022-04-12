#pragma once
#include "Data.h"
#include <QThread>

class DecodeThread : public QThread
{
public:
	DecodeThread(Data* data);
	~DecodeThread();
	
	void initDecode();

protected:
	void run() override;
private:
	QString m_path;
	Data* m_data = nullptr;

	AVFormatContext *fctx = NULL;
	AVCodecContext *cctx = NULL;
	AVCodec *c = NULL;
	AVPacket *pkt = NULL;
	AVFrame *fr = NULL;
	AVFrame *yuv = NULL;
	int videoStream = -1;
};