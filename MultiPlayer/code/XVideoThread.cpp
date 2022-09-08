#include "XVideoThread.h"
extern "C"
{
#include <libavcodec/avcodec.h>
}

#include <iostream>
#include <QDebug>
using namespace std;

XVideoThread::XVideoThread()
{
}

XVideoThread::~XVideoThread()
{
}

bool XVideoThread::Open(AVCodecParameters * para, IVideoCall * call, int width, int height)
{
	if (!para)
	{
		return false;
	}
	Clear();
	synpts = 0;
	//初始化显示窗口
	this->call = call;
	vmux.unlock();

	if (!decode->Open(para))
	{
		cout << "video XDecode open failed!" << endl;
		return false;
	}
	cout << "XVideoThread::Open succend " << endl;
	return true;
}

void XVideoThread::run()
{
	while (!isExit)
	{
		/*if (this->isPause)
		{
			msleep(5);
			continue;
		}*/
		QTime t0 = QTime::currentTime(), t1;
		if (mpt == 0)
		{
			//音视频同步
			if (isHasAudio)
			{
				if (synpts > 0 && synpts < decode->pts)
				{
					msleep(5);
					continue;
				}
			}
		}
		AVPacket *pkt = Pop();
		bool re = decode->Send(pkt);
		if (!re)
		{
			msleep(1);
			continue;
		}
		//一次send 多次recv
		while (!isExit)
		{
			AVFrame *frame = decode->Recv();
			if (!frame)
			{
				break;
			}
			if (frame->pts < seekpts)
			{
				av_frame_free(&frame);
				continue;
			}
			else
			{
				seekpts = -1;
			}
			//显示视频
			if (call)
			{
				pts = decode->pts;
				call->Repaint(frame);
			}
		}
		if (mpt == 0)
		{
			if (seekpts != -1)
			{
				msleep(1);
				continue;
			}
			t1 = QTime::currentTime();
			int val = t0.msecsTo(t1);
			int temp = 40 - val;
			if (temp < 0)
			{
				msleep(1);
			}
			else
			{
				msleep(temp * playspeed);
			}
		}
		else
		{
			msleep(1);
		}

	}
}

