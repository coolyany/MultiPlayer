#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QtGui>
#include <QStyle>
#include <QPixmap>
#include "titleBar.h"

//调用WIN API需要用到的头文件与库
#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

titleBar::titleBar(QWidget *parent)
	: QWidget(parent)
{
	setFixedHeight(30);

	//给成员变量申请内存
	m_pIconLabel = new QLabel(this);
	m_pTitleLabel = new QLabel(this);
	m_pMinimizeButton = new QPushButton(this);
	m_pMaximizeButton = new QPushButton(this);
	m_pCloseButton = new QPushButton(this);

	//初始化图标Label
	m_pIconLabel->setFixedSize(20, 20);
	m_pIconLabel->setScaledContents(true);


	QFont font(" Microsoft YaHei", 12, 87); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
	m_pTitleLabel->setFont(font);
	m_pTitleLabel->setStyleSheet("color:#6f6f70;");
	m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	//设置按钮的固定大小、图片、取消边框
	//restorePix = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);
	restorePix.load(":/tool/resource/restore.png");
	maxPix.load(":/tool/resource/max.png");

	//m_pMinimizeButton->setIconSize(QSize(27, 22));
	m_pMinimizeButton->setIcon(QIcon(":/tool/resource/min.png"));
	//QPixmap pix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
	//m_pMinimizeButton->setIcon(pix);
	m_pMinimizeButton->setFlat(true);
	//--
	//m_pMaximizeButton->setIconSize(QSize(27, 22));
	m_pMaximizeButton->setIcon(QIcon(":/tool/resource/max.png"));
	//maxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
	//m_pMaximizeButton->setIcon(maxPix);
	m_pMaximizeButton->setFlat(true);
	//--
	//m_pCloseButton->setIconSize(QSize(27, 22));
	m_pCloseButton->setIcon(QIcon(":/tool/resource/close.png"));
	//pix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
	//m_pCloseButton->setIcon(pix);
	m_pCloseButton->setFlat(true);

	//设置窗口部件的名称
	m_pTitleLabel->setObjectName("whiteLabel");
	m_pMinimizeButton->setObjectName("minimizeButton");
	m_pMaximizeButton->setObjectName("maximizeButton");
	m_pCloseButton->setObjectName("closeButton");


	//给按钮设置静态tooltip，当鼠标移上去时显示tooltip
	m_pMinimizeButton->setToolTip("Minimize");
	m_pMaximizeButton->setToolTip("Maximize");
	m_pCloseButton->setToolTip("Close");

	//标题栏布局
	QHBoxLayout *pLayout = new QHBoxLayout(this);
	pLayout->addWidget(m_pIconLabel);
	pLayout->addSpacing(5);
	pLayout->addWidget(m_pTitleLabel);
	//QSpacerItem *spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);
	//pLayout->addItem(spacerItem);
	pLayout->addWidget(m_pMinimizeButton);
	pLayout->addWidget(m_pMaximizeButton);
	pLayout->addWidget(m_pCloseButton);
	//pLayout->insertStretch(2, 500);
	pLayout->setSpacing(0);
	//setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	pLayout->setContentsMargins(5, 0, 5, 0);
	setLayout(pLayout);

	m_pMinimizeButton->setStyleSheet("QToolTip{border:1px solid rgb(118, 118, 118); background-color: #ffffff; color:#484848; font-size:12px;}"); //设置边框, 边框色, 背景色, 字体色, 字号
	m_pMaximizeButton->setStyleSheet("QToolTip{border:1px solid rgb(118, 118, 118); background-color: #ffffff; color:#484848; font-size:12px;}"); //设置边框, 边框色, 背景色, 字体色, 字号
	m_pCloseButton->setStyleSheet("QToolTip{border:1px solid rgb(118, 118, 118); background-color: #ffffff; color:#484848; font-size:12px;}"); //设置边框, 边框色, 背景色, 字体色, 字号

	//setStyleSheet("QPushButton:selected{background-color:rgb(255,0,0)}");
	//border - radius: 2px;  border: 2px groove gray; border - style: outset;
	/*setStyleSheet("QPushButton{background-color:rgb(255,45,85); color: white;}" 
		"QPushButton:hover{background-color:rgb(255,30,32); color: rgb(255,0,0);}"
		"QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }");*/
	//m_pCloseButton->setStyleSheet("QPushButton:hover{background-color:rgb(255,30,32); color: white;}"
	//	"QToolTip{border:1px solid rgb(118, 118, 118); background-color: #ffffff; color:#484848; font-size:12px;}"); //设置边框, 边框色, 背景色, 字体色, 字号

	//setStyleSheet("QPushButton{background-color:rgba(45,45,85,100%);\
 //                                           color: white;   border-radius: 0px;  border: 2px groove gray; border-style: outset;}" // 按键本色
	//	"QPushButton:hover{background-color:red; color: black;}"  // 鼠标停放时的色彩
	//	"QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }");   // 鼠标按下的色彩


	setStyleSheet("QPushButton{background-color:rgb(45,45,48);\
                                            color: white;   border-radius: 0px;  border: 0px;padding:6px 20px;}" // 按键本色
		"QPushButton:hover{background-color:rgb(30,30,32); color: black;}"  // 鼠标停放时的色彩
		"QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }");   // 鼠标按下的色彩

	//连接三个按钮的信号槽
	connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
	connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
	connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
}

titleBar::~titleBar()
{

}

//双击标题栏进行界面的最大化/还原
void titleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
	Q_UNUSED(event); //没有实质性的作用，只是用来允许event可以不使用，用来避免编译器警告

	emit m_pMaximizeButton->clicked();
}

//进行界面的拖动  [一般情况下，是界面随着标题栏的移动而移动，所以我们将事件写在标题栏中比较合理]
void titleBar::mousePressEvent(QMouseEvent *event)
{
#ifdef Q_OS_WIN
	if (ReleaseCapture())
	{
		QWidget *pWindow = this->window();
		if (pWindow->isTopLevel())
		{
			SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
		}
	}
	event->ignore();
#else
#endif
}

//使用事件过滤器监听标题栏所在的窗体，所以当窗体标题、图标等信息发生改变时，标题栏也应该随之改变
bool titleBar::eventFilter(QObject *obj, QEvent *event)
{
	switch (event->type()) //判断发生事件的类型
	{
	case QEvent::WindowTitleChange: //窗口标题改变事件
	{
		QWidget *pWidget = qobject_cast<QWidget *>(obj); //获得发生事件的窗口对象
		if (pWidget)
		{
			//窗体标题改变，则标题栏标题也随之改变
			m_pTitleLabel->setText(pWidget->windowTitle());
			return true;
		}
	}
	break;

	case QEvent::WindowIconChange: //窗口图标改变事件
	{
		QWidget *pWidget = qobject_cast<QWidget *>(obj);
		if (pWidget)
		{
			//窗体图标改变，则标题栏图标也随之改变
			QIcon icon = pWidget->windowIcon();
			m_pIconLabel->setPixmap(icon.pixmap(m_pIconLabel->size()));
			return true;
		}
	}
	break;

	case QEvent::Resize:
		updateMaximize(); //最大化/还原
		return true;

	default:
		return QWidget::eventFilter(obj, event);
	}

	return QWidget::eventFilter(obj, event);
}

//进行最小化、最大化/还原、关闭操作
void titleBar::onClicked()
{
	//QObject::Sender()返回发送信号的对象的指针，返回类型为QObject *
	QPushButton *pButton = qobject_cast<QPushButton *>(sender());

	QWidget *pWindow = this->window(); //获得标题栏所在的窗口

	if (pWindow->isTopLevel())
	{
		//判断发送信号的对象使哪个按钮
		if (pButton == m_pMinimizeButton)
		{
			pWindow->showMinimized(); //窗口最小化显示
		}
		else if (pButton == m_pMaximizeButton)
		{
			pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();  //窗口最大化/还原显示
		}
		else if (pButton == m_pCloseButton)
		{
			pWindow->close(); //窗口关闭
		}
	}
}

//最大化/还原
void titleBar::updateMaximize()
{
	QWidget *pWindow = this->window(); //获得标题栏所在的窗口

	if (pWindow->isTopLevel())
	{
		bool bMaximize = pWindow->isMaximized(); //判断窗口是不是最大化状态，是则返回true，否则返回false
		if (bMaximize)
		{
			//目前窗口是最大化状态，则最大化/还原的toolTip设置为"Restore"
			m_pMaximizeButton->setToolTip(tr("Restore"));
			//设置按钮的属性名为"maximizeProperty"
			m_pMaximizeButton->setProperty("maximizeProperty", "restore");
			m_pMaximizeButton->setIcon(restorePix);  //窗口最大化/还原显示
		}
		else
		{
			//目前窗口是还原状态，则最大化/还原的toolTip设置为"Maximize"
			m_pMaximizeButton->setToolTip(tr("Maximize"));
			//设置按钮的属性名为"maximizeProperty"
			m_pMaximizeButton->setProperty("maximizeProperty", "maximize");
			m_pMaximizeButton->setIcon(maxPix);  //窗口最大化/还原显示
		}

		m_pMaximizeButton->setStyle(QApplication::style());
	}
}
