/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: animatesplash.h 
CreateTime: 2023-11-13 22:14
Creator: scofieldzhu
=======================================================================*/
#ifndef __animatesplash_h__
#define __animatesplash_h__

#include "movielabel.h"

class MovieLabel;
class AnimateSplash : public QWidget
{
    Q_OBJECT;
public:
    void start();
    void stop();
    bool started()const;
    int currentFrameNumber()const;
    int frameCount()const;
    AnimateSplash(const QString& gif_fn, QWidget* parent = NULL);
    ~AnimateSplash();

signals:
    void finished();
    void frameChanged(int);

private:
    void paintEvent(QPaintEvent *event);
    QMovie* gif_player_;
    MovieLabel* animation_label_;  
    QPixmap bkg_img_;
};

#endif

