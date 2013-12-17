#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "HumanSprite.h"
#include "LaneSprite.h"
#include "CloudSprite.h"

using namespace cocos2d;

class GameScene : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    static GameScene* gameScene;
    static int currentLine;
    
    int currentScore;
    int currentCombo;
    int deltaComboNum;
    
    void comboPlus();
    
    void comboReset();

    void removeHumanSprite(HumanSprite* humanSprite);
    void removeLaneSprite(LaneSprite* LaneSprite);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameScene);
    
private:

    CCSprite* sprBackground;
    CCSprite* sprCharacter;
    CCSprite* sprGameOver;
    
    CCArray* arrayHumanSprite;
    CCArray* arrayLaneSprite;
    
    CCLayer* layerPauseMenu;
    CCMenu* menuStatePause;
    CCSprite* sprPauseLabel;

    
    CCMenu* menuBtnPause;
    CCMenuItem* menuItemPause;

    
    CCLabelBMFont* labelCombo;
    CCLabelBMFont* labelComboNum;
    CCLabelBMFont* labelComboMul;
    
    CCLabelBMFont* labelScore;
    CCLayer* layerCombo;
    CCLayerColor* layerColorFlash;
    CCLabelBMFont* labelScoreSpell;
    
    //추가부분
    int humanCount;    
    CCloudSprite *mainCloud;
    
    // 끝
    
    bool isHighestScore;

    
    
    int humanCountZ;
    
    int currentRunAnimation;
    int time;
//    int currentLine = 2;
    
    void updateCharAnimation();
    void changeCharLine(bool isRight);
    void update();
    
    void createHumanSprite();
    void createLaneSprite();
    
    void initBtnPause();
    void initSpriteBackground();
    void initSpritePlanet();
    void initSpritePause();
    void initSpriteStateBar();
    void initSpriteCharacter();
    void initSpriteGameOver();
    void initMenuItemBtnPause();
    void initBMFont();
    
    void initLayerPause();
    
    void initPlayerState();
    void initSpriteShield();
    void initShieldState();
    void initOptionBox();
    void initEtc();
    void initController();
    void initGameover();
    
    void startBackgroundMusic();
    void startSoundEffect(std::string fileName);
    
    // 메뉴 콜백
    void clickBtnPause();
    void clickBtnResume();
    void clickBtnExit();
    void clickBtnRestart();
    
    
    void registerWithTouchDispatcher();
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    
    ///
    void startComboEffect();

};

#endif // __HELLOWORLD_SCENE_H__
