/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: appsession.cpp 
CreateTime: 2019-6-19 21:07
=========================================================================*/
#include "appsession.h"
#include <QFile>
#include <QApplication>
#include "mainwindow.h"
USING_RATEL

static AppSession* st_AppInst = nullptr;

AppSession::AppSession(QApplication& a)
	:Session("App"),
	app_(a)
{
	st_AppInst = this;
}

AppSession::~AppSession()
{}

void AppSession::loadStyleSheets()
{
	QFile f("app.qss");
	if(f.open(QIODevice::ReadOnly)){
		QString qss = f.readAll();
		app_.setStyleSheet(qss);
	}
}

bool AppSession::onEnter()
{
	loadStyleSheets();
	mainwindow_ = new MainWindow();
	mainwindow_->show();
	mainwindow_->update();
	return true;
}

bool AppSession::onLeave()
{
	return true;
}

AppSession* GetAppSession()
{
	return st_AppInst;
}
