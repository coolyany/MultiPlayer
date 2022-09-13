#include "PixItem.h"
#include <QDebug>

PixItem::PixItem(QPixmap *pixmap)
{
	m_pix = *pixmap;
	setScale(0.7);
}


PixItem::~PixItem()
{

}

QRectF PixItem::boundingRect() const
{
	int adject = 2;
	return QRectF(-m_pix.width() / 2 - adject, -m_pix.height() / 2 - adject,
		m_pix.width() + adject * 2, m_pix.height() + adject * 2);
}

void PixItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	if (mut == false)
	{
		mut = true;
		painter->drawPixmap(-m_pix.width() / 2, -m_pix.height() / 2, m_pix);
		mut = false;

		qDebug() << "painting .........................";
	}
}

void PixItem::setQGraphicsViewWH(int nwidth, int nheight)
{
	viewWidth = nwidth;

	int nImgWidth = m_pix.width();
	int nImgHeight = m_pix.height();
	qreal temp1 = nwidth * 1.0 / nImgWidth;
	qreal temp2 = nheight * 1.0 / nImgHeight;
	if (temp1 > temp2)
	{
		m_scaleDafault = temp2;
	}
	else
	{
		m_scaleDafault = temp1;
	}
	setScale(m_scaleDafault);
	m_scaleValue = m_scaleDafault;
	qDebug() << "m_scaleDafault :: " << m_scaleDafault;
}

void PixItem::setPixmap(const QPixmap & pix)
{
	if (!this->mut)
	{
		this->mut = true;
		this->m_pix = pix;
		this->mut = false;

		qDebug() << "setPixmap +++++++++++++++++++++++++";
	}
}

int PixItem::type() const
{
	return UserType + 1;
}
