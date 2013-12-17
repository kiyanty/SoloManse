//
//  CloudSprite.h
//  MentalCare
//
//  Created by Kyoseung_Hackathon on 13. 12. 15..
//
//

#ifndef __MentalCare__CloudSprite__
#define __MentalCare__CloudSprite__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;


class CCloudSprite
{
public:
    CCloudSprite();
    ~CCloudSprite();
    
    struct SCloud{
        CCSprite *m_cloud;
        float posX, posY;
        float cloudSpeed;
    }s_cloud[6];
    void virtual update();
    
private:
    void setCloud(int num);
};

#endif /* defined(__MentalCare__CloudSprite__) */
