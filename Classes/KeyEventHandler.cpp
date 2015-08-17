#include "KeyEventHandler.h"

KeyEventHandler::KeyEventHandler()
{
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(KeyEventHandler::handleKeyPressed, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(keyListener, 500);
}

KeyEventHandler::~KeyEventHandler() { }

void KeyEventHandler::handleKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			Director::getInstance()->end();
			break;
		default:
			break;
	}
}