#ifndef _SETTINGSCENE_H_
#define _SETTINGSCENE_H_

#include "cocos2d.h"
#include "cocos2d/cocos/ui/UISlider.h"
#include "cocos2d/cocos/ui/UILayout.h"
USING_NS_CC;


class SettingScene : public Scene
{
public:
	virtual bool init();

	CREATE_FUNC(SettingScene);

	void sliderEvent(Ref *pSender, ui::Slider::EventType type);

private:
	ui::Layout* root;
};

#endif