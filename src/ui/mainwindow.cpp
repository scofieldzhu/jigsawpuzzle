/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: mainwindow.cpp 
CreateTime: 2019-6-18 21:00
=========================================================================*/
#include "mainwindow.h"
#include <QBoxLayout>
#include "clientview.h"
#include "controlpanel.h"
#include "mainwindowmediator.h"

MainWindow::MainWindow()
	:QWidget(nullptr, Qt::WindowFlags())
{
	setWindowTitle(QObject::tr("ChenChen-JigsawPuzzle"));
	setGeometry(100, 100, 1260, 680);
	createControls();
	mediator_ = new MainWindowMediator(this);
	mediator_->subscribeEvents();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createControls()
{
	QHBoxLayout* hblayout = new QHBoxLayout();
	hblayout->setContentsMargins(4, 4, 4, 4);
	hblayout->setSpacing(0);
	clientview_ = new ClientView(this);
	hblayout->addWidget(clientview_);
	ctrlpanel_ = new ControlPanel(this, 250);
	hblayout->addWidget(ctrlpanel_);
	setLayout(hblayout);
}
