/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: jpgame.cpp 
CreateTime: 2019-6-24 19:08
=========================================================================*/
#include "jpgame.h"
#include "hangupstate.h"
#include "uiglo.h"
#include "gamescene.h"
#include "gameview.h"
#include "sliceimageitem.h"

JPGame::JPGame(QPixmap& srcimg)
	:curstate_(new HangUpState()),
	srcimage_(srcimg)
{
	splitImages();
	curstate_->enter();
}

JPGame::~JPGame()
{
	curstate_->exit();
}

void JPGame::splitImages()
{
	uint32_t colnum = 3, rownum = 3;
	uint32_t wholewidth = srcimage_.width();
	uint32_t wholeheight = srcimage_.height();
	uint32_t slicewidth = wholewidth / colnum;
	uint32_t sliceheight = wholeheight / rownum;
	for(uint32_t i = 0; i < rownum; ++i){
		for(uint32_t j = 0; j < colnum; ++j){
			uint32_t posx = j * slicewidth;
			uint32_t posy = i * sliceheight;
			QPixmap subimg = srcimage_.copy(posx, posy, slicewidth, sliceheight);

			imageboards_.push_back({subimg, 0, 0});
		}
	}
}

void JPGame::start()
{
	GameView* wp = GetGameView();

	double width = wp->width();
	double height = wp->height();

	GameScene* ws = new GameScene(-width / 2.0, -height / 2.0, width, height, nullptr);

	

	SliceImageItem* slice = new SliceImageItem();
	QPixmap img("11.jpg");
	slice->setImage(img);
	slice->setPos(0.0, 0.0);
	ws->addItem(slice);

	wp->setScene(ws);

	wp->show();
	wp->update();
}

void JPGame::handleEvent(uint32_t evttype)
{
	GameState* gs = curstate_->handleEvent(evttype);
	if(gs != nullptr){
		rtdelete(curstate_);
		curstate_ = gs;
		curstate_->enter();
	}
}