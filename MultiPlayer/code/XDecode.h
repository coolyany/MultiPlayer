#pragma once
#include <mutex>

struct AVCodecParameters;
struct AVCodecContext;
struct AVPacket;
struct AVFrame;
struct AVRational;

extern void XFreePacket(AVPacket **pkt);
class XDecode
{
public:
	XDecode();
	virtual~XDecode();

	//�򿪽�����,���ܳɹ���񶼲��ͷ�para�ռ�
	virtual bool Open(AVCodecParameters *para);
	//����رջ���
	virtual void Close();
	virtual void Clear();
	//���͵������̣߳����ܳɹ�����ͷ�pkt�ռ䣨�����ý�����ݣ�
	virtual bool Send(AVPacket *pkt);
	//��ȡ��������,һ��send������Ҫ���Recv����ȡ�����е�����Send NULL��Recv���
	//ÿ�θ���һ�ݣ��ɵ������ͷ� av_frame_free
	virtual AVFrame *Recv();

	//��ǰ���뵽��pts
	long long pts = 0;
protected:
	AVCodecContext * codec = 0;
	std::mutex mux;
};
