//
//  Meteorite.h
//  2012 Prototype
//
//  Created by neko on 12. 12. 30..
//
//

#ifndef ___012_Prototype__RoadSprite__
#define ___012_Prototype__RoadSprite__

#include "cocos2d.h"

class RoadSprite : public cocos2d::CCSprite
{
private:
    RoadSprite(int numLine);
    
public:
    float deltaX;
    float deltaY;
    float deltaScale;
    
    int numLine;
    
    float currentX;
    float currentY; //= 1130.0f;
    float currentScale;// = 0.5f;

    void update();
    
//    static RoadSprite* create();
    static RoadSprite* create(int numLine);
    
};
#endif /* defined(___012_Prototype__Meteorite__) */
