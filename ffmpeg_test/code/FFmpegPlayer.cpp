#include "FFmpegPlayer.h"
#include <QDebug>
#include <iostream>

using namespace std;

static double r2d(AVRational r)
{
	return r.num == 0 || r.den == 0 ? 0. : (double)r.num / (double)r.den;
}

FFmpegPlayer::FFmpegPlayer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//QImage image("D:\\TEST\\ffmpegTest\\demo1\\FFmpegPlayer\\x64\\Debug\\1.jpg");
	//ui.label->setPixmap(QPixmap::fromImage(image));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(slotOpenFile()));
}

void FFmpegPlayer::slotOpenFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, "����Ƶ", "", "All file(*.*);;(*.mp4)");
	if (fileName == "") {
		qDebug() << "open error";
		return;
	}
	path = fileName;
	//initVideo();
	createPreviewWidthFile();
}

void FFmpegPlayer::initVideo()
{
	//��װ��ʽ������
	ic = avformat_alloc_context();

	//��������
	AVDictionary *opts = NULL;
	//����rtsp����tcpЭ���
	av_dict_set(&opts, "rtsp_transport", "tcp", 0);

	//�����ӳ�ʱ��
	av_dict_set(&opts, "max_delay", "500000", 0);
	//av_dict_set(&opts, "stimeout", "3000000", 0);  //���ó�ʱ�Ͽ�����ʱ��
	//av_dict_set(&opts, "timeout", "3000000", 0);  //���ó�ʱ�Ͽ�����ʱ��

	av_dict_set(&opts, "max_delay", "5000000", 0);
	av_dict_set(&opts, "buffer_size", "10240000", 0);

	av_dict_set(&opts, "protocol_whitelist", "file,tcp,udp,rtp", 0);

	if (avformat_open_input(&ic, path.toLocal8Bit(), 0, &opts) != 0)
	{
		qDebug() << "can not open video";
		avformat_close_input(&ic);
		return;
	}
	//��ȡ����Ϣ
	if (avformat_find_stream_info(ic, 0) != 0)
	{
		qDebug() << "can not get video stream info";

		return;
	}
	qDebug() << "msc ::" << ic->duration / (AV_TIME_BASE / 1000);

	//��ӡ��Ƶ����ϸ��Ϣ
	av_dump_format(ic, 0, path.toLocal8Bit(), 0);

	//��ȡ��Ƶ��
	videoStream = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
	AVStream *as = ic->streams[videoStream];

	cout << "===================================================" << endl;
	cout << "codec_id = " << as->codecpar->codec_id << endl;
	cout << "format = " << as->codecpar->format << endl;
	cout << videoStream << "��Ƶ��Ϣ" << endl;
	cout << "width = " << as->codecpar->width << endl;
	cout << "height = " << as->codecpar->height << endl;
	//֡�� fps ����ת��
	cout << "video fps = " << r2d(as->avg_frame_rate) << endl;

	//�����ڴ�
	AVCodecParameters *param = avcodec_parameters_alloc();
	avcodec_parameters_copy(param, ic->streams[videoStream]->codecpar);

	//�ҵ�������
	AVCodec *vcodec = avcodec_find_decoder(param->codec_id);
	if (!vcodec)
	{
		avcodec_parameters_free(&param);
		cout << "can't find the codec id " << param->codec_id << endl;
		return;
	}
	cout << "find the AVCodec " << param->codec_id << endl;

	//����AVCodecContext�ռ䡣��Ҫ����һ����������Ҳ���Բ����������������������
	codec = avcodec_alloc_context3(vcodec);
	//�ú������ڽ�������Ĳ�����Ҳ����AVStream����Ĳ���ֱ�Ӹ��Ƶ�AVCodecContext�������ĵ��С�
	avcodec_parameters_to_context(codec, param);
	avcodec_parameters_free(&param);
	//���߳̽�����
	codec->thread_count = 8;

	//�򿪽�����������
	int re = avcodec_open2(codec, vcodec, 0);
	if (re != 0)
	{
		avcodec_free_context(&codec);
		char buf[1024] = { 0 };
		av_strerror(re, buf, sizeof(buf) - 1);
		cout << "avcodec_open2 failed! :" << buf << endl;
		return;
	}
	cout << " avcodec_open2 success!" << endl;
	decodeStream();//����
}

void FFmpegPlayer::decodeStream()
{
	//AVFrame *frame = av_frame_alloc();//����һ֡�ڴ�
	AVPacket *packet = av_packet_alloc();
	while (1)
	{
		//frame = av_frame_alloc();
		//avpacket = av_packet_alloc();
		//AVPacket avpacket;
		//av_init_packet(avpacket);
		//avpacket->data = NULL;

		if (av_read_frame(ic, packet) < 0)
		{
			cout << "av_read_frame error" << endl;
			//av_frame_free(&frame);
			//av_packet_free(&avpacket);
			continue;
		}
		if (!packet || packet->size <= 0 || !packet->data) {
			cout << "packet is NULL" << endl;
		}
		//�ж��Ƿ�����Ƶ��
		if (packet->stream_index == videoStream)
		{
			//������Ƶ���ݰ� 
			int re = avcodec_send_packet(codec, packet);
			//av_packet_free(&avpacket);//�ͷ�packet�ڴ�	
			if (re != 0)
			{
				cout << "avcodec_send_packet error" << endl;
				//av_frame_free(&frame);
				continue;//����send
			}
			//һ��send��Ӧ���recevie
			while (1)
			{
				if (!codec)
				{
					cout << "codec is NULL" << endl;
					return;
				}
				AVFrame *frame = av_frame_alloc();//����һ֡�ڴ�
				re = avcodec_receive_frame(codec, frame);
				if (re == AVERROR(EAGAIN))
				{
					av_frame_free(&frame);
					cout << "avcodec recevice error:output is not available in this state,user must try to send new input" << endl;
					//continue;
					//break;
					return;
				}
				else if (re == AVERROR(EINVAL))
				{
					av_frame_free(&frame);
					cout << "avcodec recevice error:codec not open" << endl;
					//continue;
					break;
				}
				else if (re == AVERROR_EOF)
				{
					av_frame_free(&frame);
					cout << "avcodec recevice error:end of file" << endl;
					//continue;
					break;
				}
				else if (re < 0)
				{
					av_frame_free(&frame);
					cout << "avcodec recevice error" << endl;
					break;
				}
				cout << "avcodec successful" << endl;
				QImage *img = new QImage;
				img = AVFrameToImage(frame);
				ui.label->setPixmap(QPixmap::fromImage(*img));
				delete img->bits();
				delete img;
				img = NULL;
				//av_frame_free(&frame);
				break;
			}
		}
	}
}

QImage *FFmpegPlayer::AVFrameToImage(AVFrame * frame)
{
	int w = frame->width;
	int h = frame->height;
	QImage *image = NULL;
	uchar *buf = new uchar[w*h * 4];
	image = new QImage(buf, w, h, QImage::Format_ARGB32);

	struct SwsContext *sws_ctx = NULL;
	sws_ctx = sws_getContext(frame->width, frame->height, (enum AVPixelFormat)frame->format,
		w, h, AV_PIX_FMT_BGRA, SWS_BICUBIC, NULL, NULL, NULL);
	if (!sws_ctx)
	{
		return NULL;
	}
	uint8_t *data[AV_NUM_DATA_POINTERS];
	data[0] = (uint8_t *)(char*)image->bits();
	int linesize[AV_NUM_DATA_POINTERS] = { 0 };
	linesize[0] = w * 4;//ÿһ�еĿ��
	int hii = sws_scale(sws_ctx, frame->data, frame->linesize, 0, frame->height,
		data,
		linesize
	);
	sws_freeContext(sws_ctx);
	return image;

}

void FFmpegPlayer::createPreviewWidthFile()
{
	AVFormatContext* fmt_ctx = nullptr;

	//����Ƶ�ļ�
	int errCode = avformat_open_input(&fmt_ctx, path.toLocal8Bit(), nullptr, nullptr);
	if (errCode != 0) {
		qDebug() << "avformat_open_input fail" << errCode;
		return;
	}

	//��ȡ����Ƶ����Ϣ
	errCode = avformat_find_stream_info(fmt_ctx, nullptr);
	if (errCode != 0) {
		qDebug() << "avformat_find_stream_info fail" << errCode;
		avformat_close_input(&fmt_ctx);
		return;
	}
	//��ӡ�����Ƶ�����Ϣ
	av_dump_format(fmt_ctx, 0, path.toLocal8Bit(), 0);	

	AVPacket* pkt = av_packet_alloc();
	AVFrame* temp_frame = av_frame_alloc();
	SwsContext* sws_ctx = nullptr;
	int ret = 0;
	QImage preview;
	bool preview_done = false;

	//for (int i = 0; i<int(fmt_ctx->nb_streams) && !preview_done; i++) {
	//	//ֻ������Ƶ��Ϣ
	//	if (fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
			//��ȡ��Ƶ��ID
			int videoStreamId = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
			//������Ƶ������
			AVCodec* codec = avcodec_find_decoder(fmt_ctx->streams[videoStreamId]->codecpar->codec_id);
			AVCodecContext *codec_ctx = avcodec_alloc_context3(codec);
			//�����ṩ�ı������������ֵ���������������
			avcodec_parameters_to_context(codec_ctx, fmt_ctx->streams[videoStreamId]->codecpar);
			//�򿪽�����
			avcodec_open2(codec_ctx, codec, nullptr);

			//��ȡ֡����
			while (av_read_frame(fmt_ctx, pkt) >= 0) {
				av_frame_unref(temp_frame);

				//����Ƶ֡���ݽ��н���
				while ((ret = avcodec_receive_frame(codec_ctx, temp_frame)) == AVERROR(EAGAIN)) {
					ret = avcodec_send_packet(codec_ctx, pkt);
					if (ret < 0) {
						qCritical() << "Failed to send packet to decoder." << ret;
						break;
					}
				}

				if (ret < 0 && ret != AVERROR_EOF) {
					qDebug() << "Failed to receive packet from decoder." << ret;
					continue;
				}

				//�ȱ�������
				int dstH = 120;
				int dstW = qRound(dstH * (float(temp_frame->width) / float(temp_frame->height)));
				//�������ܵľ���
				dstH = (dstH >> 4) << 4;
				dstW = (dstW >> 4) << 4;

				sws_ctx = sws_getContext(
					temp_frame->width,
					temp_frame->height,
					static_cast<AVPixelFormat>(temp_frame->format),
					dstW,
					dstH,
					static_cast<AVPixelFormat>(AV_PIX_FMT_RGBA),
					SWS_FAST_BILINEAR,
					nullptr,
					nullptr,
					nullptr
				);
				int linesize[AV_NUM_DATA_POINTERS];
				linesize[0] = dstW * 4;

				//����ͼƬ
				preview = QImage(dstW, dstH, QImage::Format_RGBA8888);
				uint8_t* data = preview.bits();
				sws_scale(sws_ctx,
					temp_frame->data,
					temp_frame->linesize,
					0,
					temp_frame->height,
					&data,
					linesize);
				sws_freeContext(sws_ctx);

				avcodec_close(codec_ctx);
				avcodec_free_context(&codec_ctx);
				preview_done = true;
				break;
			}
	/*	}
	}*/
	//�ͷ���Դ
	av_frame_free(&temp_frame);
	av_packet_free(&pkt);
	avformat_close_input(&fmt_ctx);

	//ʹ�ø�ͼƬ����ͼ��textlabel
	if (preview_done) {
		ui.label->setPixmap(QPixmap::fromImage(preview));
	}
}
