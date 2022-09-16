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

	ui.horizontalSlider->setMaximum(999);
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
		//先关闭视频
		m_pc->Close();

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
	//	//˳��ѭ������
	//	playOrder();
	//	break;
	//case SINGLE:
	//	//��ѭ������
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
		//����ʧ��
		return;
	}
	ui.pushButton_play->setIcon(QIcon(":/tool/resource/pause.png"));
	m_isPause = false;

	//关闭之前定时器
	if(timerID != -1) killTimer(timerID);
	//开启定时器
	timerID = startTimer(40);

}

QString MultiPlayer::Time2Char(long long t) const
{
	int hour = ((t / 1000) / 60) / 60;
	int min = ((t / 1000) / 60) % 60;
	int sec = (t / 1000) % 60;
	char buf[1024] = { 0 };
	sprintf(buf, "%02d:%02d:%02d", hour, min, sec);
	return QString::fromUtf8(buf);
}

void MultiPlayer::timerEvent(QTimerEvent * event)
{
	if (isSliderPress) return;

	if (event->timerId() == timerID)
	{
		long long total = m_pc->GetTotalMS();
		if (total > 0)
		{
			//视频当前位置
			double mediaPos = (double)m_pc->GetPlayPts() / (double)total;
			//滑动条当前的值，视频播放位置乘滑动条最大值
			int sliderVal = ui.horizontalSlider->maximum() * mediaPos;
			qDebug() << "sliderVal :: " << sliderVal;
			ui.horizontalSlider->setValue(sliderVal);
		}
		ui.label_pre->setText(Time2Char(m_pc->GetPlayPts()));
		ui.label_last->setText(Time2Char(total));
	}
}
