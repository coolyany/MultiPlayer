#include "MultiPlayer.h"

MultiPlayer::MultiPlayer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	initMenu();
}

MultiPlayer::~MultiPlayer()
{
}

void MultiPlayer::initMenu()
{
	QMenuBar *menu_bar = new QMenuBar(this);//创建一个菜单栏
	this->setMenuBar(menu_bar);				//设置为MainWindow的菜单栏
	QToolBar *tool_bar = new QToolBar(this);//创建一个工具栏
	this->addToolBar(tool_bar);				//添加工具栏到MainWindow
	QStatusBar *status_bar = new QStatusBar(this); //创建一个状态栏
	this->setStatusBar(status_bar);			//设置为MainWindow的状态栏

	//创建菜单
	QMenu *file_menu = new QMenu(QStringLiteral("媒体(&M)"), menu_bar);
	QMenu *view_menu = new QMenu(QStringLiteral("视图(&V)"), menu_bar);
	QMenu *help_menu = new QMenu(QStringLiteral("帮助(&H)"), menu_bar);

	//创建动作
	QAction *open_media_action = new QAction(QStringLiteral("打开文件(&N)"),this);
	QAction *open_stream_action = new QAction(QStringLiteral("打开串流(&O)"));
	QAction *open_camera_action = new QAction(QStringLiteral("打开摄像头(&S)"));

	//添加状态栏提示
	open_media_action->setStatusTip(QStringLiteral("打开一个视频文件"));
	open_stream_action->setStatusTip(QStringLiteral("打开流媒体视频"));
	open_camera_action->setStatusTip(QStringLiteral("打开本地摄像头"));

	//添加动作到媒体菜单，QAction就会自动变成子菜单
	file_menu->addAction(open_media_action);
	file_menu->addAction(open_stream_action);
	file_menu->addSeparator();                      //添加菜单分隔符
	file_menu->addAction(open_camera_action);

	//创建视图动作
	QAction *aSplitScreen = new QAction(QStringLiteral("视图(&T)"),this);
	QAction *fourSplitScreen = new QAction(QStringLiteral("四分屏视图(&T)(&T)"), this);
	QAction *nineSplitScreen = new QAction(QStringLiteral("九分屏视图(&T)"), this);

	//给视图菜单添加子菜单
	view_menu->addAction(aSplitScreen);
	view_menu->addAction(fourSplitScreen);
	view_menu->addAction(nineSplitScreen);

	//给帮助菜单添加子菜单
	help_menu->addAction(QStringLiteral("关于(&A)"));

	//把菜单添加到菜单栏
	menu_bar->addMenu(file_menu);
	menu_bar->addMenu(view_menu);
	menu_bar->addMenu(help_menu);

	//把动作添加到工具栏，QAction就会自动变成工具
	tool_bar->addAction(open_media_action);
	tool_bar->addAction(open_stream_action);
	tool_bar->addAction(open_camera_action);
}
