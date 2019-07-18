/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: controlpanelmediator.cpp 
CreateTime: 2019-6-20 21:17
=========================================================================*/
#include "controlpanelmediator.h"
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include "controlpanel.h"
#include "uiglo.h"
#include "mainwindow.h"
#include "jpgame.h"
#include "gamescene.h"
#include "path.h"
#include "dirwalker.h"
#include "appconf.h"
USING_RATEL

#define ENABLE_IMG_CHANGE_SIGNAL() connect(ui_->originimgcb, SIGNAL(currentTextChanged(const QString&)), this, SLOT(handleOriginImageCurrentTextChanged(const QString&)))
#define DISABLE_IMG_CHANGE_SIGNAL() disconnect(ui_->originimgcb, SIGNAL(currentTextChanged(const QString&)), this, SLOT(handleOriginImageCurrentTextChanged(const QString&)))

ControlPanelMediator::ControlPanelMediator(ControlPanel* ui)
	:QObject(ui),
	MediatorSelf(ui)
{
}

ControlPanelMediator::~ControlPanelMediator()
{
	unsubscribe();
}

void ControlPanelMediator::initAppUI()
{
    DISABLE_IMG_CHANGE_SIGNAL();
    collectImageFiles();
    ENABLE_IMG_CHANGE_SIGNAL();
    ui_->originimgcb->setCurrentIndex(-1);
    ui_->originimgcb->setCurrentIndex(0);  //force trigger refresh background 
}

void ControlPanelMediator::subscribeEvents()
{
    ENABLE_IMG_CHANGE_SIGNAL();
	connect(ui_->startgametbtn, SIGNAL(released()), this, SLOT(handleStartGameBtnClicked()));    
	connect(ui_->giveupbtn, SIGNAL(released()), this, SLOT(handleGiveUpBtnClicked()));    
	connect(ui_->hintbtn, SIGNAL(released()), this, SLOT(handleHitBtnClicked()));
    startedconn_ = GameStartedSignal::Inst().connect(boost::bind(&ControlPanelMediator::handleGameStartedSignal, this, _1));
    stoppedconn_ = GameStoppedSignal::Inst().connect(boost::bind(&ControlPanelMediator::handleGameStoppedSignal, this, _1));
    hinttimeoutconn_ = GameHintTimeOutSignal::Inst().connect(boost::bind(&ControlPanelMediator::handleGameHintTimeOutSignal, this, _1));    
    updateclockconn_ = GameClockUpdateSignal::Inst().connect(boost::bind(&ControlPanelMediator::handleUpdateClockSignal, this, _1));    
}

void ControlPanelMediator::unsubscribe()
{
    startedconn_.disconnect();
    stoppedconn_.disconnect();
    hinttimeoutconn_.disconnect();
    updateclockconn_.disconnect();
}

void ControlPanelMediator::handleStartGameBtnClicked()
{
    Q_ASSERT(GetActiveGame() == nullptr);    
    Path imgfolder = GetAppConf().gameimagefolder;
    Path selimgfilepath = imgfolder.join(ui_->originimgcb->currentText().toUtf8().data());
    if(selimgfilepath.exists()){
        QPixmap originimg(selimgfilepath.cstr());
        if(!originimg.isNull()){
            GameConfig conf;
            conf.originimage = originimg;
            GetAppConf().getLevel(ui_->difficultycb->currentText().toUtf8().data(), conf.level);
            JPGame* newgame = new JPGame(conf);
            newgame->start();
        }
    }
}

void ControlPanelMediator::handleGiveUpBtnClicked()
{
    JPGame* game = GetActiveGame();
    if(game && game->isStarted())
        game->stop(kForceStopped);        
}

void ControlPanelMediator::handleOriginImageCurrentTextChanged(const QString&)
{
    handleGiveUpBtnClicked();
    Path imgfolder = GetAppConf().gameimagefolder;
    Path selimgfilepath = imgfolder.join(ui_->originimgcb->currentText().toUtf8().data());
    if(selimgfilepath.exists()){
        QPixmap originimg(selimgfilepath.cstr());
        GetGameScene()->setBackgroundImage(originimg);
        GetGameScene()->update();
    }
}

void ControlPanelMediator::collectImageFiles()
{
    ui_->originimgcb->clear();
    const Path imgfolder = GetAppConf().gameimagefolder;
    if(!imgfolder.exists())
        return;
    std::vector<Path> imgfiles;
    auto meetfunc = [&imgfiles](const Path& path)->void{
        RString ext = path.extension().rstring().upper();
        if(GetAppConf().isValidImageFileExt(ext))
            imgfiles.push_back(path.filename());
    };
    DirWalker(imgfolder).walk(meetfunc);    
    for(auto f : imgfiles)
        ui_->originimgcb->addItem(QString::fromUtf8(f.cstr()));
}

void ControlPanelMediator::handleGameStartedSignal(const GameStartedEvent& event)
{
    ui_->startgametbtn->setEnabled(false);
    ui_->giveupbtn->setEnabled(true);
    ui_->hintbtn->setEnabled(true);
}

void ControlPanelMediator::handleGameStoppedSignal(const GameStoppedEvent& event)
{
    ui_->startgametbtn->setEnabled(true);
    ui_->giveupbtn->setEnabled(false);
    ui_->hintbtn->setEnabled(false);
    delete event.game; //destroy current active game
    if(event.reason == kNormalStopped)
        GetGameScene()->showNotice(QObject::tr("Congratulations!"));
}

void ControlPanelMediator::handleGameHintTimeOutSignal(const GameHintTimeOutEvent& event)
{
    ui_->giveupbtn->setEnabled(true);
    ui_->hintbtn->setEnabled(!event.islastone);
}

void ControlPanelMediator::handleUpdateClockSignal(const GameClockUpdateEvent& event)
{
    int32_t m = event.costsecs / 60;
    int32_t s = event.costsecs - m * 60;
    ui_->timevallabel->setText(QString("00:%1:%2").arg(m, 2, 10, QChar('0')).arg(s, 2, 10, QChar('0')));
}

void ControlPanelMediator::handleHitBtnClicked()
{
    if(GetActiveGame()){
        ui_->giveupbtn->setEnabled(false);
        ui_->hintbtn->setEnabled(false);
        GetActiveGame()->hintOnce();
    }
}
