#pragma once
#include <QGraphicsView>

#include "IVideoCall.h"

class MyData;
class MyGraphicsView : public QGraphicsView, public IVideoCall
{
	Q_OBJECT
public:
	MyGraphicsView(QWidget *parent = Q_NULLPTR);
	~MyGraphicsView();

public:
	void SetMyData(MyData *md);

	void resizeEvent(QResizeEvent* size);
	void Repaint(AVFrame *image);

protected:
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *mouseEvent);
private:
	MyData *m_data = NULL;

	//cv::Mat currentImage;//��ǰ���ŵ�ͼƬ
	AVFrame *currentFrame = NULL;//��ǰ��ʾ��Frame
};