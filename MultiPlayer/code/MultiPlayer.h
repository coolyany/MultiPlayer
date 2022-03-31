#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MultiPlayer.h"
#include <QButtonGroup>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/highgui.hpp>

class MultiPlayer : public QMainWindow
{
    Q_OBJECT

public:
    MultiPlayer(QWidget *parent = Q_NULLPTR);
	~MultiPlayer();

	void initMenu();
	void initIcon();
	void initTool();
	void initConnect();

	void cancelAllCheckRadioButton();//取消选中所有radiobutton
	QImage cvMat2QImage(const cv::Mat& mat);
public slots:
	void showCamera();
private:
    Ui::MultiPlayerClass ui;

	cv::VideoCapture capture;
	bool isCameraOpen = false;
	bool isPlayEnd = false;
	QButtonGroup *ScreenButton;
};
