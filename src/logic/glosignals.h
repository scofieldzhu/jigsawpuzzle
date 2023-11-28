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
#include "common.h"

class JPGame;
struct GameNotifyEvent
{
    JPGame* game;
    GameNotifyEvent(JPGame& g)
        :game(&g){}
};

struct GameStoppedEvent : public GameNotifyEvent
{    
    GameStoppedEvent(JPGame& g, GameStoppedReason r)
        :GameNotifyEvent(g),
        reason(r){}    
    GameStoppedReason reason;
};
typedef RATEL::XSignal<GameStoppedEvent> GameStoppedSignal;

struct GameStartedEvent : public GameNotifyEvent
{
    GameStartedEvent(JPGame& g)
        :GameNotifyEvent(g){}
};
typedef RATEL::XSignal<GameStartedEvent> GameStartedSignal;

struct GameHintTimeOutEvent : public GameNotifyEvent
{
    GameHintTimeOutEvent(JPGame& g, bool lastone)
        :GameNotifyEvent(g),
        islastone(lastone){}
    bool islastone = false;
};
typedef RATEL::XSignal<GameHintTimeOutEvent> GameHintTimeOutSignal;

struct SliceImageSwappedEvent{};
typedef RATEL::XSignal<SliceImageSwappedEvent> SliceImageSwappedSignal;

struct GameClockUpdateEvent : public GameNotifyEvent
{
    GameClockUpdateEvent(JPGame& g, uint32_t time)
        :GameNotifyEvent(g),
        costsecs(time){}
    uint32_t costsecs;
};
typedef RATEL::XSignal<GameClockUpdateEvent> GameClockUpdateSignal;


#endif
