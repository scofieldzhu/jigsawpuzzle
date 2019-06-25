/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: hangupstate.h 
CreateTime: 2019-6-22 20:45
=========================================================================*/
#ifndef __hangupstate_h__
#define __hangupstate_h__

#include "gamestate.h"

class HangUpState : public GameState
{
public:
	GameState* handleEvent(uint32_t evttype);
	void enter();
	void exit();
	HangUpState();
	~HangUpState();
};

#endif
