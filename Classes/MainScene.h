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

	CCArray* arrayCloudSprite;

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
	void initCloudSprite();
    
    void initToggleBtn();
    // After init
    void initHowtoLayer(CCObject*);
    void initCreditLayer(CCObject*);
    
    // Out Layer
    void outHowtoLayer();
    void outCreditLayer();
    
    // Scene
    void gotoGameScene(CCObject*);
    void gotoHowtoScene();
    void gotoCreditScene();
    void gotoRankHomePage(CCObject*);
    
    void clickOptionMusic(CCObject*);
    
    void virtual update(float);
    
    void registerWithTouchDispatcher();
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    virtual void keyBackClicked();
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
};

#endif // __MainScene_SCENE_H__
