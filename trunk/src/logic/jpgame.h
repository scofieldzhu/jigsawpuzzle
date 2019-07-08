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
#include "glosignals.h"

class QGraphicsTextItem;
class JPGame
{
public:
	void start();
	void pause();
	void shuffle();
	void stop(GameStoppedReason reason);
	GameState state()const { return state_; }
    bool isStarted()const{ return state_ != kStoppedState; }
	void setOperatingImagePane(SliceImagePane* pane);
	SliceImagePane* operatingImagePane();
	void showOriginImage(bool toggled);
	void showText(const QString& text);
	void hideText();
	bool checkFinishFlag()const;
	JPGame(QPixmap& srcimg, uint32_t rows, uint32_t cols);
	~JPGame();

private:
    void handleSliceImageSwappedSignal(const SliceImageSwappedEvent&);
	std::vector<int32_t> generateRandomNums(uint32_t cnt, int32_t min);
	void generateResource();
	GameState state_ = kStoppedState;
	QPixmap srcimage_;
	uint32_t kGridRows_, kGridCols_;
	QList<SliceImagePane*> sliceimagepanes_;
	QGraphicsTextItem* textitem_ = nullptr;
    SliceImageSwappedSignal::SigCon imageswappedconn_;
};

#endif
