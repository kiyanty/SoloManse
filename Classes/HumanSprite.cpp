//
//  Meteorite.cpp
//  2012 Prototype
//
//  Created by neko on 12. 12. 30..
//
//

#include "HumanSprite.h"
#include "GameScene.h"
#include "GameData.h"
#include "SimpleAudioEngine.h"


//int HumanSprite::minDropSpeed = 1;
//int HumanSprite::maxDropSpeed = 4;
int HumanSprite::maxFrame = 300;

// 0 112 225 337 450 563 675 787 900
HumanSprite::HumanSprite(int humanState, int numLine) : humanState(humanState), numLine(numLine), currentX((numLine + 2) * 100), currentY(1130), currentScale(0.5f)
{
    switch(numLine)
    {
        case 1:
//            currentX = 300;
            deltaX = (112 - 300) / (float) maxFrame;
            break;
        case 2:
//            currentX = 400;
            deltaX = (337 - 400) / (float) maxFrame;
            break;
        case 3:
//            currentX = 500;
            deltaX = (563 - 500) / (float) maxFrame;
            break;
        case 4:
//            currentX = 600;
            deltaX = (787 - 600) / (float) maxFrame;
            break;
    }
    deltaY = currentY / (float) maxFrame;
    deltaScale = currentScale / (float) maxFrame;
    
//    currentY = 1084;
    CCLOG("%f %f %f %f", currentX, currentY, deltaX, deltaY);
    this->setPosition(ccp(currentX, currentY));
    this->setScale(currentScale);
}

/*
HumanSprite* HumanSprite::create()
{
    
    HumanSprite *pobSprite = new HumanSprite();
    
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

HumanSprite* HumanSprite::create(bool isCouple, int numLine)
{
    int humanState = isCouple ? 0 : (rand() % 10 == 0 ? 2 : 1);
    HumanSprite *pobSprite = new HumanSprite(humanState, numLine);

    if (pobSprite && pobSprite->initWithFile(humanState == 0 ? "coupleon.png" : humanState == 1 ? "solo.png" : "female_solo.png"))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void HumanSprite::update()
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
        GameScene::gameScene->removeHumanSprite(this);
        if(humanState == 0)
        {
            GameScene::gameScene->comboReset();
        }
    }
    if(currentY > 110 && currentY < 180)
    {
        if(numLine == GameScene::currentLine)
        {
            switch(humanState)
            {
                case 0:
                    this->setTexture(CCTextureCache::sharedTextureCache()->addImage("couplebreak.png"));
                    humanState = 3;
                    GameScene::gameScene->comboPlus();
                    if(GameData::isMusicSound)
                    {
                        (CocosDenshion::SimpleAudioEngine::sharedEngine())->playEffect("pong.wav");
                    }
                    break;
                case 1:
                    GameScene::gameScene->removeHumanSprite(this);
                    if(GameData::isMusicSound)
                    {
                        (CocosDenshion::SimpleAudioEngine::sharedEngine())->playEffect("puck.mp3");
                    }
                    
                    break;
                case 2:
                    GameScene::gameScene->removeHumanSprite(this);
                    if(GameData::isMusicSound)
                    {
                        (CocosDenshion::SimpleAudioEngine::sharedEngine())->playEffect("pong.wav");
                    }
                    GameScene::gameScene->currentScore += 500 * GameScene::gameScene->deltaComboNum;
                    
                    break;
            }
        }
    }

}