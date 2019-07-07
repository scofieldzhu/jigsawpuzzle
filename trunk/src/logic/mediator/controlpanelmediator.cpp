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
#include "gamescene.h"

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
    connect(ui_->originimgcb, SIGNAL(currentTextChanged(const QString&)), this, SLOT(handleOriginImageCurrentTextChanged(const QString&)));
	connect(ui_->startgametbtn, SIGNAL(released()), this, SLOT(handleStartGameBtnClicked()));
	connect(ui_->giveupbtn, SIGNAL(released()), this, SLOT(handleGiveUpBtnClicked()));
	connect(ui_->hintbtn, SIGNAL(released()), this, SLOT(handleHitBtnClicked()));
}

void ControlPanelMediator::unsubscribe()
{
}

void ControlPanelMediator::handleStartGameBtnClicked()
{
    if(GetActiveGame()){
        GetActiveGame()->stop();
        delete GetActiveGame();
    }
    QPixmap originimg(ui_->originimgcb->currentText());
	if(!originimg.isNull()){
        int index = ui_->difficultycb->currentIndex();
        QSize dim;
        if(index == 0){
            dim = {3, 3};
        } else if(index == 1){
            dim = {4, 4};
        } else{
            dim = {5, 5};
        }
		JPGame* newgame = new JPGame(originimg, dim.width(), dim.height());
		newgame->start();
        ui_->startgametbtn->setEnabled(false);
        ui_->giveupbtn->setEnabled(true);
        ui_->hintbtn->setEnabled(true);
	}	
}

void ControlPanelMediator::handleGiveUpBtnClicked()
{
    if(GetActiveGame()){
        GetActiveGame()->stop();
        ui_->startgametbtn->setEnabled(true);
    }
}

void ControlPanelMediator::handleOriginImageCurrentTextChanged(const QString&)
{
    handleGiveUpBtnClicked();
    QPixmap originimg(ui_->originimgcb->currentText());
    GetGameScene()->setBackgroundImage(originimg);
    GetGameScene()->update();
}

void ControlPanelMediator::handleHitBtnClicked()
{
	if(GetActiveGame())
		GetActiveGame()->showOriginImage(true);
}
