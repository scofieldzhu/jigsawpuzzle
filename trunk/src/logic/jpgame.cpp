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
{
	SetActiveGame(nullptr);
}

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
	scene->setBackgroundImage(bestfitimg);	
	uint32_t kSubImgWidth = bestfitimg.width() / kGridCols_;
	uint32_t kSubImgHeight = bestfitimg.height() / kGridRows_;			
	auto randomnums = generateRandomNums(kGridCols_ * kGridRows_, 0);
	int32_t rnumindex = 0;
	for(int32_t i = 0; i < kGridRows_; ++i){
		for(int32_t j = 0; j < kGridCols_; ++j){			
			int32_t imgseq = randomnums[rnumindex++];
			int32_t imgseqx = imgseq / kGridCols_;
			int32_t imgseqy = imgseq - imgseqx * kGridCols_;
			const QPoint kImgSeqPos(imgseqx, imgseqy);
			QPixmap img = bestfitimg.copy(kImgSeqPos.y() * kSubImgWidth, kImgSeqPos.x() * kSubImgHeight, kSubImgWidth, kSubImgHeight);			
			const QPoint kDestImgSeqPos(i, j);
			SliceImagePane* imgpane = new SliceImagePane(img, kDestImgSeqPos);
			scene->addItem(imgpane);			
			imgpane->setGridPos(kImgSeqPos);		
			QPointF scenepos = scene->sceneRect().topLeft();			
			scenepos.rx() += (kDestImgSeqPos.y() + 0.5) * kSubImgWidth;
			scenepos.ry() += (kDestImgSeqPos.x() + 0.5) * kSubImgHeight;
			imgpane->setPos(scenepos);
			sliceimagepanes_.push_back(imgpane);
		}
	}

	if(textitem_ == nullptr){
		textitem_ = new QGraphicsTextItem(nullptr);
		scene->addItem(textitem_);
		textitem_->setDefaultTextColor(Qt::red);
		QFont ft(QStringLiteral("΢���ź�"));
		ft.setPixelSize(30);
		ft.setStyle(QFont::StyleNormal);
		ft.setBold(true);
		textitem_->setFont(ft);
		textitem_->setPos({-100.0, -100.0});
		textitem_->setVisible(false);
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
	state_ = kPlayingState;
}

void JPGame::pause()
{

}

void JPGame::shuffle()
{
	if(sliceimagepanes_.empty())
		return;
	GameScene* scene = GetGameScene();
	QPixmap& bestfitimg = scene->backgroundImage();
	const uint32_t kSubImgWidth = bestfitimg.width() / kGridCols_;
	const uint32_t kSubImgHeight = bestfitimg.height() / kGridRows_;
	auto randomnums = generateRandomNums(kGridCols_ * kGridRows_, 0);
	int32_t rnumindex = 0;	
	for(SliceImagePane* pane : sliceimagepanes_){
		int32_t imgseq = randomnums[rnumindex++];
		int32_t imgseqx = imgseq / kGridCols_;
		int32_t imgseqy = imgseq - imgseqx * kGridCols_;
		const QPoint kImgSeqPos(imgseqx, imgseqy);
		QPixmap img = scene->backgroundImage().copy(kImgSeqPos.y() * kSubImgWidth, kImgSeqPos.x() * kSubImgHeight, kSubImgWidth, kSubImgHeight);
		pane->setImage(img);
		pane->setGridPos({imgseqx, imgseqy});		
	}
	scene->update();
}

void JPGame::stop()
{
	GameScene* scene = GetGameScene();
	for(auto pane : sliceimagepanes_)
		scene->removeItem(pane);
	sliceimagepanes_.clear();
	state_ = kStoppedState;
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

void JPGame::showOriginImage(bool toggled)
{
	for(auto pane : sliceimagepanes_)
		pane->setVisible(!toggled);
}

void JPGame::showText(const QString& text)
{
	if(textitem_){
		textitem_->setPlainText(text);
		textitem_->setVisible(true);
	}
}

void JPGame::hideText()
{
	if(textitem_)
		textitem_->setVisible(false);
}

bool JPGame::checkFinishFlag() const
{
	for(auto pane : sliceimagepanes_){
		if(pane->currentGridPos() != pane->destGridPos())
			return false;
	}
	return true;
}
