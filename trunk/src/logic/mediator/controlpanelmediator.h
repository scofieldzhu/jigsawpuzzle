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

class ControlPanel;
class ControlPanelMediator : public QObject, public UIMediator<ControlPanel>
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

private:
    void collectImageFiles();
    void handleGameStartedSignal(const GameStartedEvent&);
    void handleGameStoppedSignal(const GameStoppedEvent&);
    void handleGameHintTimeOutSignal(const GameHintTimeOutEvent&);
    void handleUpdateClockSignal(const GameClockUpdateEvent&);
    SignalCon startedconn_;
    SignalCon stoppedconn_;
    SignalCon hinttimeoutconn_;
    SignalCon updateclockconn_;
};

#endif
