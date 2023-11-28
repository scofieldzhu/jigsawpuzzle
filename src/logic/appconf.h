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

#include "gamelevel.h"

struct AppConf
{
    bool isValidImageFileExt(const RString& ext)const { return std::find(gameimagefileexts.begin(), gameimagefileexts.end(), ext) != gameimagefileexts.end(); }
    bool getLevel(const RString& name, GameLevel& reslevel)const
    {
        auto it = std::find_if(gamelevels.begin(), gamelevels.end(), [&name](const GameLevel& level){return name == level.name;});
        if(it != gamelevels.end()){
            reslevel = *it;
            return true;
        }
        return false;
    }
    RString gameimagefolder;
    RStrings gameimagefileexts;
    std::vector<GameLevel> gamelevels;
};

#endif
