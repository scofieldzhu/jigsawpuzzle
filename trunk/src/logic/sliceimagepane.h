/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: sliceimagepane.h 
CreateTime: 2019-6-21 22:15
=========================================================================*/
#ifndef __sliceimagepane_h__
#define __sliceimagepane_h__

#include <QGraphicsItem>

class SliceImagePane : public QGraphicsItem
{
public:
	void setImage(QPixmap& pix) { image_ = pix; }
	QPixmap& image() { return image_; }
	void setGridPos(const QPoint& pos);
	const QPoint& currentGridPos()const { return curgridpos_; }
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	SliceImagePane(QPixmap& slice, const QPoint& destgridpos);
	~SliceImagePane();

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
	QPixmap image_;
	QPoint curgridpos_;
	QPoint destgridpos_;
};

#endif
