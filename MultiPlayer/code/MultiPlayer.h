#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MultiPlayer.h"

#include "MyData.h"
#include "PlayCtrl.h"

#include <QFileDialog>

class MultiPlayer : public QMainWindow {
public:
	MultiPlayer(QWidget *parent = Q_NULLPTR);

//��ʼ������
public:
	void init();//initialize the set
	void SignConnect();//initialize the connect
//�ۺ���
public:
	void onClickActMedia(QAction *act);
//��������
public:
	void playLocalMedia();
private:
	MyData *m_data = nullptr;
	MyData::MyMediaWay m_pw;
	QString m_currentPath;
	PlayCtrl *m_pc = nullptr;
private:
	Ui::MultiPlayer ui;
};