#ifndef __playingstate_h__
#define __playingstate_h__

#include "gamestate.h"

class PlayingState : public GameState
{
public:
    void onEnter();
    void onLeave();
    void handleEvent(EventId eid);
    PlayingState();
    ~PlayingState();
};

#endif
