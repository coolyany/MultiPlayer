#include "XMediaThread.h"

using namespace std;

XMediaThread::XMediaThread()
{

}

XMediaThread::~XMediaThread()
{
	isExit = true;
	wait();
}

bool XMediaThread::Open(const char * url, IVideoCall * call, int type)
{
	if (url == nullptr || *url == '\0')
		return false;
	if (!m_media) m_media = new XMedia();
	if (!m_vt) m_vt = new XVideoThread();

	bool re = m_media->Open(url);
	if (!re)
	{
		delete m_vt;
		//delete at;
		m_vt = NULL;
		//at = NULL;
		cout << "demux->Open(url) failed!" << endl;
		return false;
	}

	//打开视频解码器和处理线程
	re = m_vt->Open(m_media->CopyVPara(), call, m_media->width, m_media->height);
	if (!re)
	{
		re = false;
		cout << "vt->Open failed!" << endl;
	}


	isExit = false;
	return re;
}

void XMediaThread::Start()
{
	mux.lock();
	if (!m_media) m_media = new XMedia();
	if (!m_vt) m_vt = new XVideoThread();
	//if (!at) at = new XAudioThread();
	//启动当前线程
	QThread::start();
	//启动视频解码线程
	if (m_vt) m_vt->start();
	//if (at) at->start();
	mux.unlock();
}

void XMediaThread::Close()
{
	isExit = true;
	wait();
	if (m_vt) m_vt->Close();
	mux.lock();
	delete m_vt;
	//delete at;
	m_vt = NULL;
	//at = NULL;
	mux.unlock();
}

void XMediaThread::Clear()
{
	mux.lock();
	if (m_media)
	{
		m_media->Clear();
	}
	/*if (at)
	{
		at->Clear();
	}*/
	if (m_vt)
	{
		m_vt->Clear();
	}
	mux.unlock();
}

void XMediaThread::run()
{
	while (!isExit)
	{
		
		/*if (isPause)
		{
			msleep(5);
			continue;
		}*/
		if (!m_media)
		{
			msleep(5);
			continue;
		}
		//音视频同步
		/*if (m_pt == 0)
		{
			if (vt && at)
			{
				pts = at->pts;
				vt->synpts = at->pts;
			}
		}*/

		AVPacket *pkt = m_media->Read();
		if (!pkt)
		{
			if (isEof())
			{
				//isExit = true;
				emit PlayEnd();
				//重头开始播放
				//Seek(0.0);
			}
			msleep(5);
			continue;
		}
		//判断数据为音频
		//if (m_media->isAudio(pkt))
		//{
		//	if (at)	at->Push(pkt);
		//}
		//else //视频
		//{
			if (m_vt)	m_vt->Push(pkt);
			/*if (demux->isRecord)
			{
				demux->SavePackData(pkt);
			}*/
		//}
		//qDebug() << "1";
		msleep(1);
	}
}

bool XMediaThread::isEof()
{
	if (m_media->isEof && /*at->isPacketsEmpty() &&*/ m_vt->isPacketsEmpty())
	{
		return true;
		//emit PlayEnd();
	}
	else
	{
		return false;
	}
}
