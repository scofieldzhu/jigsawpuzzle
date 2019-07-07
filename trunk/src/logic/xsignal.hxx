/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: xsignal.hxx 
CreateTime: 2019-7-7 21:11
Creator: scofieldzhu
=======================================================================*/
#ifndef __xsignal_hxx__
#define __xsignal_hxx__

#include <boost/signals2.hpp>

template <typename EvtCls>
struct XSignal
{
    typedef EvtCls MyEvtCls;
    typedef XSignal<EvtCls> Self;
    typedef boost::signals2::connection BoostSig2Con;
    typedef boost::signals2::signal<void(const EvtCls&)> BoostSig2;
    typedef typename BoostSig2::slot_type BoostSig2Slot;
    static Self& Instance()
    {
        static Self s;
        return s;
    }
    enum PosType
    {
        kBack,
        kFront,
    };
    BoostSig2Con connect(const BoostSig2Slot& subscriber, PosType postype = kBack)
    {
        return sigsource_.connect(subscriber, (boost::signals2::connect_position)postype);
    }
    BoostSig2Con connect(const BoostSig2Slot& subscriber, int group, PosType postype = kBack)
    {
        return sigsource_.connect(group, subscriber, (boost::signals2::connect_position)postype);
    }         
    void trigger(const EvtCls& event)
    {
        sigsource_(event);
    }
    void disconnectAll()
    {
        sigsource_.disconnect_all_slots();
    }
    bool empty()const
    {
        return sigsource_.empty();
    }
private:
    BoostSig2 sigsource_;
};

#endif

