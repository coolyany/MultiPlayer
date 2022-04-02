#include "FFmpegPlayer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FFmpegPlayer w;
    w.show();
    return a.exec();
}
