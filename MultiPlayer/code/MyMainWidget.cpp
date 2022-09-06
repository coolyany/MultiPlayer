#include "MyMainWidget.h"
//#include "ui_widget.h"
#include "titlebar.h" //包含“自定义标题栏”头文件
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QDebug>
#include "MultiPlayer.h"
//调用WIN API需要用到的头文件与库 [实现缩放]
#ifdef Q_OS_WIN
#include <qt_windows.h>
#include <Windowsx.h>
#endif

MyMainWidget::MyMainWidget(QWidget *parent) :
	QWidget(parent)
{
	//ui->setupUi(this);

	//Qt::FramelessWindowHint设置窗口标志为无边框，而Qt::WindowStaysOnTopHint使窗口位于所有界面之上
	//this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->setWindowFlags(Qt::FramelessWindowHint);
	//背景透明
	//setAttribute(Qt::WA_TranslucentBackground, true);

	//定义自定义标题栏对象
	titleBar *pTitleBar = new titleBar(this);
	installEventFilter(pTitleBar);

	setWindowTitle("MultiPlayer 1.0"); //设置窗口名称，会发生窗口标题栏改变事件，随之自定义标题栏的标题会更新
	//setWindowIcon(QIcon(":/IASPlayer/Resources/title.ico")); //设置窗口图标，会发生窗口图标改变事件，随之自定义标题栏的图标会更新

	//使用调色板设置窗口的背景色
	/*QPalette pal(palette());
	pal.setColor(QPalette::Background, QColor(45, 45, 48));
	setAutoFillBackground(true);
	setPalette(pal);*/

	setStyleSheet(QString::fromUtf8("background-color: rgb(45, 45, 48);\n"
		"color: rgb(255, 255, 255);"));

	/*setStyleSheet("QTabBar::tab { height: 32px; \
		width:120px;color: white;background:rgb(50,50,52); padding: 5px;}"
		"QTabBar::tab:selected { background: rgb(0,122,204); } "
		"QTabWidget::pane{ border - right: 0;}");
	background - color: rgb(45, 45, 48);*/
//color: rgb(200, 200, 220);
	

	MultiPlayer *tbt = new MultiPlayer(this);
	//TitleBarTest *tbt = new TitleBarTest();//可以不指定this

	tbt->setWindowFlags(Qt::Widget);//修改窗口为Widget属性
	//窗口布局中加入标题栏
	QVBoxLayout *pLayout = new QVBoxLayout();
	pLayout->addWidget(pTitleBar);
	pLayout->addWidget(tbt);
	//pLayout->addStretch();
	pLayout->setSpacing(0);
	//pLayout->setContentsMargins(0, 0, 0, 0);
	pLayout->setContentsMargins(2, 2, 2, 2);
	setLayout(pLayout);

	//m_nBorder表示鼠标位于边框缩放范围的宽度，可以设置为5
	m_nBorderWidth = 5;

	int screenCount = QApplication::desktop()->screenCount();
	qDebug() << "screen count" << screenCount;

	if (screenCount > 0)
	{
		QWidget *widget = QApplication::desktop()->screen(0);
		resize(widget->width() / 3 * 2, widget->height() / 3 * 2);
		move((widget->width() - this->width()) / 2, (widget->height() - this->height()) / 2);
	}
}

MyMainWidget::~MyMainWidget()
{
	//delete ui;
}

//nativeEvent主要用于进程间通信-消息传递，使用这种方式后来实现窗体的缩放 [加上了这函数，窗口也能移动了]
bool MyMainWidget::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	Q_UNUSED(eventType)

		MSG *param = static_cast<MSG *>(message);

	switch (param->message)
	{
	case WM_NCHITTEST:
	{
		int nX = GET_X_LPARAM(param->lParam) - this->geometry().x();
		int nY = GET_Y_LPARAM(param->lParam) - this->geometry().y();

		// 如果鼠标位于子控件上，则不进行处理
		if (childAt(nX, nY) != nullptr)
			return QWidget::nativeEvent(eventType, message, result);

		*result = HTCAPTION;

		// 鼠标区域位于窗体边框，进行缩放
		if ((nX > 0) && (nX < m_nBorderWidth))
			*result = HTLEFT;

		if ((nX > this->width() - m_nBorderWidth) && (nX < this->width()))
			*result = HTRIGHT;

		if ((nY > 0) && (nY < m_nBorderWidth))
			*result = HTTOP;

		if ((nY > this->height() - m_nBorderWidth) && (nY < this->height()))
			*result = HTBOTTOM;

		if ((nX > 0) && (nX < m_nBorderWidth) && (nY > 0)
			&& (nY < m_nBorderWidth))
			*result = HTTOPLEFT;

		if ((nX > this->width() - m_nBorderWidth) && (nX < this->width())
			&& (nY > 0) && (nY < m_nBorderWidth))
			*result = HTTOPRIGHT;

		if ((nX > 0) && (nX < m_nBorderWidth)
			&& (nY > this->height() - m_nBorderWidth) && (nY < this->height()))
			*result = HTBOTTOMLEFT;

		if ((nX > this->width() - m_nBorderWidth) && (nX < this->width())
			&& (nY > this->height() - m_nBorderWidth) && (nY < this->height()))
			*result = HTBOTTOMRIGHT;

		return true;
	}
	}

	return QWidget::nativeEvent(eventType, message, result);
}