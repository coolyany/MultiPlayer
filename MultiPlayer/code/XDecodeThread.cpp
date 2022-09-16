#include "XDecodeThread.h"
#include <QDebug>
XDecodeThread::XDecodeThread()
{
	//�򿪽�����
	if (!decode)
	{
		decode = new XDecode();
	}
}

XDecodeThread::~XDecodeThread()
{
}

bool XDecodeThread::isPacketsEmpty()
{
	pmux.lock();
	if (packs.empty())
	{
		pmux.unlock();
		return true;
	}
	pmux.unlock();
	return false;
}

AVPacket * XDecodeThread::Pop()
{
	pmux.lock();
	if (packs.empty())
	{
		pmux.unlock();
		return NULL;
	}
	AVPacket *pkt = packs.front();
	packs.pop_front();
	pmux.unlock();
	return pkt;
}

void XDecodeThread::Push(AVPacket * pkt)
{
	if (!pkt) return;
	//����
	while (!isExit)
	{
		qDebug() << "packs_size:" << packs.size();
		if (packs.size() < maxList)
		{
			pmux.lock();
			packs.push_back(pkt);
			pmux.unlock();
			break;
		}
		msleep(1);
	}
}

void XDecodeThread::Clear()
{
	decode->Clear();
	pmux.lock();
	while (!packs.empty())
	{
		AVPacket *pkt = packs.front();
		XFreePacket(&pkt);
		packs.pop_front();
	}
	pmux.unlock();
}

void XDecodeThread::Close()
{
	Clear();
	//�ȴ��߳��˳�
	isExit = true;
	wait();
	decode->Close();
	mux.lock();
	delete decode;
	decode = NULL;
	mux.unlock();
}
