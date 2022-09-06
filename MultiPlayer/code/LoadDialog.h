#pragma once

#include <QDialog>
#include "ui_LoadDialog.h"

class LoadDialog : public QDialog
{
	Q_OBJECT

public:
	LoadDialog(QWidget *parent = Q_NULLPTR);
	~LoadDialog();

	void paintEvent(QPaintEvent *event);
	void timerEvent(QTimerEvent *e);
public slots:
	
private:
	Ui::LoadDialog ui;
	QImage img;
	int num = 0;
};
