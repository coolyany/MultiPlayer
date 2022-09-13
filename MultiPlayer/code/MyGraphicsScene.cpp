#include "MyGraphicsScene.h"

MyGraphicsScene::MyGraphicsScene(QObject *parent)
	: QGraphicsScene(parent)
{
	QString path = ":/tool/resource/back.jpg";

	QPixmap pix;
	pix.load(path);
	//¸³Öµ¸ß¡¢¿í
	pixw = pix.width();
	pixh = pix.height();
	m_pixItem = new PixItem(&pix);

	setBackgroundBrush(QBrush(QColor(0, 0, 0)));
	m_pixItem->setFlags(QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsFocusable |
		QGraphicsItem::ItemIsSelectable |
		QGraphicsItem::ItemSendsGeometryChanges
	);
	this->addItem(m_pixItem);
	setSceneRect(QRectF(-(pixw / 2), -(pixh / 2), pixw, pixh));

}


MyGraphicsScene::~MyGraphicsScene()
{
}

void MyGraphicsScene::setPixmap(const QPixmap & pix)
{
	m_pixItem->setPixmap(pix);
	pixw = pix.width();
	pixh = pix.height();
}
