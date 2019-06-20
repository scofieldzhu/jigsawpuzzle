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
class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow();
	~MainWindow();
	ClientView* clientview = nullptr;
	ControlPanel* ctrlpanel = nullptr;

private:
	void createControls();
};

#endif
