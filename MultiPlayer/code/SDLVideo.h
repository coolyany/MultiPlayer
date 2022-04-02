#pragma once
#include <iostream>
#include <QObject>
#include <QImage>
#include "Data.h"
#include "SDLVideoThread.h"

extern "C" {
#include <SDL.h>
#undef main
}

class SDLVideo : public QObject
{
	Q_OBJECT
public:
	SDLVideo(const void* wid, const int winW, const int winH);
	~SDLVideo();

	/* basic func */
	void setPlayWay(PLAYWAY way);
	void startPlay();
	void endPlay();
	void updateSDLVideo();
private:
	/* SDL func */
	void initSDL();

	/* opencv func */
private:
	SDL_Texture* tex = NULL;
	SDL_Window *screen = nullptr;
	SDL_Renderer *render = NULL;
	SDL_Texture *bitmapTex = NULL;

	int m_winW;
	int m_winH;
	const void *m_wid;

	bool isEnd = false;
	bool isCamera = false;
	PLAYWAY m_playway = NONE;

	SDLVideoThread* sdlVideoThread = nullptr;
	Data* m_data = nullptr;

	//opencv
	cv::VideoCapture capture;
};