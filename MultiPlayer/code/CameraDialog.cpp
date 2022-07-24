#include "CameraDialog.h"
#include <iostream>
#include <QDebug>

#include <opencv2\opencv.hpp>

CameraDialog::CameraDialog(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	initCameraDev();

}

void CameraDialog::initCameraDev()
{
	QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
	int index = cameras.size() - 1;
	foreach(auto cameraInfo, cameras) {
		QString str = cameraInfo.description();
		QString str_name = cameraInfo.deviceName();

		//std::cout << "description :: " << str.toStdString() << std::endl;
		//std::cout << "name :: " << str2.toStdString() << std::endl;

		ui.comboBox->addItem(str, index);
		index--;
	}
}

void CameraDialog::accept( )
{
	std::cout << "finished" << std::endl;
	std::cout << ui.comboBox->currentData().toInt() << std::endl;

	int camIndex = ui.comboBox->currentData().toInt();
	QString camText = ui.comboBox->currentText();


	emit acceptSig(camIndex, camText);
	//cv::VideoCapture capture;
	//capture.open(camIndex);

	//while (true)
	//{
	//	cv::Mat frame;
	//	capture >> frame;
	//	cv::imshow(camText.toStdString(), frame);
	//	cv::waitKey(30);	//—” ±30
	//}


}
