/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: jpgame.cpp 
CreateTime: 2019-6-24 19:08
=========================================================================*/
#include "jpgame.h"
#include "uiglo.h"
#include "gamescene.h"
#include "gameview.h"
#include "sliceimagepane.h"

JPGame::JPGame(QPixmap& srcimg, uint32_t rows, uint32_t cols)
	:srcimage_(srcimg),
	kGridRows_(rows),
	kGridCols_(cols)
{
	SetActiveGame(this);
}

JPGame::~JPGame()
{}

std::vector<int32_t> JPGame::generateRandomNums(uint32_t cnt, int32_t min)
{
	std::vector<int32_t> resultnums(cnt, 0);
	std::generate(resultnums.begin(), resultnums.end(), [n = min]() mutable { return n++; });
	std::random_shuffle(resultnums.begin(), resultnums.end());
	return resultnums;
}

void JPGame::initGameResource()
{
	GameScene* scene = GetGameScene();
	QSizeF scenesize = scene->sceneRect().size();
	QPixmap bestfitimg = srcimage_.scaled(scenesize.width(), scenesize.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	uint32_t srcimgwidth = bestfitimg.width();
	uint32_t srcimgheight = bestfitimg.height();	
	uint32_t subimgwidth = srcimgwidth / kGridCols_;
	uint32_t subimgheight = srcimgheight / kGridRows_;			
	auto randomnums = generateRandomNums(kGridCols_ * kGridRows_, 0);
	int32_t rnumindex = 0;
	for (int32_t i = 0; i < kGridRows_; ++i){
		for (int32_t j = 0; j < kGridCols_; ++j){			
			QPixmap subimg = bestfitimg.copy(j * subimgwidth, i * subimgheight, subimgwidth, subimgheight);			
			SliceImagePane* imgpane = new SliceImagePane(subimg, {i, j});
			scene->addItem(imgpane);
			int32_t noseq = randomnums[rnumindex++];
			int32_t noseqx = noseq / kGridCols_;
			int32_t noseqy = noseq - noseqx * kGridCols_;
			const QPoint gpos(noseqx, noseqy);
			imgpane->setGridPos(gpos);		
			QPointF newpos = scene->sceneRect().topLeft();
			newpos.rx() += (gpos.y() + 0.5) * subimgwidth;
			newpos.ry() += (gpos.x() + 0.5) * subimgheight;
			imgpane->setPos(newpos);
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

void JPGame::pause()
{

}

void JPGame::shuffle()
{
	if(sliceimagepanes_.empty())
		return;
	auto randomnums = generateRandomNums(kGridCols_ * kGridRows_, 0);
	int32_t rnumindex = 0;
	for(SliceImagePane* pane : sliceimagepanes_){
		int32_t noseq = randomnums[rnumindex++];
		int32_t noseqx = noseq / kGridCols_;
		int32_t noseqy = noseq - noseqx * kGridCols_;
		pane->setGridPos({noseqx, noseqy});
	}
}

void JPGame::setOperatingImagePane(SliceImagePane* pane)
{
	for(SliceImagePane* p : sliceimagepanes_)
		p->setOperating(p == pane);
	GetGameScene()->update();
}

SliceImagePane* JPGame::operatingImagePane()
{
	auto it = std::find_if(sliceimagepanes_.begin(), sliceimagepanes_.end(), [](const SliceImagePane* p){return p->operating();});
	return it == sliceimagepanes_.end() ? nullptr : *it;
}
