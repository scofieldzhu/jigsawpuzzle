/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: gameview.cpp 
CreateTime: 2019-6-21 21:38
=========================================================================*/
#include "gameview.h"
#include "gamescene.h"

GameView::GameView(GameScene* scene, QWidget* parent)
	:QGraphicsView(scene, parent)
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

GameView::~GameView()
{}

GameScene* GameView::localScene()
{
	return qobject_cast<GameScene*>(scene());
}