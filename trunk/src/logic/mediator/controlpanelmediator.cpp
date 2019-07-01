/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: controlpanelmediator.cpp 
CreateTime: 2019-6-20 21:17
=========================================================================*/
#include "controlpanelmediator.h"
#include <QPushButton>
#include <QMessageBox>
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
	connect(ui_->nextgamebtn, SIGNAL(released()), this, SLOT(handleNextGameBtnClicked()));
	connect(ui_->showoriginimgbtn, SIGNAL(toggled(bool)), this, SLOT(handleShowOriginImgBtnClicked(bool)));
}

void ControlPanelMediator::unsubscribe()
{
}

void ControlPanelMediator::handleStartGameBtnClicked()
{
	QPixmap bkgimg("111.jpg");
	if(!bkgimg.isNull()){
		JPGame* newgame = new JPGame(bkgimg, 3, 3);
		newgame->start();
	}	
}

void ControlPanelMediator::handleNextGameBtnClicked()
{
	if(GetActiveGame())
		GetActiveGame()->shuffle();
}

void ControlPanelMediator::handleShowOriginImgBtnClicked(bool chk)
{
	if(GetActiveGame())
		GetActiveGame()->showOriginImage(chk);
}
