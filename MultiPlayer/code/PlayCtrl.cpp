#include "PlayCtrl.h"

PlayCtrl::PlayCtrl()
{
}

PlayCtrl::~PlayCtrl()
{
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

	}
}
