#pragma once
#include <qgraphicsscene.h>
#include "PixItem.h"

class MyGraphicsScene : public QGraphicsScene
{
	Q_OBJECT
public:
	MyGraphicsScene(QObject *parent = nullptr);
	~MyGraphicsScene();

	void setPixmap(const QPixmap &pix);


private:
	PixItem *m_pixItem = NULL;
	int pixw;
	int pixh;

};