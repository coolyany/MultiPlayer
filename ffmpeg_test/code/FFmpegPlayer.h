#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FFmpegPlayer.h"
#include <QFileDialog>
#include <QImage>
#include <QPixmap>

extern "C" {
#include "libavformat/avformat.h"
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
}

class FFmpegPlayer : public QMainWindow
{
    Q_OBJECT

public:
    FFmpegPlayer(QWidget *parent = Q_NULLPTR);

	void initVideo();
	void decodeStream();
	QImage *AVFrameToImage(AVFrame *frame);
	
	void createPreviewWidthFile();
public slots:
	void slotOpenFile();
private:
    Ui::FFmpegPlayerClass ui;

	QString path;
	AVFormatContext *ic = NULL;
	AVCodecContext *codec = NULL;
	AVPacket *avpacket = NULL;
	//AVFrame *frame = NULL;
	int videoStream = 0;
};
