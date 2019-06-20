/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: clientview.h 
CreateTime: 2019-6-20 20:10
=========================================================================*/
#ifndef __clientview_h__
#define __clientview_h__

#include <QWidget>

class ClientView : public QWidget
{
	Q_OBJECT
public:
	ClientView(QWidget* parent = Q_NULLPTR);
	~ClientView();

private:
	void createControls();
	void paintEvent(QPaintEvent*);
};

#endif
