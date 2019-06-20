/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.

Project: jigsawpuzzle
Module: uimediator.h
CreateTime: 2019-6-18 22:04
=========================================================================*/
#ifndef __uimediator_hxx__
#define __uimediator_hxx__

template <class UI>
class UIMediator
{
public:
	typedef UIMediator<UI> MediatorSelf;
	virtual void subscribeEvents() = 0;
	virtual void unsubscribe() = 0;
	void setUI(UI* ui) { ui_ = ui; }
	UI* ui() { return ui_; }
	UIMediator(UI* ui):ui_(ui){}
	virtual ~UIMediator(){}

protected:
	UI* ui_;
};

#endif
