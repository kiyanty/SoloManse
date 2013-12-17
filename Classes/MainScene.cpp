#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "GameData.h"
#include "FileIO.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID


using namespace cocos2d;
using namespace CocosDenshion;

CCScene* MainScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MainScene *layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    this->initBackground();
    // Background init
    
    
    
    this->initMenu();
    // Menu init
    this->initToggleBtn();
    this->initLayer();
    // Layer init
    
    this->mainCloud = new CCloudSprite();
    for( int i = 0; i < 6; i++ )
        this->addChild( this->mainCloud->s_cloud[i].m_cloud );
    
    this->initSprite();

    
    this->uFrame = 0;
    this->inMenu = 0;
    this->schedule( schedule_selector(MainScene::update) );
    // update Register
    this->setTouchEnabled(true);
    
    CocosDenshion::SimpleAudioEngine* instance = CocosDenshion::SimpleAudioEngine::sharedEngine();
    instance->stopBackgroundMusic();
    
    
    if(GameData::isMusicSound)
    {
        instance->playBackgroundMusic("main.wav", true);
    }

    
    return true;
}

// Background init
void MainScene::initBackground()
{
    this->sprBackground = CCSprite::create("mainbackground.png");
    this->sprBackground->setPosition(ccp(450, 800));
    this->addChild(this->sprBackground);
}

void MainScene::initSprite()
{
    this->sprMainLogo = CCSprite::create("title.png");
    this->sprMainLogo->setPosition(ccp(450, 800));
    this->addChild(this->sprMainLogo);
}

// Menu init
void MainScene::initMenu()
{
    
    this->miStart = CCMenuItemImage::create("starton.png", "startoff.png", this, menu_selector(MainScene::gotoGameScene));
    this->miHowTo = CCMenuItemImage::create("howtoon.png", "howtooff.png", this, menu_selector(MainScene::initHowtoLayer));
    this->miRanking = CCMenuItemImage::create("rankon.png", "rankoff.png", this, menu_selector(MainScene::gotoRankHomePage));
    this->miCredit = CCMenuItemImage::create("crediton.png", "creditoff.png", this, menu_selector(MainScene::initCreditLayer));
    this->miExit = CCMenuItemImage::create("exiton.png", "exitoff.png", this, menu_selector(MainScene::menuCloseCallback));
    
    this->menuMain = CCMenu::create( this->miStart, this->miHowTo, this->miRanking, this->miCredit, this->miExit, NULL );
    this->menuMain->alignItemsVerticallyWithPadding(40);
    this->menuMain->setPosition( ccp(450, 500) );
    this->addChild(this->menuMain);
}

void MainScene::gotoRankHomePage()
{
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //    CCMessageBox("Developer : Joong Seok Lee\nIllustrator : Min Su Park\n\n[ Homepage ]\nfacebook.com/StoneAttack", "Stone Attack\n- The Last Survivor -");
    char buf[200];
    sprintf(buf, "%s%d%s%d", "http://chilx2.cafe24.com/apps/server/solo/save_Rank.php?id=", GameData::guestId, "&score=", GameData::highScore);
    
//    NSString* str = [NSString stringWithString:@"http://chilx2.cafe24.com/apps/server/solo/save_Rank.php?name="];
    
    
    NSURL * url = [NSURL URLWithString:[NSString stringWithUTF8String:buf]];
    [[UIApplication sharedApplication] openURL: url];
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //    CCMessageBox("Developer : Joong Seok Lee\nIllustrator : Min Su Park\n\n[ Homepage ]\nfacebook.com/StoneAttack", "Stone Attack");
    
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "com.solo.manse/SoloManse", "goHomepage", "(II)V"))
    {
        ///< 함수 호출
        t.env->CallStaticVoidMethod(t.classID, t.methodID, GameData::guestId, GameData::highScore);
        ///< Release
        t.env->DeleteLocalRef(t.classID);
    }
    
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
}

// Layer init
void MainScene::initLayer()
{
    this->howtoLayer[0] = NULL;
    this->howtoLayer[1] = NULL;
    this->creditLayer = NULL;
}

// update
void MainScene::update()
{
    this->mainCloud->update();
    // 시간에 따른 배경화면 변경
}

// GameScene 으로 
void MainScene::gotoGameScene()
{
    CCScene* scene = CCTransitionFade::create(0.3f, GameScene::scene());
    CCDirector::sharedDirector()->replaceScene(scene);
}

// 게임 종료
void MainScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

// HowtoLayer init
void MainScene::initHowtoLayer()
{
    this->menuMain->setEnabled(false);
    this->menuBtnSetting->setEnabled(false);
    if( this->howtoLayer[0] == NULL )
    {
        this->howtoLayer[0] = CCLayer::create();
        this->howtoLayer[1] = CCLayer::create();
        
        CCSprite* sprHowtoBackground1 = CCSprite::create("howto1.png");
        sprHowtoBackground1->setPosition(ccp(450, 800));
        CCSprite* sprHowtoBackground2 = CCSprite::create("howto2.png");
        sprHowtoBackground2->setPosition(ccp(450, 800));
    
        this->howtoLayer[0]->addChild( sprHowtoBackground1 );
        this->howtoLayer[1]->addChild( sprHowtoBackground2 );
        this->addChild( this->howtoLayer[0]);
        this->addChild( this->howtoLayer[1]);
        this->howtoLayer[1]->setVisible(false);
    }
    else
    {
        this->howtoLayer[0]->setVisible( true );
        this->howtoLayer[1]->setVisible( false );
    }
    this->inMenu = 11;
}

// CreditLayer init
void MainScene::initCreditLayer()
{
    this->menuMain->setEnabled(false);
        this->menuBtnSetting->setEnabled(false);
    if( this->creditLayer == NULL )
    {
        this->creditLayer = CCLayer::create();
        
        CCSprite* sprCreditBackground = CCSprite::create("credit_.png");
        sprCreditBackground->setPosition(ccp(450, 800));
    
        this->creditLayer->addChild( sprCreditBackground );
        this->addChild( this->creditLayer );
    }
    else
    {
        this->creditLayer->setVisible( true );
    }
    this->inMenu = 21;
}

// out HowtoLayer
void MainScene::outHowtoLayer()
{
    this->howtoLayer[0]->setVisible( false );
    this->howtoLayer[1]->setVisible( false );
    this->menuMain->setEnabled(true);
    this->menuBtnSetting->setEnabled(true);
}

// out CreditLayer
void MainScene::outCreditLayer()
{
    this->menuMain->setEnabled(true);
    this->menuBtnSetting->setEnabled(true);
    this->creditLayer->setVisible( false );
}


void MainScene::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool MainScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if( this->inMenu == 11 )
    {
        this->howtoLayer[0]->setVisible(false);
        this->howtoLayer[1]->setVisible(true);
        this->inMenu = 12;
    }
    else if( this->inMenu == 12 )
        this->outHowtoLayer();
    else if( this->inMenu == 21 )
        this->outCreditLayer();
        
    // 한번 클릭할 때마다 호출됨.
    return false;
}

void MainScene::clickOptionMusic()
{
    GameData::isMusicSound = !GameData::isMusicSound;
    FileIO::sharedInstance()->saveFile();
    CocosDenshion::SimpleAudioEngine* instance = CocosDenshion::SimpleAudioEngine::sharedEngine();
    instance->stopBackgroundMusic();
    if(GameData::isMusicSound)
    {
        
        instance->playBackgroundMusic("main.wav", true);
    }
}

void MainScene::initToggleBtn()
{
    CCMenuItemImage* btn1_1;
    CCMenuItemImage* btn1_2;
    
    if(GameData::isMusicSound)
    {
        btn1_1 = CCMenuItemImage::create("soundon.png", "soundoff.png");
        btn1_2 = CCMenuItemImage::create("soundoff.png", "soundon.png");
    }
    else
    {
        btn1_2 = CCMenuItemImage::create("soundon.png", "soundoff.png");
        btn1_1 = CCMenuItemImage::create("soundoff.png", "soundon.png");
    }

//    btn1_1->setScale(0.5f);
//    btn1_2->setScale(0.5f);
    
    CCMenuItemToggle* toggle1 = CCMenuItemToggle::createWithTarget(this, menu_selector(MainScene::clickOptionMusic), btn1_1, btn1_2, NULL);

    menuBtnSetting = CCMenu::create(toggle1, NULL);
    menuBtnSetting->setPosition(ccp(770, 130));
    this->addChild(menuBtnSetting);
}