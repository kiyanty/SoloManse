//
//  GameState.h
//  Earth_Collapse
//
//  Created by neko on 13. 1. 24..
//
//

#ifndef Earth_Collapse_GameData_h
#define Earth_Collapse_GameData_h

#define Show_Rating_Scene

class GameData
{
public:
    static int gameState;
    static const int STATE_PLAYING = 1;
    static const int STATE_PAUSE = 2;
    static const int STATE_GAMEOVER = 3;
    static const int STATE_MENU = 4;
    static const int STATE_RECORD = 5;
    static const int STATE_INTRO = 6;
//    static bool isHardCore;
//
    static int highScore;
    static bool isMusicSound;
    static int guestId;
////    static bool isEffectSound;
//    static bool isVibrate;
//    static int currentBgmNumber;
//    static int openedBgmNumber;
//    
//    static int highestNormalScore;
//    static int highestHardcoreScore;
//    static const int SCORE_VERSION = 3;
//    static int saveVersion;
//    
//    static bool getNewBgm;
    
};

#endif
