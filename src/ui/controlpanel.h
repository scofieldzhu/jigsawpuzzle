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
#include "ui_controlpanel.h"

class QLabel;
class QComboBox;
class QPushButton;
class ControlPanelMediator;
class ControlPanel : public QWidget
{
	Q_OBJECT
public:
    Ui::CtrlPanelUI ui;
	ControlPanel(QWidget* parent, int32_t fixedwidth);
	~ControlPanel();
	QPushButton* startgametbtn = nullptr;
	QPushButton* giveupbtn = nullptr;
	QPushButton* hintbtn = nullptr;
	QLabel* originimglabel = nullptr;
	QComboBox* originimgcb = nullptr;
	QLabel* difficultylabel = nullptr;
	QComboBox* difficultycb = nullptr;
	QLabel* timelabel = nullptr;
	QLabel* timevallabel = nullptr;
	ControlPanelMediator* mediator = nullptr;

private:
	void createControls();
	void paintEvent(QPaintEvent*);
};
#endif
