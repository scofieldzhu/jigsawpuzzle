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
#include <QTranslator>
#include "mainwindow.h"
#include "mainwindowmediator.h"
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

void AppSession::loadLanguage()
{
	QTranslator* zhtranslator = new QTranslator();
	if(zhtranslator->load("jigsawpuzzle_zh.qm")){
		app_.installTranslator(zhtranslator);
	}
	
}

bool AppSession::onEnter()
{
	loadStyleSheets();
	loadLanguage();
	mainwindow_ = new MainWindow();
// 	mainwindow_->show();
// 	mainwindow_->update();
	mainwindow_->mediator()->initAppUI();
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
