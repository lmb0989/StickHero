#include "Pillar.h"

float Pillar::STICK_HEIGHT = 0;
float Pillar::STICK_MAX_WIDTH = 0;
float Pillar::STICK_MIN_WIDTH = 0;

Pillar::Pillar() { }

Pillar::~Pillar() { }

bool Pillar::init()
{
	initConstantValue();
	if(!LayerColor::init()) return false;
	ignoreAnchorPointForPosition(false);
	setAnchorPoint(Vec2(1.0f, 1.0f));

	float width = random<float>(STICK_MIN_WIDTH, STICK_MAX_WIDTH);
	log("width = %f", width);
	initWithColor(Color4B(0,0,0,255) ,width, STICK_HEIGHT);

	return true;
}

void Pillar::initConstantValue() 
{
	if(STICK_MIN_WIDTH>0 && STICK_MAX_WIDTH>0 && STICK_HEIGHT>0) return;
	
	STICK_MIN_WIDTH = Director::getInstance()->getVisibleSize().width/16;
	STICK_MAX_WIDTH = Director::getInstance()->getVisibleSize().width/6;
	STICK_HEIGHT = Director::getInstance()->getVisibleSize().height/3;
	log("STICK_MIN_WIDTH = %f, STICK_MAX_WIDTH = %f, STICK_HEIGHT = %f", STICK_MIN_WIDTH, STICK_MAX_WIDTH, STICK_HEIGHT);
}

void Pillar::setAsFirstPillar()
{
	setPosition(STICK_MAX_WIDTH, STICK_HEIGHT);
}

void Pillar::setAsSecondPillar()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int stickWidth = getContentSize().width;
	int minPos = 10 + stickWidth;
	int maxPos = visibleSize.width - STICK_MAX_WIDTH - stickWidth - 10;
	setPosition(STICK_MAX_WIDTH + random<int>(minPos, maxPos), STICK_HEIGHT);
}

void Pillar::setAsThirdPillar(Pillar* first, Pillar* second)
{
	float distance = second->getPositionX() - first->getPositionX();
	float spaceDis = Director::getInstance()->getVisibleSize().width - distance - STICK_MAX_WIDTH;
	float newPosX = random<float>(this->getContentSize().width, distance)+spaceDis+second->getPositionX();
	setPosition(newPosX, STICK_HEIGHT);
}