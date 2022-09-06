#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MultiPlayer.h"

#include "MyData.h"
#include "PlayCtrl.h"

#include <QFileDialog>

class MultiPlayer : public QMainWindow {
public:
	MultiPlayer(QWidget *parent = Q_NULLPTR);

//初始化函数
public:
	void init();//initialize the set
	void SignConnect();//initialize the connect
//槽函数
public:
	void onClickActMedia(QAction *act);
//方法函数
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