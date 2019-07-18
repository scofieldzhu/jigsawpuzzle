/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: mainwindowmediator.cpp 
CreateTime: 2019-7-3 21:26
=========================================================================*/
#include "mainwindowmediator.h"
#include <QComboBox>
#include "mainwindow.h"
#include "controlpanel.h"
#include "controlpanelmediator.h"
#include "gamescene.h"
#include "gameview.h"
#include "uiglo.h"

MainWindowMediator::MainWindowMediator(MainWindow* ui)
	:QObject(ui),
	MediatorSelf(ui)
{
}

MainWindowMediator::~MainWindowMediator()
{
	unsubscribe();
}

void MainWindowMediator::subscribeEvents()
{}

void MainWindowMediator::unsubscribe()
{}

void MainWindowMediator::initAppUI()
{
    ui_->ctrlPanel()->mediator->initAppUI();	
}