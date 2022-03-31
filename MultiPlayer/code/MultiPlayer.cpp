#include "MultiPlayer.h"
#include <QDebug>

extern "C" {
	#include <SDL.h>
}
//#pragma comment(lib, "..\\libjpeg-turbo.lib")

MultiPlayer::MultiPlayer(QWidget *parent)
    : QMainWindow(parent),
	ScreenButton(nullptr)
{
    ui.setupUi(this);
	ui.label_4->setStyleSheet("background-color: black");
	initMenu();
	initIcon();
	initTool();
	initConnect();
}

MultiPlayer::~MultiPlayer()
{
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

void MultiPlayer::showCamera()
{
	//isCameraOpen = !isCameraOpen;
	ui.pushButton_play->setIcon(QIcon(":/tool/resource/pause.png"));

	capture.open(1);
	capture.set(cv::CAP_PROP_FRAME_WIDTH, ui.label_4->width());
	capture.set(cv::CAP_PROP_FRAME_HEIGHT, ui.label_4->height());

	while (!isPlayEnd) {
		cv::Mat frame;
		capture >> frame;
		QImage showImg = cvMat2QImage(frame);
		ui.label_4->setPixmap(QPixmap::fromImage(showImg));
		cv::waitKey(30);
	}
}
