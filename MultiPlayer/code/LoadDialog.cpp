#include "LoadDialog.h"
#include <QMessageBox>
#include<QImage>
#include<QPainter>

LoadDialog::LoadDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);//去掉窗口上方的X
	
	//QString applicationDirPathStr = QCoreApplication::applicationDirPath() + "/logo.PNG";
	QString applicationDirPathStr = ":/tool/resource/loading.jpg";
	bool re = img.load(applicationDirPathStr);
	startTimer(40);
}

LoadDialog::~LoadDialog()
{
}
void LoadDialog::timerEvent(QTimerEvent *e)
{
	/*size_t length = 100000;
	for (size_t i = 0; i < length; i++)
	{

	}*/
	num++;
	if(num == 50)
		QDialog::accept();
}
void LoadDialog::paintEvent(QPaintEvent *event)
{
	if (&img != NULL)
	{
		QImage newImg = img.scaled(this->width(), this->height());
		QPainter painter;
		painter.begin(this);
		painter.drawImage(QPoint(0, 0), newImg);
		painter.end();
	}
}