#pragma once
#include <QGraphicsView>
#include <QTimer>
#include <chrono>   
#include <iostream>
#include <ctime>
#include <ratio>


#include "MyData.h"
#include "MyConvert.h"
#include "MyGraphicsScene.h"
#include "IVideoCall.h"

class MyData;
class MyGraphicsView : 
	public QGraphicsView, public IVideoCall
{
	Q_OBJECT
public:
	MyGraphicsView(QWidget *parent = Q_NULLPTR);
	~MyGraphicsView();

public:
	void SetMyData(MyData *md);

	void resizeEvent(QResizeEvent* size);
	void Repaint(AVFrame *image);

	void slotUpdateUI();


protected:
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *mouseEvent);
private:
	MyData *m_data = NULL;
	MyGraphicsScene *qgraphicsScene = NULL;

	//cv::Mat currentImage;//当前播放的图片
	AVFrame *currentFrame = NULL;//当前显示的Frame
};