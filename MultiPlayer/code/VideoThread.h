#pragma once
#include <iostream>
#include <QThread>
#include <QImage>
#include "Data.h"

using namespace std;

class VideoThread : public QThread
{
	Q_OBJECT
public:
	VideoThread(Data *data = nullptr, QObject* parent = nullptr);

	inline void setStart(bool start) {
		isStart = start;
	}
	inline void setPlayWay(PLAYWAY way) { m_PlayWay = way; }
	void Start();
	void Stop();
	void setVideoCapture(cv::VideoCapture *cap);
	void openMedia(QString &filePath);
	QImage cvMat2QImage(const cv::Mat& mat);
	QImage avFrame2QImage(AVFrame *frame);
	QImage *AVFrame2QImage(AVFrame *avframe);

public:
	void initDecode(QString &filePath);
	void setEnd();
signals:
	void updateGL();
protected:
	virtual void run() override;
private:
	bool isStart = false;
	PLAYWAY m_PlayWay = NONE;
	Data* m_data = nullptr;
	cv::VideoCapture  *m_cap = nullptr;

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

	AVFrame *pFrmDst = nullptr;
	struct SwsContext *img_convert_ctx = nullptr;

	QString m_mediaPath;
};