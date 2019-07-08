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

class GameConfig
{
public:
    QPixmap originimage;
    int gridrows;
    int gridcols;
    int watchimageseconds;
    int hintcount;    
    GameConfig();
    ~GameConfig();
};

#endif
