#include "MyGraphicsView.h"

MyGraphicsView::MyGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{
	setStyleSheet("padding: 0px; border: 0px;");//没有滚动条
}

MyGraphicsView::~MyGraphicsView()
{
}

void MyGraphicsView::SetMyData(MyData * md)
{
	m_data = md;
}

void MyGraphicsView::resizeEvent(QResizeEvent * size)
{
	int nwith = this->width() - 3;//获取界面控件Graphics View的宽度
	int nheight = this->height() - 3;//获取界面控件Graphics View的高度
}

void MyGraphicsView::Repaint(AVFrame * image)
{
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent * event)
{
}

void MyGraphicsView::mousePressEvent(QMouseEvent * event)
{
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent * event)
{
}

void MyGraphicsView::mouseDoubleClickEvent(QMouseEvent * mouseEvent)
{
}
