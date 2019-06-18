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

class ControlPanel : public QWidget
{
	Q_OBJECT
public:
	ControlPanel(QWidget* parent = Q_NULLPTR);
	~ControlPanel();

private:
	void createControls();

};
#endif
