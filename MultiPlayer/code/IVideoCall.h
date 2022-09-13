#pragma once
struct AVFrame;

class IVideoCall 
{
public:
	virtual void Repaint(AVFrame *image) = 0;
};