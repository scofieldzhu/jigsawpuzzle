/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: glo.h 
CreateTime: 2019-6-20 21:34
=========================================================================*/
#ifndef __glo_h__
#define __glo_h__

#include "common.h"

class AppSession;
AppSession* GetTheAppSession();
struct AppConf;
const AppConf& GetAppConf();
class JPGame;
void SetActiveGame(JPGame* game);
JPGame* GetActiveGame();


#endif
