#ifndef _KEYEVENT_HANDLER_H_
#define _KEYEVENT_HANDLER_H_

#include "cocos2d.h"
USING_NS_CC;

class KeyEventHandler
{
public:
	KeyEventHandler();
	~KeyEventHandler();
	void handleKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
};

#endif