#ifndef _H_COCOSSTUDIOTEST_
#define _H_COCOSSTUDIOTEST_

#include "cocos2d.h"

USING_NS_CC;

class CocosStudioTest : public Layer
{
	virtual bool init();
	virtual void onEnter() override;
	static Scene* create();

	CREATE_FUNC(CocosStudioTest);
};

#endif