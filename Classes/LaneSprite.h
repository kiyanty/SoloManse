//
//  Meteorite.h
//  2012 Prototype
//
//  Created by neko on 12. 12. 30..
//
//

#ifndef ___012_Prototype__LaneSprite__
#define ___012_Prototype__LaneSprite__

#include "cocos2d.h"

class LaneSprite : public cocos2d::CCSprite
{
private:
    LaneSprite(int numLine);
    
public:
    float deltaX;
    float deltaY;
    float deltaScale;
    
    int numLine;
    
    float currentX;
    float currentY; //= 1130.0f;
    float currentScale;// = 0.5f;

    void update();
    
//    static LaneSprite* create();
    static LaneSprite* create(int numLine);
    
};
#endif /* defined(___012_Prototype__Meteorite__) */
