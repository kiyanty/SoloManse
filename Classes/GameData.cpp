//
//  GameState.cpp
//  Earth_Collapse
//
//  Created by neko on 13. 1. 24..
//
//

#include "GameData.h"
#include <cmath>

int GameData::gameState = STATE_PLAYING;
bool GameData::isMusicSound = true;
int GameData::highScore = 0;
int GameData::guestId = 0;

//// bool GameData::isEffectSound = true;
//bool GameData::isVibrate = true;
//
//int GameData::highestNormalScore = 0;
//int GameData::highestHardcoreScore = 0;
//
//bool GameData::getNewBgm = false;
//bool GameData::isHardCore = false;
//
//int GameData::saveVersion = 3;
//
//int GameData::currentBgmNumber = 1;
//int GameData::openedBgmNumber = 1;
