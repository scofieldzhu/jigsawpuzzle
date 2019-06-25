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
	GameScene(qreal x, qreal y, qreal width, qreal height, QObject* parent = nullptr);
	~GameScene();
};
#endif

