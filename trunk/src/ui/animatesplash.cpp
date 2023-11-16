#include "animatesplash.h"
#include <QMovie>
#include <QBoxLayout>
#include <QPainter>
#include "movielabel.h"

AnimateSplash::AnimateSplash(const QString& gif_fn, QWidget* parent)
    :QWidget(parent)
{
    QVBoxLayout* main_layout = new QVBoxLayout(this);
    gif_player_ = new QMovie(gif_fn);
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

void AnimateSplash::setBackgroudImage(QPixmap img)
{
    bkg_img_ = img;
}

void AnimateSplash::paintEvent(QPaintEvent *event)
{
    if(bkg_img_.isNull())
        return;
    QPainter penter(this);
    penter.drawPixmap({0, 0, width(), height()}, bkg_img_);}

void AnimateSplash::showEvent(QShowEvent *event)
{
    gif_player_->start();
}

void AnimateSplash::hideEvent(QHideEvent *event)
{
    gif_player_->stop();
}
