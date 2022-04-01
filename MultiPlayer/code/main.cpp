#include "MultiPlayer.h"
#include <QtWidgets/QApplication>
#include <QDateTime>
#include <QFile>
#include <QTranslator>
#include <QDebug>



FILE* g_loggerfp = NULL;
#define LOG_LEVEL   0
// 自定义消息处理程序
void myLogHandler(QtMsgType type, const QMessageLogContext & ctx, const QString & msg)
{
	if (type < LOG_LEVEL)
		return;
	char szType[16];
	switch (type) {
	case QtDebugMsg:
		strcpy(szType, "Debug");
		break;
	case QtInfoMsg:
		strcpy(szType, "Info");
		break;
	case QtWarningMsg:
		strcpy(szType, "Warning");
		break;
	case QtCriticalMsg:
		strcpy(szType, "Critical");
		break;
	case QtFatalMsg:
		strcpy(szType, "Fatal");
	}

	QString strLog = QString::asprintf("[%s] [%s]:%s [%s:%d-%s]\n",
		QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz").toLocal8Bit().data(),
		szType,
		msg.toLocal8Bit().data(),
		ctx.file, ctx.line, ctx.function);


	QString strLogFilePath = "qt.log";

	if (!g_loggerfp) {
		g_loggerfp = fopen(strLogFilePath.toLocal8Bit().data(), "a");
	}

	if (g_loggerfp) {
		fseek(g_loggerfp, 0, SEEK_END);
		if (ftell(g_loggerfp) > (2 << 20)) {
			fclose(g_loggerfp);
			g_loggerfp = fopen(strLogFilePath.toLocal8Bit().data(), "w");
		}
	}

	if (g_loggerfp) {
		fputs(strLog.toLocal8Bit().data(), g_loggerfp);
	}
}

inline void loadStyleSheet(const char* qss)
{
	QFile file(qss);
	if (file.open(QFile::ReadOnly)) {
		qApp->setStyleSheet(file.readAll());
		file.close();
	}
}

inline void loadLang(const char* qm) {
	QTranslator *translator = new QTranslator(qApp);
	translator->load(qm);
	qApp->installTranslator(translator);
}

int main(int argc, char *argv[])
{
	qInstallMessageHandler(myLogHandler);

    QApplication a(argc, argv);
	a.setApplicationName("MultiPlayer");
	loadStyleSheet("./qss/MaterialDark.qss");
	a.setFont(QFont("黑体",12));
    MultiPlayer w;
	//w.showMaximized();//开启最大化
    w.show();
    return a.exec();
}

