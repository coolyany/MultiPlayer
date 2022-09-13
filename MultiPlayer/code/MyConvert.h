#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <QImage>

struct AVFrame;
struct SwsContext;

class MyConvert
{
public:
	MyConvert();
	~MyConvert();
	static QImage *AVFrame2QImage(AVFrame *frame);
	static cv::Mat AVFrameTocvMat(AVFrame *avframe);
	static QImage cvMat2QImage(const cv::Mat& mat);
	static AVFrame *cvMatToAVFrame(cv::Mat &mat);
	static AVFrame *YUV420_To_AVFrame(unsigned char* pYUV420, int width, int height);
	static IplImage *AVFrameToIplImage(AVFrame *frame);
	static AVFrame *cvIplImageToAVFrame(IplImage *img);

	static AVFrame *nv12_to_yuv420p(AVFrame *nv12_frame);
	static AVFrame *yuv420p_to_nv12(AVFrame *yuv420p_frame);
};
