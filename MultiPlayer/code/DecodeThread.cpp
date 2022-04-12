#include "DecodeThread.h"
using namespace std;

DecodeThread::DecodeThread(Data* data)
{
	m_data = data;
	m_path = data->getMediaPath();
	initDecode();
}

DecodeThread::~DecodeThread()
{
}

void DecodeThread::initDecode()
{
	/* alloc AvFormatContext memory */
	fctx = avformat_alloc_context();
	if (!fctx)
	{
		cout << "fctx is nullptr" << endl;
	}
	if (avformat_open_input(&fctx, m_path.toLocal8Bit(), NULL, NULL) != 0)
	{
		cout << "File open failed!" << endl;
		return;
	}
	if (avformat_find_stream_info(fctx, NULL) < 0)
	{
		cout << "Stream find failed!\n";
		return;
	}
	av_dump_format(fctx, -1, m_path.toLocal8Bit(), NULL);

	//找视频流
	/*for (int i = 0; i < fctx->nb_streams; i++)
	{
		if (fctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
			videoStream = i;
	}*/
	videoStream = av_find_best_stream(fctx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
	if (videoStream == -1)
	{
		cout << "Codec find failed!" << endl;
		return;
	}
	cctx = avcodec_alloc_context3(NULL);
	if (avcodec_parameters_to_context(cctx, fctx->streams[videoStream]->codecpar) < 0)
	{
		cout << "Copy stream failed!" << endl;
		return;
	}
	c = avcodec_find_decoder(cctx->codec_id);
	if (!c) {
		cout << "Find DecodeThreadr failed!" << endl;
		return;
	}
	if (avcodec_open2(cctx, c, NULL) != 0) {
		cout << "Open codec failed!" << endl;
		return;
	}
	cout << " avcodec_open2 success!" << endl;
}

void DecodeThread::run()
{
}
