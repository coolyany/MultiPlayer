#pragma once
#include <QObject>

#include "IVideoCall.h"
#include "MyData.h"
//class MyData;

class PlayCtrl :public QObject
{
	Q_OBJECT;
public:
	PlayCtrl();
	~PlayCtrl();

//��������
public:
	void SetMyData(MyData *data);
	bool OpenMedia(const QString &path, MyData::MyMediaWay way, IVideoCall *call);
private:
	MyData *m_data = nullptr;
	MyData::MyMediaWay m_curType;
	IVideoCall *m_call = nullptr;
};