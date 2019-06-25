/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: uiglo.cpp 
CreateTime: 2019-6-20 21:39
=========================================================================*/
#include "uiglo.h"
#include "appsession.h"
#include "mainwindow.h"
#include "clientview.h"

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
