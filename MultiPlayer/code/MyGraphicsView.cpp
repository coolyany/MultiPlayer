#include "MyGraphicsView.h"

MyGraphicsView::MyGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{
	setStyleSheet("padding: 0px; border: 0px;");//û�й�����
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
	int nwith = this->width() - 3;//��ȡ����ؼ�Graphics View�Ŀ��
	int nheight = this->height() - 3;//��ȡ����ؼ�Graphics View�ĸ߶�
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
