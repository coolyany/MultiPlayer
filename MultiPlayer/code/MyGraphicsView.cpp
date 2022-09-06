#include "MyGraphicsView.h"

MyGraphicsView::MyGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{

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
