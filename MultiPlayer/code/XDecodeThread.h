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
	//ȡ��һ֡���ݣ�����ջ,���û���򷵻�NULL
	virtual AVPacket *Pop();
	virtual void Push(AVPacket *pkt);

	//�������
	virtual void Clear();
	//������Դ��ֹͣ�߳�
	virtual void Close();

	XDecode *decode = nullptr;
	//������
	int maxList = 1000;
	bool isExit = false;
protected:
	std::list <AVPacket *> packs;
	std::mutex mux;
	std::mutex pmux;

};
