//
//  Meteorite.cpp
//  2012 Prototype
//
//  Created by neko on 12. 12. 30..
//
//

#include "LaneSprite.h"
#include "GameScene.h"
#include "HumanSprite.h"

// 0 112 225 337 450 563 675 787 900
// 가로 250 300 350 400 450 500 550 600 650 세로 516

LaneSprite::LaneSprite(int numLine) : numLine(numLine), currentY(1130), currentScale(0.5f)
{
    switch(numLine)
    {
        case 1:
            currentX = 350;
            deltaX = (225 - 350) / (float) HumanSprite::maxFrame;
            break;
        case 2:
            currentX = 450;
            deltaX = 0;
            break;
        case 3:
            currentX = 550;
            deltaX = (675 - 550) / (float) HumanSprite::maxFrame;
            break;
    }
    
    deltaY = currentY / (float) HumanSprite::maxFrame;
    deltaScale = currentScale / (float) HumanSprite::maxFrame;
    
//    currentY = 1084;
    
    this->setPosition(ccp(currentX, currentY));
    this->setScale(currentScale);
}

/*
LaneSprite* LaneSprite::create()
{
    
    LaneSprite *pobSprite = new LaneSprite();
    
    int randNum = rand() % 4;
    if (pobSprite && pobSprite->initWithFile(randNum == 0 ? "metheo1.png" : randNum == 1 ? "metheo2.png" : randNum == 3 ? "metheo3.png" : "metheo4.png"))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}
*/

LaneSprite* LaneSprite::create(int numLine)
{
    LaneSprite *pobSprite = new LaneSprite(numLine);

    if (pobSprite && pobSprite->initWithFile("dote.png"))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void LaneSprite::update()
{
    
    /*
     if(GameData::gameState == GameData::STATE_PAUSE)
     {
        return;
     }
     */

    currentX += deltaX;
    currentY -= deltaY;
    this->setPosition(ccp((int) currentX, (int) currentY));
    this->setScale(this->getScale() + deltaScale);

    deltaX *= 1.03f;
    deltaY *= 1.03f;
    deltaScale *= 1.03f;
    
    if(currentY < -200)
    {
        GameScene::gameScene->removeLaneSprite(this);
    }
    
}