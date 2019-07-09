/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: gameconfig.h 
CreateTime: 2019-7-3 19:16
=========================================================================*/
#ifndef __gameconfig_h__
#define __gameconfig_h__

#include <QPixmap>

struct GameConfig
{
    QPixmap originimage; //origin image file for game, no any data modified
    int gridrows = 3; //jigsaw puzzle grid row count
    int gridcols = 3; //jigsaw puzzle grid column count
    int displayhinttime = 3; //time cost of each hint 
    int hintcount = 1; // max permitted hint count       
};

#endif
