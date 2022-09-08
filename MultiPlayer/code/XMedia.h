#pragma once
#include <iostream>
#include <mutex>
struct AVFormatContext;
struct AVPacket;
struct AVCodecParameters;

class XMedia {
public:
	XMedia();

	//打开媒体文件，或者流媒体 rtmp http rstp
	virtual bool Open(const char *url);
	//关闭
	virtual void Close();
	//获取视频参数 返回的空间需要清理 avcodec_parameters_free
	virtual AVCodecParameters *CopyVPara();
	//空间需要调用释放，释放AVPacket对象空间，和数据空间 av_packet_free
	virtual AVPacket *Read();

public:
	int totalMs = 0;
	int width = 0;
	int height = 0;

	int sampleRate = 0;
	int channels = 0;

	//音视频索引，读取时区分音视频
	int videoStream = 0;
	int audioStream = 1;

	bool isEof = false;//判断文件或者网络是否结束

protected:
	std::mutex mux;

	//解封装上下文
	AVFormatContext *ic = NULL;

	AVFormatContext *ofmt_ctx = NULL;
};
