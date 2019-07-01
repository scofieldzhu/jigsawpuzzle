/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: controlpanel.cpp 
CreateTime: 2019-6-18 22:04
=========================================================================*/
#include "controlpanel.h"
#include <QBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QPushButton>
#include "controlpanelmediator.h"

ControlPanel::ControlPanel(QWidget* parent, int32_t fixedwidth)
	:QWidget(parent)
{
	setFixedWidth(fixedwidth);
	createControls();
	mediator = new ControlPanelMediator(this);
	mediator->subscribeEvents();
}

ControlPanel::~ControlPanel()
{}

void ControlPanel::createControls()
{
	QVBoxLayout* mainlayout = new QVBoxLayout();
	mainlayout->setContentsMargins(10, 10, 10, 10);
	mainlayout->setSpacing(10);

	startgametbtn = new QPushButton();
	startgametbtn->setFixedSize(200, 80);
	startgametbtn->setText(QObject::tr("Start Game"));
	mainlayout->addWidget(startgametbtn);

	nextgamebtn = new QPushButton();
	nextgamebtn->setFixedSize(200, 80);
	nextgamebtn->setText(QObject::tr("Next Game"));
	mainlayout->addWidget(nextgamebtn);

	showoriginimgbtn = new QPushButton();
	showoriginimgbtn->setCheckable(true);
	showoriginimgbtn->setChecked(false);
	showoriginimgbtn->setFixedSize(200, 80);
	showoriginimgbtn->setText(QObject::tr("Show Origin Image"));
	mainlayout->addWidget(showoriginimgbtn);
	mainlayout->addStretch();

	setLayout(mainlayout);
}

void ControlPanel::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
