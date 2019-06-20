/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: clientview.cpp 
CreateTime: 2019-6-20 20:10
=========================================================================*/
#include "clientview.h"
#include <QStyleOption>
#include <QPainter>

ClientView::ClientView(QWidget* parent /*= Q_NULLPTR*/)
	:QWidget(parent)
{
	createControls();
}

ClientView::~ClientView()
{}

void ClientView::createControls()
{
}

void ClientView::paintEvent(QPaintEvent*)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
