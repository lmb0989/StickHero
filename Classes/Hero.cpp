#include "Hero.h"
#include "Pillar.h"

Hero::Hero() {}

Hero::~Hero() {}

Hero* Hero::instance = nullptr;
const float Hero::speed = 300.0f;

bool Hero::init()
{
	if(!Sprite::init()) return false;
	this->initWithFile("hero.png");
	this->ignoreAnchorPointForPosition(false);
	this->setAnchorPoint(Vec2(1.0f, 0)); 

	Animation* walk = createAnimation("walk");
	walk->setDelayPerUnit(2.8f/14.0f);
	walk->setRestoreOriginalFrame(true);
	AnimationCache::getInstance()->addAnimation(walk, "walkAnimation");

	Animation* stay = createAnimation("stay");
	stay->setDelayPerUnit(2.8f/14.0f);
	stay->setRestoreOriginalFrame(true);
	AnimationCache::getInstance()->addAnimation(stay, "stayAnimation");

	return true;
}

Animation* Hero::createAnimation(char *name)
{
	Animation* animation = Animation::create();
	for(int i=1; i<=5; i++)
	{
		char aName[20];
		sprintf(aName, "animation/%s%d.png", name, i);
		animation->addSpriteFrameWithFile(aName);
	}
	return animation;
}

Hero* Hero::getInstance()
{
	if (instance == nullptr)
	{
		instance = new(std::nothrow) Hero();
		instance->init();
	}
	return instance;
}

void Hero::destory()
{
	if(instance!=nullptr)
	{
		instance->getParent()->removeChild(instance);
		instance = nullptr;
	}
}

void Hero::walk(float distance)
{
	this->stopAllActions();
	float duration = distance/speed;
	MoveBy* moveBy = MoveBy::create(duration, Vec2(distance, 0));
	Animate* walkAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("walkAnimation"));
	Spawn* spawn = Spawn::createWithTwoActions(walkAnimate, moveBy);
	this->runAction(spawn);
	scheduleOnce(walkFinishSchedule = schedule_selector(Hero::walkFinish), duration);
}

void Hero::walkFinish(float dt)
{
	unschedule(walkFinishSchedule);
	stay();
	onWalkFinish();
}

void Hero::stay()
{
	log("hero staying!!!");
	this->stopAllActions();
	Animation* stay = AnimationCache::getInstance()->getAnimation("stayAnimation");
	this->runAction(RepeatForever::create(Animate::create(stay)));
}

void Hero::fall()
{
	this->stopAllActions();
	float duration = 0.3f;
	MoveBy* moveBy = MoveBy::create(duration, Vec2(0, -(Pillar::STICK_HEIGHT+getContentSize().height + 100)));
	this->runAction(moveBy);
	scheduleOnce(fallFinishSchedule = schedule_selector(Hero::fallFinish), duration);
}

void Hero::fallFinish(float dt)
{
	unschedule(fallFinishSchedule);
	this->stopAllActions();
	onFallFinish();
}