#include "CloudSprite.h"

CCloudSprite::CCloudSprite(void)
{
	this->cloudSpeed = rand()% 6 + 1;
	this->cX = rand()% 1100 - 100;
	this->cY = rand()% 400 + 1200;

	this->setScale( 1.0f );
	this->setPosition( ccp( this->cX, this->cY ) );
}

CCloudSprite::~CCloudSprite(void)
{
}

CCloudSprite* CCloudSprite::create()
{
	CCloudSprite *pobSprite = new CCloudSprite();
	int rnd = rand()%4;
	bool enPob = false;
	if( pobSprite/*&& pobSprite->initWithFile("cloud1.png") */)
	{
		if( rnd == 0 )
		{
			if( pobSprite->initWithFile("cloud1.png") )
			{
				enPob = true;
			}
		}
		else if( rnd == 1 )
		{
			if( pobSprite->initWithFile("cloud2.png") )
			{
				enPob = true;
			}
		}
		else if( rnd == 2 )
		{
			if( pobSprite->initWithFile("cloud3.png") )
			{
				enPob = true;
			}
		}
		else if( rnd == 3 )
		{
			if( pobSprite->initWithFile("cloud4.png") )
			{
				enPob = true;
			}
		}

		if( enPob == true )
		{	
			pobSprite->autorelease();
			return pobSprite;
		}
	}
	CC_SAFE_DELETE( pobSprite );
	return NULL;
}

void CCloudSprite::update()
{
	this->cX += this->cloudSpeed;
	if( this->cX >= 1000 )
		this->resetCloud();
	this->setPosition( ccp( this->cX, this->cY ) );
}

void CCloudSprite::resetCloud()
{
	this->cX = -100;
	this->cY = this->cY = rand()% 300 + 1200;
	this->cloudSpeed = rand()% 6 + 1;
}