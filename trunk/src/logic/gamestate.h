/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: gamestate.h 
CreateTime: 2019-7-3 19:16
=========================================================================*/
#ifndef __gamestate_h__
#define __gamestate_h__

#include "common.h"

class GameState
{
public:
    virtual void onEnter() = 0;
    virtual void onLeave() = 0;
    virtual void handleEvent(EventType evttype) = 0;
    virtual ~GameState() = default;
};

#endif
