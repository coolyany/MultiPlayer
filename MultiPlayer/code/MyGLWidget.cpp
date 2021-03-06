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
#include <QLabel>
#include <QPixmap>

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
void MyGLWidget::UpdateFrame()
{
	if (!m_data)
		return;
	if (m_data->getPlayWay() == CAMERA)
	{
		QImage img = m_data->popCamFrame();
		setImage(img);
	}
	else if (m_data->getPlayWay() == MEDIA)
	{
		QImage* img = m_data->popMediaFrame();
		if (!img)
			return;
		setImage(*img);
		delete img;
		img = nullptr;
		//QImage *img2 = new QImage("D:\\Code\\MultiPlayer\\a.jpg");
		
		
	}
	
}
//
//void MyGLWidget::paintEvent(QPaintEvent * e)
//{
//	QPainter painter;
//	painter.begin(this);
//	if (!m_data || !m_data->isCamFrameNull())
//	{
//		return;
//	}
//	QImage img = m_data->popCamFrame();
//	/*QImage img;
//	img.load("D:\\Code\\MultiPlayer\\MultiPlayer\\a.jpg");*/
//	std::cout << "img size :: " << img.width() << " " << img.height() << std::endl;
//	std::cout << "this size :: " << this->width() << " " << this->height() << std::endl;
//
//	//QRectF target(this->x(), this->y(),this->width(),this->height());
//	//QRectF source(0.0, 0.0, 128.0, 128.0);
//	//QPixmap pixmap = QPixmap::fromImage(img.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
//	//std::cout << "pixmap size :: " << pixmap.width() << " " << pixmap.height() << std::endl;
//
//	painter.drawImage(QPoint(0, 0), img);
//	//painter.drawPixmap(QPoint(0, 0), pixmap);
//	//painter.drawImage(target, img, source);
//
//	painter.end();
//
//	printf("11111111111111111111111\n");
//}
//
//void MyGLWidget::resizeEvent(QResizeEvent * event)
//{
//	//ui.widget->setGeometry(0, size().height() - 100, size().width(), size().height());
//}

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

void MyGLWidget::initializeGL()
{
	initializeOpenGLFunctions(); //??????OPenGL????????
	glClearColor(0, 0, 0, 0);    //??????????????
	glEnable(GL_TEXTURE_2D);     //????????2D????????
	initTextures();              //??????????????
	initShaders();               //??????shaders
}

void MyGLWidget::resizeGL(int w, int h)
{
	// ??????????????
	qreal aspect = qreal(w) / qreal(h ? h : 1);
	// ???????????? 3.0, ???????? 7.0, ????45??
	const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;
	// ????????
	projection.setToIdentity();
	// ????????????
	projection.perspective(fov, static_cast<float>(aspect), zNear, zFar);
}

void MyGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //??????????????????????
	QMatrix4x4 matrix;
	matrix.translate(0.0, 0.0, -5.0);                   //????????
	program.enableAttributeArray(0);
	program.enableAttributeArray(1);
	program.setAttributeArray(0, vertices.constData());
	program.setAttributeArray(1, texCoords.constData());
	program.setUniformValue("texture", 0); //??????????????????????????????????value
	texture->bind();  //????????
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);//????????
	texture->release(); //??????????????
	texture->destroy(); //??????????????????
	texture->create();
}

void MyGLWidget::setImage(const QImage & image)
{
	texture->setData(image); //????????????
	//????????????
	texture->setLevelofDetailBias(-1);//??????????????????
	update();
}

void MyGLWidget::initTextures()
{
	// ???? Avengers.jpg ????
	texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
	texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	texture->setMagnificationFilter(QOpenGLTexture::Linear);
	//????????????????
	//????????(1.1, 1.2)??(0.1, 0.2)????
	texture->setWrapMode(QOpenGLTexture::Repeat);
	//????????????
	texture->setSize(this->width(), this->height());
	//????????????
	texture->allocateStorage();
}

void MyGLWidget::initShaders()
{
	//????????
	texCoords.append(QVector2D(0, 1)); //????
	texCoords.append(QVector2D(1, 1)); //????
	texCoords.append(QVector2D(0, 0)); //????
	texCoords.append(QVector2D(1, 0)); //????
	//????????
	vertices.append(QVector3D(-1, -1, 1));//????
	vertices.append(QVector3D(1, -1, 1)); //????
	vertices.append(QVector3D(-1, 1, 1)); //????
	vertices.append(QVector3D(1, 1, 1));  //????
	QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
	const char *vsrc =
		"attribute vec4 vertex;\n"
		"attribute vec2 texCoord;\n"
		"varying vec2 texc;\n"
		"void main(void)\n"
		"{\n"
		"    gl_Position = vertex;\n"
		"    texc = texCoord;\n"
		"}\n";
	vshader->compileSourceCode(vsrc);//??????????????????

	QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
	const char *fsrc =
		"uniform sampler2D texture;\n"
		"varying vec2 texc;\n"
		"void main(void)\n"
		"{\n"
		"    gl_FragColor = texture2D(texture,texc);\n"
		"}\n";
	fshader->compileSourceCode(fsrc); //??????????????????

	program.addShader(vshader);//??????????????
	program.addShader(fshader);//??????????????????
	program.bindAttributeLocation("vertex", 0);//????????????????
	program.bindAttributeLocation("texCoord", 1);//????????????????
	// ??????????????
	if (!program.link())
		close();
	// ??????????????
	if (!program.bind())
		close();
}

