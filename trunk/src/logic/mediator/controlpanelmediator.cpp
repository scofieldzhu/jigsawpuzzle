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
#include "gamescene.h"
#include "gameview.h"
#include "sliceimageitem.h"

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
	connect(ui_->showoriginimgbtn, SIGNAL(released()), this, SLOT(handleShowOriginImgBtnClicked()));
}

void ControlPanelMediator::unsubscribe()
{
}

void ControlPanelMediator::handleStartGameBtnClicked()
{
	
}

void ControlPanelMediator::handleNextGameBtnClicked()
{
	QMessageBox msgbox(QMessageBox::Information, "tip dialog", "next game!", QMessageBox::NoButton, GetMainWindow());
	msgbox.exec();
}

void ControlPanelMediator::handleShowOriginImgBtnClicked()
{
	QMessageBox msgbox(QMessageBox::Information, "tip dialog", "show origin image!", QMessageBox::NoButton, GetMainWindow());
	msgbox.exec();
}
