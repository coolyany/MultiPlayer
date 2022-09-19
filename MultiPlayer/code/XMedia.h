#pragma once
#include <iostream>
#include <mutex>
struct AVFormatContext;
struct AVPacket;
struct AVCodecParameters;

class XMedia {
public:
	XMedia();
	virtual ~XMedia();

	//��ý���ļ���������ý�� rtmp http rstp
	virtual bool Open(const char *url);
	//�ر�
	virtual void Close();
	//�������
	virtual void Clear();
	//��ȡ��Ƶ���� ���صĿռ���Ҫ���� avcodec_parameters_free
	virtual AVCodecParameters *CopyVPara();
	//�ռ���Ҫ�����ͷţ��ͷ�AVPacket����ռ䣬�����ݿռ� av_packet_free
	virtual AVPacket *Read();

	virtual bool Seek(double pos);
public:
	int totalMs = 0;
	int width = 0;
	int height = 0;

	int sampleRate = 0;
	int channels = 0;

	//����Ƶ��������ȡʱ��������Ƶ
	int videoStream = 0;
	int audioStream = 1;

	bool isEof = false;//�ж��ļ����������Ƿ����

protected:
	std::mutex mux;

	//���װ������
	AVFormatContext *ic = NULL;

	AVFormatContext *ofmt_ctx = NULL;
};
