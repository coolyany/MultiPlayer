#pragma once
#include <list>
#include <mutex>
#include <QThread>
#include "XDecode.h"

//class XDecode;

class XDecodeThread : public QThread
{
public:
	XDecodeThread();
	virtual ~XDecodeThread();
	virtual bool isPacketsEmpty();
	//取出一帧数据，并出栈,如果没有则返回NULL
	virtual AVPacket *Pop();
	virtual void Push(AVPacket *pkt);

	//清理队列
	virtual void Clear();
	//清理资源，停止线程
	virtual void Close();

	XDecode *decode = nullptr;
	//最大队列
	int maxList = 1000;
	bool isExit = false;
protected:
	std::list <AVPacket *> packs;
	std::mutex mux;
	std::mutex pmux;

};
