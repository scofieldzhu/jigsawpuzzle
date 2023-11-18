/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: animatesplash.cpp 
CreateTime: 2023-11-13 22:14
Creator: scofieldzhu
=======================================================================*/
#include "animatesplash.h"
#include <QMovie>
#include <QBoxLayout>
#include <QPainter>
#include <QApplication>
#include <QScreen>
#include "uiglo.h"
#include "mainwindow.h"
#include "movielabel.h"
#include "applogger.h"

AnimateSplash::AnimateSplash(const QString& gif_fn, QWidget* parent)
    :QWidget(parent)
{
    QVBoxLayout* main_layout = new QVBoxLayout(this);
    gif_player_ = new QMovie(gif_fn);
    connect(gif_player_, &QMovie::finished, this, &AnimateSplash::finished);
    connect(gif_player_, &QMovie::frameChanged, this, &AnimateSplash::frameChanged);
    animation_label_ = new MovieLabel(this);
    animation_label_->setMovie(gif_player_);
    QHBoxLayout* hb_layout = new QHBoxLayout;
    hb_layout->addStretch();
    hb_layout->addWidget(animation_label_);
    hb_layout->addStretch();
    main_layout->addLayout(hb_layout);
}

AnimateSplash::~AnimateSplash()
{}

void AnimateSplash::start()
{
    if(started()){
        slog_err(applogger) << "Animation is playing already!" << endl;
        return;
    }
    bkg_img_ = QApplication::primaryScreen()->grabWindow(GetMainWindow()->winId());
    setGeometry({0, 0, GetMainWindow()->width(), GetMainWindow()->height()});
    show();
    gif_player_->start();    
}

void AnimateSplash::stop()
{
    if(started()){
        gif_player_->stop();
        bkg_img_ = QPixmap();
        hide();
    }
}

bool AnimateSplash::started() const
{
    return gif_player_->state() == QMovie::Running;
}

int AnimateSplash::currentFrameNumber() const
{
    return gif_player_->currentFrameNumber();
}

int AnimateSplash::frameCount() const
{
    return gif_player_->frameCount();
}

void AnimateSplash::paintEvent(QPaintEvent *event)
{
    if(bkg_img_.isNull())
        return;
    QPainter penter(this);
    penter.drawPixmap({0, 0, width(), height()}, bkg_img_);
}
