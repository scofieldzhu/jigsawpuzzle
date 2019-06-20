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

MainWindow::MainWindow()
	:QWidget(nullptr, Qt::WindowFlags())
{
	setGeometry(100, 100, 1260, 680);
	createControls();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createControls()
{
	QHBoxLayout* hblayout = new QHBoxLayout();
	hblayout->setContentsMargins(4, 4, 4, 4);
	hblayout->setSpacing(0);
	clientview = new ClientView(this);
	hblayout->addWidget(clientview);
	ctrlpanel = new ControlPanel(this, 250);
	hblayout->addWidget(ctrlpanel);
	setLayout(hblayout);
}
