#include "SettingScene.h"
#include "cocos2d.h"
#include "cocos2d/cocos/editor-support/cocostudio/ActionTimeline/CSLoader.h"
#include "cocos2d/cocos/ui/UISlider.h"
#include "cocos2d/cocos/ui/UIHelper.h"
#include "cocos2d/cocos/ui/UILayout.h"
#include "TouchUtil.h"
USING_NS_CC;
using namespace ui;

bool SettingScene::init() 
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Layer* layer = static_cast<Layer*>(CSLoader::createNode("Setting.csb"));
	layer->setAnchorPoint(Vec2(0.5, 0.5));
	layer->setPosition(visibleSize.width/2, visibleSize.height/2);

	this->addChild(layer);

	root = static_cast<Layout*>(layer->getChildByName("Panel_2"));
	Slider* musicControl = static_cast<Slider*>(Helper::seekWidgetByTag(root, 33));
	//Slider* musicControl = static_cast<Slider*>(layer->getChildByName("musicControl"));
	//Slider* musicControl = static_cast<Slider*>(layer->getChildByTag(33));
	if(!musicControl) {
		log("musicControl is null");
	}
	//auto listener = EventListenerTouchOneByOne::create();
	//listener->onTouchBegan = [](Touch* touch, Event* event)
	//{
	//	log("listener is called");
	//	auto slider = event->getCurrentTarget();
	//	bool result = TouchUtil::isTouchInRect(slider, touch);
	//	if(result) {
	//		log("µã»÷ÁË");
	//	}
	//	return result;
	//};
	//listener->onTouchMoved = [](Touch* touch, Event* event)
	//{

	//};
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, musicControl);

	//musicControl->addCCSEventListener(CC_CALLBACK_1(SettingScene::sliderCallBack, this));

	musicControl->addEventListener([this](Ref* pSender, Slider::EventType type)
	{
		switch (type)
		{
		case Slider::EventType::ON_PERCENTAGE_CHANGED:
			{
				Slider* slider = static_cast<Slider*>(pSender);
				Slider* soundSlider = static_cast<Slider*>(Helper::seekWidgetByTag(root, 32));

				soundSlider->setPercent(slider->getPercent());
				log("percent %d", slider->getPercent());
			}
			break;

		default:
			break;
		}

	});
	return true;
}

void SettingScene::sliderEvent(Ref *pSender, Slider::EventType type)
{
	//switch (type)
	//{
	//case Slider::EventType::ON_PERCENTAGE_CHANGED:
	//	{
	//		Slider* slider = static_cast<Slider*>(pSender);
	//		Slider* soundSlider = static_cast<Slider*>(Helper::seekWidgetByTag(root, 32));

	//		soundSlider->setPercent(slider->getPercent());
	//		log(CCString::createWithFormat("percent %d", slider->getPercent())->getCString());
	//	}
	//	break;

	//default:
	//	break;
	//}
}