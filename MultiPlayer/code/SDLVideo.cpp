#include "SDLVideo.h"

SDLVideo::SDLVideo(const void* wid, const int winW, const int winH)
	:m_wid(wid),
	 m_winW(winW),
	 m_winH(winH)
{
	initSDL();
	m_data = new Data(winW, winH);
	sdlVideoThread = new SDLVideoThread(m_data);
	
	//更新画面
	connect(sdlVideoThread, &SDLVideoThread::UpdateSDL, this, &SDLVideo::updateSDLVideo);
}

SDLVideo::~SDLVideo()
{
	endPlay();
}

void SDLVideo::setPlayWay(PLAYWAY way)
{
	m_playway = way;
	m_data->setPlayWay(way);
}

void SDLVideo::startPlay()
{
	sdlVideoThread->start();
}

void SDLVideo::endPlay()
{
	sdlVideoThread->setEnd(true);
	m_data->setPlayWay(NONE);
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(screen);
	SDL_Quit();

	sdlVideoThread->quit();
	sdlVideoThread->wait();
}

void SDLVideo::updateSDLVideo()
{
	static int i = 0;
	std::cout << "frame :: " << i++ << std::endl;
	SDL_RenderClear(render);//初始化后备缓冲区
	/* 读取帧 */
	cv::Mat img = m_data->popFrame();
	/* Mat转存buf容器 */
	/*int img_size = img.cols * img.rows;
	unsigned char* buf = new unsigned char[img_size];
	int n = 0;
	std::cout << "pix :: " << img.at<uchar>(11, 11) << std::endl;
	for (size_t i = 0; i < img.rows; i++)
	{
		for (size_t j = 0; j < img.cols; j++) {
			buf[n] = img.at<uchar>(i, j);
			n++;
		}
	}*/
	cv::Mat dest = img;
	cv::imwrite("test.bmp", dest);
	//SDL_Rect rect = SDL_Rect{ 0,0,ui.openGLWidget->width(),ui.openGLWidget->height() };   // 尺寸需要与texture相同
	//SDL_UpdateTexture(tex, &rect, (const void*)buf, img.cols);
	//SDL_RenderCopy(render, tex, NULL, &rect);
	//SDL_RenderPresent(render);
	SDL_Surface *pic = SDL_LoadBMP("test.bmp");
	//载入的图片生成SDL材质
	SDL_Texture * texture = SDL_CreateTextureFromSurface(render, pic);

	//把材质复制到渲染器
	SDL_RenderCopy(render, texture, NULL, NULL);
	//显示出来
	SDL_RenderPresent(render);

	// 清理资源
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(pic);
	//销毁纹理
	//SDL_DestroyTexture(tex);
	//delete[] buf;
	//buf = nullptr;
	//SDL_Delay(40);
}

void SDLVideo::initSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL_Init failed" << std::endl;
		return;
	}
	screen = SDL_CreateWindowFrom(m_wid);
	if (!screen)
	{
		std::cout << "DL_CreateWindowFrom failed" << std::endl;
		return;
	}
	render = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);//渲染器使用硬件加速
	if (!render)
	{
		std::cout << "SDL_CreateRenderer failed" << std::endl;
		return;
	}
	tex = SDL_CreateTexture(
		render, SDL_PIXELFORMAT_BGR555, SDL_TEXTUREACCESS_STREAMING, m_winW,
		m_winH);
	if (!tex) {
		SDL_LogError(1, "SDL: SDL_CreateTexture failed.");
		return;
	}
}
