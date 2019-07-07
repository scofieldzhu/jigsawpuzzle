/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: controlpanelmediator.cpp 
CreateTime: 2019-6-20 21:17
=========================================================================*/
#include "controlpanelmediator.h"
#include <QPushButton>
#include <QComboBox>
#include "controlpanel.h"
#include "uiglo.h"
#include "mainwindow.h"
#include "jpgame.h"

ControlPanelMediator::ControlPanelMediator(ControlPanel* ui)
	:QObject(ui),
	MediatorSelf(ui)
{
}

ControlPanelMediator::~ControlPanelMediator()
{
	unsubscribe();
}

void ControlPanelMediator::subscribeEvents()
{
	connect(ui_->startgametbtn, SIGNAL(released()), this, SLOT(handleStartGameBtnClicked()));
	connect(ui_->giveupbtn, SIGNAL(released()), this, SLOT(handleGiveUpBtnClicked()));
	connect(ui_->hintbtn, SIGNAL(released()), this, SLOT(handleHitBtnClicked()));
}

void ControlPanelMediator::unsubscribe()
{
}

void ControlPanelMediator::handleStartGameBtnClicked()
{
    QPixmap originimg(ui_->originimgcb->currentText());
	if(!originimg.isNull()){
		JPGame* newgame = new JPGame(originimg, 3, 3);
		newgame->start();
	}	
}

void ControlPanelMediator::handleGiveUpBtnClicked()
{
	if(GetActiveGame())
		GetActiveGame()->stop();
}

void ControlPanelMediator::handleHitBtnClicked()
{
	if(GetActiveGame())
		GetActiveGame()->showOriginImage(true);
}
