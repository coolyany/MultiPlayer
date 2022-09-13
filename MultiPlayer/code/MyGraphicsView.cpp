#include "MyGraphicsView.h"
#include <QDebug>

extern "C"
{
#include <libavutil/frame.h>
#include <libavformat/avformat.h>
}
#pragma comment(lib,"avcodec.lib")

using namespace std;
MyGraphicsView::MyGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{
	setStyleSheet("padding: 0px; border: 0px;");//û�й�����

	qgraphicsScene = new MyGraphicsScene(this);
	setScene(qgraphicsScene);//Sets the current scene to scene. If scene is already being viewed, this function does nothing.
	//this->setMouseTracking(true);
	
}

MyGraphicsView::~MyGraphicsView()
{
	if (currentFrame)
		av_frame_free(&currentFrame);
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
	if (!image)
	{
		return;
	}
	m_data->vW = image->width;
	m_data->vH = image->height;
	//������Ƶ
	/*if (m_data->isRecord())
	{
		AVFrame *clone = av_frame_clone(image);
		m_data->PushSaveFrame(clone);
	}*/
	//bool isRe = false;//�ж��Ƿ���Ҫ�ı�secen��С
	if (currentFrame)
	{
		/*if (image->width != currentFrame->width
			|| image->height != currentFrame->height)
		{
			isRe = true;
		}*/
		av_frame_free(&currentFrame);
	}
	currentFrame = av_frame_alloc();
	if (currentFrame)
	{
		currentFrame->format = image->format;
		currentFrame->width = image->width;
		currentFrame->height = image->height;
		currentFrame->pts = image->pts;
		int ret = av_frame_get_buffer(currentFrame, 32);
		if (ret < 0) {
			av_frame_free(&currentFrame);
		}
		else
		{
			ret = av_frame_copy(currentFrame, image);
			if (ret < 0) {
				av_frame_free(&currentFrame);
			}
		}
	}
	auto start = chrono::system_clock::now();
	//�˾�����
	//AVFrame *frame = m_data->FilterDeal(image);
	auto end = chrono::system_clock::now();
	//auto duration = duration_cast<microseconds>(end - start);
	auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
	//<< double(duration.count()) * microseconds::period::num / microseconds::period::den
	cout << "������"
		<< double(duration.count()) / 1000
		<< "����" << endl;
	if (image == NULL)
		return;
	QImage *img = MyConvert::AVFrame2QImage(image);
	qgraphicsScene->setPixmap(QPixmap::fromImage(*img));
	delete img->bits();
	delete img;
	img = NULL;
	av_frame_free(&image);
	//if (isRe)
	//{
	//	int nwith = this->width() - 3;//��ȡ����ؼ�Graphics View�Ŀ��
	//	int nheight = this->height() - 3;//��ȡ����ؼ�Graphics View�ĸ߶�
	//	qgraphicsScene->setQGraphicsViewWH(nwith, nheight);
	//}
	slotUpdateUI();
}

void MyGraphicsView::slotUpdateUI()
{
	this->viewport()->update();
	qDebug() << "************  update  **************";
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
