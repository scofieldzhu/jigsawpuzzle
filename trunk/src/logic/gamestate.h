#ifndef __gamestate_h__
#define __gamestate_h__

#include "common.h"

class GameState
{
public:
    virtual void onEnter() = 0;
    virtual void onLeave() = 0;
    virtual void handleEvent(EventId eid) = 0;
    virtual ~GameState() = default;
};

#endif
