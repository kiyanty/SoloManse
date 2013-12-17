//
//  RatingScene.h
//  StoneAttack
//
//  Created by neko on 13. 2. 28..
//
//

#ifndef __StoneAttack__RatingScene__
#define __StoneAttack__RatingScene__

#include "cocos2d.h"

class RatingScene : public cocos2d::CCLayer
{
public:
    // Scene 초기화
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(RatingScene);

    
private:
    void nextScene();
};

#endif /* defined(__StoneAttack__RatingScene__) */
