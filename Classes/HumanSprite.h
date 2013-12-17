//
//  Meteorite.h
//  2012 Prototype
//
//  Created by neko on 12. 12. 30..
//
//

#ifndef ___012_Prototype__HumanSprite__
#define ___012_Prototype__HumanSprite__

#include "cocos2d.h"

class HumanSprite : public cocos2d::CCSprite
{
private:
    HumanSprite(int humanState, int numLine);
    
public:
    static int maxFrame;
    float deltaX;
    float deltaY;
    float deltaScale;
    
    int humanState;
    int numLine;
    
    float currentX;
    float currentY; //= 1130.0f;
    float currentScale;// = 0.5f;

    void update();
    
//    static HumanSprite* create();
    static HumanSprite* create(bool isCouple, int numLine);
    
};
#endif /* defined(___012_Prototype__Meteorite__) */
