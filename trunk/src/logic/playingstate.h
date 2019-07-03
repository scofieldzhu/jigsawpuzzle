/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: playingstate.h 
CreateTime: 2019-7-3 19:16
=========================================================================*/
#ifndef __playingstate_h__
#define __playingstate_h__

#include "gamestate.h"

class PlayingState : public GameState
{
public:
    void onEnter();
    void onLeave();
    void handleEvent(EventType evttype);
    PlayingState();
    ~PlayingState();
};

#endif
