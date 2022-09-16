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
	//获取解码数据,一次send可能需要多次Recv，获取缓冲中的数据Send NULL在Recv多次
	//每次复制一份，由调用者释放 av_frame_free
	virtual AVFrame *Recv();

	//��ǰ���뵽��pts
	long long pts = 0;
protected:
	AVCodecContext * codec = nullptr;
	std::mutex mux;
};
