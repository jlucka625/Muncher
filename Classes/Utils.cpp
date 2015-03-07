/*
 * Utils.cpp
 *
 *  Created on: Mar 5, 2014
 *      Author: jonathanlucka
 */

#include "Utils.h"
#include "Constants.h"

using namespace cocos2d;

static int proportion = 0;

MainGame* Utils::gameLayer()
{
	return (MainGame*)Utils::layerWithTag(TAG_GAME_LAYER);
}

HUD* Utils::hudLayer()
{
	return (HUD*)Utils::layerWithTag(TAG_HUD);
}

CCLayer* Utils::layerWithTag(int tag)
{
	CCScene *scene = CCDirector::sharedDirector()->getRunningScene();
	if(scene->getTag() == TAG_GAME_SCENE)
	{
		CCLayer *layer = (CCLayer*)scene->getChildByTag(tag);
		return layer;
	}
	return NULL;
}

CCSize Utils::size()
{
    return CCDirector::sharedDirector()->getWinSize();
}

void Utils::scale(CCSprite *sprite, float scaleFactor)
{
    float rX = (Utils::size().width / sprite->getContentSize().width)/scaleFactor;
    float rY = (Utils::size().height / sprite->getContentSize().height)/(16 * scaleFactor/9);

    sprite->setScaleX(rX);
    sprite->setScaleY(rY);
}

void Utils::scale(CCMenuItemSprite *sprite, float scaleFactor)
{
    float rX = (Utils::size().width / sprite->getContentSize().width)/scaleFactor;
    float rY = (Utils::size().height / sprite->getContentSize().height)/(16 * scaleFactor/9);

    sprite->setScaleX(rX);
    sprite->setScaleY(rY);
}

void Utils::bgScale(CCSprite *sprite)
{
    float rX = (Utils::size().width / sprite->getContentSize().width);
    float rY = (Utils::size().height / sprite->getContentSize().height);

    sprite->setScaleX(rX);
    sprite->setScaleY(rY);
}

bool Utils::hitLeftEdge(CCSprite *sprite)
{
	if(CCRect::CCRectGetMinX(sprite->boundingBox()) <= 0)
		return true;
	else return false;
}

bool Utils::hitRightEdge(CCSprite *sprite)
{
	if(CCRect::CCRectGetMaxX(sprite->boundingBox()) >= Utils::size().width)
		return true;
	else return false;
}

void Utils::setProportion(int width)
{
	proportion = Utils::size().width/width;
}

int Utils::getProportion()
{
	return proportion;
}
float Utils::getActualWidth(CCSprite *sprite)
{
	return (sprite->getContentSize().width * sprite->getScaleX());
}
float Utils::getActualHeight(CCSprite *sprite)
{
	return (sprite->getContentSize().height * sprite->getScaleY());
}

long Utils::getCurrentTime()
{
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
	/*time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	float totalMs = (timeinfo->tm_year * 31,536,000 + timeinfo->tm_mon * 2,628,000 +
			timeinfo->tm_mday * 86400 + timeinfo->tm_hour * 3600 + timeinfo->tm_min * 60 +
			timeinfo->tm_sec) * 1000;
	return totalMs;*/
}






