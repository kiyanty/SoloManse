#pragma once
#include "cocos2d.h"

class CCloudSprite : public cocos2d::CCSprite
{
public:
	CCloudSprite(void);
	~CCloudSprite(void);

	static CCloudSprite* create();
	void update();
private:
	float cloudSpeed;
	float cX, cY;

	void resetCloud();
};

