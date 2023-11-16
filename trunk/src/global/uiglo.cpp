/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: uiglo.cpp 
CreateTime: 2019-6-20 21:39
=========================================================================*/
#include "uiglo.h"
#include <QApplication>
#include <QScreen>
#include "appsession.h"
#include "mainwindow.h"
#include "clientview.h"
#include "gameview.h"
#include "animatesplash.h"

MainWindow* GetMainWindow()
{
	return GetAppSession()->mainWindow();
}

ClientView* GetClientView()
{
	return GetMainWindow()->clientView(); 
}

GameView* GetGameView()
{
	return GetMainWindow()->clientView()->gameView();
}

GameScene* GetGameScene()
{
	return GetGameView()->localScene();
}

AnimateSplash* gPlayingSplash = nullptr;

void PlayAnimation(const QString& gif_path)
{
    if(gPlayingSplash)
        StopPlayAnimation();    
    QPixmap main_snapshot = QApplication::primaryScreen()->grabWindow(GetMainWindow()->winId());
    gPlayingSplash = new AnimateSplash(gif_path, GetMainWindow());
    gPlayingSplash->setBackgroudImage(main_snapshot);
    gPlayingSplash->setGeometry({0, 0, GetMainWindow()->width(), GetMainWindow()->height()});
    gPlayingSplash->show();
}

void StopPlayAnimation()
{
    if(gPlayingSplash){
        gPlayingSplash->hide();
        delete gPlayingSplash;
        gPlayingSplash = nullptr;
    }
}
