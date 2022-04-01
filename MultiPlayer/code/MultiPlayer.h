#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MultiPlayer.h"
#include <QButtonGroup>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/highgui.hpp>

//#define SDL_MAIN_HANDLED
extern "C" {
#include <SDL.h>
	//#include <SDL_main.h>
#undef main
}

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
	void initSDL();

	void cancelAllCheckRadioButton();//取消选中所有radiobutton
	QImage cvMat2QImage(const cv::Mat& mat);
	void loadSDLImage(const cv::Mat &img);//SDL加载图片
public slots:
	void showCamera();
	void closeCamera();
private:
    Ui::MultiPlayerClass ui;

	cv::VideoCapture capture;
	bool isCameraOpen = false;
	bool isPlayEnd = false;
	QButtonGroup *ScreenButton;

	SDL_Texture* tex = NULL;
	SDL_Window *screen = nullptr;
	SDL_Renderer *render = NULL;
	SDL_Texture *bitmapTex = NULL;
};
