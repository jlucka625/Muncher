#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "cocos2d.h"

class MainGame : public cocos2d::CCLayer
{
public:
	cocos2d::CCArray *munchers, *pipes, *candies, *candiesToRemove;
	float dropTimer, timeBetweenDrops, walkingDistance, minTimeBetweenDrops, maxWalkingDistance, accel, maxWalkingTime;
	cocos2d::CCRect boundingBox;
	float newX, newY, newWidth, newHeight;
	bool secondMuncher, thirdMuncher, muncherMoving;
	int currentPipeIndex, activePipeCount;
	long lastUpdateTime;

	virtual bool init();
	static cocos2d::CCScene* scene();

	//overrides
	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	//scheduled events
	void update();
	void walkMuncher();

	//other methods
	void spawnCandy();
	void dropCandy();
	void removeCandies();
	void missed();
	void increaseDifficulty();
	void spawnNewMuncher(int xPos);

	void menuCloseCallback(CCObject* pSender);
	LAYER_CREATE_FUNC(MainGame);
};

#endif
