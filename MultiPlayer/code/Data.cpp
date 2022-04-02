#include "Data.h"

Data::Data(int width, int height)
	:m_width(width),
	 m_height(height)
{
}

Data::~Data()
{
}

void Data::addFrame(cv::Mat frame)
{
	vidFrame.enqueue(frame);
}

cv::Mat Data::popFrame()
{
	return vidFrame.dequeue();
}
