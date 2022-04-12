#include "MultiPlayer.h"
#include <QDebug>

//#pragma comment(lib, "..\\libjpeg-turbo.lib")

MultiPlayer::MultiPlayer(QWidget *parent)
    : QMainWindow(parent),
	  ScreenButton(NULL),
	sdlVideo(NULL)
{
    ui.setupUi(this);
	//ui.label_4->setStyleSheet("background-color: black");
	initMenu();
	initIcon();
	initTool();
	initConnect();
	//initSDL();

	sdlVideo = new SDLVideo((const void*)ui.openGLWidget->winId(), ui.openGLWidget->width(), ui.openGLWidget->height());
}

MultiPlayer::~MultiPlayer()
{
	if (sdlVideo != NULL)
	{
		delete sdlVideo;
		sdlVideo = NULL;
	}
}

void MultiPlayer::initMenu()
{
	//添加状态栏提示
	ui.action_file->setStatusTip(QStringLiteral("打开一个视频文件"));
	ui.action_stream->setStatusTip(QStringLiteral("打开流媒体视频"));
	ui.action_camera->setStatusTip(QStringLiteral("打开本地摄像头"));
}

void MultiPlayer::initIcon()
{
	//ui.pushButton_play->setIcon(QIcon(":/tool/resource/play.png"));
}

void MultiPlayer::initTool()
{
	ui.radioButton->setChecked(true);
	ScreenButton = new QButtonGroup(this);
	ScreenButton->addButton(ui.radioButton);
	ScreenButton->addButton(ui.radioButton_two);
	ScreenButton->addButton(ui.radioButton_four);
	ScreenButton->addButton(ui.radioButton_nine);
}

void MultiPlayer::initConnect()
{
	//connect(ui.action_camera, &QAction::triggered, this, &MultiPlayer::showCamera);
	connect(ui.buttonStopPlay, &QPushButton::clicked, this, &MultiPlayer::closeCamera);
	connect(ui.action_file, &QAction::triggered, this, &MultiPlayer::openVideo);
}

//void MultiPlayer::initSDL()
//{
//	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
//		std::cout << "SDL_Init failed" << std::endl;
//		return;
//	}
//	screen = SDL_CreateWindowFrom((void*)ui.openGLWidget->winId());
//	if (!screen)
//	{
//		std::cout << "DL_CreateWindowFrom failed" << std::endl;
//		return;
//	}
//	render = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);//渲染器使用硬件加速
//	if (!render)
//	{
//		std::cout << "SDL_CreateRenderer failed" << std::endl;
//		return;
//	}
//	tex = SDL_CreateTexture(
//		render, SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, ui.openGLWidget->width(),
//		ui.openGLWidget->height());
//	if (!tex) {
//		SDL_LogError(1, "SDL: SDL_CreateTexture failed.");
//		return;
//	}
//}

void MultiPlayer::cancelAllCheckRadioButton()
{
	for (auto item : ScreenButton->buttons()) {
		item->setChecked(false);
	}
}

//void MultiPlayer::loadSDLImage(const cv::Mat &img)
//{
//	static int i = 0;
//	std::cout << "frame :: " << i++ << std::endl;
//	SDL_RenderClear(render);//初始化后备缓冲区
//	
//	/* Mat转存buf容器 */
//	int img_size = img.cols * img.rows;
//	unsigned char* buf = new unsigned char[img_size];
//	int n = 0;
//	std::cout << "pix :: " << img.at<uchar>(11, 11) << std::endl;
//	for (size_t i = 0; i < img.rows; i++)
//	{
//		for (size_t j = 0; j < img.cols; j++) {
//			buf[n] = img.at<uchar>(i, j);
//			n++;
//		}
//	}
//	cv::Mat dest = img;
//	cv::imwrite("test.bmp", dest);
//	//SDL_Rect rect = SDL_Rect{ 0,0,ui.openGLWidget->width(),ui.openGLWidget->height() };   // 尺寸需要与texture相同
//	//SDL_UpdateTexture(tex, &rect, (const void*)buf, img.cols);
//	//SDL_RenderCopy(render, tex, NULL, &rect);
//	//SDL_RenderPresent(render);
//	SDL_Surface *pic = SDL_LoadBMP("test.bmp");
//	//载入的图片生成SDL材质
//	SDL_Texture * texture = SDL_CreateTextureFromSurface(render, pic);
//
//	//把材质复制到渲染器
//	SDL_RenderCopy(render, texture, NULL, NULL);
//	//显示出来
//	SDL_RenderPresent(render);
//
//	// 清理资源
//	SDL_DestroyTexture(texture);
//	SDL_FreeSurface(pic);
//	//销毁纹理
//	//SDL_DestroyTexture(tex);
//	delete[] buf;
//	buf = nullptr;
//	SDL_Delay(40);
//}

void MultiPlayer::closeCamera()
{
	//isPlayEnd = true;
	//isCameraOpen = false;
	//capture.release();
	sdlVideo->endPlay();
}

void MultiPlayer::openVideo()
{
	std::cout << "***************************** " << std::endl;;
	QString fileName = QFileDialog::getOpenFileName(this, tr("open local media"), ".", "*.avi *.mp4 *.wmv;;*.*");
	std::cout << "file "<< fileName.toLocal8Bit().data() << std::endl;
	if (fileName.isEmpty())
	{
		return;
	}
	sdlVideo->openVideo(fileName);
}

void MultiPlayer::showCamera()
{
	ui.pushButton_play->setIcon(QIcon(":/tool/resource/pause.png"));
	sdlVideo->setPlayWay(CAMERA);
	sdlVideo->startPlay();
	//if (isCameraOpen == true)
	//{
	//	return;
	//}
	//ui.pushButton_play->setIcon(QIcon(":/tool/resource/pause.png"));
	////ui.action_camera->setText(QStringLiteral("关闭摄像头"));

	//capture.open(0);
	//std::cout << "摄像头已经打开：" << capture.isOpened() << std::endl;
	//capture.set(cv::CAP_PROP_FRAME_WIDTH, ui.openGLWidget->width());
	//capture.set(cv::CAP_PROP_FRAME_HEIGHT, ui.openGLWidget->height());
	//cv::Mat srcFrame;
	//cv::Mat outFrame;
	//while (!isPlayEnd) {
	//	srcFrame.release();
	//	outFrame.release();
	//	capture >> srcFrame;
	//	//cv::cvtColor(srcFrame, outFrame, CV_BGR2GRAY);
	//	//QImage showImg = cvMat2QImage(frame);
	//	//ui.label_4->setPixmap(QPixmap::fromImage(showImg));
	//	loadSDLImage(srcFrame);
	//	cv::waitKey(30);
	//}
}
