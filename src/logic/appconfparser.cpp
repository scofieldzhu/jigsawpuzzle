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
    const char* kGameImageFileExtsTag = "GameImageFileExts";
    const char* kGameLevelsTag = "GameLevels";
    const char* kLevelTag = "Level";
    const char* kNameTag = "Name";
    const char* kGridRowsTag = "GridRows";
    const char* kGridColsTag = "GridCols";
    const char* kStartSecondsTag = "StartSeconds";
    const char* kHintCountTag = "HintCount";
    const char* kHintSecondsTag = "HintSeconds";
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
    xml_node gifenode = rootnode_.child(kGameImageFileExtsTag);
    if(gifenode.empty())
        return false;
    RString rawexts = gifenode.child_value();
    refappconf_->gameimagefileexts = rawexts.split('|');
    return parseGameLevels();
}

bool AppConfParser::parseGameLevels()
{
    xml_node glsnode = rootnode_.child(kGameLevelsTag);
    if(glsnode.empty())
        return false;
    for(xml_node lnode = glsnode.child(kLevelTag); !lnode.empty(); lnode = lnode.next_sibling()){
        if(!parseGameLevel(lnode))
            return false;
    }
    return !refappconf_->gamelevels.empty();
}

bool AppConfParser::parseGameLevel(xml_node& levelnode)
{
    GameLevel newlevel;
    xml_node namenode = levelnode.child(kNameTag);
    if(namenode.empty())
        return false;
    newlevel.name = namenode.child_value();
    xml_node grnode = levelnode.child(kGridRowsTag);
    if(grnode.empty())
        return false;
    newlevel.gridrows = RString(grnode.child_value()).toUInt32();
    xml_node gcnode = levelnode.child(kGridColsTag);
    if(gcnode.empty())
        return false;
    newlevel.gridcols = RString(gcnode.child_value()).toUInt32();
    xml_node ssnode = levelnode.child(kStartSecondsTag);
    if(ssnode.empty())
        return false;
    newlevel.startseconds = RString(ssnode.child_value()).toUInt32();
    xml_node hcnode = levelnode.child(kHintCountTag);
    if(hcnode.empty())
        return false;
    newlevel.hintcount = RString(hcnode.child_value()).toUInt32();
    xml_node hsnode = levelnode.child(kHintSecondsTag);
    if(hsnode.empty())
        return false;
    newlevel.hintseconds = RString(hsnode.child_value()).toUInt32();
    refappconf_->gamelevels.push_back(newlevel);
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