#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/highgui.hpp>
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libswresample/swresample.h>
}

#include <QQueue>


enum PLAYWAY
{
	NONE,
	CAMERA,
	MEDIA,
	STREAM
};

class Data {
public:
	Data(int width,int height);
	~Data();
	inline void setVideoWH(int width, int height) { m_width = width; m_height = height; }
	inline PLAYWAY getPlayWay() { return m_playway; }
	inline void setPlayWay(PLAYWAY way) { m_playway = way; }

	void addFrame(AVFrame* frame);//缓存帧
	AVFrame* popFrame();//取帧

	void setMediaPath(const QString &path);
	inline QString &getMediaPath() { return mediaPath; }

	int m_width, m_height;

	void setAVCodecContext(AVCodecContext *ic);

	AVCodecContext* m_ic = nullptr;
	int videoStream = -1;
private:
	PLAYWAY m_playway = NONE;

	QQueue<AVFrame*>vidFrame;
	QString mediaPath;
};