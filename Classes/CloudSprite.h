#pragma once
#include "cocos2d.h"

class CCloudSprite : public cocos2d::CCSprite
{
public:
	CCloudSprite(void);
	CCloudSprite(float x, float y, float speed);
	~CCloudSprite(void);

	static CCloudSprite* create();
	static CCloudSprite* create(float x, float y, float speed);
	void update();
private:
	float cloudSpeed;
	float cX, cY;

	void resetCloud();
};

