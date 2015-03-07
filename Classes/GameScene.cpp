#define COCOS2D_DEBUG 1
#include "GameScene.h"
#include "Utils.cpp"
#include "Constants.h"
#include "HUD.h"
#include "Candy.cpp"
//#include "GameOver.h"
#include "Munchie.cpp"

USING_NS_CC;

CCScene* MainGame::scene()
{
	//autorelease object
	CCScene *scene = CCScene::create();
	scene->setTag(TAG_GAME_SCENE);

	//Main Game Layer
	MainGame *gameLayer = MainGame::create();
	scene->addChild(gameLayer, 0, TAG_GAME_LAYER);

	//HUD Layer
	HUD *hud = HUD::create();
	scene->addChild(hud, 1, TAG_HUD);

	//GameOver Layer
	//GameOver *gameOverLayer = GameOver::create();
	//scene->addChild(gameOverLayer, 1, TAG_GAMEOVER);

	return scene;
}

bool MainGame::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	//starting random seed
	srand(time(0));

	//initiailizing vars
	dropTimer = 0.0f;
	timeBetweenDrops = 15.0f;
	minTimeBetweenDrops = 6.0f;

	walkingDistance = 0.0f;
	maxWalkingDistance = Utils::size().width/2;
	muncherMoving = false;

	activePipeCount = 0;
	currentPipeIndex = 0;

	secondMuncher = false;
	thirdMuncher = false;

	accel = 0.3;

	//initializing arrays
	munchers = CCArray::create();
	munchers->retain();
	pipes = CCArray::create();
	pipes->retain();
	candies = CCArray::create();
	candies->retain();
	candiesToRemove = CCArray::create();
	candiesToRemove->retain();

	//Update Sprite Frame Cache
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("munchiesheet.plist");

	//create background
    CCSprite *bg = CCSprite::create("gamebg2.png");
    bg->setPosition(ccp(Utils::size().width/2, Utils::size().height/2));
    this->addChild(bg, 1);
    Utils::bgScale(bg);

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
    	pipes->addObject(pipe);
    }

    //create first muncher
    spawnNewMuncher(-1 * Utils::size().width/2);

    this->setTouchEnabled(true);
    this->schedule(schedule_selector(MainGame::update));

    return true;
}

void MainGame::update()
{
	spawnCandy();
	dropCandy();
	removeCandies();

	if(!muncherMoving)
		this->unschedule(schedule_selector(MainGame::walkMuncher));
}

void MainGame::increaseDifficulty()
{
	int score = Utils::hudLayer()->getScore();
	if(score > 5 && !secondMuncher)
	{
		secondMuncher = true;
		spawnNewMuncher(-1 * Utils::size().width/2);
	}
	if(score > 15 && secondMuncher && !thirdMuncher)
	{
		thirdMuncher = true;
		spawnNewMuncher(-1 * Utils::size().width/2);
	}
	if(score % 10 == 0 && timeBetweenDrops > minTimeBetweenDrops)
	{
		timeBetweenDrops--;
	}
	if(score % 8 == 0 && accel < 0.6)
	{
		accel += 0.1;
	}
}

void MainGame::spawnNewMuncher(int xPos)
{
    Munchie *muncher = Munchie::create();
    muncher->bindSprite((CCSprite::create("munchiecl.png")));
    Utils::scale(muncher->getSprite(), 5.0);
    muncher->getSprite()->setScaleX(muncher->getSprite()->getScaleX() * -1);
    muncher->getSprite()->setPosition(ccp(xPos, Utils::size().height/6));
    munchers->addObject(muncher);
    this->addChild(muncher, 1);

    CCSprite* pipe;
    if(secondMuncher && !thirdMuncher)
    {
    	muncher->createAnimations(3);
    	pipe = (CCSprite*)pipes->objectAtIndex(1);
    }
    else if(secondMuncher && thirdMuncher)
    {
    	muncher->createAnimations(8);
    	pipe = (CCSprite*)pipes->objectAtIndex(2);
    }
    else
    {
    	muncher->createAnimations(6);
    	pipe = (CCSprite*)pipes->objectAtIndex(0);
    }
    muncherMoving = true;
	maxWalkingDistance = pipe->getPositionX() + Utils::size().width/2;

	lastUpdateTime = Utils::getCurrentTime();
	muncher->playAnimation(muncher->getWalkingFrames(), 0.13, true);
	this->schedule(schedule_selector(MainGame::walkMuncher));
}

void MainGame::walkMuncher()
{
	long timeElapsed = Utils::getCurrentTime() - lastUpdateTime;

	CCLOG("TIME ELAPSED %ld", timeElapsed);

	Munchie* muncher = (Munchie*)munchers->objectAtIndex(munchers->count() - 1);
	CCSprite* muncherSprite = muncher->getSprite();

	if(walkingDistance >= maxWalkingDistance)
	{
		muncherMoving = false;
		walkingDistance = 0;
		activePipeCount++;
		muncherSprite->stopAllActions();
		muncherSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("munchiecl.png"));
	}
	if(walkingDistance + timeElapsed > maxWalkingDistance)
		muncherSprite->setPosition(ccpAdd(muncherSprite->getPosition(), ccp(maxWalkingDistance - walkingDistance, 0)));
	else
		muncherSprite->setPosition(ccpAdd(muncherSprite->getPosition(), ccp(timeElapsed, 0)));

	walkingDistance += timeElapsed;

	lastUpdateTime = Utils::getCurrentTime();
}

void MainGame::spawnCandy()
{
	if(dropTimer >= timeBetweenDrops)
	{
		Candy* candy = Candy::create();
		HUD* hud = Utils::hudLayer();

		//deciding what kind of candy drops
		int itemType = rand() % 10;
		if(itemType >= 0 && itemType < 8) //candy
		{
			int candyType = rand() % 3;
			if(candyType == 0){candy->bindSprite((CCSprite::create("mint.png")), TAG_CANDY); Utils::scale(candy->getSprite(), 11.5);}
			else if(candyType == 1){candy->bindSprite((CCSprite::create("gumdrop.png")), TAG_CANDY); Utils::scale(candy->getSprite(), 11.5);}
			else if(candyType == 2){candy->bindSprite((CCSprite::create("lollipop.png")), TAG_CANDY); Utils::scale(candy->getSprite(), 8.0);}
		}
		else //fruits and veggies
		{
			int foodType = rand() % 2;
			if(foodType == 0){candy->bindSprite((CCSprite::create("apple.png")), TAG_NONCANDY); Utils::scale(candy->getSprite(), 11.5);}
			else if(foodType == 1){candy->bindSprite((CCSprite::create("broccoli.png")), TAG_NONCANDY); Utils::scale(candy->getSprite(), 8.0);}
		}

		//deciding what pipe the candy should fall from
		CCSprite *candySprite = candy->getSprite();
		currentPipeIndex = (rand() % activePipeCount);
		CCSprite* pipe = (CCSprite*)pipes->objectAtIndex(currentPipeIndex);
		candySprite->setPosition(ccp(pipe->getPositionX(), 6 * Utils::size().height/7));

		candies->addObject(candy);
		this->addChild(candy, 1);

		dropTimer = 0.0f;
	}
	dropTimer += 0.1f;
}

void MainGame::dropCandy()
{
	for(int i = 0; i < candies->count(); i++)
	{
		Candy* candy = (Candy*)candies->objectAtIndex(i);
		CCSprite* candySprite = candy->getSprite();
		candy->fall(accel);

		//check collisions with each muncher
		for(int j = 0; j < munchers->count(); j++)
		{
			Munchie* muncher = (Munchie*)munchers->objectAtIndex(j);
			CCSprite* muncherSprite = muncher->getSprite();
			boundingBox = muncherSprite->boundingBox();

			newX = CCRect::CCRectGetMinX(boundingBox);
			newY = CCRect::CCRectGetMidY(boundingBox);
			newWidth = CCRect::CCRectGetMaxX(boundingBox) - CCRect::CCRectGetMinX(boundingBox);
			newHeight = (CCRect::CCRectGetMaxY(boundingBox) - CCRect::CCRectGetMinY(boundingBox))/8.0;

			boundingBox.setRect(newX, newY, newWidth, newHeight);

			if(CCRect::CCRectContainsPoint(boundingBox, ccp(candySprite->getPositionX(), candySprite->getPositionY())))
			{
				if(muncher->isMouthOpen())
				{
					if(candy->getCandyTag() == TAG_CANDY)
					{
						Utils::hudLayer()->scored();
						candiesToRemove->addObject(candy);
						increaseDifficulty();
					}
					else //ate a fruit or veggie
					{
						muncher->playAnimation(muncher->getEwwFrames(), 0.13, false);
						muncher->closeMouth();
						candiesToRemove->addObject(candy);
						missed();
					}
				}
			}
			if(candySprite->getPositionY() <= 0 && (CCRect::CCRectGetMidX(candySprite->boundingBox()) >= CCRect::CCRectGetMinX(muncherSprite->boundingBox())) && (CCRect::CCRectGetMidX(candySprite->boundingBox()) <= CCRect::CCRectGetMaxX(muncherSprite->boundingBox()))) //candy falls below screen
			{
				if(candy->getCandyTag() == TAG_CANDY)
				{
					candiesToRemove->addObject(candy);
					missed();
				}
			}
		}
	}
}

void MainGame::missed()
{
	HUD *hud = Utils::hudLayer();
	hud->decreaseLives();
}

void MainGame::removeCandies()
{
	for(int i = 0; i < candiesToRemove->count(); i++)
	{
		Candy* candy = (Candy*)candiesToRemove->objectAtIndex(i);
		candies->removeObject(candy);
		this->removeChild(candy, true);
	}
	candiesToRemove->removeAllObjects();
}

void MainGame::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch *)pTouches->anyObject();
    CCPoint location = touch->locationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);

    for(int i = 0; i < munchers->count(); i++)
    {
    	Munchie *muncher = (Munchie*)munchers->objectAtIndex(i);
    	CCSprite* muncherSprite = muncher->getSprite();
    	if(CCRect::CCRectContainsPoint(muncherSprite->boundingBox(), location))
    	{
    		muncher->openMouth();
    	}
    }
}

void MainGame::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
