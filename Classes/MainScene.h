#ifndef __MainScene_SCENE_H__
#define __MainScene_SCENE_H__

#include "cocos2d.h"
#include "CloudSprite.h"

using namespace cocos2d;

class MainScene : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(MainScene);
    
private:
    CCSprite* sprBackground;
    CCSprite* sprMainLogo;

    CCMenu* menuMain;
    CCMenuItem *miStart, *miHowTo, *miRanking, *miCredit, *miExit;
    
    CCLayer *howtoLayer[2], *creditLayer;
    
    CCloudSprite *mainCloud;
    
    CCMenu* menuBtnSetting;
    
    // 시작한 후 프레임 수
    int uFrame;
    
    int inMenu;
    
    // init
    void initBackground();
    void initSprite();
    void initMenu();
    void initLayer();
    
    void initToggleBtn();
    // After init
    void initHowtoLayer();
    void initCreditLayer();
    
    // Out Layer
    void outHowtoLayer();
    void outCreditLayer();
    
    // Scene
    void gotoGameScene();
    void gotoHowtoScene();
    void gotoCreditScene();
    void gotoRankHomePage();
    
    void clickOptionMusic();
    
    void virtual update();
    
    void registerWithTouchDispatcher();
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
};

#endif // __MainScene_SCENE_H__
