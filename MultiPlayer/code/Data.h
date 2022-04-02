#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/highgui.hpp>

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

	void addFrame(cv::Mat frame);//缓存帧
	cv::Mat popFrame();//取帧

	int m_width, m_height;
private:
	PLAYWAY m_playway = NONE;

	QQueue<cv::Mat>vidFrame;
};