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
#include "appconfparser.h"
#include "path.h"
#include "applogger.h"
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

bool AppSession::loadConfigs()
{
    AppConfParser parser;
    if(!parser.load("conf/appconf.xml", appconf_))
        return false;
    return true;
}

void AppSession::loadStyleSheets()
{
	QFile f("conf/app.qss");
	if(f.open(QIODevice::ReadOnly)){
		QString qss = f.readAll();
		app_.setStyleSheet(qss);
	}
}

void AppSession::loadLanguage()
{
	QTranslator* zhtranslator = new QTranslator();
	if(zhtranslator->load("conf/language/jigsawpuzzle_zh.qm"))
		app_.installTranslator(zhtranslator);	
}

bool AppSession::onEnter()
{
    if(!loadConfigs()){
        slog_err(applogger) << "load configs failed!" << endl;
        return false;
    }
	loadStyleSheets();
	loadLanguage();
	mainwindow_ = new MainWindow();    
 	mainwindow_->show();
 	mainwindow_->update();	
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
