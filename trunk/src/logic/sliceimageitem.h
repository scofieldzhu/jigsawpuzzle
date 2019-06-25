/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: sliceimageitem.h 
CreateTime: 2019-6-21 22:15
=========================================================================*/
#ifndef __sliceimageitem_h__
#define __sliceimageitem_h__

#include <QGraphicsItem>

class SliceImageItem : public QGraphicsItem
{
public:
	void setImage(QPixmap& pix) { image_ = pix; }
	QPixmap& image() { return image_; }
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	SliceImageItem();
	~SliceImageItem();

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
	QPixmap image_;
};

#endif
