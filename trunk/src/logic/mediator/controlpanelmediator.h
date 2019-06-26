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

class JPGame;
class ControlPanel;
class ControlPanelMediator : public QObject, public UIMediator<ControlPanel>
{
	Q_OBJECT
public:
	void subscribeEvents();
	void unsubscribe();
	ControlPanelMediator(ControlPanel* ui);
	~ControlPanelMediator();

private slots:
	void handleStartGameBtnClicked();
	void handleNextGameBtnClicked();
	void handleShowOriginImgBtnClicked();

private:
	JPGame* activegame_ = nullptr;
};

#endif
