#include "EffectManager.h"

cocos2d::Map<std::string, int> effectManager;
SimpleAudioEngine* engineInstance = SimpleAudioEngine::getInstance();

void EffectManager::loadEffectFile(const string &fileName) 
{
	string effectFile = "sound/"+fileName;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	effectFile = effectFile + "ogg";
#else
	effectFile = effectFile + "wav";
#endif
	engineInstance->preloadEffect(effectFile.c_str());
	effectManager.insert(fileName, UNKNOW_ID);
}

void EffectManager::playEffect(const string &fileName) 
{
	effectManager.find(fileName);
	CCASSERT(effectManager.find(fileName)!=nullptr);


}

void EffectManager::stopEffect(const string&fileName) 
{

}