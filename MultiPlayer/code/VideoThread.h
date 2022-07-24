#pragma once
#include <iostream>
#include <QThread>
#include <QImage>
#include "Data.h"

class VideoThread : public QThread
{
	Q_OBJECT
public:
	VideoThread(Data *data = nullptr, QObject* parent = nullptr);

	inline void setStart(bool start) {
		isStart = start;
	}
	inline void setPlayWay(PLAYWAY way) { m_PlayWay = way; }
	void Start();
	void Stop();
	void setVideoCapture(cv::VideoCapture *cap);
	QImage cvMat2QImage(const cv::Mat& mat);
signals:
	void updateGL();
protected:
	virtual void run() override;
private:
	bool isStart = false;
	PLAYWAY m_PlayWay = NONE;
	Data* m_data = nullptr;
	cv::VideoCapture  *m_cap = nullptr;
};