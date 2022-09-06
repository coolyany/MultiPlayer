#pragma once
struct AVFrame;

class IVideoCall {
	virtual void Repaint(AVFrame *image) = 0;
};