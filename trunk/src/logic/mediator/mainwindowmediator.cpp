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
#include "clientview.h"
#include "gameview.h"

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
	QPixmap originimg(ui_->ctrlPanel()->originimgcb->currentText());
	originimg.save("xx.jpg");
	QBrush bkgbrush(originimg);
	GameView* gview = ui_->clientView()->gameView();
	gview->setBackgroundBrush(bkgbrush);	
	gview->setCacheMode(QGraphicsView::CacheBackground);
	gview->invalidateScene();
	gview->update();
}