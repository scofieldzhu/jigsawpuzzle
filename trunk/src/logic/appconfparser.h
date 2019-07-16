/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: appconfparser.h 
CreateTime: 2019-7-16 20:56
Creator: scofieldzhu
=======================================================================*/
#ifndef __appconfparser_h__
#define __appconfparser_h__

#include "common.h"
#include "pugixml.hpp"

struct AppConf;
class AppConfParser
{
public:
    bool load(const RATEL::Path& conffilepath, AppConf& resconf);
    AppConfParser();
    ~AppConfParser();

private:
    bool parseDoc();
    pugi::xml_document doc_;
    pugi::xml_node rootnode_;
    AppConf* refappconf_ = nullptr;
};

#endif
