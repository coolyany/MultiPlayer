#include "MultiPlayer.h"
#include <QDebug>

MultiPlayer::MultiPlayer(QWidget *parent)
	:QMainWindow(parent)
{
	ui.setupUi(this);

	init();
	SignConnect();
}

MultiPlayer::~MultiPlayer()
{
	if (m_data)
	{
		delete  m_data;
		m_data = nullptr;
	}
	if (m_pc)
	{
		delete m_pc;
		m_pc = nullptr;
	}
}

void MultiPlayer::init()
{
	m_data = new MyData();
	m_pc = new PlayCtrl();
	m_pw = MyData::LocalPlay;

	m_pc->SetMyData(m_data);
	ui.graphicsView->SetMyData(m_data);
	ui.graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

void MultiPlayer::SignConnect()
{
	connect(ui.menu_media, &QMenu::triggered, this, &MultiPlayer::onClickActMedia);
	connect(m_pc, &PlayCtrl::playEnd, this, &MultiPlayer::slotPlayEnd);
	connect(ui.pushButton_play, &QPushButton::clicked, this, &MultiPlayer::slotPlayAndPause);
}

void MultiPlayer::onClickActMedia(QAction *act)
{
	QString actName = act->text();
	if (actName == QStringLiteral("本地媒体"))
	{
		playLocalMedia();
		ui.pushButton_play->setIcon(QIcon(":/tool/resource/pause.png"));
		m_isPause = false;
	}


}

void MultiPlayer::slotPlayEnd()
{
	//switch (m_playModel)
	//{
	//case ORDER:
	//	//顺序循环播放
	//	playOrder();
	//	break;
	//case SINGLE:
	//	//单循环播放
	//	playSingle();
	//	break;
	//default:
	//	break;
	//}
}

void MultiPlayer::slotPlayAndPause()
{
	m_isPause = !m_isPause;
	if (m_isPause)
	{
		ui.pushButton_play->setIcon(QIcon(":/tool/resource/play.png"));
	}
	else 
	{
		ui.pushButton_play->setIcon(QIcon(":/tool/resource/pause.png"));
	}

	m_pc->SetPause(m_isPause);
}

void MultiPlayer::playLocalMedia()
{
	QString path = QFileDialog::getOpenFileName(NULL, "video", ".", "*.mp4 *.avi *.mov *.flv *.mkv *.h264 *.hevc");
	if (path.isEmpty())
		return;
	m_currentPath = path;
	m_pw = MyData::LocalPlay;

	if (!m_pc->OpenMedia(m_currentPath,m_pw,ui.graphicsView))
	{
		//播放失败
		return;
	}

}
