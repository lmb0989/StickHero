#ifndef _PILLAR_H_
#define _PILLAR_H_

#include "cocos2d.h"
USING_NS_CC;

class Pillar : public LayerColor
{
public:
	Pillar();
	~Pillar();
	virtual bool init() override;
	void initConstantValue();

	void setAsFirstPillar();
	void setAsSecondPillar();
	void setAsThirdPillar(Pillar* first, Pillar* second);

	CREATE_FUNC(Pillar);

	static float STICK_HEIGHT;
	static float STICK_MIN_WIDTH;
	static float STICK_MAX_WIDTH;

};

#endif