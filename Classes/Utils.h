/*
 * Utils.h
 *
 *  Created on: Mar 5, 2014
 *      Author: jonathanlucka
 */

#ifndef UTILS_H_
#define UTILS_H_

#include "cocos2d.h"
#include "HUD.h"
#include "GameScene.h"

using namespace cocos2d;

class Utils
{
public:
    static MainGame* gameLayer();
    static HUD* hudLayer();
    static cocos2d::CCLayer* layerWithTag(int tag);
    static cocos2d::CCSize size();
    static void scale(cocos2d::CCSprite *sprite, float scaleFactor);
    static void scale(cocos2d::CCMenuItemSprite *sprite, float scaleFactor);
    static void bgScale(cocos2d::CCSprite *sprite);
    static bool hitLeftEdge(cocos2d::CCSprite *sprite);
    static bool hitRightEdge(cocos2d::CCSprite *sprite);
    static void setProportion(int width);
    static int getProportion();
    static float getActualHeight(CCSprite *sprite);
    static float getActualWidth(CCSprite *sprite);
    static long getCurrentTime();
};



#endif /* UTILS_H_ */
