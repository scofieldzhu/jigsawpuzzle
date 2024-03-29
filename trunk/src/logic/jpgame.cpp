/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: jpgame.cpp 
CreateTime: 2019-6-24 19:08
=========================================================================*/
#include "jpgame.h"
#include <QTimer>
#include <random>
#include "uiglo.h"
#include "gamescene.h"
#include "gameview.h"
#include "sliceimagepane.h"
#include "glosignals.h"
#include "animatesplash.h"
#include "mainwindow.h"
#include "applogger.h"

JPGame::JPGame(const GameConfig& conf)
	:QObject(nullptr),
    config_(conf),
    timer_(new QTimer(this)),
    clocktimer_(new QTimer(this))
{
	SetActiveGame(this);        
    connect(timer_, SIGNAL(timeout()), this, SLOT(handleTimeOut()));
    connect(clocktimer_, SIGNAL(timeout()), this, SLOT(handleClockTimeout()));
}

JPGame::~JPGame()
{
	SetActiveGame(nullptr);
}

std::vector<int32_t> JPGame::generateRandomNums(uint32_t cnt, int32_t min)
{
	std::vector<int32_t> resultnums(cnt, 0);
	std::generate(resultnums.begin(), resultnums.end(), [n = min]() mutable { return n++; });
    std::shuffle(resultnums.begin(), resultnums.end(), std::random_device());
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
	uint32_t kSubImgWidth = curgameimage_.width() / config_.level.gridcols;
	uint32_t kSubImgHeight = curgameimage_.height() / config_.level.gridrows;			
	auto randomnums = generateRandomNums(config_.level.gridrows * config_.level.gridcols, 0);
	int32_t rnumindex = 0;
	for(int32_t i = 0; i < config_.level.gridrows; ++i){
		for(int32_t j = 0; j < config_.level.gridcols; ++j){			
			int32_t imgseq = randomnums[rnumindex++];
			int32_t imgseqx = imgseq / config_.level.gridcols;
			int32_t imgseqy = imgseq - imgseqx * config_.level.gridcols;
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
    showSliceImagePanes(false);
    GetMainWindow()->update();
    GetMainWindow()->show();
    
    if(animation_player_ == nullptr){
        const QString& gif_path = "res/image/count-down-3s.gif";
        animation_player_ = new AnimateSplash(gif_path, GetMainWindow());
        if(!animation_player_->isValid()){
            slog_err(applogger) << "Invalid animation image file:" << gif_path.toLocal8Bit().toStdString().c_str() << endl;
            delete animation_player_;
            return;
        }
    }
    animation_player_->start();
    timer_->start(1000);
    currenttimertype_ = kStartUp;
    currentremainsecs_ = 3;/*config_.level.startseconds*/;
}

void JPGame::handleTimeOut()
{
    if(currenttimertype_ == kStartUp){
        --currentremainsecs_;
        //GetGameScene()->showNotice(QString::number(currentremainsecs_));
        if(currentremainsecs_ <= 0){ //record game cost time start
            //GetGameScene()->hideNotice();
            animation_player_->stop();
            remainhintcount_ = config_.level.hintcount;
            timer_->stop();
            state_ = kPlayingState;            
            loadGame();            
        }
    }else if(currenttimertype_ == kHint){
        --currentremainsecs_;
        GetGameScene()->showNotice(QString::number(currentremainsecs_));
        if(currentremainsecs_ <= 0){ 
            GetGameScene()->hideNotice();
            showSliceImagePanes(true);            
            timer_->stop();
            GameHintTimeOutSignal::Inst().trigger(GameHintTimeOutEvent(*this, remainhintcount_ == 0));
        }
    }
}

void JPGame::handleClockTimeout()
{
    GameClockUpdateEvent event(*this, (::GetTickCount() - starttickcount_) / 1000);
    GameClockUpdateSignal::Inst().trigger(event);
}

void JPGame::loadGame()
{
    generateResource();    
    imageswappedconn_ = SliceImageSwappedSignal::Inst().connect(boost::bind(&JPGame::handleSliceImageSwappedSignal, this, _1));
    GameStartedSignal::Inst().trigger(GameStartedEvent(*this));
    clocktimer_->start(300);
    starttickcount_ = ::GetTickCount();    
}

void JPGame::pause()
{

}

void JPGame::shuffle()
{
	if(sliceimagepanes_.empty())
		return;
	GameScene* scene = GetGameScene();
	const uint32_t kSubImgWidth = curgameimage_.width() / config_.level.gridcols;
	const uint32_t kSubImgHeight = curgameimage_.height() / config_.level.gridrows;
	auto randomnums = generateRandomNums(config_.level.gridrows * config_.level.gridcols, 0);
	int32_t rnumindex = 0;	
	for(SliceImagePane* pane : sliceimagepanes_){
		int32_t imgseq = randomnums[rnumindex++];
		int32_t imgseqx = imgseq / config_.level.gridcols;
		int32_t imgseqy = imgseq - imgseqx * config_.level.gridcols;
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
        timer_->stop();
        currenttimertype_ = kNone;
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

void JPGame::showSliceImagePanes(bool visible)
{
	for(auto pane : sliceimagepanes_)
		pane->setVisible(visible);
}

void JPGame::hintOnce()
{    
    if(remainhintcount_ > 0){
        showSliceImagePanes(false);
        currenttimertype_ = kHint;
        timer_->start(1000);
        currentremainsecs_ = config_.level.hintseconds;
        --remainhintcount_;        
    }    
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
    if(checkFinishFlag()){
        stop(kNormalStopped);
    }        
}
