/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: appsession.h 
CreateTime: 2019-6-19 21:07
=========================================================================*/
#ifndef __appsession_h__
#define __appsession_h__

#include "session.h"

class AppSession : public RATEL::Session
{
public:
	AppSession();
	~AppSession();
};

#endif
