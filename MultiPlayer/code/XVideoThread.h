#pragma once
#include <iostream>
#include <mutex>
#include <QThread>
#include "IVideoCall.h"
#include "XDecodeThread.h"
#include <QTime>

class XVideoThread : public XDecodeThread
{
public:
	XVideoThread();
	~XVideoThread();

public:
	//打开，不管成功与否都清理
	virtual bool Open(AVCodecParameters *para, IVideoCall *call, int width, int height);
	void run();
	void SetPause(bool isPause);
public:
	//同步时间，由外部传入
	long long synpts = 0;
	long long pts = 0;
	bool isPause = false;
	IVideoCall *call = NULL;
	int mpt = 0;//播放类型， 0本地文件 1网络文件
	bool isHasAudio = false;//是否有音频
	long long seekpts = 0;//seek时间，外部传入
	float playspeed = 1.0;//倍率
protected:
	std::mutex vmux;
	int timeelapsed = 0;
	int oldtime = 0;
	QTime time;
};


