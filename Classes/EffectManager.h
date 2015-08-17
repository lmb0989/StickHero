#ifndef _EFFECTMANAGER_H_
#define _EFFECTMANAGER_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

class EffectManager 
{
public:
	static void loadEffectFile(const string &fileName);
	static void playEffect(const string &fileName);
	static void stopEffect(const string&fileName);
private:
	static Map<std::string, int> effectManager;
	static SimpleAudioEngine* engineInstance;
	const static unsigned int UNKNOW_ID = 0x00000;
};

#endif