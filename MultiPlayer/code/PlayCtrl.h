#pragma once
#include <QObject>

#include "IVideoCall.h"
#include "MyData.h"
#include "XMediaThread.h"
//class MyData;

class PlayCtrl :public QObject
{
	Q_OBJECT;
public:
	PlayCtrl();
	~PlayCtrl();

//方法函数
public:
	void SetMyData(MyData *data);
	bool OpenMedia(const QString &path, MyData::MyMediaWay way, IVideoCall *call);

	void SetPause(bool isPause);//暂停
//槽函数
public:
	void slotPlayEnd();//播放结束
signals:
	void playEnd();
private:
	MyData *m_data = nullptr;
	MyData::MyMediaWay m_curType;
	IVideoCall *m_call = nullptr;
	XMediaThread *m_mt = nullptr;
};