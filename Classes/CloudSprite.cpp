//
//  CloudSprite.cpp
//  MentalCare
//
//  Created by Kyoseung_Hackathon on 13. 12. 15..
//
//

#include "CloudSprite.h"

CCloudSprite::CCloudSprite()
{
    this->s_cloud[0].m_cloud = CCSprite::create("cloud1.png");
    this->s_cloud[1].m_cloud = CCSprite::create("cloud2.png");
    this->s_cloud[2].m_cloud = CCSprite::create("cloud3.png");
    this->s_cloud[3].m_cloud = CCSprite::create("cloud4.png");
    this->s_cloud[4].m_cloud = CCSprite::create("cloud3.png");
    this->s_cloud[5].m_cloud = CCSprite::create("cloud2.png");

    this->s_cloud[0].posX = 123;
    this->s_cloud[1].posX = 234;
    this->s_cloud[2].posX = 345;
    this->s_cloud[3].posX = 526;
    this->s_cloud[4].posX = -20;
    this->s_cloud[5].posX = 859;
    
    this->s_cloud[0].posY = 1456;
    this->s_cloud[1].posY = 1654;
    this->s_cloud[2].posY = 1579;
    this->s_cloud[3].posY = 1369;
    this->s_cloud[4].posY = 1404;
    this->s_cloud[5].posY = 1311;
    
    this->s_cloud[0].cloudSpeed = 2;
    this->s_cloud[1].cloudSpeed = 3.8;
    this->s_cloud[2].cloudSpeed = 5;
    this->s_cloud[3].cloudSpeed = 2.4;
    this->s_cloud[4].cloudSpeed = 3.1;
    this->s_cloud[5].cloudSpeed = 4.3;
    
}

CCloudSprite::~CCloudSprite()
{
    
}

void CCloudSprite::update()
{
    for( int i = 0; i < 6; i++ )
    {
        this->s_cloud[i].posX += this->s_cloud[i].cloudSpeed;
        this->s_cloud[i].m_cloud->setPosition( CCPointMake( this->s_cloud[i].posX , this->s_cloud[i].posY ));
        if( this->s_cloud[i].posX >= 1000)
            this->setCloud(i);
    }
}

void CCloudSprite::setCloud(int num)
{
    this->s_cloud[num].posY = 1400 + (rand() % 300);
    this->s_cloud[num].cloudSpeed = 2 + (( rand() % 50 ) / 10);
    this->s_cloud[num].posX = -100;
}
