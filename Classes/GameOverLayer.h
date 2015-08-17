#ifndef _GAMEOVER_LAYER_H_
#define _GAMEOVER_LAYER_H_

#include "cocos2d.h"
USING_NS_CC;

class GameOverlayer : public LayerColor
{
public:
	GameOverlayer();
	~GameOverlayer();
	virtual bool init();
	CREATE_FUNC(GameOverlayer);
	std::function<void()> ccClean;
	char* G2U(const char* gb2312);
};

#endif