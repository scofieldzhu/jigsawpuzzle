/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: sliceimagepane.cpp 
CreateTime: 2019-6-21 22:16
=========================================================================*/
#include "sliceimagepane.h"
#include <QPainter>
#include <QPixmap>
#include <QGraphicsScene>

SliceImagePane::SliceImagePane(QPixmap& slice, const QPoint& destgridpos)
	:image_(slice),
	destgridpos_(destgridpos),
	curgridpos_(destgridpos)
{
	Q_ASSERT(!slice.isNull());
}

SliceImagePane::~SliceImagePane()
{}

void SliceImagePane::setGridPos(const QPoint& gpos)
{
	curgridpos_ = gpos;
	QPointF newpos = scene()->sceneRect().topLeft();
	newpos.rx() += (curgridpos_.y() + 0.5) * image_.width();
	newpos.ry() += (curgridpos_.x() + 0.5) * image_.height();
	setPos(newpos);
}

QRectF SliceImagePane::boundingRect() const
{
	QSize s = image_.size();
	return {-s.width() / 2.0, -s.height() / 2.0, (qreal)s.width(), (qreal)s.height()};
}

void SliceImagePane::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);	
	painter->drawPixmap(boundingRect(), image_, {0.0, 0.0, (qreal)image_.width(), (qreal)image_.height()});
 	painter->setPen(Qt::black);
	painter->drawRect(boundingRect());
 	/*painter->setBrush(Qt::darkGray);*/
// 	painter->drawEllipse(-12, -12, 30, 30);
// 	painter->setPen(QPen(Qt::black, 1));
// 	painter->setBrush(QBrush(color));
// 	painter->drawEllipse(-15, -15, 30, 30);
}

void SliceImagePane::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void SliceImagePane::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}

void SliceImagePane::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
