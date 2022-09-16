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

//��������
public:
	void SetMyData(MyData *data);
	bool OpenMedia(const QString &path, MyData::MyMediaWay way, IVideoCall *call);

	void SetPause(bool isPause);//��ͣ
	void Close();

	long long GetTotalMS() const;//获取总时长
	long long GetPlayPts() const;//获取已播放时长

//�ۺ���
public:
	void slotPlayEnd();//���Ž���
signals:
	void playEnd();
private:
	MyData *m_data = nullptr;
	MyData::MyMediaWay m_curType;
	IVideoCall *m_call = nullptr;
	XMediaThread *m_mt = nullptr;
};