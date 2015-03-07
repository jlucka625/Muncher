#define COCOS2D_DEBUG 1
#include "Utils.h"
#include "Constants.h"
#include "MainMenu.h"

USING_NS_CC;

CCScene* MainMenu::scene()
{
	//autorelease object
	CCScene *scene = CCScene::create();
	scene->setTag(TAG_MENU);

	//Main Menu Layer
	MainMenu *menuLayer = MainMenu::create();
	scene->addChild(menuLayer, 0, TAG_MENU);
	return scene;
}

bool MainMenu::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	//create background
    CCSprite *bg = CCSprite::create("gamebg2.png");
    bg->setPosition(ccp(Utils::size().width/2, Utils::size().height/2));
    this->addChild(bg, 1);
    Utils::bgScale(bg);

    CCSprite *overlay = CCSprite::create("mainmenu.png");
    overlay->setPosition(ccp(Utils::size().width/2, Utils::size().height/2));
    this->addChild(overlay, 1);
    Utils::bgScale(overlay);

    //create pipes
    for(int i = 0; i < 3; i++)
    {
    	CCSprite *pipe = CCSprite::create("pipe.png");
    	Utils::scale(pipe, 6.0); pipe->setScaleY(pipe->getScaleY() * 2.0); pipe->setScaleX(pipe->getScaleX() * 1.4);
    	if(i == 0)
    		pipe->setPosition(ccp(Utils::size().width/2, Utils::size().height - Utils::getActualHeight(pipe)/2));
    	else if(i == 1)
    		pipe->setPosition(ccp(Utils::getActualWidth(pipe)/2, Utils::size().height - Utils::getActualHeight(pipe)/2));
    	else
    		pipe->setPosition(ccp(Utils::size().width - Utils::getActualWidth(pipe)/2 , Utils::size().height - Utils::getActualHeight(pipe)/2));

    	this->addChild(pipe, 2);
    }

    this->setTouchEnabled(true);
    return true;
}

void MainMenu::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	CCDirector::sharedDirector()->replaceScene(MainGame::scene());
}
