/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: gamescene.h 
CreateTime: 2019-6-21 21:40
=========================================================================*/
#ifndef __gamescene_h__
#define __gamescene_h__

#include <QGraphicsScene>

class GameScene : public QGraphicsScene
{
	Q_OBJECT
public:
    void setGameImage(QPixmap& pix) { gameimg_ = pix; }
    QPixmap& gameImage() { return gameimg_; }
	void setBackgroundImage(QPixmap& pix) { bkg_ = pix; }
	QPixmap& backgroundImage() { return bkg_; }
    GameScene(QObject *parent = Q_NULLPTR);
    GameScene(const QRectF &sceneRect, QObject *parent = Q_NULLPTR);
    GameScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = Q_NULLPTR);
	~GameScene();

private:
	void drawBackground(QPainter *painter, const QRectF &rect);
	QPixmap bkg_;
    QPixmap gameimg_;
};
#endif

