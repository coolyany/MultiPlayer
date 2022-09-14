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
	//���������߳�
	virtual void Start();
	//�ر��߳�������Դ
	virtual void Close();
	virtual void Clear();
	void run();
	bool isEof();
signals:
	void PlayEnd();

public:
	bool isExit = false;
	long long pts = 0;
	long long totalMs = 0;
private:
	XMedia *m_media = nullptr;
	XVideoThread *m_vt = nullptr;
	std::mutex mux;
};