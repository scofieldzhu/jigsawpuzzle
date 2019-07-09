/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: jpgame.cpp 
CreateTime: 2019-6-24 19:08
=========================================================================*/
#include "jpgame.h"
#include <QTimer>
#include "uiglo.h"
#include "gamescene.h"
#include "gameview.h"
#include "sliceimagepane.h"
#include "glosignals.h"

JPGame::JPGame(const GameConfig& conf)
	:QObject(nullptr),
    config_(conf),
    timer_(new QTimer(this))
{
	SetActiveGame(this);        
    connect(timer_, SIGNAL(timeout()), this, SLOT(handleTimeOut()));
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

void JPGame::generateResource()
{	
    GameView* gview = GetGameView();
    GameScene* gscene = gview->localScene();    
    double vwidth = gview->width();
    double vheight = gview->height();
    gscene->setSceneRect({-vwidth / 2.0, -vheight / 2.0, vwidth, vheight});    
	QSizeF scenesize = gscene->sceneRect().size();
	curgameimage_ = config_.originimage.scaled(scenesize.width(), scenesize.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	uint32_t kSubImgWidth = curgameimage_.width() / config_.gridcols;
	uint32_t kSubImgHeight = curgameimage_.height() / config_.gridrows;			
	auto randomnums = generateRandomNums(config_.gridrows * config_.gridcols, 0);
	int32_t rnumindex = 0;
	for(int32_t i = 0; i < config_.gridrows; ++i){
		for(int32_t j = 0; j < config_.gridcols; ++j){			
			int32_t imgseq = randomnums[rnumindex++];
			int32_t imgseqx = imgseq / config_.gridcols;
			int32_t imgseqy = imgseq - imgseqx * config_.gridcols;
			const QPoint kImgSeqPos(imgseqx, imgseqy);
			QPixmap img = curgameimage_.copy(kImgSeqPos.y() * kSubImgWidth, kImgSeqPos.x() * kSubImgHeight, kSubImgWidth, kSubImgHeight);			
			const QPoint kDestImgSeqPos(i, j);
			SliceImagePane* imgpane = new SliceImagePane(img, kDestImgSeqPos);
			gscene->addItem(imgpane);			
			imgpane->setGridPos(kImgSeqPos);		
			QPointF scenepos = gscene->sceneRect().topLeft();			
			scenepos.rx() += (kDestImgSeqPos.y() + 0.5) * kSubImgWidth;
			scenepos.ry() += (kDestImgSeqPos.x() + 0.5) * kSubImgHeight;
			imgpane->setPos(scenepos);
			sliceimagepanes_.push_back(imgpane);
		}
	}
}

void JPGame::start()
{	
    timer_->start(1000);
    currenttimertype_ = kStartUp;
    currentremainsecs_ = config_.startupseconds;	    
    state_ = kPlayingState;
    imageswappedconn_ = SliceImageSwappedSignal::Inst().connect(boost::bind(&JPGame::handleSliceImageSwappedSignal, this, _1));
    GameStartedSignal::Inst().trigger(GameStartedEvent(*this));
}

void JPGame::handleTimeOut()
{
    if(currenttimertype_ == kStartUp){
        --currentremainsecs_;
        GetGameScene()->showNotice(QString::number(currentremainsecs_));
        if(currentremainsecs_ <= 0){ //record game cost time start
            GetGameScene()->hideNotice();
            generateResource();
            timer_->stop();            
        }
    }else if(currenttimertype_ == kHint){

    }
}

void JPGame::pause()
{

}

void JPGame::shuffle()
{
	if(sliceimagepanes_.empty())
		return;
	GameScene* scene = GetGameScene();
	const uint32_t kSubImgWidth = curgameimage_.width() / config_.gridcols;
	const uint32_t kSubImgHeight = curgameimage_.height() / config_.gridrows;
	auto randomnums = generateRandomNums(config_.gridrows * config_.gridcols, 0);
	int32_t rnumindex = 0;	
	for(SliceImagePane* pane : sliceimagepanes_){
		int32_t imgseq = randomnums[rnumindex++];
		int32_t imgseqx = imgseq / config_.gridcols;
		int32_t imgseqy = imgseq - imgseqx * config_.gridcols;
		const QPoint kImgSeqPos(imgseqx, imgseqy);
		QPixmap img = curgameimage_.copy(kImgSeqPos.y() * kSubImgWidth, kImgSeqPos.x() * kSubImgHeight, kSubImgWidth, kSubImgHeight);
		pane->setImage(img);
		pane->setGridPos({imgseqx, imgseqy});		
	}
	scene->update();
}

void JPGame::stop(GameStoppedReason reason)
{
    if(state_ != GameState::kStoppedState){
        GameScene* scene = GetGameScene();
        for(auto pane : sliceimagepanes_){
            scene->removeItem(pane);
            rtdelete(pane); //free memory
        }
        sliceimagepanes_.clear();
        state_ = kStoppedState;
        imageswappedconn_.disconnect();
        GameStoppedSignal::Inst().trigger(GameStoppedEvent(*this, reason));
    }	
}

void JPGame::setOperatingImagePane(SliceImagePane* pane)
{
	for(SliceImagePane* p : sliceimagepanes_) //exclusive operation
		p->setOperating(p == pane);
	GetGameScene()->update();
}

SliceImagePane* JPGame::operatingImagePane()
{
	auto it = std::find_if(sliceimagepanes_.begin(), sliceimagepanes_.end(), [](const SliceImagePane* p){return p->operating();});
	return it == sliceimagepanes_.end() ? nullptr : *it;
}

void JPGame::showGameImage(bool toggled)
{
	for(auto pane : sliceimagepanes_)
		pane->setVisible(!toggled);
}

void JPGame::hintOnce()
{

}

bool JPGame::checkFinishFlag() const
{
	for(auto pane : sliceimagepanes_){
		if(pane->currentGridPos() != pane->destGridPos())
			return false;
	}
	return true;
}

void JPGame::handleSliceImageSwappedSignal(const SliceImageSwappedEvent&)
{
    if(checkFinishFlag())
        stop(kNormalStopped);
}
