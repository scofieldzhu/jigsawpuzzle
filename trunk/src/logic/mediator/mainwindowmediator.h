/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: mainwindowmediator.h 
CreateTime: 2019-7-3 21:26
=========================================================================*/
#ifndef __mainwindowmediator_h__
#define __mainwindowmediator_h__

#include <QObject>
#include "uimediator.hxx"

class MainWindow;
class MainWindowMediator : public QObject, public UIMediator<MainWindow>
{
	Q_OBJECT
public:
	void subscribeEvents();
	void unsubscribe();
	void initAppUI();
	MainWindowMediator(MainWindow* ui);
	~MainWindowMediator();
};

#endif
