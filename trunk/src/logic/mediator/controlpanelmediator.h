/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: controlpanelmediator.h 
CreateTime: 2019-6-20 21:17
=========================================================================*/
#ifndef __controlpanelmediator_h__
#define __controlpanelmediator_h__

#include <QObject>
#include "uimediator.hxx"
#include "glosignals.h"

class QSound;
class QTimer;
class AnimateSplash;
class ControlPanel;
class ControlPanelMediator : public QObject, public RATEL::UIMediator<ControlPanel>
{
	Q_OBJECT
public:
    void initAppUI();
	void subscribeEvents();
	void unsubscribe();
	ControlPanelMediator(ControlPanel* ui);
	~ControlPanelMediator();

private slots:
	void handleStartGameBtnClicked();
	void handleGiveUpBtnClicked();
	void handleHitBtnClicked();
    void handleOriginImageCurrentTextChanged(const QString&);
    void handleTimerOut();

private:
    void collectImageFiles();
    void handleGameStartedSignal(const GameStartedEvent&);
    void handleGameStoppedSignal(const GameStoppedEvent&);
    void handleGameHintTimeOutSignal(const GameHintTimeOutEvent&);
    void handleUpdateClockSignal(const GameClockUpdateEvent&);
    RATEL::SignalCon startedconn_;
    RATEL::SignalCon stoppedconn_;
    RATEL::SignalCon hinttimeoutconn_;
    RATEL::SignalCon updateclockconn_;    
    QTimer* animation_play_timer_ = nullptr;
    AnimateSplash* success_player_ = nullptr;
    QSound* success_sound_player_ = nullptr;
    AnimateSplash* fail_player_ = nullptr;
    QSound* cry_sound_player_ = nullptr;
};

#endif
