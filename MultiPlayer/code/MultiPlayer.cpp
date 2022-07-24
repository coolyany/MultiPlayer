#include "MultiPlayer.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QMessageBox>

//#pragma comment(lib, "..\\libjpeg-turbo.lib")

MultiPlayer::MultiPlayer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	//ui.label_4->setStyleSheet("background-color: black");
	
	//initSDL();

	this->setWindowTitle("Split_Screen");
	//ui.widget->setStyleSheet("background-color : rgb(255,0,0);");
	//show_1();

	m_data = new Data();
	cap = new cv::VideoCapture;
	vidtd = new VideoThread(m_data, this);
	glwdt = new MyGLWidget(this);
	glwdt->setData(m_data);

	initMenu();
	initIcon();
	initTool();
	initLayout();
	initConnect();
}

MultiPlayer::~MultiPlayer()
{
	closeCamera();


	if (vidtd)
	{
		delete vidtd;
		vidtd = nullptr;
	}
	if (m_data)
	{
		delete m_data;
		m_data = nullptr;
	}
	if (cap)
	{
		delete cap;
		cap = nullptr;
	}
	if (glwdt)
	{
		delete glwdt;
		glwdt = nullptr;
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

}

void MultiPlayer::initLayout()
{
	//glwdt->resize(QSize(ui.widget->width(), ui.widget->height()));
	QHBoxLayout *hLayout = new QHBoxLayout(this);
	hLayout->addWidget(glwdt);
	ui.widget->setLayout(hLayout);
}

void MultiPlayer::initConnect()
{
	connect(ui.action_camera, &QAction::triggered, this, &MultiPlayer::openCamera);
	connect(vidtd, &VideoThread::updateGL, this, [=]() {
		glwdt->update();
	});
}


void MultiPlayer::cancelAllCheckRadioButton()
{

}


void MultiPlayer::closeCamera()
{
	vidtd->setStart(false);
	vidtd->setPlayWay(NONE);

	vidtd->requestInterruption();
	vidtd->wait();

	cap->release();
}

void MultiPlayer::closeEvent(QCloseEvent * event)
{
	//QMessageBox::StandardButton button;
	//button = QMessageBox::question(this, tr("退出程序"), QString(tr("确认退出程序")), QMessageBox::Yes | QMessageBox::No);
	//if (button == QMessageBox::No)
	//{
	//	event->ignore(); // 忽略退出信号，程序继续进行  
	//}
	//else if (button == QMessageBox::Yes)
	//{
	//	event->accept(); // 接受退出信号，程序退出  
	//}
}

void MultiPlayer::openCamera()
{
	/*QList<QCameraInfo> cameras = QCameraInfo::availableCameras();

	foreach(auto cameraInfo, cameras) {
		QString str = cameraInfo.description();
		QString str2 = cameraInfo.deviceName();

		std::cout << "description :: " << str.toStdString() << std::endl;
		std::cout << "name :: " << str2.toStdString() << std::endl;
	}*/

	//CameraDialog camDlg;
	//camDlg.exec();
	if (!camDlg)
	{
		camDlg = new CameraDialog(this);

		if (!vidtd->isRunning())
		{
			vidtd->start();
		}
		connect(camDlg, &CameraDialog::acceptSig, this, [=](int camIndex, QString camName) {
			camDlg->hide();
			//打开摄像头
			cap->open(camIndex);
			cap->set(cv::CAP_PROP_FRAME_WIDTH, 1920);
			cap->set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
			cap->set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
			// cap->set(cv::CAP_PROP_FPS, 30);//帧数
			//cap->set(cv::CAP_PROP_BRIGHTNESS, 1);//亮度 50
			//cap->set(cv::CAP_PROP_CONTRAST, 40);//对比度 50
			//cap->set(cv::CAP_PROP_SATURATION, 50);//饱和度 50
			//cap->set(cv::CAP_PROP_HUE, 50);//色调 0
			//cap->set(cv::CAP_PROP_EXPOSURE, 50);//曝光 -12	

			vidtd->setVideoCapture(cap);
			vidtd->setStart(true);
			vidtd->setPlayWay(CAMERA);
			vidtd->start();

			
		});
	}
	camDlg->show();

	//ui.pushButton_play->setIcon(QIcon(":/tool/resource/pause.png"));
	//sdlVideo->setPlayWay(CAMERA);
	//sdlVideo->startPlay();
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
