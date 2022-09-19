#pragma once
#include <iostream>
#include <QThread>
#include <mutex>
#include "IVideoCall.h"
#include "XVideoThread.h"
#include "XMedia.h"
//class XMedia;


class XMediaThread : public QThread {
	Q_OBJECT
public:
	XMediaThread();
	virtual ~XMediaThread();

public:
	virtual bool Open(const char *url, IVideoCall *call, int type = 0);
	//��������߳�
	virtual void Start();
	//�ر��߳�������Դ
	virtual void Close();
	virtual void Clear();
	virtual void Seek(double pos);

	void run();
	bool isEof();
	void SetPause(bool isPause);
	long long GetPlayPts() const;//获取视频的pts
signals:
	void PlayEnd();

public:
	bool isExit = false;
	long long pts = 0;
	long long totalMs = 0;
	bool isPause = false;

private:
	XMedia *m_media = nullptr;
	XVideoThread *m_vt = nullptr;
	std::mutex mux;
	int m_pt = 0;//播放类型 0 本地文件 1 网络文件
	bool isSeeking = false;
};