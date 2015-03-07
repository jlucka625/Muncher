/*
 * Candy.cpp
 *
 *  Created on: Mar 11, 2014
 *      Author: jonathanlucka
 */
#include "candy.h"

Candy::Candy()
{
	candySprite = NULL;
	dropSpeed = 0.0;
}

Candy::~Candy(){}

Candy* Candy::create()
{
	Candy* c = new Candy;
	c->autorelease();
	return c;
}

void Candy::bindSprite(CCSprite* sprite, int tag)
{
	candySprite = sprite;
	candyTag = tag;
	this->addChild(candySprite);
}

CCSprite* Candy::getSprite()
{
	return candySprite;
}

float Candy::getDropSpeed()
{
	return dropSpeed;
}

void Candy::fall(float accel)
{
	dropSpeed -= accel;
	candySprite->setPosition(ccpAdd(candySprite->getPosition(), ccp(0, dropSpeed)));
}

int Candy::getCandyTag()
{
	return candyTag;
}

void Candy::setCandyTag(int tag)
{
	candyTag = tag;
}

