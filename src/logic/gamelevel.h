/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: gamelevel.h 
CreateTime: 2019-7-18 20:40
Creator: scofieldzhu
=======================================================================*/
#ifndef __gamelevel_h__
#define __gamelevel_h__

#include "common.h"

struct GameLevel
{
    RString name = "no";
    uint32_t gridrows = 3;//jigsaw puzzle grid row count
    uint32_t gridcols = 3;//jigsaw puzzle grid column count
    uint32_t startseconds = 2;//cost time of startup process in seconds
    uint32_t hintcount = 1;// max permitted hint count  
    uint32_t hintseconds = 2;//time cost of each hint in seconds 
};

#endif