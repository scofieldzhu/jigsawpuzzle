#pragma once

#include "movielabel.h"

class MovieLabel;
class AnimateSplash : public QWidget
{
    Q_OBJECT;
public:
    void setBackgroudImage(QPixmap img);
    AnimateSplash(const QString& gif_fn, QWidget* parent = NULL);
    ~AnimateSplash();

private:
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    QMovie* gif_player_;
    MovieLabel* animation_label_;  
    QPixmap bkg_img_;
};

