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
	void pause();
	void shuffle();
	GameState state()const { return state_; }
	JPGame(QPixmap& srcimg, uint32_t rows, uint32_t cols);
	~JPGame();

private:
	std::vector<int32_t> generateRandomNums(uint32_t cnt, int32_t min);
	void initGameResource();
	GameState state_ = kStoppedState;
	QPixmap srcimage_;
	uint32_t kGridRows_, kGridCols_;
	QList<SliceImagePane*> sliceimagepanes_;
};

#endif
