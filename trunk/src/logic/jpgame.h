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
#include "glosignals.h"
#include "gameconfig.h"

class QTimer;
class QGraphicsTextItem;
class JPGame : public QObject
{
    Q_OBJECT
public:
	void start();
	void pause();
	void shuffle();
	void stop(GameStoppedReason reason);
	GameState state()const { return state_; }
    bool isStarted()const{ return state_ != kStoppedState; }
	void setOperatingImagePane(SliceImagePane* pane);
	SliceImagePane* operatingImagePane();
	void showSliceImagePanes(bool visible);	
    void hintOnce();
	bool checkFinishFlag()const;
	JPGame(const GameConfig& conf);
	~JPGame();

private slots:
    void handleTimeOut();

private:
    void loadGame();
    void handleSliceImageSwappedSignal(const SliceImageSwappedEvent&);
	std::vector<int32_t> generateRandomNums(uint32_t cnt, int32_t min);
	void generateResource();
	GameState state_ = kStoppedState;
	QList<SliceImagePane*> sliceimagepanes_;
    SignalCon imageswappedconn_;
    GameConfig config_;
    QPixmap curgameimage_;
    QTimer* timer_;
    enum TimerType
    {
        kNone,
        kStartUp,
        kHint
    };
    int32_t currentremainsecs_ = 0;
    TimerType currenttimertype_ = kNone;
    int32_t remainhintcount_ = 0;
};

#endif
