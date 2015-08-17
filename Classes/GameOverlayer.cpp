#include "GameOverlayer.h"
#include "HeroRunLayer.h"
#include "StringUtil.h"

GameOverlayer::GameOverlayer() { }

GameOverlayer::~GameOverlayer() { }

bool GameOverlayer::init()
{
	if (!LayerColor::init()) return false;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	initWithColor(Color4B(0, 0, 0, 220), visibleSize.width, visibleSize.height);

	TTFConfig ttfConfig("fonts/arial.ttf", 64);
	Label* gameoverLabel = Label::createWithTTF(ttfConfig, "Game Over", TextHAlignment::CENTER);
	gameoverLabel->setPosition(visibleSize.width / 2, visibleSize.height / 4 * 3);
	addChild(gameoverLabel);
	
	Label* palyAgainLabel = Label::createWithTTF(TTFConfig("fonts/arial.ttf", 36), "Play Again", TextHAlignment::CENTER);
	ccMenuCallback callback = [this](Ref* pSender)
	{
		ccClean();
		auto scene = HeroRunLayer::createScene();
		Director::getInstance()->replaceScene(scene);
	};
	MenuItemLabel* playAgain = MenuItemLabel::create(palyAgainLabel, callback);
	playAgain->setPosition(Vec2(gameoverLabel->getPositionX(), gameoverLabel->getPositionY() - 80));
	playAgain->setColor(Color3B(255,20,20));
	Menu* menu = Menu::create(playAgain, nullptr);
	menu->setPosition(Point::ZERO);
	addChild(menu);

	Label* hintLabel = Label::createWithTTF(TTFConfig("fonts/simhei.ttf", 32), "Touch Screen To Continue", TextHAlignment::CENTER);
	hintLabel->setPosition(visibleSize.width / 2, visibleSize.height / 8 * 1);
	addChild(hintLabel);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [this](Touch* touch, Event* event)
	{
		ccClean();
		auto scene = HeroRunLayer::createScene();
		Director::getInstance()->replaceScene(scene);
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}

