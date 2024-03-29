/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: appsession.h 
CreateTime: 2019-6-19 21:07
=========================================================================*/
#ifndef __appsession_h__
#define __appsession_h__

#include "session.h"
#include "appconf.h"

class MainWindow;
class QApplication;
class AppSession : public RATEL::Session
{
public:
    const AppConf& conf()const { return appconf_; }
	MainWindow* mainWindow() { return mainwindow_; }
	AppSession(QApplication& a);
	~AppSession();

private:
    bool loadConfigs();
	void loadStyleSheets();
	void loadLanguage();
	bool onEnter();
	bool onLeave();
	QApplication& app_;
	MainWindow* mainwindow_ = nullptr;
    AppConf appconf_;
};

AppSession* GetAppSession();

#endif
