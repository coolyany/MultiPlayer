#include "XMedia.h"
using namespace std;
extern "C" {
#include <libavformat/avformat.h>
}
#pragma comment(lib,"avformat.lib")
#pragma comment(lib,"avutil.lib")
#pragma comment(lib,"avcodec.lib")

static double r2d(AVRational r)
{
	return r.num == 0 || r.den == 0 ? 0. : (double)r.num / (double)r.den;
}

XMedia::XMedia()
{
	static bool isFirst = true;
	static std::mutex dmux;
	dmux.lock();
	if (isFirst)
	{
		//初始化封装库
		av_register_all();

		//初始化网络库（可以打开rtsp rtmp http 协议的流媒体视频）
		//avformat_network_init();
		isFirst = false;
	}
	dmux.unlock();
}

bool XMedia::Open(const char * url)
{
	Close();

	//参数设置
	AVDictionary *opts = NULL;
	//设置rtsp流以tcp协议打开
	av_dict_set(&opts, "rtsp_transport", "tcp", 0);

	//网络延迟时间
	//av_dict_set(&opts, "max_delay", "500", 0);
	//av_dict_set(&opts, "stimeout", "3000000", 0);  //设置超时断开连接时间
	av_dict_set(&opts, "timeout", "3000000", 0);  //设置超时断开连接时间

	av_dict_set(&opts, "max_delay", "5000000", 0);
	av_dict_set(&opts, "buffer_size", "10240000", 0);

	av_dict_set(&opts, "protocol_whitelist", "file,tcp,udp,rtp", 0);

	//av_dict_set(&opts, "probesize", "1433600000", 0);

	//设置log输出等级
	av_log_set_level(AV_LOG_QUIET);
	mux.lock();
	int re = avformat_open_input(
		&ic,
		url,
		0,      // 0 表示自动选择解封器
		&opts   // 参数设置，比如rtsp的延时时间
	);
	if (re != 0)
	{
		mux.unlock();
		char buf[1024] = { 0 };
		av_strerror(re, buf, sizeof(buf) - 1);
		cout << "open " << url << " failed! :" << buf << endl;
		return false;
	}
	cout << "open " << url << " success! " << endl;

	//获取流信息
	re = avformat_find_stream_info(ic, 0);
	if (re != 0)
	{
		mux.unlock();
		char buf[1024] = { 0 };
		av_strerror(re, buf, sizeof(buf) - 1);
		cout << "open " << url << " failed! :" << buf << endl;
		return false;
	}

	//总时长 毫秒
	totalMs = ic->duration / (AV_TIME_BASE / 1000);
	cout << "totalMs = " << totalMs << endl;
	if (totalMs == 0)
	{
		mux.unlock();
		cout << "Video does not exist" << endl;
		avformat_close_input(&ic);
		char buf[1024] = { 0 };
		av_strerror(re, buf, sizeof(buf) - 1);
		cout << "open " << url << " failed! :" << buf << endl;
		return false;
	}

	//打印视频流详细信息
	av_dump_format(ic, 0, url, 0);

	//获取视频流
	videoStream = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
	AVStream *as = ic->streams[videoStream];
	width = as->codecpar->width;
	height = as->codecpar->height;

	int num = as->time_base.num;
	int den = as->time_base.den;

	//获取音频流
	audioStream = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
	if (audioStream >= 0)
	{
		ic->nb_streams;
		as = ic->streams[audioStream];
		sampleRate = as->codecpar->sample_rate;
		channels = as->codecpar->channels;

		cout << "===================================================" << endl;
		cout << audioStream << "音频信息" << endl;
		cout << "sample_rate = " << as->codecpar->sample_rate << endl;
		//AVSampleFormat
		cout << "channels = " << as->codecpar->channels << endl;
		//一帧数据?? 单通道样本数
		cout << "frame_size = " << as->codecpar->frame_size << endl;
		//1024 * 2 *2=4096 fps = sample_rate/frame_size
	}

	mux.unlock();
	return true;
}

void XMedia::Close()
{
	mux.lock();
	if (!ic)
	{
		mux.unlock();
		return;
	}
	avformat_close_input(&ic);
	totalMs = 0;
	isEof = false;
	mux.unlock();

}

AVCodecParameters * XMedia::CopyVPara()
{
	mux.lock();
	if (!ic || videoStream < 0)
	{
		mux.unlock();
		return NULL;
	}
	AVCodecParameters *pa = avcodec_parameters_alloc();
	avcodec_parameters_copy(pa, ic->streams[videoStream]->codecpar);
	mux.unlock();
	return pa;
}

AVPacket * XMedia::Read()
{
	if (!ic)
	{
		return NULL;
	}
	AVPacket *pkt = av_packet_alloc();
	//读取一帧并分配空间
	int re = av_read_frame(ic, pkt);
	if (re != 0)
	{
		if (re == AVERROR_EOF || -138)
		{
			isEof = true;
		}
		av_packet_free(&pkt);
		return NULL;
	}
	//pts转换为毫秒
	pkt->pts = pkt->pts*(1000 * (r2d(ic->streams[pkt->stream_index]->time_base)));
	pkt->dts = pkt->dts*(1000 * (r2d(ic->streams[pkt->stream_index]->time_base)));

	return pkt;
}
