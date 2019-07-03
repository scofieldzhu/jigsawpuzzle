/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: gameview.h 
CreateTime: 2019-6-21 21:38
=========================================================================*/
#ifndef __gameview_h__
#define __gameview_h__

#include <QGraphicsView>

class GameScene;
class GameView : public QGraphicsView
{
	Q_OBJECT
public:
	GameScene* localScene();
	GameView(GameScene* scene, QWidget* parent = nullptr);
	~GameView();

	virtual void drawBackground(QPainter *painter, const QRectF &rect);
	virtual void drawForeground(QPainter *painter, const QRectF &rect);
};

#endif