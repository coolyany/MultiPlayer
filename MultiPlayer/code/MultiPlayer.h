﻿#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MultiPlayer.h"

#include "MyData.h"
#include "PlayCtrl.h"

#include <QFileDialog>
#include <QTimerEvent>

class MultiPlayer : public QMainWindow {
	Q_OBJECT
public:
	MultiPlayer(QWidget *parent = Q_NULLPTR);
	~MultiPlayer();
//��ʼ������
public:
	void init();//initialize the set
	void SignConnect();//initialize the connect
//槽函数
public:
	void onClickActMedia(QAction *act);
	void slotPlayEnd();
	void slotPlayAndPause();//播放/暂停
	void slotSliderPressed();
	void slotSliderReleased();

//��������
public:
	void playLocalMedia();
	QString Time2Char(long long time) const;
protected:
	void timerEvent(QTimerEvent *event) override;
private:
	MyData *m_data = nullptr;
	MyData::MyMediaWay m_pw;
	QString m_currentPath;
	PlayCtrl *m_pc = nullptr;
	bool m_isPause = false;
	bool isSliderPress = false;
	int seek_value = -1;
	bool m_isPlaying = false;
	//QTimer m_timer;
	int timerID = -1;
private:
	Ui::MultiPlayer ui;
};