/*
 * HUD.cpp
 *
 *  Created on: Mar 7, 2014
 *      Author: jonathanlucka
 */

#include "HUD.h"
#include "Utils.h"
#include "Constants.h"
#include "GameScene.h"


using namespace cocos2d;

bool HUD::init()
{
    if (!CCLayer::init()) {
        return false;
    }

    paused = false;

    score = 0;
    highscore = CCUserDefault::sharedUserDefault()->getIntegerForKey(HIGH_SCORE);
    missesLeft = 3;

    determineFontSize();

    scoreLabel = CCLabelTTF::create("0", CCString::createWithFormat("%s.ttf", FONT_MAIN)->getCString(),80);
    scoreLabel->setAnchorPoint(ccp(0,1));
    scoreLabel->setPosition(ccp(Utils::size().width/2, Utils::size().height - 30));
    this->addChild(scoreLabel,1);

    lives = CCArray::create();
    lives->retain();
    drawLives();

    pauseButton = CCSprite::create("pause.png");
    Utils::scale(pauseButton, 8.0);
    pauseButton->setPosition(ccp(Utils::getActualWidth(pauseButton)/2 + 20, Utils::size().height - Utils::getActualHeight(pauseButton)/2 - 20));
    this->addChild(pauseButton);

    this->setTouchEnabled(true);
    return true;
}

void HUD::determineFontSize()
{
	int width = Utils::size().width;
	if(width <= 800)
		fontSize = 35;
	else if(width <= 1300)
		fontSize = 53;
	else
		fontSize = 70;
}

void HUD::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	if(!isGameover)
	{
		CCTouch *touch = (CCTouch *)pTouches->anyObject();
		CCPoint location = touch->locationInView();
		location = CCDirector::sharedDirector()->convertToGL(location);

		if(CCRect::CCRectContainsPoint(pauseButton->boundingBox(), location))
		{
			togglePause();
		}
	}
	else
	{
		CCDirector::sharedDirector()->replaceScene(MainGame::scene());
	}
}

void HUD::togglePause()
{
	MainGame* g = Utils::gameLayer();
	if(paused)
	{
		paused = false;
		g->resumeSchedulerAndActions();
		pauseButton->setTexture(CCTextureCache::sharedTextureCache()->addImage("pause.png"));
	}
	else
	{
		paused = true;
		g->pauseSchedulerAndActions();
		pauseButton->setTexture(CCTextureCache::sharedTextureCache()->addImage("play.png"));
	}
}

void HUD::scored()
{
	score++;
	scoreLabel->setString(CCString::createWithFormat("%d",score)->getCString());
}

int HUD::getScore()
{
	return score;
}

void HUD::drawLives()
{
	for(int i = 0; i < 3; i++)
	{
		CCSprite* lifeSprite = CCSprite::create("x.png");
		Utils::scale(lifeSprite, 9.0);
		lifeSprite->setPosition(ccp(Utils::size().width - (i * Utils::getActualWidth(lifeSprite)) - Utils::getActualWidth(lifeSprite)/2 - ((i + 1) * 10), Utils::size().height - Utils::getActualHeight(lifeSprite)/2 - 20));
		this->addChild(lifeSprite, 0);
		lives->addObject(lifeSprite);
	}
}

void HUD::decreaseLives()
{
	CCSprite* lifeSprite = (CCSprite*)lives->objectAtIndex(missesLeft - 1);
	lives->removeObject(lifeSprite);
	this->removeChild(lifeSprite, true);

	if(missesLeft <= 1)
	{
		MainGame* g = Utils::gameLayer();
		g->pauseSchedulerAndActions();
		if(score > CCUserDefault::sharedUserDefault()->getIntegerForKey(HIGH_SCORE))
		{
			CCUserDefault::sharedUserDefault()->setIntegerForKey(HIGH_SCORE, score);
			CCUserDefault::sharedUserDefault()->flush();
			highscore = score;
		}
		gameover();
	}
	else
	{
		missesLeft--;
	}
}

void HUD::gameover()
{
	scoreLabel->setVisible(false);
	pauseButton->setVisible(false);
	isGameover = true;

	gameoverSprite = CCSprite::create("gameover2.png");
	Utils::scale(gameoverSprite, 1.4);
	gameoverSprite->setPosition(ccp(Utils::size().width/2, Utils::size().height/2));
	this->addChild(gameoverSprite, 0);

    finalScoreLabel = CCLabelTTF::create(CCString::createWithFormat("YOUR SCORE: %d", score)->getCString(), CCString::createWithFormat("%s.ttf", FONT_MAIN)->getCString(),fontSize);
    finalScoreLabel->setPosition(ccp(Utils::size().width/2, Utils::size().height/2 + 2 * fontSize));
    this->addChild(finalScoreLabel,1);

    highScoreLabel = CCLabelTTF::create(CCString::createWithFormat("YOUR HIGH SCORE: %d", highscore)->getCString(), CCString::createWithFormat("%s.ttf", FONT_MAIN)->getCString(),fontSize);
    highScoreLabel->setPosition(ccp(Utils::size().width/2, Utils::size().height/2 - 2 * fontSize));
    this->addChild(highScoreLabel,1);
}


