#pragma once
#include <iostream>
#include <QObject>
#include <QImage>
#include "Data.h"
#include <QThread>
#include <QMutex>
#include "pVideo.h"
#include "DecodeThread.h"


extern "C" {
#include <SDL.h>
#undef main
#include "libavformat/avformat.h"
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
}

class SDLVideo : public QThread
{
	Q_OBJECT
public:
	SDLVideo(const void* wid, const int winW, const int winH);
	~SDLVideo();

	/* basic func */
	void setPlayWay(PLAYWAY way);
	bool openVideo(const QString &path);
	void startPlay();
	void endPlay();
	void threadQuit();
	void updateSDLVideo();
private:
	/* SDL func */
	bool initSDL();
	QImage cvMat2QImage(const cv::Mat& mat);
	bool openCodec(const QString &path);	//打开解码器
	/* opencv func */
protected:
	void run();
private:
	SDL_Texture* tex = NULL;
	SDL_Window *screen = nullptr;
	SDL_Renderer *render = NULL;
	SDL_Texture *bitmapTex = NULL;
	SDL_Rect srect = { 0 };

	//ffmpeg

	AVFormatContext *fctx = NULL;
	AVCodecContext *cctx = NULL;
	AVCodec *codec = NULL;
	AVPacket *pkt = NULL;
	AVFrame *frame = NULL;
	AVFrame *yuv = NULL;
	uint8_t *buf = NULL;
	int vsize;
	int videoStream = -1;
	struct SwsContext *imgCtx = NULL;

	int m_winW;
	int m_winH;
	const void *m_wid;

	bool isEnd = false;
	bool isCamera = false;
	PLAYWAY m_playway = NONE;

	QMutex mutex;
	//Data* m_data = nullptr;

};