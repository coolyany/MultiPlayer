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
	// �򿪣����ܳɹ��������
	virtual bool Open(AVCodecParameters *para, IVideoCall *call, int width, int height);
	void run();
	void SetPause(bool isPause);
public:
	//ͬ��ʱ�䣬���ⲿ����
	long long synpts = 0;
	long long pts = 0;
	//void SetPause(bool ipause);
	bool isPause = false;
	IVideoCall *call = NULL;
	int mpt = 0;//�������ͣ� 0�����ļ� 1�����ļ�
	bool isHasAudio = false;//�Ƿ�����Ƶ
	long long seekpts = 0;//seekʱ�䣬�ⲿ����
	float playspeed = 1.0;//����
protected:
	std::mutex vmux;
	int timeelapsed = 0;
	int oldtime = 0;
	QTime time;
};


