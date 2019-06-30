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
#include <QGraphicsSceneMouseEvent>
#include "uiglo.h"
#include "gamescene.h"
#include "jpgame.h"

SliceImagePane::SliceImagePane(QPixmap& slice, const QPoint& destgridpos)
	:image_(slice),
	kDestGridPos_(destgridpos),
	curgridpos_(destgridpos)
{
	Q_ASSERT(!slice.isNull());
}

SliceImagePane::~SliceImagePane()
{}

void SliceImagePane::swap(SliceImagePane& pane)
{
	QPixmap tmppix = image_;
	setImage(pane.image());
	pane.setImage(tmppix);
	QPoint curpos = curgridpos_;
	setGridPos(pane.currentGridPos());
	pane.setGridPos(curpos);
	update();
}

// void SliceImagePane::setGridPos(const QPoint& gpos)
// {
// 	curgridpos_ = gpos;
// 	QPointF newpos = scene()->sceneRect().topLeft();
// 	newpos.rx() += (curgridpos_.y() + 0.5) * image_.width();
// 	newpos.ry() += (curgridpos_.x() + 0.5) * image_.height();
// 	setPos(newpos);
// }

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
	if(operating_){
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

void SliceImagePane::setOperating(bool operating)
{
	if(operating_ != operating){
		operating_ = operating;
		update();
	}
}

void SliceImagePane::mousePressEvent(QGraphicsSceneMouseEvent* event)
{	
	QGraphicsItem::mousePressEvent(event);
	if(event->button() == Qt::LeftButton){
		if(operating_)
			return;
		GetActiveGame()->setOperatingImagePane(this);		
	}else if(event->button() == Qt::RightButton){
		if(operating_){
			GetActiveGame()->setOperatingImagePane(nullptr);		
			return;
		}
		SliceImagePane* opimagepane = GetActiveGame()->operatingImagePane();
		if(opimagepane){
			swap(*opimagepane);
			scene()->update();
		}
		//QGraphicsScene* gs = scene();
		// 			QList<QGraphicsItem*> selitems = gs->selectedItems();
		// 			if(!selitems.empty()){
		// 				SliceImagePane* otherpane = static_cast<SliceImagePane*>(selitems[0]);
		// 				swap(*otherpane);
		// 				gs->update();
		// 			}
	}
// 		if(isSelected()){
// 			event->accept();
// 			return;
// 		}
// 		QGraphicsScene* gs = scene();
// 		QList<QGraphicsItem*> selitems = gs->selectedItems();
// 		if(selitems.empty()){
// 			setSelected(true);
// 			gs->update();
// 			event->accept();
// 			return;
// 		}		
// 		SliceImagePane* otherpane = static_cast<SliceImagePane*>(selitems[0]);
// 		otherpane->setSelected(false);
// 		QPoint newpos = otherpane->currentGridPos();
// 		QPoint selfpos = curgridpos_;
// 		setGridPos(newpos);
// 		otherpane->setGridPos(selfpos);
// 		//gs->clearSelection();
// 		gs->update();
// 		event->accept();
// 	}else{
// 		QGraphicsItem::mousePressEvent(event);
// 		event->accept();
// 	}
}

void SliceImagePane::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mouseMoveEvent(event);
}

void SliceImagePane::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mouseReleaseEvent(event);
}

void SliceImagePane::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mouseDoubleClickEvent(event);
// 	if(event->button() == Qt::LeftButton){
// 		if(!isSelected()){				
// 			QGraphicsScene* gs = scene();
// 			QList<QGraphicsItem*> selitems = gs->selectedItems();
// 			if(!selitems.empty()){
// 				SliceImagePane* otherpane = static_cast<SliceImagePane*>(selitems[0]);
// 				swap(*otherpane);
// 				gs->update();
// 			}
// 		}
// 		return;
// 	}	
}
