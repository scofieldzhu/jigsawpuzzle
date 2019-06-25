/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: gamescene.cpp 
CreateTime: 2019-6-21 21:40
=========================================================================*/
#include "gamescene.h"

GameScene::GameScene(qreal x, qreal y, qreal width, qreal height, QObject* parent /*= nullptr*/)
	:QGraphicsScene(x, y, width, height)
{}

GameScene::~GameScene()
{}
