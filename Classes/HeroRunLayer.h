#ifndef _HERORUN_SCENE_H_
#define _HERORUN_SCENE_H_

#include "cocos2d.h"
#include "Stick.h"
#include "Pillar.h"
#include "Hero.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

class HeroRunLayer : public Layer
{
public:
	static Scene* createScene();

	virtual bool init() override;
	void setBackground();
	CREATE_FUNC(HeroRunLayer);

	bool layerTouchBegin(Touch* touch, Event* event);
	void layerTouchEnded(Touch* touch, Event* event);
	void afterStickFallDown();
	void afterHeroWalk();
	void afterHeroFall();
	void afterUILayerMove(float dt);
	void update(float dt);
	void clean(Node* node);
	void GameReset();

	void gameFailed();
	void gameContinue();
	void setScore(int score);

private:
	static const char* BUTTON_EFF;
	static const char* DEATH_EFF;
	static const char* FALL_EFF;
	static const char* KICK_EFF;
	static const char* SCORE_EFF;
	static const char* STICK_GROW_LOOP_EFF;
	static const char* VICTORY_EFF;

private:
	Hero* hero;
	Layer* uiLayer;
	Size visibleSize;

	Stick* stick;
	Pillar* firstPillar;
	Pillar* secondPillar;

	SEL_SCHEDULE stickGrow;
	Texture2D* image;

	float twoStickDistance;
	bool isHeroRunning;
	Vector<Node*> needCleanList;
	SimpleAudioEngine* audioEngine;

	int score = 0;
	Label* scoreLabel;

};

#endif