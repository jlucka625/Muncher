/*
 * Candy.h
 *
 *  Created on: Mar 10, 2014
 *      Author: jonathanlucka
 */

#ifndef CANDY_H_
#define CANDY_H_

#include "cocos2d.h"
#include "constants.h"

class Candy : public cocos2d::CCNode
{
public:
	Candy();
	~Candy();
	static Candy* create();
	void bindSprite(CCSprite* sprite, int tag);
	CCSprite* getSprite();
	float getDropSpeed();
	void fall(float accel);
	int getCandyTag();
	void setCandyTag(int tag);

private:
	CCSprite* candySprite;
	float dropSpeed;
	int candyTag;
};



#endif /* CANDY_H_ */
