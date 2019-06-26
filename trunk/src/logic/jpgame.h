/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: jpgame.h 
CreateTime: 2019-6-24 19:08
=========================================================================*/
#ifndef __jpgame_h__
#define __jpgame_h__

#include <QPixmap>
#include "common.h"


class JPGame
{
public:
	void start();
	void shuffle();
	GameState* gameState() { return curstate_; }
	void handleEvent(uint32_t evttype);
	JPGame(QPixmap& srcimg);
	~JPGame();

private:
	void initGameResource();
	GameState* curstate_;
	QPixmap srcimage_;
	QList<SliceImagePane*> sliceimagepanes_;
};

#endif
