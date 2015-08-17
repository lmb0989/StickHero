#include "Stick.h"

Stick::Stick():length(0) { }
Stick::~Stick() { }

bool Stick::init()
{
	if(!Sprite::init()) return false;

	return true;
}

Stick* Stick::create(std::string fileName)
{
	Texture2D* image = Director::getInstance()->getTextureCache()->addImage(fileName);
	return create(image);
}

Stick* Stick::create(Texture2D* texture)
{
	Stick* stick = new(std::nothrow) Stick();
	if(stick && stick->init()) {
		stick->initWithTexture(texture);
		stick->autorelease();
		return stick;
	}
	return nullptr;
}

void Stick::setAnchor()
{
	ignoreAnchorPointForPosition(false);
	setAnchorPoint(Vec2(1.0f, 0));
}

void Stick::grow()
{
	setAnchor();
	length = length + 1.5;
	setScaleY(length);
}

void Stick::fallDown()
{
	Sequence* sequence = Sequence::create(DelayTime::create(0.3f), RotateBy::create(0.5f, 90), nullptr);
	if(sequence!=nullptr)
	{
		runAction(sequence);
	}
	scheduleOnce(fallDownFinishSchedule = schedule_selector(Stick::fallDownFinish), 0.8f);
}

void Stick::fallDownFinish(float dt)
{
	onStickFallDownFinish();
}

float Stick::getLengthbeforeFallDown() const
{
	return getBoundingBox().size.height;
}

float Stick::getLengthAfterFallDown() const
{
	return getBoundingBox().size.width;
}