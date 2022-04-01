#include "MultiPlayer.h"
#include <QDebug>


//#pragma comment(lib, "..\\libjpeg-turbo.lib")

MultiPlayer::MultiPlayer(QWidget *parent)
    : QMainWindow(parent),
	ScreenButton(nullptr)
{
    ui.setupUi(this);
	//ui.label_4->setStyleSheet("background-color: black");
	initMenu();
	initIcon();
	initTool();
	initSDL();
	initConnect();
}

MultiPlayer::~MultiPlayer()
{
	isPlayEnd = false;
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(screen);
	SDL_Quit();
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
	connect(ui.action_camera, &QAction::triggered, this, &MultiPlayer::showCamera);
	connect(ui.buttonStopPlay, &QPushButton::clicked, this, &MultiPlayer::closeCamera);
}

void MultiPlayer::initSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL_Init failed" << std::endl;
		return;
	}
	screen = SDL_CreateWindowFrom((void*)ui.frame->winId());
	if (!screen)
	{
		std::cout << "DL_CreateWindowFrom failed" << std::endl;
		return;
	}
	render = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);//渲染器使用硬件加速
	if (!render)
	{
		std::cout << "SDL_CreateRenderer failed" << std::endl;
		return;
	}
	tex = SDL_CreateTexture(
		render, SDL_PIXELFORMAT_BGR555, SDL_TEXTUREACCESS_STREAMING, ui.frame->width(),
		ui.frame->height());
	if (!tex) {
		SDL_LogError(1, "SDL: SDL_CreateTexture failed.");
		return;
	}
	std::cout << "width :: " << ui.frame->width() << " " << ui.frame->height() << std::endl;
}

void MultiPlayer::cancelAllCheckRadioButton()
{
	for (auto item : ScreenButton->buttons()) {
		item->setChecked(false);
	}
}

QImage MultiPlayer::cvMat2QImage(const cv::Mat & mat)
{
	// 8-bits unsigned, NO. OF CHANNELS = 1
	if (mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		// Set the color table (used to translate colour indexes to qRgb values)
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		// Copy input Mat
		uchar *pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	// 8-bits unsigned, NO. OF CHANNELS = 3
	else if (mat.type() == CV_8UC3)
	{
		// Copy input Mat
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		qDebug() << "CV_8UC4";
		// Copy input Mat
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		qDebug() << "ERROR: Mat could not be converted to QImage.";
		return QImage();
	}
}

void MultiPlayer::loadSDLImage(const cv::Mat &img)
{
	static int i = 0;
	std::cout << "frame :: " << i++ << std::endl;
	SDL_RenderClear(render);//初始化后备缓冲区
	
	/* Mat转存buf容器 */
	int img_size = img.cols * img.rows;
	unsigned char* buf = new unsigned char[img_size];
	int n = 0;
	std::cout << "pix :: " << img.at<uchar>(11, 11) << std::endl;
	for (size_t i = 0; i < img.rows; i++)
	{
		for (size_t j = 0; j < img.cols; j++) {
			buf[n] = img.at<uchar>(i, j);
			n++;
		}
	}
	cv::Mat dest = img;
	cv::imwrite("test.jpg", dest);
	SDL_Rect rect = SDL_Rect{ 0,0,ui.frame->width(),ui.frame->height() };   // 尺寸需要与texture相同
	SDL_UpdateTexture(tex, &rect, (const void*)buf, ui.frame->width());
	SDL_RenderCopy(render, tex, NULL, NULL);
	SDL_RenderPresent(render);

	//销毁纹理
	//SDL_DestroyTexture(tex);
	delete[] buf;
	buf = nullptr;
	SDL_Delay(40);
}

void MultiPlayer::closeCamera()
{
	isPlayEnd = true;
	isCameraOpen = false;
	capture.release();
}

void MultiPlayer::showCamera()
{

	if (isCameraOpen == true)
	{
		return;
	}
	ui.pushButton_play->setIcon(QIcon(":/tool/resource/pause.png"));
	//ui.action_camera->setText(QStringLiteral("关闭摄像头"));

	capture.open(0);
	std::cout << "摄像头已经打开：" << capture.isOpened() << std::endl;
	capture.set(cv::CAP_PROP_FRAME_WIDTH, ui.frame->width());
	capture.set(cv::CAP_PROP_FRAME_HEIGHT, ui.frame->height());
	cv::Mat srcFrame;
	cv::Mat outFrame;
	while (!isPlayEnd) {
		srcFrame.release();
		outFrame.release();
		capture >> srcFrame;
		cv::cvtColor(srcFrame, outFrame, CV_BGR2GRAY);
		//QImage showImg = cvMat2QImage(frame);
		//ui.label_4->setPixmap(QPixmap::fromImage(showImg));
		loadSDLImage(outFrame);
		cv::waitKey(30);
	}
}
