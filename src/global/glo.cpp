/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: glo.cpp 
CreateTime: 2019-6-20 21:34
=========================================================================*/
#include "glo.h"
#include "appsession.h"

AppSession* GetTheAppSession()
{
	return GetAppSession();
}

const AppConf& GetAppConf()
{
    return GetAppSession()->conf();
}

JPGame* g_ActiveGame = nullptr;

void SetActiveGame(JPGame* game)
{
	g_ActiveGame = game;
}

JPGame* GetActiveGame()
{
	return g_ActiveGame;
}
