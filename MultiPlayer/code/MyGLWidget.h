#pragma once
#include <QOpenGLWidget>
#include <QWidget>
#include "Data.h"
#include <QWidget>
#include <QList>
#include <QLayout>
#include <QListWidget>
#include "ui_MyGLWidget.h"
#define ERROR 0

class MyGLWidget : public QOpenGLWidget
{
	Q_OBJECT
public:
	MyGLWidget(QWidget *parent = nullptr);
	~MyGLWidget();

public:
	void setData(Data* data);
protected:
	void paintEvent(QPaintEvent *e) override;
	void resizeEvent(QResizeEvent *event) override;
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

	Ui::MyGLWidget ui;
};