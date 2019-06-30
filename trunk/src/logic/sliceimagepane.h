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
	void swap(SliceImagePane& pane); //swap image and grid position
	void setImage(QPixmap& pix) { image_ = pix; }
	QPixmap& image() { return image_; }
	void setGridPos(const QPoint& pos) { curgridpos_ = pos; }
	const QPoint& currentGridPos()const { return curgridpos_; }
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	const QPoint& destGridPos()const { return kDestGridPos_; }
	void setOperating(bool operating);
	bool operating()const { return operating_; }
	SliceImagePane(QPixmap& slice, const QPoint& destgridpos);
	~SliceImagePane();

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

private:
	QPixmap image_;
	QPoint curgridpos_;
	QPoint kDestGridPos_;
	bool operating_ = false;
};

#endif
