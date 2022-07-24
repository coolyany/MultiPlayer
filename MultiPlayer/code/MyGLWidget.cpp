#include "MyGLWidget.h"
#include <QPainter>
#include <iostream>

#include <QHBoxLayout>
#include <QListWidget>
#include <QSplitter>
#include <QPushButton>
#include <QDebug>
#include <QList>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QScopedPointer>
#include <QStatusBar>
#include <QGridLayout>
#include <QStackedWidget>
#include <QWidget>
#include <QMessageBox>
#include <QTextEdit>
#include <QList>
#include <QMessageBox>

MyGLWidget::MyGLWidget(QWidget *parent)
	: QOpenGLWidget(parent),
	  m_flag(ERROR)
{
	ui.setupUi(this);
	this->setWindowTitle("Split_Screen");
}

MyGLWidget::~MyGLWidget()
{
	
}

void MyGLWidget::setData(Data * data)
{
	m_data = data; 
}

void MyGLWidget::paintEvent(QPaintEvent * e)
{
	QPainter painter;
	painter.begin(this);
	if (!m_data || !m_data->isCamFrameNull())
	{
		return;
	}
	QImage img = m_data->popCamFrame();
	/*QImage img;
	img.load("D:\\Code\\MultiPlayer\\MultiPlayer\\a.jpg");*/
	std::cout << "img size :: " << img.width() << " " << img.height() << std::endl;
	std::cout << "this size :: " << this->width() << " " << this->height() << std::endl;

	//QRectF target(this->x(), this->y(),this->width(),this->height());
	//QRectF source(0.0, 0.0, 128.0, 128.0);

	QPixmap pixmap = QPixmap::fromImage(img.scaled(this->size(), Qt::KeepAspectRatio));

	std::cout << "pixmap size :: " << pixmap.width() << " " << pixmap.height() << std::endl;

	painter.drawPixmap(QPoint(0, 0), pixmap);
	//painter.drawImage(target, img, source);

	painter.end();

	printf("11111111111111111111111\n");
}

void MyGLWidget::resizeEvent(QResizeEvent * event)
{
	//ui.widget->setGeometry(0, size().height() - 100, size().width(), size().height());
}

void MyGLWidget::show_1()
{
}

void MyGLWidget::show_4()
{
}

void MyGLWidget::show_6()
{
}

void MyGLWidget::show_9()
{
}

void MyGLWidget::show_16()
{
}
