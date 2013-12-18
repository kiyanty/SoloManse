#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "GameData.h"
#include "MainScene.h"
#include "FileIO.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID


using namespace cocos2d;
using namespace CocosDenshion;

GameScene* GameScene::gameScene;
int GameScene::currentLine = 2;

// 0 112 225 337 450 563 675 787 900
// 가로 250 300 350 400 450 500 550 600 650 세로 516
CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    GameData::gameState = GameData::STATE_PLAYING;
    
    gameScene = this;
    humanCountZ = 50;
 
    this->initSpriteBackground();
    this->initSpriteCharacter();
    this->initBtnPause();
    this->initLayerPause();
    this->initSpriteGameOver();
    this->initBMFont();
    
    this->schedule(schedule_selector(GameScene::update));
    this->setTouchEnabled(true);
    this->setKeypadEnabled(true);
    
    arrayHumanSprite = CCArray::create();
    arrayHumanSprite->retain();
    
    arrayLaneSprite = CCArray::create();
    arrayLaneSprite->retain();
    
    arrayRoadSprite = CCArray::create();
    arrayRoadSprite->retain();

	this->initCloudSprite();
    
    this->startBackgroundMusic();
    
    //plus
    
    this->humanCount = 0;
    
    currentLine = 2;
    this->deltaComboNum = 1;
    HumanSprite::maxFrame = 300;
    roadChairCoolTime = 0;

	this->currentCombo = 0;
	this->currentRunAnimation = 0;
	this->currentScore = 0;
	this->time = -1;
    
    return true;
}

void GameScene::update(float ct)
{
    if(GameData::gameState == GameData::STATE_PAUSE)
    {
        return;
    }
    else if(GameData::gameState == GameData::STATE_GAMEOVER)
    { 
        return;
    }
    updateCharAnimation();
    
	time++;
    if(time % 15 == 0)
    {
        this->createLaneSprite();
        this->createRoadSprite();
        if(rand() % 20 == 0 && time == 30)
        {
            HumanSprite* woman = HumanSprite::create(2, rand() % 4 + 1);
            arrayHumanSprite->addObject(woman);
            this->addChild(woman, humanCountZ);
        }
        if(time == 60)
        {
            this->createHumanSprite();
            
            if(HumanSprite::maxFrame > 30)
            {
                HumanSprite::maxFrame -= 2;
            }
            time = 0;
        }
    }
    
    currentScore += deltaComboNum;
    char buf[16];
    sprintf(buf, "%d", currentScore);
    labelScore->setString(buf);

 
    
//    CCObject* temp;
    /*
    CCARRAY_FOREACH(arrayHumanSprite, temp)
    {
        ((HumanSprite*) temp)->update();
    }
     */
    /*
    CCARRAY_FOREACH(arrayLaneSprite, temp)
    {
        ((LaneSprite*) temp)->update();
    }
    */
    for(int i=0; i<arrayHumanSprite->count(); i++)
    {
        HumanSprite* human = (HumanSprite*) arrayHumanSprite->objectAtIndex(i);
        human->update();
    }
    for(int i=0; i<arrayLaneSprite->count(); i++)
    {
        LaneSprite* lane = (LaneSprite*) arrayLaneSprite->objectAtIndex(i);
        lane->update();
    }
    for(int i=0; i<arrayRoadSprite->count(); i++)
    {
        RoadSprite* road = (RoadSprite*) arrayRoadSprite->objectAtIndex(i);
        road->update();
    }
	for( int i = 0; i < this->arrayCloudSprite->count(); i++ )
	{
		//this->arrayCloudSprite->objectAtIndex(i)->update((float)NULL);
		CCloudSprite* cloud = (CCloudSprite*) this->arrayCloudSprite->objectAtIndex(i);
		cloud->update();
	}
}

void GameScene::comboPlus()
{
    char buf[16];
//    realMeteorScore++;
//    currentScore += deltaComboNum;//currentCombo < 100 ? 1 : currentCombo < 300 ? 2 : currentCombo < 600 ? 3 : currentCombo < 1000 ? 5 : currentCombo < 1500 ? 10 : 20;
    sprintf(buf, "%d", currentScore);
//    labelScore->setString(buf);
    
    if(!isHighestScore && currentScore > GameData::highScore)
    {
        isHighestScore = true;
        labelScore->setColor(ccc3(255, 255, 80));
        labelScore->setPosition(ccp(590, 1550));
        labelScoreSpell->setString("Highest");
        labelScoreSpell->setColor(ccc3(255, 255, 80));
    }
    
    // 210, 255, 255
    currentCombo++;
    switch(currentCombo)
    {
        case 20:
            labelComboMul->setString("x2");
            //            labelComboMul->setColor(ccc3(247, 156, 15));
            // 100, 255, 100
            labelComboMul->setColor(ccc3(150, 255, 120));
            //            labelCombo->setColor(ccc3(150, 255, 100));
            //            labelComboNum->setColor(ccc3(150, 255, 100));
            deltaComboNum = 2;
            labelComboMul->setVisible(true);
            break;
        case 40:
            labelComboMul->setString("x3");
            //            labelComboMul->setColor(ccc3(176, 214, 27));
            // 0, 127, 255
            labelComboMul->setColor(ccc3(100, 240, 240));
            //            labelCombo->setColor(ccc3(100, 240, 240));
            //            labelComboNum->setColor(ccc3(100, 240, 240));
            deltaComboNum = 3;
            break;
        case 70:
            labelComboMul->setString("x4");
            //            labelComboMul->setColor(ccc3(20, 141, 113));
            // 255, 200, 100
            //255 77 159
            labelComboMul->setColor(ccc3(255, 100, 170));
            //            labelCombo->setColor(ccc3(255, 100, 170));
            //            labelComboNum->setColor(ccc3(255, 100, 170));
            deltaComboNum = 4;
            break;
        case 100:
            labelComboMul->setString("x5");
            //            labelComboMul->setColor(ccc3(24, 33, 139));
            // 255, 100, 200
            labelComboMul->setColor(ccc3(255, 127, 255));
            //            labelCombo->setColor(ccc3(255, 127, 255));
            //            labelComboNum->setColor(ccc3(255, 127, 255));
            deltaComboNum = 5;
            break;
            /*
             case 250:
             labelComboMul->setString("x20");
             //            labelComboMul->setColor(ccc3(191, 21, 111));
             // 255, 80, 80
             labelComboMul->setColor(ccc3(226, 116, 242));
             //            labelCombo->setColor(ccc3(255, 255, 100));
             //            labelComboNum->setColor(ccc3(255, 255, 100));
             deltaComboNum = 20;
             break;
             */
    }
    
    if(currentCombo == 1)
    {
        return;
    }
    else if(GameData::gameState == GameData::STATE_PLAYING)
    {
        layerCombo->setVisible(true);
    }
    //    return;
    sprintf(buf, "%d", currentCombo);
    labelComboNum->setString(buf);
    
    startComboEffect();
}

void GameScene::comboReset()
{
    labelComboMul->setString("");
    currentCombo = 0;
    
    deltaComboNum = 1;
    layerCombo->setVisible(false);
    //    labelCombo->setVisible(false);
    labelComboNum->setString("");
    //    this->makeMeteor();
}


void GameScene::startComboEffect()
{
    if(currentCombo >= 2)
    {
        bool temp = currentCombo % 10 == 0;
        
        CCScaleTo* scaleAction = CCScaleTo::create(temp ? 0.03f : 0.02f, temp ? 2.8f : 2.3f);
        CCScaleTo* scaleActionReverse = CCScaleTo::create(0.05f, 2.0f);
        CCScaleTo* scaleAction2 = CCScaleTo::create(temp ? 0.03f : 0.02f, temp ? 2.8f : 2.3f);
        CCScaleTo* scaleActionReverse2 = CCScaleTo::create(0.05f, 2.0f);
        
        temp = currentCombo == 20 || currentCombo == 40 || currentCombo == 70 || currentCombo == 100;
        CCScaleTo* scaleAction3 = CCScaleTo::create(temp ? 0.05f : 0.02f, temp ? 4.0f : 2.3f);
        CCScaleTo* scaleActionReverse3 = CCScaleTo::create(0.05f, 2.0f);
        //    CCAction* actions = CCSpawn::create(scaleActionReverse, scaleAction, NULL);
        //    labelCombo->runAction(actions);
        //    labelComboNum->runAction(actions);
        labelComboNum->runAction(CCSequence::create(scaleAction, scaleActionReverse, NULL));
        labelCombo->runAction(CCSequence::create(scaleAction2, scaleActionReverse2, NULL));
        labelComboMul->runAction(CCSequence::create(scaleAction3, scaleActionReverse3, NULL));
    }
}


void GameScene::removeHumanSprite(HumanSprite *humanSprite)
{
    if(humanSprite->humanState == 1 && humanSprite->currentY > -200)
    {
        GameData::gameState = GameData::STATE_GAMEOVER;
        sprGameOver->setVisible(true);
        
        CocosDenshion::SimpleAudioEngine* instance = CocosDenshion::SimpleAudioEngine::sharedEngine();
        instance->stopBackgroundMusic();
        
        this->unschedule(schedule_selector(GameScene::update));
        layerCombo->setVisible(false);
        
        if(GameData::highScore < currentScore)
        {
            GameData::highScore = currentScore;
            FileIO::sharedInstance()->saveFile();
        }
        
        return;
    }
    arrayHumanSprite->removeObject(humanSprite);
    this->removeChild(humanSprite, true);
}

void GameScene::removeLaneSprite(LaneSprite *laneSprite)
{
    arrayLaneSprite->removeObject(laneSprite);
    this->removeChild(laneSprite, true);
}

void GameScene::removeRoadSprite(RoadSprite *roadSprite)
{
    arrayRoadSprite->removeObject(roadSprite);
    this->removeChild(roadSprite, true);
}

void GameScene::updateCharAnimation()
{
    currentRunAnimation++;
    
    switch(currentRunAnimation)
    {
        case 1:
            sprCharacter->setTexture(CCTextureCache::sharedTextureCache()->addImage("player1.png"));
            break;
            
        case 4:
            sprCharacter->setTexture(CCTextureCache::sharedTextureCache()->addImage("player2.png"));
            break;

        case 7:
            sprCharacter->setTexture(CCTextureCache::sharedTextureCache()->addImage("player3.png"));
            break;

        case 10:
            sprCharacter->setTexture(CCTextureCache::sharedTextureCache()->addImage("player4.png"));
            break;

        case 13:
            sprCharacter->setTexture(CCTextureCache::sharedTextureCache()->addImage("player5.png"));
            break;
            
        case 16:
            sprCharacter->setTexture(CCTextureCache::sharedTextureCache()->addImage("player6.png"));
            break;

        case 19:
            sprCharacter->setTexture(CCTextureCache::sharedTextureCache()->addImage("player7.png"));
            break;
            
        case 21:
            currentRunAnimation = 0;
            break;
    }
}

void GameScene::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void GameScene::changeCharLine(bool isRight)
{
    if(isRight)
    {
        if(currentLine < 4)
        {
            currentLine++;
        }
    }
    else
    {
        if(currentLine > 1)
        {
            currentLine--;
        }
    }
    switch(currentLine)
    {
        case 1:
            sprCharacter->setPosition(ccp(112, 150));
            break;
        case 2:
            sprCharacter->setPosition(ccp(337, 150));
            break;
        case 3:
            sprCharacter->setPosition(ccp(563, 150));
            break;
        case 4:
            sprCharacter->setPosition(ccp(787, 150));
            break;
    }
}

bool GameScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(GameData::gameState == GameData::STATE_PAUSE)
    {
        return false;
    }
    else if(GameData::gameState == GameData::STATE_GAMEOVER)
    {
        CocosDenshion::SimpleAudioEngine* instance = CocosDenshion::SimpleAudioEngine::sharedEngine();
        instance->stopBackgroundMusic();

        CCScene* scene = CCTransitionFade::create(0.3f, MainScene::scene());
        CCDirector::sharedDirector()->replaceScene(scene);

        GameData::gameState = GameData::STATE_PLAYING;
    
        return false;
    }
    int x = (CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView())).x;
    if(x>450)
    {
        this->changeCharLine(true);
    }
    else
    {
        this->changeCharLine(false);
    }
    return false;
}

void GameScene::createHumanSprite()
{
    
//    HumanSprite* spr = HumanSprite::create(rand() % 2, rand() % 4 + 1);
//    arrayHumanSprite->addObject(spr);

    humanCountZ--;
    if(humanCountZ == 3)
    {
        humanCountZ = 50;
    }
//    this->addChild(spr, humanCountZ);

    
    // HumanSprite::create(int humanState, int numLine); 으로 변경
    // 여자는 독립적으로 나오게 할 것, 지금은 임시로 GameScene::update()에서 생성함
    // humanState 0: couple 1: man 2: woman
    
    if( this->humanCount <= 20 )
    {
        HumanSprite* spr = HumanSprite::create(rand() % 2, rand() % 4 + 1);
        arrayHumanSprite->addObject(spr);
        this->addChild(spr, humanCountZ);
    }
    else if( this->humanCount <= 50 )
    {
        HumanSprite* spr[2];
        int block1 = rand() % 4 + 1;
        spr[0] = HumanSprite::create(0, block1);
        int block2 = (block1 + 1) % 4 + 1;
        spr[1] = HumanSprite::create(1, block2);
        arrayHumanSprite->addObject(spr[0]);
        this->addChild(spr[0], humanCountZ);
        arrayHumanSprite->addObject(spr[1]);
        this->addChild(spr[1], humanCountZ);
    }
    else if( this->humanCount <= 80 )
    {
        HumanSprite* spr[2];
        int block1 = rand() % 4 + 1;
        spr[0] = HumanSprite::create(0, block1);
        int block2 = (block1) % 4 + 1;
        spr[1] = HumanSprite::create(1, block2);
        arrayHumanSprite->addObject(spr[0]);
        this->addChild(spr[0], humanCountZ);
        arrayHumanSprite->addObject(spr[1]);
        this->addChild(spr[1], humanCountZ);
    }
    else if( this->humanCount <= 130 )
    {
        HumanSprite* spr[3];
        int block1 = rand() % 4 + 1;
        spr[0] = HumanSprite::create(1, block1);
        int block2 = (block1) % 4 + 1;
        int block3 = (block2 + 1) % 4 + 1;
        spr[1] = HumanSprite::create(0, block2);
        spr[2] = HumanSprite::create(0, block3);
        arrayHumanSprite->addObject(spr[0]);
        this->addChild(spr[0], humanCountZ);
        arrayHumanSprite->addObject(spr[1]);
        this->addChild(spr[1], humanCountZ);
        arrayHumanSprite->addObject(spr[2]);
        this->addChild(spr[2], humanCountZ);
    }
    else if( this->humanCount <= 200 )
    {
        HumanSprite* spr[3];
        int block1 = rand() % 4 + 1;
        spr[0] = HumanSprite::create(1, block1);
        int block2 = (block1) % 4 + 1;
        int block3 = (block2) % 4 + 1;
        spr[1] = HumanSprite::create(0, block2);
        spr[2] = HumanSprite::create(0, block3);
        arrayHumanSprite->addObject(spr[0]);
        this->addChild(spr[0], humanCountZ);
        arrayHumanSprite->addObject(spr[1]);
        this->addChild(spr[1], humanCountZ);
        arrayHumanSprite->addObject(spr[2]);
        this->addChild(spr[2], humanCountZ);
    }
    else
    {
        HumanSprite* spr[4];
        int block1 = rand() % 4 + 1;
        spr[0] = HumanSprite::create(1, block1);
        int block2 = (block1) % 4 + 1;
        int block3 = (block2) % 4 + 1;
        int block4 = (block2) % 4 + 1;
        spr[1] = HumanSprite::create(0, block2);
        spr[2] = HumanSprite::create(0, block3);
        spr[3] = HumanSprite::create(0, block4);
        arrayHumanSprite->addObject(spr[0]);
        this->addChild(spr[0], humanCountZ);
        arrayHumanSprite->addObject(spr[1]);
        this->addChild(spr[1], humanCountZ);
        arrayHumanSprite->addObject(spr[2]);
        this->addChild(spr[2], humanCountZ);
        arrayHumanSprite->addObject(spr[3]);
        this->addChild(spr[3], humanCountZ);
    }
    // Human Cound
    this->humanCount++;
}

void GameScene::createLaneSprite()
{
    LaneSprite* spr1 = LaneSprite::create(1);
    arrayLaneSprite->addObject(spr1);
    LaneSprite* spr2 = LaneSprite::create(2);
    arrayLaneSprite->addObject(spr2);
    LaneSprite* spr3 = LaneSprite::create(3);
    arrayLaneSprite->addObject(spr3);

    this->addChild(spr1, 3);
    this->addChild(spr2, 3);
    this->addChild(spr3, 3);
}

void GameScene::createRoadSprite()
{
    roadChairCoolTime++;
    bool isChair = false;
    if(roadChairCoolTime == 3)
    {
        roadChairCoolTime = 0;
        isChair = true;
    }
    
    RoadSprite* spr1 = RoadSprite::create(true, isChair);
    arrayRoadSprite->addObject(spr1);
    RoadSprite* spr2 = RoadSprite::create(false, isChair);
    arrayRoadSprite->addObject(spr2);
    
    this->addChild(spr1, 3);
    this->addChild(spr2, 3);
}

void GameScene::initCloudSprite()
{
	this->arrayCloudSprite = CCArray::create();
	this->arrayCloudSprite->retain();

	CCloudSprite* cloud[8];
	for( int i = 0; i < 8; i++ )
	{
		cloud[i] = CCloudSprite::create();
		this->arrayCloudSprite->addObject(cloud[i]);
		this->addChild(cloud[i], 2);
	}
}

void GameScene::clickBtnPause(CCObject* pOjbect)
{
    //    initMenuItemBtnPause();
    if(GameData::gameState == GameData::STATE_GAMEOVER)
    {
        return;
    }
    startSoundEffect("pong.wav");
    GameData::gameState = GameData::STATE_PAUSE;
    layerPauseMenu->setVisible(true);
    
    CocosDenshion::SimpleAudioEngine* instance = CocosDenshion::SimpleAudioEngine::sharedEngine();
    instance->pauseBackgroundMusic();
}

void GameScene::clickBtnExit(CCObject* pObject)
{
    CocosDenshion::SimpleAudioEngine* instance = CocosDenshion::SimpleAudioEngine::sharedEngine();
    instance->stopBackgroundMusic();

    CCScene* scene = CCTransitionFade::create(0.3f, MainScene::scene());
    CCDirector::sharedDirector()->replaceScene(scene);
//    GameData::gameState = GameData::STATE_PLAYING;
}

void GameScene::clickBtnRestart(CCObject* pObject)
{
//    layerPauseMenu->setVisible(false);
//    GameData::gameState = GameData::STATE_PLAYING;
    HumanSprite::maxFrame = 300;
/*
    int count = arrayHumanSprite->count();
    for(int i = count-1; i >= 0; i--)
    {
        HumanSprite* buf = (HumanSprite*) arrayHumanSprite->objectAtIndex(i);
        arrayHumanSprite->removeObjectAtIndex(i);
        this->removeChild(buf, true);
    }
    
    count = arrayLaneSprite->count();
    for(int i = count-1; i >= 0; i--)
    {
        LaneSprite* buf = (LaneSprite*) arrayLaneSprite->objectAtIndex(i);
        arrayLaneSprite->removeObjectAtIndex(i);
        this->removeChild(buf, true);
    }
  */
    CCScene* scene = CCTransitionFade::create(0.3f, GameScene::scene());
    CCDirector::sharedDirector()->replaceScene(scene);
    
}

void GameScene::clickBtnResume(CCObject* pObject)
{
    layerPauseMenu->setVisible(false);
    GameData::gameState = GameData::STATE_PLAYING;

    CocosDenshion::SimpleAudioEngine* instance = CocosDenshion::SimpleAudioEngine::sharedEngine();
    instance->resumeBackgroundMusic();
}


void GameScene::initSpriteBackground()
{
    sprBackground = CCSprite::create("newbackground.png");
    sprBackground->setPosition(ccp(450, 800));
    this->addChild(sprBackground, 1);
}

void GameScene::initSpriteCharacter()
{
    sprCharacter = CCSprite::create("player1.png");
    sprCharacter->setPosition(ccp(337, 170));
    this->addChild(sprCharacter, 99);
}

void GameScene::initBtnPause()
{
    menuItemPause = CCMenuItemImage::create("pausebutton.png", "pausebuttonpressed.png", this, menu_selector(GameScene::clickBtnPause));
//    menuItemPause->setAnchorPoint(ccp(0, 1));
    menuItemPause->setScale(1.5f);
    
    menuBtnPause = CCMenu::create(menuItemPause, NULL);
    
    menuBtnPause->setPosition(ccp(100, 1500));
    this->addChild(menuBtnPause, 10);
}

void GameScene::initLayerPause()
{
    CCMenuItem* menuItemResume = CCMenuItemImage::create("resumeon.png", "resumeoff.png", this, menu_selector(GameScene::clickBtnResume));
    CCMenuItem* menuItemRestart = CCMenuItemImage::create("restarton.png", "restartoff.png", this, menu_selector(GameScene::clickBtnRestart));
    CCMenuItem* menuItemExit = CCMenuItemImage::create("exiton_.png", "exitoff_.png", this, menu_selector(GameScene::clickBtnExit));
    
//    menuItemResume->setScale(0.7f);
//    menuItemExit->setScale(0.7f);
//    menuItemRestart->setScale(0.7f);

    menuStatePause = CCMenu::create(menuItemResume, menuItemRestart, menuItemExit, NULL);
    menuStatePause->alignItemsVerticallyWithPadding(40); // 7
    menuStatePause->setPosition(ccp(0, 0));
    menuStatePause->setPosition(ccp(450, 600));
    
    sprPauseLabel = CCSprite::create("pausescreen.png");
    sprPauseLabel->setPosition(ccp(450, 800));
//    sprPauseLabel->setScale(0.9f);
    
    layerPauseMenu = CCLayer::create();
    layerPauseMenu->addChild(sprPauseLabel);
    layerPauseMenu->addChild(menuStatePause);
    
    layerPauseMenu->setVisible(false);
    this->addChild(layerPauseMenu, 100);
}

void GameScene::initSpriteGameOver()
{
    sprGameOver = CCSprite::create("gameover.png");
    sprGameOver->setPosition(ccp(450, 800));
    sprGameOver->setVisible(false);
    this->addChild(sprGameOver, 101);
}

void GameScene::startBackgroundMusic()
{
    CocosDenshion::SimpleAudioEngine* instance = CocosDenshion::SimpleAudioEngine::sharedEngine();
    instance->stopBackgroundMusic();
    
    
    if(GameData::isMusicSound)
    {
        instance->playBackgroundMusic("game.wav", true);
    }
}

void GameScene::startSoundEffect(std::string fileName)
{
    if(GameData::isMusicSound)
    {
        (CocosDenshion::SimpleAudioEngine::sharedEngine())->playEffect(fileName.c_str());
    }
}

void GameScene::initBMFont()
{
    
    layerCombo = CCLayer::create();
    
    labelCombo = CCLabelBMFont::create("Combo", "bmfontCB64.fnt");
    //    labelCombo->setPosition(ccp(planetCenterX, /*450*/465));
    labelCombo->setPosition(ccp(450, 1350));
    //    labelCombo->setOpacity(180);
    labelCombo->setColor(ccc3(255, 255, 0));
    //    labelCombo->setVisible(false);

    labelCombo->setScale(1.6f);
    layerCombo->addChild(labelCombo);
    
    labelComboNum = CCLabelBMFont::create("", "bmfontCB64.fnt");
    //    labelComboNum->setPosition(ccp(planetCenterX, /*370*/ 400));
    labelComboNum->setPosition(ccp(450, 1230));
    //    labelComboNum->setOpacity(180);
    labelComboNum->setColor(ccc3(255, 255, 0));
    labelComboNum->setScale(1.6f);
    layerCombo->addChild(labelComboNum);
    
    labelComboMul = CCLabelBMFont::create("", "bmfontCB64.fnt");
    labelComboMul->setPosition(ccp(660, 1200));
    labelComboMul->setScale(2.0f);
    labelComboMul->setVisible(false);
    //    labelComboMul->setAnchorPoint(ccp(1.0f, 0.5f));
    //    labelComboMul->setPosition(ccp(/*550*/550, /*320*/370));
    //    labelComboMul->setOpacity(180);
    //    labelComboMul->setColor(ccc3(255, 255, 100));
    
    layerCombo->addChild(labelComboMul);
    layerCombo->setVisible(false);
    //    layerCombo->setAnchorPoint(ccp(450, 370));
    
    this->addChild(layerCombo, 98);
    
    ///
    
    labelScore = CCLabelBMFont::create("0", "bmfontCB64.fnt");;
    //    labelScore->setPosition(ccp(planetCenterX, planetCenterY));
    labelScore->setPosition(ccp(660, 1550));
    labelScore->setColor(ccc3(255, 255, 255));
    labelScore->setScale(1.4f);
    labelScore->setAnchorPoint(ccp(1.0f, 0.5f));
    this->addChild(labelScore, 98);
    
    labelScoreSpell = CCLabelBMFont::create("Score", "bmfontCB64.fnt");
    labelScoreSpell->setPosition(ccp(880, 1540));
    labelScoreSpell->setColor(ccc3(255, 255, 255));
    labelScoreSpell->setScale(1.1f);
    labelScoreSpell->setAnchorPoint(ccp(1.0f, 0.5f));
    this->addChild(labelScoreSpell, 98);
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void GameScene::keyBackClicked()
{
    if(GameData::gameState == GameData::STATE_PLAYING)
    {
//        startSoundEffect("pong.wav");
        this->clickBtnPause(NULL);
    }
    else
    {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, "com.solo.manse/SoloManse", "backButton", "()V"))
        {
            ///< 함수 호출
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
            ///< Release
            t.env->DeleteLocalRef(t.classID);
        }
    }
}
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
