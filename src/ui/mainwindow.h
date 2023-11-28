/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: mainwindow.h 
CreateTime: 2019-6-18 21:00
=========================================================================*/
#ifndef __mainwindow_h__
#define __mainwindow_h__

#include <QWidget>

class ClientView;
class ControlPanel;
class MainWindowMediator;
class MainWindow : public QWidget
{
	Q_OBJECT
public:
	ClientView* clientView() { return clientview_; }
	ControlPanel* ctrlPanel() { return ctrlpanel_; }
	MainWindowMediator* mediator() { return mediator_; }
	MainWindow();
	~MainWindow();	

private:
	void createControls();
	ClientView* clientview_ = nullptr;
	ControlPanel* ctrlpanel_ = nullptr;
	MainWindowMediator* mediator_ = nullptr;
};

#endif
