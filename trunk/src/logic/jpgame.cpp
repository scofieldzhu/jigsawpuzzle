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
#include "sliceimagepane.h"

JPGame::JPGame(QPixmap& srcimg)
	:curstate_(new HangUpState()),
	srcimage_(srcimg)
{
	curstate_->enter();
}

JPGame::~JPGame()
{
	curstate_->exit();
}

void JPGame::initGameResource()
{
	GameScene* scene = GetGameScene();
	QRectF scenerect = scene->sceneRect();
	QSizeF scenesize = scenerect.size();
	uint32_t colnum = 3, rownum = 3;
	QPixmap bestfitimg = srcimage_.scaled(scenesize.width(), scenesize.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	uint32_t srcimgwidth = bestfitimg.width();
	uint32_t srcimgheight = bestfitimg.height();	
	uint32_t srcsubimgwidth = srcimgwidth / colnum;
	uint32_t srcsubimgheight = srcimgheight / rownum;	
	uint32_t dstpanewidth = scenesize.width() / colnum;
	uint32_t dstpaneheight = scenesize.height() / rownum;
	QPointF startscenepos = scenerect.topLeft();

	//generate random sequence
	std::vector<int32_t> randomnums(colnum * rownum, 0);
	std::generate(randomnums.begin(), randomnums.end(), [n = 0]() mutable { return n++; });
	std::random_shuffle(randomnums.begin(), randomnums.end());
	int32_t rnumindex = 0;
	for (int32_t i = 0; i < rownum; ++i){
		for (int32_t j = 0; j < colnum; ++j){
			uint32_t imgposx = j * srcsubimgwidth;
			uint32_t imgposy = i * srcsubimgheight;
			QPixmap subimg = bestfitimg.copy(imgposx, imgposy, srcsubimgwidth, srcsubimgheight);			
			SliceImagePane* imgpane = new SliceImagePane(subimg, {i, j});
			scene->addItem(imgpane);
			int32_t noseq = randomnums[rnumindex++];
			int32_t noseqx = noseq / colnum;
			int32_t noseqy = noseq - noseqx * colnum;
			imgpane->setGridPos({noseqx, noseqy});		
			sliceimagepanes_.push_back(imgpane);
		}
	}
}

void JPGame::start()
{
	GameView* wp = GetGameView();
	double width = wp->width();
	double height = wp->height();
	GameScene* ws = new GameScene(-width / 2.0, -height / 2.0, width, height, nullptr);	
	wp->setScene(ws);
	initGameResource();
	wp->show();
	wp->update();
}

void JPGame::shuffle()
{
	if(sliceimagepanes_.empty())
		return;
	uint32_t colnum = 3, rownum = 3;
	std::vector<int32_t> randomnums(colnum * rownum, 0);
	std::generate(randomnums.begin(), randomnums.end(), [n = 0]() mutable { return n++; });
	std::random_shuffle(randomnums.begin(), randomnums.end());
	int32_t rnumindex = 0;
	for(SliceImagePane* pane : sliceimagepanes_){
		int32_t noseq = randomnums[rnumindex++];
		int32_t noseqx = noseq / colnum;
		int32_t noseqy = noseq - noseqx * colnum;
		pane->setGridPos({noseqx, noseqy});
	}
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