/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: applogger.h 
CreateTime: 2019-7-17 21:02
Creator: scofieldzhu
=======================================================================*/
#ifndef __applogger_h__
#define __applogger_h__

#include "sflogger/utilmacro.h"

void InitLogger();

extern SFLOGGER::Logger* g_LoggerInst;

#define applogger g_LoggerInst
using std::endl;

#endif
