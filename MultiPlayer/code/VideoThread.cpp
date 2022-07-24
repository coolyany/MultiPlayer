#include "VideoThread.h"
#include <QDebug>

VideoThread::VideoThread(Data *data, QObject* parent)
	: QThread(parent),
	  m_data(data)
{
}

void VideoThread::Start()
{
}

void VideoThread::Stop()
{
}

void VideoThread::setVideoCapture(cv::VideoCapture * cap)
{
	m_cap = cap;
}

QImage VideoThread::cvMat2QImage(const cv::Mat & mat)
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

void VideoThread::run()
{
	while (isStart)
	{
		if (m_PlayWay == CAMERA)
		{
			if (!m_cap)
			{
				return;
			}
			cv::Mat frame;
			m_cap->read(frame);

			QImage img =  cvMat2QImage(frame);

			std::cout << "frame size :: " << img.width() << " " << img.height() << std::endl;
			m_data->addCamFrame(img);
		}
		else if (m_PlayWay == MEDIA)
		{

		}
		else
		{
			continue;
		}
		msleep(10);
		emit updateGL();

	}
}
