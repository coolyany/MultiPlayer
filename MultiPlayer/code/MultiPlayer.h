#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MultiPlayer.h"

#include "MyData.h"
#include "PlayCtrl.h"

#include <QFileDialog>

class MultiPlayer : public QMainWindow {
	Q_OBJECT
public:
	MultiPlayer(QWidget *parent = Q_NULLPTR);
	~MultiPlayer();
//初始化函数
public:
	void init();//initialize the set
	void SignConnect();//initialize the connect
//槽函数
public:
	void onClickActMedia(QAction *act);
	void slotPlayEnd();
	void slotPlayAndPause();//暂停和播放
//方法函数
public:
	void playLocalMedia();
private:
	MyData *m_data = nullptr;
	MyData::MyMediaWay m_pw;
	QString m_currentPath;
	PlayCtrl *m_pc = nullptr;
	bool m_isPause = false;
private:
	Ui::MultiPlayer ui;
};