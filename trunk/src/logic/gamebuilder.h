#ifndef __gamebuilder_h__
#define __gamebuilder_h__

class GameBuilder
{
public:
    virtual JPGame* build(GameConfig& conf) = 0;
    virtual ~GameBuilder(){}
};

#endif
