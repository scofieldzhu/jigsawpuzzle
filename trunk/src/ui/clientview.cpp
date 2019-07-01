/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: clientview.cpp 
CreateTime: 2019-6-20 20:10
=========================================================================*/
#include "clientview.h"
#include <QBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include "gameview.h"

ClientView::ClientView(QWidget* parent /*= Q_NULLPTR*/)
	:QWidget(parent)
{
	createControls();
}

ClientView::~ClientView()
{}

void ClientView::createControls()
{
	QHBoxLayout* mainlayout = new QHBoxLayout();
	mainlayout->setContentsMargins(4, 4, 4, 4);
	mainlayout->setSpacing(0);

	wpview_ = new GameView(nullptr, this);
	mainlayout->addWidget(wpview_);

	setLayout(mainlayout);
}

void ClientView::paintEvent(QPaintEvent*)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
