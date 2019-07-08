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
#include "glosignals.h"

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
    SliceImageSwappedSignal::Inst().trigger(SliceImageSwappedEvent());
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
 	double border = 0.0;
	if(operating_){
		border = 2.0;
		pen.setColor(Qt::red);
		pen.setWidth(border);
	}
 	QRectF newrt = boundrect;
 	QPointF newtf = newrt.topLeft();
 	newtf.rx() += border;
 	newtf.ry() += border;
 	newrt.setTopLeft(newtf);
   	QPointF newbr = newrt.bottomRight();
   	newbr.rx() -= border;
   	newbr.ry() -= border;
   	newrt.setBottomRight(newbr);
	painter->setPen(pen);
	painter->drawRect(newrt);
	painter->restore();
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
            GetGameScene()->update();
        }
	}
}