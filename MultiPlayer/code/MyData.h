#pragma once
#include <iostream>

extern "C"
{
#include <libavutil/frame.h>
#include <libavformat/avformat.h>
}
#pragma comment(lib,"avcodec.lib")

class MyData {
public:
	enum MyMediaWay {
		LocalPlay,
		CamPlay,
		NetPlay,
	};
	void PushSaveFrame(AVFrame *frame);


	int vW = 0;//当前视频的宽
	int vH = 0;//当前视频的高
private:


};