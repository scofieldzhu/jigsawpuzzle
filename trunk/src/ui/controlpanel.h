/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: controlpanel.h 
CreateTime: 2019-6-18 22:04
=========================================================================*/
#ifndef __controlpanel_h__
#define __controlpanel_h__

#include <QWidget>

class QPushButton;
class ControlPanelMediator;
class ControlPanel : public QWidget
{
	Q_OBJECT
public:
	ControlPanel(QWidget* parent, int32_t fixedwidth);
	~ControlPanel();
	QPushButton* startgametbtn = nullptr;
	QPushButton* nextgamebtn = nullptr;
	QPushButton* showoriginimgbtn = nullptr;
	ControlPanelMediator* mediator = nullptr;

private:
	void createControls();
	void paintEvent(QPaintEvent*);
};
#endif
