#pragma once

/*************************************************************************************
 * 功能：实现自定义窗体的无边框与移动,以及自定义标题栏-用来显示窗体的图标、标题，以及控制窗体最小化、最大化/还原、关闭、缩放（仅支持windows平台）。
*************************************************************************************/

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
	class Widget;
}

class MyMainWidget : public QWidget
{
	Q_OBJECT

public:
	explicit MyMainWidget(QWidget *parent = nullptr);
	~MyMainWidget();

	bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private:
	//Ui::Widget *ui;

	int m_nBorderWidth; //m_nBorder表示鼠标位于边框缩放范围的宽度
};
