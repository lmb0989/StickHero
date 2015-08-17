#include "HeroRunLayer.h"
#include "Pillar.h"
#include "GameOverlayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//const char* HeroRunLayer::BUTTON_EFF = "sound/button.ogg";
const char* HeroRunLayer::DEATH_EFF = "sound/death.ogg";
const char* HeroRunLayer::FALL_EFF = "sound/fall.ogg";
//const char* HeroRunLayer::KICK_EFF = "sound/kick.ogg";
const char* HeroRunLayer::SCORE_EFF = "sound/score.ogg";
const char* HeroRunLayer::STICK_GROW_LOOP_EFF = "sound/stick_grow_loop.ogg";
//const char* HeroRunLayer::VICTORY_EFF = "sound/victory.ogg";
#else
//const char* HeroRunLayer::BUTTON_EFF = "sound/button.wav";
const char* HeroRunLayer::DEATH_EFF = "sound/death.wav";
const char* HeroRunLayer::FALL_EFF = "sound/fall.wav";
//const char* HeroRunLayer::KICK_EFF = "sound/kick.wav";
const char* HeroRunLayer::SCORE_EFF = "sound/score.wav";
const char* HeroRunLayer::STICK_GROW_LOOP_EFF = "sound/stick_grow_loop.wav";
//const char* HeroRunLayer::VICTORY_EFF = "sound/victory.wav";
#endif

static const std::string MOON = "moon.png";
static const std::string backgroundImages[] = 
{
	"bg1.jpg",
	"bg2.jpg",
	"bg3.jpg",
	"bg4.jpg",
	"bg5.jpg"
};

Scene* HeroRunLayer::createScene() 
{
	Scene* scene = Scene::create();
	Layer* layer = HeroRunLayer::create();
	scene->addChild(layer);
	return scene;
}

bool HeroRunLayer::init()
{
	isHeroRunning = false;
	needCleanList = cocos2d::Vector<Node*>();
	visibleSize = Director::getInstance()->getVisibleSize();
	image = Director::getInstance()->getTextureCache()->addImage("bridge.png");
	audioEngine = SimpleAudioEngine::getInstance();
	audioEngine->preloadEffect(DEATH_EFF);
	audioEngine->preloadEffect(FALL_EFF);
	//audioEngine->preloadEffect(KICK_EFF);
	audioEngine->preloadEffect(SCORE_EFF);
	audioEngine->preloadEffect(STICK_GROW_LOOP_EFF);
	//audioEngine->preloadEffect(VICTORY_EFF);

	setBackground();
	Sprite* scoreBG = Sprite::createWithTexture(TextureCache::getInstance()->addImage("scoreBg.png"));
	scoreBG->setScale(0.8f);
	//scoreBG->setOpacity(0.5f);
	scoreBG->setPosition(visibleSize.width / 2, visibleSize.height / 8 * 7);
	addChild(scoreBG, 2);

	scoreLabel = Label::create();
	scoreLabel->setAlignment(TextHAlignment::CENTER);
	scoreLabel->setTTFConfig(TTFConfig("fonts/arial.ttf", 24));
	scoreLabel->setPosition(scoreBG->getPosition());
	setScore(score);
	addChild(scoreLabel, 2);

	uiLayer = Layer::create();
	addChild(uiLayer, 1);

	firstPillar = Pillar::create();
	firstPillar->setAsFirstPillar();
	uiLayer->addChild(firstPillar);

	secondPillar = Pillar::create();
	secondPillar->setAsSecondPillar();
	uiLayer->addChild(secondPillar);

	hero = Hero::getInstance();
	hero->onWalkFinish = CC_CALLBACK_0(HeroRunLayer::afterHeroWalk, this);
	hero->onFallFinish = CC_CALLBACK_0(HeroRunLayer::afterHeroFall, this);
	//hero->setScale(0.5f); 
	hero->setPosition(firstPillar->getPosition());
	uiLayer->addChild(hero);
	hero->stay();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HeroRunLayer::layerTouchBegin, this);
	listener->onTouchEnded = CC_CALLBACK_2(HeroRunLayer::layerTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, uiLayer);
	return true;
}

void HeroRunLayer::setScore(int score)
{
	char charScore[3];
	sprintf(charScore, "%d", score);
	scoreLabel->setString(charScore);
}

void HeroRunLayer::setBackground()
{
	int size = sizeof(backgroundImages)/sizeof(backgroundImages[0]);
	std::string image = backgroundImages[random<int>(0, size-1)];
	Sprite* background = Sprite::create(image);
	background->ignoreAnchorPointForPosition(false);
	background->setAnchorPoint(Vec2(0.5f, 0.5f));
	background->setPosition(visibleSize.width/2, visibleSize.height/2);
	this->addChild(background);
	Sprite* moon = Sprite::create(MOON);
	moon->ignoreAnchorPointForPosition(false);
	moon->setAnchorPoint(Vec2(0.5f, 0.5f));
	moon->setPosition(visibleSize.width/2, visibleSize.height/4*3);
	this->addChild(moon);
}

bool HeroRunLayer::layerTouchBegin(Touch* touch, Event* event)
{
	if (isHeroRunning) return false;
	stick = Stick::create(image);
	stick->setPosition(firstPillar->getPosition());
	stick->onStickFallDownFinish = CC_CALLBACK_0(HeroRunLayer::afterStickFallDown, this);

	uiLayer->addChild(stick);
	//audioEngine->playEffect(STICK_GROW_LOOP_EFF,true);
	schedule(stickGrow = schedule_selector(HeroRunLayer::update), 0.01f, kRepeatForever, 0);
	return true;
}

void HeroRunLayer::update(float dt)
{
	//audioEngine->playEffect(STICK_GROW_LOOP_EFF);
	stick->grow();
}

void HeroRunLayer::layerTouchEnded(Touch* touch, Event* event)
{
	//audioEngine->stopAllEffects();
	unschedule(stickGrow);
	isHeroRunning = true;
	audioEngine->playEffect(FALL_EFF);
	stick->fallDown();
}

void HeroRunLayer::afterStickFallDown()
{
	twoStickDistance = secondPillar->getPosition().x - firstPillar->getPosition().x;
	float spaceDistance = visibleSize.width - Pillar::STICK_MAX_WIDTH;
	float stickLength = stick->getLengthAfterFallDown();
	if(stickLength>spaceDistance)
	{
		hero->walk(spaceDistance);
	}
	else if( stickLength>twoStickDistance || stickLength<twoStickDistance-secondPillar->getContentSize().width )
	{
		hero->walk(stickLength);
	}
	else
	{
		hero->walk(twoStickDistance);
	}
}

void HeroRunLayer::afterHeroWalk()
{
	float stickLength = stick->getLengthAfterFallDown();
	if( stickLength>twoStickDistance || stickLength<twoStickDistance-secondPillar->getContentSize().width )
	{
		gameFailed();
		return;
	}
	gameContinue();
}

void HeroRunLayer::clean(Node* node)
{
	needCleanList.pushBack(node);
	if (needCleanList.size() >= 5)
	{
		int i = 1;
		auto it = needCleanList.begin();
		while(it != needCleanList.end())
		{
			if (i > 3)
			{
				break;
			}
			uiLayer->removeChild(*it);
			it = needCleanList.erase(it);
			i++;
		}
	}
}

void HeroRunLayer::gameFailed() 
{
	log("game Failed");
	audioEngine->playEffect(DEATH_EFF);
	stick->runAction(RotateBy::create(0.3f, 90));
	hero->fall();
}

void HeroRunLayer::afterHeroFall()
{
	GameOverlayer* gameOverLayer = GameOverlayer::create();
	gameOverLayer->ccClean = CC_CALLBACK_0(HeroRunLayer::GameReset, this);
	this->addChild(gameOverLayer, 2);
}

void HeroRunLayer::gameContinue()
{
	hero->stay();	
	Pillar* pillar = Pillar::create();
	pillar->setAsThirdPillar(firstPillar, secondPillar);
	uiLayer->addChild(pillar);
	Pillar* oldPillar = firstPillar;
	
	audioEngine->playEffect(SCORE_EFF);
	float duration = 0.3f; /*twoStickDistance / 300.0f;*/
	MoveBy* moveBy = MoveBy::create(duration, Vec2(-twoStickDistance, 0));
	uiLayer->runAction(moveBy);
	scheduleOnce(schedule_selector(HeroRunLayer::afterUILayerMove), duration);

	firstPillar = secondPillar;
	secondPillar = pillar;
	clean(stick);
	clean(oldPillar);
}

void HeroRunLayer::afterUILayerMove(float dt)
{
	setScore(++score);
	isHeroRunning = false;
}

void HeroRunLayer::GameReset()
{
	Hero::destory();
	needCleanList.clear();
}