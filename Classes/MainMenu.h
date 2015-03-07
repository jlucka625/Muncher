/*
 * MainMenu.h
 *
 *  Created on: May 27, 2014
 *      Author: jonathanlucka
 */

#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "cocos2d.h"

class MainMenu : public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();

	//overrides
	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	void menuCloseCallback(CCObject* pSender);
	LAYER_CREATE_FUNC(MainMenu);
};

#endif
