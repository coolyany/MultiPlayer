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
void MyGLWidget::UpdateFrame()
{
	if (!m_data)
		return;
	QImage img = m_data->popCamFrame();
	setImage(img);
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
	initializeOpenGLFunctions(); //初始化OPenGL功能函数
	glClearColor(0, 0, 0, 0);    //设置背景为黑色
	glEnable(GL_TEXTURE_2D);     //设置纹理2D功能可用
	initTextures();              //初始化纹理设置
	initShaders();               //初始化shaders
}

void MyGLWidget::resizeGL(int w, int h)
{
	// 计算窗口横纵比
	qreal aspect = qreal(w) / qreal(h ? h : 1);
	// 设置近平面值 3.0, 远平面值 7.0, 视场45度
	const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;
	// 重设投影
	projection.setToIdentity();
	// 设置透视投影
	projection.perspective(fov, static_cast<float>(aspect), zNear, zFar);
}

void MyGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除屏幕缓存和深度缓冲
	QMatrix4x4 matrix;
	matrix.translate(0.0, 0.0, -5.0);                   //矩阵变换
	program.enableAttributeArray(0);
	program.enableAttributeArray(1);
	program.setAttributeArray(0, vertices.constData());
	program.setAttributeArray(1, texCoords.constData());
	program.setUniformValue("texture", 0); //将当前上下文中位置的统一变量设置为value
	texture->bind();  //绑定纹理
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);//绘制纹理
	texture->release(); //释放绑定的纹理
	texture->destroy(); //消耗底层的纹理对象
	texture->create();
}

void MyGLWidget::setImage(const QImage & image)
{
	texture->setData(image); //设置纹理图像
	//设置纹理细节
	texture->setLevelofDetailBias(-1);//值越小，图像越清晰
	update();
}

void MyGLWidget::initTextures()
{
	// 加载 Avengers.jpg 图片
	texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
	texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	texture->setMagnificationFilter(QOpenGLTexture::Linear);
	//重复使用纹理坐标
	//纹理坐标(1.1, 1.2)与(0.1, 0.2)相同
	texture->setWrapMode(QOpenGLTexture::Repeat);
	//设置纹理大小
	texture->setSize(this->width(), this->height());
	//分配储存空间
	texture->allocateStorage();
}

void MyGLWidget::initShaders()
{
	//纹理坐标
	texCoords.append(QVector2D(0, 1)); //左上
	texCoords.append(QVector2D(1, 1)); //右上
	texCoords.append(QVector2D(0, 0)); //左下
	texCoords.append(QVector2D(1, 0)); //右下
	//顶点坐标
	vertices.append(QVector3D(-1, -1, 1));//左下
	vertices.append(QVector3D(1, -1, 1)); //右下
	vertices.append(QVector3D(-1, 1, 1)); //左上
	vertices.append(QVector3D(1, 1, 1));  //右上
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
	vshader->compileSourceCode(vsrc);//编译顶点着色器代码

	QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
	const char *fsrc =
		"uniform sampler2D texture;\n"
		"varying vec2 texc;\n"
		"void main(void)\n"
		"{\n"
		"    gl_FragColor = texture2D(texture,texc);\n"
		"}\n";
	fshader->compileSourceCode(fsrc); //编译纹理着色器代码

	program.addShader(vshader);//添加顶点着色器
	program.addShader(fshader);//添加纹理碎片着色器
	program.bindAttributeLocation("vertex", 0);//绑定顶点属性位置
	program.bindAttributeLocation("texCoord", 1);//绑定纹理属性位置
	// 链接着色器管道
	if (!program.link())
		close();
	// 绑定着色器管道
	if (!program.bind())
		close();
}

