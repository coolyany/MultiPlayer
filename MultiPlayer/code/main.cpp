//#include "IASPlayer.h"
#include <QtWidgets/QApplication>
#include "LoadDialog.h"
#include "MyMainWidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QFont font = a.font();
	font.setPointSize(12);
	a.setFont(font);

	LoadDialog *dlg = new LoadDialog();
	int re = dlg->exec();
	if (re == 0)
	{
		delete dlg;
		dlg = NULL;
		return -1;
	}
	delete dlg;
	dlg = NULL;
	MyMainWidget w;
	//IASPlayer w;
	//w.move((QApplication::desktop()->width() - w.width()) / 2, (QApplication::desktop()->height() - w.height()) / 2);
	w.show();
	return a.exec();
}
