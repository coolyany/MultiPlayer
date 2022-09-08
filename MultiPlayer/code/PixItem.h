#pragma once
#include <qgraphicsitem.h>
#include <QPixmap>

class PixItem : public QGraphicsItem, public QObject
{
	Q_OBJECT
public:
	PixItem(QPixmap *pixmap);
	~PixItem();
private:

};