/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: glosignals.h 
CreateTime: 2019-7-7 22:10
Creator: scofieldzhu
=======================================================================*/
#ifndef __glosignals_h__
#define __glosignals_h__

#include "xsignal.hxx"

struct GameStoppedEvent
{
    enum Reason{
        kNormal,
        kForce
    };
    Reason r;
};
typedef XSignal<GameStoppedEvent> GameStoppedSignal;

#endif
