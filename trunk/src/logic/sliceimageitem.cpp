/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: sliceimageitem.cpp 
CreateTime: 2019-6-21 22:16
=========================================================================*/
#include "sliceimageitem.h"
#include <QPainter>
#include <QPixmap>

SliceImageItem::SliceImageItem()
{}

SliceImageItem::~SliceImageItem()
{}

QRectF SliceImageItem::boundingRect() const
{
	QRectF rt;
	if(!image_.isNull()){
		QSize s = image_.size();
		return {-s.width() / 2.0, -s.height() / 2.0, (qreal)s.width(), (qreal)s.height()};
	}
	return rt;
}

void SliceImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);
	if(image_.isNull())
		return;
	QRectF rtf = boundingRect();
	rtf = mapToScene(rtf).boundingRect();
	/*QPolygonF pf;*/
	painter->drawPixmap(rtf, image_, {0.0, 0.0, (qreal)image_.width(), (qreal)image_.height()});
// 	painter->setPen(Qt::NoPen);
// 	painter->setBrush(Qt::darkGray);
// 	painter->drawEllipse(-12, -12, 30, 30);
// 	painter->setPen(QPen(Qt::black, 1));
// 	painter->setBrush(QBrush(color));
// 	painter->drawEllipse(-15, -15, 30, 30);
}

void SliceImageItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void SliceImageItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}

void SliceImageItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
