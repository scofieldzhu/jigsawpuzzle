/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: appconfparser.cpp 
CreateTime: 2019-7-16 20:56
Creator: scofieldzhu
=======================================================================*/
#include "appconfparser.h"
#include "path.h"
#include "appconf.h"
USING_RATEL
using namespace pugi;

namespace
{
    const char* kAppConfTag = "AppConf";
    const char* kGameImageFolderTag = "GameImageFolder";
}

AppConfParser::AppConfParser()
{

}

AppConfParser::~AppConfParser()
{

}

bool AppConfParser::parseDoc()
{
    rootnode_ = doc_.root().first_child();
    xml_node gifnode = rootnode_.child(kGameImageFolderTag);
    if(gifnode.empty())
        return false;    
    refappconf_->gameimagefolder = gifnode.child_value();
    return true;
}

bool AppConfParser::load(const Path& conffilepath, AppConf& resconf)
{
    refappconf_ = &resconf;
    if(conffilepath.exists()){
        xml_parse_result res = doc_.load_file(conffilepath.cstr(), parse_default, encoding_utf8);
        if(res)
            return parseDoc();
    }
    return false;
}