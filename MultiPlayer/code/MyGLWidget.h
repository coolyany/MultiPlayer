#pragma once
#include <QOpenGLWidget>
#include <QWidget>
#include "Data.h"
#include <QWidget>
#include <QList>
#include <QLayout>
#include <QListWidget>

#include <GL/gl.h>
#include <GL/glu.h>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QImage>
#include <QtOpenGL/QGLWidget>
#include <QGraphicsOpacityEffect>

#include "ui_MyGLWidget.h"
#define ERROR 0

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT
public:
	MyGLWidget(QWidget *parent = nullptr);
	~MyGLWidget();

public:
	void setData(Data* data);

	void UpdateFrame();
protected:
	//void paintEvent(QPaintEvent *e) override;
	//void resizeEvent(QResizeEvent *event) override;

	void initializeGL() Q_DECL_OVERRIDE;
	void resizeGL(int w, int h) Q_DECL_OVERRIDE;
	void paintGL() Q_DECL_OVERRIDE;
	void setImage(const QImage &image);
	void initTextures();
	void initShaders();
public slots:
	void show_1();
	void show_4();
	void show_6();
	void show_9();
	void show_16();
private:
	QList<QLayout*> list_layout;
	QList<QWidget*> list_widget;
	QList<QListWidget*> list_CreateWidget;
	enum {
		ONE = 0x01,
		FOUR,
		SIX,
		NINE,
		SIXTEEN
	};
	int m_flag;
	Data* m_data = nullptr;
	QWidget* m_pWidget = nullptr;

	QVector<QVector3D> vertices;
	QVector<QVector2D> texCoords;
	QOpenGLShaderProgram program;
	QOpenGLTexture *texture;
	QMatrix4x4 projection;

	Ui::MyGLWidget ui;
};