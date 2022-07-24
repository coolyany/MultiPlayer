#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MultiPlayer.h"
#include <QButtonGroup>
#include <QFileDialog>
#include <QCameraInfo>
#include <QList>
#include <QLayout>
#include <QListWidget>
#include <QCloseEvent>  

#include "CameraDialog.h"
#include "VideoThread.h"
#include "MyGLWidget.h"

#define ERROR 0

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
	void initLayout();
	void initConnect();
	//void initSDL();

	void cancelAllCheckRadioButton();//取消选中所有radiobutton
	//void loadSDLImage(const cv::Mat &img);//SDL加载图片
public slots:
	void openCamera();
	void closeCamera();
protected:
	void closeEvent(QCloseEvent *event) override;
private:
    Ui::MultiPlayerClass ui;
	bool isStop = false;
	QButtonGroup *ScreenButton = nullptr;
	//SDL_Texture *tex = noullptr;
	//SDL_Window *screen = nullptr;
	//SDL_Renderer *render = nullptr;
	//SDL_Texture *bitmapTex = nullptr;

	Data* m_data = nullptr;
	CameraDialog* camDlg = nullptr;
	VideoThread* vidtd = nullptr;
	cv::VideoCapture *cap = nullptr;
	MyGLWidget* glwdt = nullptr;
};
