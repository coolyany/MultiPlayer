#include "PlayCtrl.h"

PlayCtrl::PlayCtrl()
{
	m_mt = new XMediaThread();

	connect(m_mt, SIGNAL(PlayEnd()), this, SLOT(slotPlayEnd()));

}

PlayCtrl::~PlayCtrl()
{
	if (m_mt)
	{
		delete m_mt;
		m_mt = nullptr;
	}
}

void PlayCtrl::SetMyData(MyData * data)
{
	m_data = data;
}

bool PlayCtrl::OpenMedia(const QString & path, MyData::MyMediaWay way, IVideoCall * call)
{
	m_curType = way;
	m_call = call;
	//�򿪱�����Ƶ
	if (way == MyData::LocalPlay)
	{
		//0表示本地媒体
		if (!m_mt->Open(path.toLocal8Bit(), call, 0))
		{
			return false;
		}
		
		m_mt->Start();
	}

	return true;
}

void PlayCtrl::SetPause(bool isPause)
{
	m_mt->SetPause(isPause);
}

void PlayCtrl::Seek(double pos)
{
	if (m_curType == MyData::LocalPlay)
	{
		m_mt->Seek(pos);
	}
}

void PlayCtrl::Close()
{
	if (m_curType == 0)
	{
		m_mt->Close();
	}
}

long long PlayCtrl::GetTotalMS() const
{
	long long temp = 0;
	if (m_curType == 0)
	{
		temp = m_mt->totalMs;
	}
	return temp;
}

long long PlayCtrl::GetPlayPts() const
{
	long long temp = 0;
	if (m_curType == 0)
	{
		temp = m_mt->GetPlayPts();
	}
	return temp;
}

void PlayCtrl::slotPlayEnd()
{
	emit playEnd();

}
