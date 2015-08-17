#ifndef _STICK_H_
#define _STICK_H_

#include "cocos2d.h"
USING_NS_CC;

class Stick : public Sprite
{
public:
	Stick();
	~Stick();
	virtual bool init() override;
	static Stick* create(std::string fileName);
	static Stick* create(Texture2D* texture);

	typedef std::function<void()> ccFallDownCallback;
	ccFallDownCallback onStickFallDownFinish;

	void setAnchor();
	void grow();
	float getLengthbeforeFallDown() const;
	float getLengthAfterFallDown() const;
	void fallDown();
	void fallDownFinish(float dt);

	SEL_SCHEDULE fallDownFinishSchedule;

private:
	float length;

};

#endif