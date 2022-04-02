#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MultiPlayer.h"
#include <QButtonGroup>
#include "SDLVideo.h"


//#include "Data.h"
//extern "C" {
//	#include <SDL.h>
//	#undef main
//}

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
	//void initSDL();

	void cancelAllCheckRadioButton();//取消选中所有radiobutton
	//void loadSDLImage(const cv::Mat &img);//SDL加载图片
public slots:
	void showCamera();
	void closeCamera();
private:
    Ui::MultiPlayerClass ui;

	//cv::VideoCapture capture;
	//bool isCameraOpen = false;
	//bool isPlayEnd = false;
	QButtonGroup *ScreenButton;
	SDLVideo* sdlVideo;
	//SDL_Texture *tex = nullptr;
	//SDL_Window *screen = nullptr;
	//SDL_Renderer *render = nullptr;
	//SDL_Texture *bitmapTex = nullptr;
};
