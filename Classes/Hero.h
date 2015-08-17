#ifndef _HERO_H_
#define _HERO_H_

#include "cocos2d.h"
USING_NS_CC;

class Hero : public Sprite
{
public:
	virtual bool init() override;
	static Hero* getInstance();
	static void destory();
	Animation* createAnimation(char *name);

	void walk(float distance);
	void walkFinish(float dt);
	void stay();
	void fall();
	void fallFinish(float dt);

	typedef std::function<void()> ccWalkFinishCallback;
	typedef std::function<void()> ccFallFinishCallback;

	ccWalkFinishCallback onWalkFinish;
	ccFallFinishCallback onFallFinish;

	~Hero();
	Hero();
private:
	static Hero* instance;

	static const float speed;
	SEL_SCHEDULE walkFinishSchedule;
	SEL_SCHEDULE fallFinishSchedule;
	//Animate* stayAnimate;
	//Animate* walkAnimate;
};

#endif