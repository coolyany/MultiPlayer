#include "Data.h"

Data::Data()
{
}

Data::Data(int width, int height)
	:m_width(width),
	 m_height(height)
{
}

Data::~Data()
{
	for (auto item : vidFrame) {
		delete item;
		item = NULL;
	}
}

void Data::addFrame(AVFrame* frame)
{
	vidFrame.enqueue(frame);
}

AVFrame* Data::popFrame()
{
	return vidFrame.dequeue();
}

void Data::addCamFrame(QImage img)
{
	camFrames.enqueue(img);
}

QImage Data::popCamFrame()
{
	return camFrames.dequeue();
}

bool Data::isCamFrameNull()
{
	if (camFrames.length() == 0)
		return false;
	else
		return true;
}

void Data::setMediaPath(const QString & path)
{
	mediaPath = path;
}

void Data::setAVCodecContext(AVCodecContext * ic)
{
	m_ic = ic;
}
