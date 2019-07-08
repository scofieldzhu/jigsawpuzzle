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
#include "glosignals.h"

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

void JPGame::generateResource()
{	
    GameView* gview = GetGameView();
    GameScene* gscene = gview->localScene();    
    double vwidth = gview->width();
    double vheight = gview->height();
    gscene->setSceneRect({-vwidth / 2.0, -vheight / 2.0, vwidth, vheight});    
	QSizeF scenesize = gscene->sceneRect().size();
	QPixmap gameimg = srcimage_.scaled(scenesize.width(), scenesize.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    gscene->setGameImage(gameimg);
	uint32_t kSubImgWidth = gameimg.width() / kGridCols_;
	uint32_t kSubImgHeight = gameimg.height() / kGridRows_;			
	auto randomnums = generateRandomNums(kGridCols_ * kGridRows_, 0);
	int32_t rnumindex = 0;
	for(int32_t i = 0; i < kGridRows_; ++i){
		for(int32_t j = 0; j < kGridCols_; ++j){			
			int32_t imgseq = randomnums[rnumindex++];
			int32_t imgseqx = imgseq / kGridCols_;
			int32_t imgseqy = imgseq - imgseqx * kGridCols_;
			const QPoint kImgSeqPos(imgseqx, imgseqy);
			QPixmap img = gameimg.copy(kImgSeqPos.y() * kSubImgWidth, kImgSeqPos.x() * kSubImgHeight, kSubImgWidth, kSubImgHeight);			
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

	if(textitem_ == nullptr){
		textitem_ = new QGraphicsTextItem(nullptr);
		gscene->addItem(textitem_);
		textitem_->setDefaultTextColor(Qt::red);
		QFont ft(QStringLiteral("Î¢ÈíÑÅºÚ"));
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
	generateResource();
    GameView* wp = GetGameView();	
	wp->show();
	wp->update();
	state_ = kPlayingState;
    imageswappedconn_ = SliceImageSwappedSignal::Inst().connect(boost::bind(&JPGame::handleSliceImageSwappedSignal, this, _1));
    GameStartedSignal::Inst().trigger(GameStartedEvent(*this));
}

void JPGame::pause()
{

}

void JPGame::shuffle()
{
	if(sliceimagepanes_.empty())
		return;
	GameScene* scene = GetGameScene();
	QPixmap& gameimg = scene->gameImage();
	const uint32_t kSubImgWidth = gameimg.width() / kGridCols_;
	const uint32_t kSubImgHeight = gameimg.height() / kGridRows_;
	auto randomnums = generateRandomNums(kGridCols_ * kGridRows_, 0);
	int32_t rnumindex = 0;	
	for(SliceImagePane* pane : sliceimagepanes_){
		int32_t imgseq = randomnums[rnumindex++];
		int32_t imgseqx = imgseq / kGridCols_;
		int32_t imgseqy = imgseq - imgseqx * kGridCols_;
		const QPoint kImgSeqPos(imgseqx, imgseqy);
		QPixmap img = gameimg.copy(kImgSeqPos.y() * kSubImgWidth, kImgSeqPos.x() * kSubImgHeight, kSubImgWidth, kSubImgHeight);
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

void JPGame::handleSliceImageSwappedSignal(const SliceImageSwappedEvent&)
{
    if(checkFinishFlag()){
        stop(kNormalStopped);
        showText(QObject::tr("Congratulations!"));
    }
}
