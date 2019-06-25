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

enum UIEventType
{
	kStartGameEvent,
	kStopGameEvent,
	kPauseGameEvent
};

class QPixmap;
class GameState;

#endif
