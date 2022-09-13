#pragma once
#include <qgraphicsitem.h>
#include <qobject.h>
#include <QPixmap>
#include <QPainter>

class PixItem : public QObject, public QGraphicsItem
{
	Q_OBJECT
	Q_INTERFACES(QGraphicsItem)
public:
	PixItem(QPixmap *pixmap);
	~PixItem();
public:
	QRectF boundingRect() const;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	void setQGraphicsViewWH(int nwidth, int nheight);
	void setPixmap(const QPixmap &pix);
	int     type() const;

signals:
	void updateUI();
private:
	QPixmap m_pix;
	qreal m_scaleDafault;
	qreal m_scaleValue;
	bool mut = false;
	int viewWidth;

};