#include "SDLVideoThread.h"
#include <QImage>
#include <QDebug>

SDLVideoThread::SDLVideoThread(Data *data, QObject *parent)
	:m_data(data)
{
	
}



QImage SDLVideoThread::cvMat2QImage(const cv::Mat & mat)
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

SDLVideoThread::~SDLVideoThread()
{

}

void SDLVideoThread::initVideo()
{
	if (m_data->getPlayWay() == CAMERA)
	{
		cap.open(0);
		cap.set(cv::CAP_PROP_FRAME_WIDTH, m_data->m_width);
		cap.set(cv::CAP_PROP_FRAME_HEIGHT, m_data->m_height);
	}
}

void SDLVideoThread::setEnd(bool re)
{
	if (re)
	{
		isEnd = true;
		if (m_data->getPlayWay() == CAMERA)
		{
			cap.release();
		}
		
	}
	
}

void SDLVideoThread::run()
{
	initVideo();
	while (!isEnd) {
		if (m_data->getPlayWay() == CAMERA)
		{
			//std::cout << "111111111111111" << std::endl;
			if (!cap.isOpened())
			{
				return;
			}
			curFrame.release();
			cap >> curFrame;
			m_data->addFrame(curFrame);
			//cv::waitKey(30);
			emit UpdateSDL();
		}

		//QThread::sleep(10);
	}
}
