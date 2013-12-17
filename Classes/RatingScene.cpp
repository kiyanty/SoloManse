//
//  RatingScene.cpp
//  StoneAttack
//
//  Created by neko on 13. 2. 28..
//
//

#include "RatingScene.h"
#include "MainScene.h"
#include "FileIO.h"
#include "GameData.h"

using namespace cocos2d;

CCScene* RatingScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = cocos2d::CCScene::create();
    
    // 'layer' is an autorelease object
    RatingScene *layer = RatingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool RatingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !cocos2d::CCLayer::init() )
    {
        return false;
    }
    FileIO::sharedInstance()->readFile();
    if(GameData::guestId == 0)
    {
        GameData::guestId = rand();
        FileIO::sharedInstance()->saveFile();
    }
    
    CCLayerColor* layerColor = CCLayerColor::create(ccc4(255, 255, 255, 255));
    
    CCLabelTTF* labelText = cocos2d::CCLabelTTF::create("이 게임물은 전체이용가 게임물입니다.", "Arial", 40);
    labelText->setPosition(ccp(450, 800));
    labelText->setColor(ccc3(0, 0, 0));
    layerColor->addChild(labelText);
    
    CCSprite* ratingIcon = CCSprite::create("All_Rating_300.png");
    ratingIcon->setPosition(ccp(764, 1440));
//    ratingIcon->setScale(0.5f);
    layerColor->addChild(ratingIcon);
    
    this->addChild(layerColor);
    
    this->schedule(schedule_selector(RatingScene::nextScene), 0, false, 2.0f);
    return true;
}

void RatingScene::nextScene()
{
    CCScene* scene = CCTransitionFade::create(0.3f, MainScene::scene());
    CCDirector::sharedDirector()->replaceScene(scene);
}