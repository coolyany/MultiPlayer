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
		//��ʼ����װ��
		av_register_all();

		//��ʼ������⣨���Դ�rtsp rtmp http Э�����ý����Ƶ��
		//avformat_network_init();
		isFirst = false;
	}
	dmux.unlock();
}

XMedia::~XMedia()
{

}

bool XMedia::Open(const char * url)
{
	Close();

	//��������
	AVDictionary *opts = NULL;
	//����rtsp����tcpЭ���
	av_dict_set(&opts, "rtsp_transport", "tcp", 0);

	//�����ӳ�ʱ��
	//av_dict_set(&opts, "max_delay", "500", 0);
	//av_dict_set(&opts, "stimeout", "3000000", 0);  //���ó�ʱ�Ͽ�����ʱ��
	av_dict_set(&opts, "timeout", "3000000", 0);  //���ó�ʱ�Ͽ�����ʱ��

	av_dict_set(&opts, "max_delay", "5000000", 0);
	av_dict_set(&opts, "buffer_size", "10240000", 0);

	av_dict_set(&opts, "protocol_whitelist", "file,tcp,udp,rtp", 0);

	//av_dict_set(&opts, "probesize", "1433600000", 0);

	//����log����ȼ�
	av_log_set_level(AV_LOG_QUIET);
	mux.lock();
	int re = avformat_open_input(
		&ic,
		url,
		0,      // 0 ��ʾ�Զ�ѡ������
		&opts   // �������ã�����rtsp����ʱʱ��
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

	//��ȡ����Ϣ
	re = avformat_find_stream_info(ic, 0);
	if (re != 0)
	{
		mux.unlock();
		char buf[1024] = { 0 };
		av_strerror(re, buf, sizeof(buf) - 1);
		cout << "open " << url << " failed! :" << buf << endl;
		return false;
	}

	//��ʱ�� ����
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

	//��ӡ��Ƶ����ϸ��Ϣ
	av_dump_format(ic, 0, url, 0);

	//��ȡ��Ƶ��
	videoStream = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
	AVStream *as = ic->streams[videoStream];
	width = as->codecpar->width;
	height = as->codecpar->height;

	int num = as->time_base.num;
	int den = as->time_base.den;

	//��ȡ��Ƶ��
	audioStream = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
	if (audioStream >= 0)
	{
		ic->nb_streams;
		as = ic->streams[audioStream];
		sampleRate = as->codecpar->sample_rate;
		channels = as->codecpar->channels;

		cout << "===================================================" << endl;
		cout << audioStream << "��Ƶ��Ϣ" << endl;
		cout << "sample_rate = " << as->codecpar->sample_rate << endl;
		//AVSampleFormat
		cout << "channels = " << as->codecpar->channels << endl;
		//һ֡����?? ��ͨ��������
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

void XMedia::Clear()
{
	mux.lock();
	if (!ic)
	{
		mux.unlock();
		return;
	}
	//�����ȡ����
	avformat_flush(ic);
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
	//��ȡһ֡������ռ�
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
	//ptsת��Ϊ����
	pkt->pts = pkt->pts*(1000 * (r2d(ic->streams[pkt->stream_index]->time_base)));
	pkt->dts = pkt->dts*(1000 * (r2d(ic->streams[pkt->stream_index]->time_base)));

	return pkt;
}

bool XMedia::Seek(double pos)
{
	mux.lock();
	//若上下文不存在,则退出
	if (!ic)
	{
		mux.unlock();
		return false;
	}
	long long seekpos = 0;
	seekpos = ic->streams[videoStream]->duration * pos;//视频总时长除以滑动条位置
	int re = av_seek_frame(ic, videoStream, seekpos, AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME);
	mux.unlock();

	if (re < 0)
	{
		//qDebug() << ""
		return false;
	}
	return true;
}
