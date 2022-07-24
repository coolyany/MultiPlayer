#pragma once
#include "ui_CameraDialog.h"
#include <QDialog>
#include <QCameraInfo>

class CameraDialog : public QDialog
{
	Q_OBJECT

public:
	CameraDialog(QWidget* parent = nullptr);

	void initCameraDev();

signals:
	void acceptSig(int index,QString name);
protected:
	virtual void accept();
private:
	Ui::CameraDialog ui;
};