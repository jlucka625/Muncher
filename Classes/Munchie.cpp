#include "Munchie.h"

Munchie::Munchie()
{
	munchieSprite = NULL;
	mouthOpen = false;
	openTimer = 0.0f;
	maxOpenTime = 80.0f;
}

Munchie::~Munchie(){}

Munchie* Munchie::create()
{
	Munchie* m = new Munchie;
	m->autorelease();
	return m;
}

void Munchie::bindSprite(CCSprite* sprite)
{
	munchieSprite = sprite;
	this->addChild(munchieSprite);
}

CCSprite* Munchie::getSprite()
{
	return munchieSprite;
}

void Munchie::openMouth()
{
	if(!mouthOpen)
	{
		mouthOpen = true;
		lastUpdateTime = Utils::getCurrentTime();
		this->schedule(schedule_selector(Munchie::keepMouthOpen));
		munchieSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("munchie.png"));
	}
}

void Munchie::closeMouth()
{
	mouthOpen = false;
	openTimer = 0.0f;
	this->unschedule(schedule_selector(Munchie::keepMouthOpen));
	munchieSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("munchiecl.png"));
}

void Munchie::keepMouthOpen()
{
	openTimer += Utils::getCurrentTime() - lastUpdateTime;
	if(openTimer >= maxOpenTime)
	{
		closeMouth();
	}
	lastUpdateTime = Utils::getCurrentTime();
}

void Munchie::createAnimations(int cycles)
{
	walkingFrames = CCArray::create();
	walkingFrames->retain();
	eatingFrames = CCArray::create();
	eatingFrames->retain();
	ewwFrames = CCArray::create();
	ewwFrames->retain();

	//for(int i = 0; i < cycles; i++)
	//{
		walkingFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("munchiecl.png"));
		walkingFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("munchiecl2.png"));
		//eatingFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("munchie.png"));
		//eatingFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("munchie2.png"));
	//}
	//walkingFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("munchiecl.png"));
	//eatingFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("munchie.png"));

	for(int i = 0; i < 5; i++)
	{
		ewwFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("munchiehit.png"));
	}
	ewwFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("munchiecl.png"));
}

void Munchie::playAnimation(CCArray* frames, float frameRate, bool repeat)
{
	munchieSprite->stopAllActions();

	if(repeat)
		munchieSprite->runAction(CCRepeatForever::create(CCAnimate::create(CCAnimation::create(frames, frameRate))));
	else
		munchieSprite->runAction(CCAnimate::create(CCAnimation::create(frames, frameRate)));

}

bool Munchie::isMouthOpen()
{
	return mouthOpen;
}

CCArray* Munchie::getWalkingFrames()
{
	return walkingFrames;
}

CCArray* Munchie::getEwwFrames()
{
	return ewwFrames;
}




