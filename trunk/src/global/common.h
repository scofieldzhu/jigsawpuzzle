/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: common.h 
CreateTime: 2019-6-24 21:08
=========================================================================*/
#ifndef __common_h__
#define __common_h__

#include "kernelpublic.h"
#include "filesyspublic.h"

class QPixmap;
class SliceImagePane;
class JPGame;

enum GameState
{
	kStoppedState,
	kPlayingState,		
	kPausedState
};

enum GameStoppedReason
{
    kNormalStopped,
    kForceStopped
};

enum EventType{
	kStartGameBtnClicked,
	kHangUpGameBtnClicked,
	kShowOriginImageBtnClicked,
};

using RString = RATEL::RString;
using RStrings = RATEL::RStrings;

#endif
