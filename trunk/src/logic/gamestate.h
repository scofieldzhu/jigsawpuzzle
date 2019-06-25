/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: gamestate.h 
CreateTime: 2019-6-22 19:09
=========================================================================*/
#ifndef __gamestate_h__
#define __gamestate_h__

#include <stdint.h>

class GameState
{
public:
	virtual GameState* handleEvent(uint32_t evttype) = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;
	virtual ~GameState(){}
};

#endif
