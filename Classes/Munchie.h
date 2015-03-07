#ifndef MUNCHIE_H_
#define MUNCHIE_H_

#include "cocos2d.h"
#include "constants.h"

class Munchie : public cocos2d::CCNode
{
public:
	Munchie();
	~Munchie();
	static Munchie* create();
	void bindSprite(CCSprite* sprite);
	CCSprite* getSprite();
	bool isMouthOpen();
	void openMouth();
	void keepMouthOpen();
	void createAnimations(int cycles);
	void playAnimation(CCArray* frames, float frameRate, bool repeat);
	CCArray* getWalkingFrames();
	CCArray* getEwwFrames();
	void closeMouth();
private:
	CCSprite *munchieSprite;
	CCArray *walkingFrames, *eatingFrames, *ewwFrames;
	bool mouthOpen;
	float openTimer, maxOpenTime;
	long lastUpdateTime;
};

#endif
