/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: uiglo.h 
CreateTime: 2019-6-20 21:39
=========================================================================*/
#ifndef __uiglo_h__
#define __uiglo_h__

#include <QString>
#include "glo.h"

class MainWindow;
MainWindow* GetMainWindow();
class ClientView;
ClientView* GetClientView();
class GameView;
GameView* GetGameView();
class GameScene;
GameScene* GetGameScene();

void PlayAnimation(const QString& gif_path);
void StopPlayAnimation();

#endif
