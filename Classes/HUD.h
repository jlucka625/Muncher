/*
 * HUD.h
 *
 *  Created on: Mar 7, 2014
 *      Author: jonathanlucka
 */

#ifndef HUD_H_
#define HUD_H_

#include "cocos2d.h"

class HUD : public cocos2d::CCLayer
{
	int missesLeft, score, highscore, fontSize;
	bool paused, isGameover;
	cocos2d::CCSprite *pauseButton, *gameoverSprite;
	cocos2d::CCArray* lives;
	cocos2d::CCLabelTTF *scoreLabel, *finalScoreLabel, *highScoreLabel;
public:
	virtual bool init();
	void determineFontSize();
	void scored();
	int getScore();
	void decreaseLives();
	void drawLives();
	void togglePause();
	void gameover();

	//overrides
	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	LAYER_CREATE_FUNC(HUD);
};


#endif /* HUD_H_ */
