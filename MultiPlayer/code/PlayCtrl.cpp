#include "PlayCtrl.h"

PlayCtrl::PlayCtrl()
{
	m_mt = new XMediaThread();

	connect(m_mt, SIGNAL(PlayEnd()), this, SLOT(slotPlayEnd()));

}

PlayCtrl::~PlayCtrl()
{
	/*if (m_mt)
	{
		delete m_mt;
		m_mt = nullptr;
	}*/
}

void PlayCtrl::SetMyData(MyData * data)
{
	m_data = data;
}

bool PlayCtrl::OpenMedia(const QString & path, MyData::MyMediaWay way, IVideoCall * call)
{
	m_curType = way;
	m_call = call;
	//打开本地视频
	if (way == MyData::LocalPlay)
	{
		if (!m_mt->Open(path.toLocal8Bit(), call, way))
		{
			return false;
		}
		
		m_mt->Start();
	}
}

void PlayCtrl::SetPause(bool isPause)
{
	m_mt->SetPause(isPause);
}

void PlayCtrl::slotPlayEnd()
{
	emit playEnd();

}
