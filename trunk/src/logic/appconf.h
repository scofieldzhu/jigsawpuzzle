/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: appconf.h 
CreateTime: 2019-7-15 22:07
Creator: scofieldzhu
=======================================================================*/
#ifndef __appconf_h__
#define __appconf_h__

#include "common.h"

struct GameLevel
{
    RString description = "no";
    uint32_t gridrows = 3;
    uint32_t gridcols = 3;
    uint32_t startseconds = 2;
    uint32_t hintcount = 1;
    uint32_t hintseconds = 2;
};

struct AppConf
{
    bool isValidImageFileExt(const RString& ext)const { return std::find(gameimagefileexts.begin(), gameimagefileexts.end(), ext) != gameimagefileexts.end(); }
    RString gameimagefolder;
    RStrings gameimagefileexts;
    std::vector<GameLevel> gamelevels;
};

#endif
