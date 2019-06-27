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
#include <QGraphicsSceneMouseEvent>

SliceImagePane::SliceImagePane(QPixmap& slice, const QPoint& destgridpos)
	:image_(slice),
	destgridpos_(destgridpos),
	curgridpos_(destgridpos)
{
	setFlags(QGraphicsItem::ItemIsSelectable);
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
	painter->save();
	QRectF boundrect = boundingRect();
	painter->drawPixmap(boundingRect(), image_, {0.0, 0.0, (qreal)image_.width(), (qreal)image_.height()});
	QPen pen(Qt::black);
	double border = 2.0;
	QRectF newrt = boundrect;
	QPointF newtf = newrt.topLeft();
	newtf.rx() += border;
	newtf.ry() += border;
	newrt.setTopLeft(newtf);
// 	QPointF newbr = newrt.bottomRight();
// 	newbr.rx() -= border;
// 	newbr.ry() -= border;
// 	newrt.setBottomRight(newbr);
	if(isSelected()){
		pen.setColor(Qt::red);
		pen.setWidth(2.0);
	}
	painter->setPen(pen);
	painter->drawRect(newrt);
	painter->restore();
 	/*painter->setBrush(Qt::darkGray);*/
// 	painter->drawEllipse(-12, -12, 30, 30);
// 	painter->setPen(QPen(Qt::black, 1));
// 	painter->setBrush(QBrush(color));
// 	painter->drawEllipse(-15, -15, 30, 30);
}

void SliceImagePane::mousePressEvent(QGraphicsSceneMouseEvent* event)
{	
	if(event->button() == Qt::LeftButton){
		QList<QGraphicsItem*> selitems = scene()->selectedItems();
		if(selitems.empty()){
			setSelected(true);
			update();			
		}else{
			QGraphicsItem* other = selitems[0];
			if(other != this){
				scene()->clearSelection();
				SliceImagePane* otherpane = static_cast<SliceImagePane*>(other);
				QPoint newpos = otherpane->currentGridPos();
				QPoint selfpos = curgridpos_;
				setGridPos(newpos);
				otherpane->setGridPos(selfpos);
				update();
			}else{
				setSelected(false);
				update();
			}
		}
	}else{
		QGraphicsItem::mousePressEvent(event);
		event->accept();
	}
}

void SliceImagePane::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mouseMoveEvent(event);
}

void SliceImagePane::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mouseReleaseEvent(event);
}
