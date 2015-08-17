#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

Vec2 temp;

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* background = Sprite::create("background.png");
	background->setPosition(Point::ZERO);
	//background->setScaleX(960/720);
	//background->setScaleY(640/720);
	this->addChild(background);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(	    "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    cocos2d::log("x:%f  y:%f",origin.x, origin.y);
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + visibleSize.height + closeItem->getContentSize().height/2));

	log("x=%f, y=%f", visibleSize.width, visibleSize.height);

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	map = TMXTiledMap::create("map.tmx");
	map->setPosition(Point::ZERO);
	this->addChild(map);

	Label* left = Label::createWithTTF("Left", "fonts/arial.ttf", 18);
	left->setPosition(Point(left->getContentSize().width/2, visibleSize.height/2));
	left->retain();
	this->addChild(left, 2);

	auto leftListener = EventListenerTouchOneByOne::create();
	leftListener->onTouchBegan = [](Touch* touch, Event* event) {
		Label* label = static_cast<Label*>(event->getCurrentTarget());
		Point touchPointInNode = label->convertToNodeSpace(touch->getLocation());
		Size labelSize = label->getContentSize();
		Rect rect = Rect(0, 0, labelSize.width, labelSize.height);
		if(rect.containsPoint(touchPointInNode)){
			return true;
		}
		return false;
	};
	leftListener->onTouchMoved = [=](Touch*touch, Event* evt){
		float mapPointX = map->getPositionX();
		if(mapPointX <= -(map->getContentSize().width - visibleSize.width)) return;
		map->setPosition(Point(mapPointX-10, 0));
	};
	leftListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(leftListener, left);

	Label* right = Label::createWithTTF("Right", "fonts/arial.ttf", 18);
	right->setPosition(Point(left->getContentSize().width + right->getContentSize().width/2 +20, visibleSize.height/2));
	this->addChild(right, 2);

	auto rightListener = EventListenerTouchOneByOne::create();
	rightListener->onTouchBegan = [](Touch* touch, Event* event) {
		auto label = (Label*)event->getCurrentTarget();
		Point touchPointInNode = label->convertToNodeSpace(touch->getLocation());
		Size labelSize = label->getContentSize();
		Rect rect = Rect(0, 0, labelSize.width, labelSize.height);
		if(rect.containsPoint(touchPointInNode)) {
			return true;
		}
		return false;
	};
	rightListener->onTouchMoved = [=](Touch* touch, Event* evt){
		float mapPointX = map->getPositionX();
		if(mapPointX >= 0) return;
		map->setPosition(Point(mapPointX+10, 0));
	};
	rightListener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(rightListener, right);

	//auto touchListener = EventListenerTouchOneByOne::create();
	//touchListener->onTouchBegan = [this](Touch* touch, Event* event) {
	//	//beganPoint = this->convertToNodeSpace(touch->getLocation());
	//	beganPoint = touch->getLocation();
	//	log("beganPoint x = %f, y = %f", beganPoint.x, beganPoint.y);
	//	return true;
	//};
	//touchListener->onTouchMoved = [=](Touch* touch, Event* evt){
	//	//Point touchPoint = this->convertToNodeSpace(touch->getLocation());
	//	Point touchPoint = touch->getLocation();
	//	log("touchPoint x = %f, y = %f", touchPoint.x, touchPoint.y);
	//	log("beganPoint x = %f, y = %f", beganPoint.x, beganPoint.y);
	//	float moveX = touchPoint.x - beganPoint.x;
	//	float moveY = touchPoint.y - beganPoint.y;
	//	log("moveX = %f, moveY = %f", moveX, moveY);
	//	Point mapPoint = map->getPosition();
	//	map->setPosition(mapPoint.x+moveX, mapPoint.y+moveY);
	//};
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [](Touch* touch, Event* event) {
		//beganPoint = this->convertToNodeSpace(touch->getLocation());
		temp = touch->getLocation();
		return true;
	};
	touchListener->onTouchMoved = [visibleSize, this](Touch* touch, Event* evt){
		Point mapPoint = map->getPosition();
		Vec2 point = touch->getLocation();
		float offsetX = point.x - temp.x;
		//if(mapPoint.x>0 && offsetX>=0) return;
		//if(mapPoint.x<= -(map->getContentSize().width-visibleSize.width) && offsetX<=0) return;
		log("point.x = %f, temp.x = %f", point.x, temp.x);
		float mapNewPoint = mapPoint.x + offsetX;
		if(mapNewPoint >= 0) mapNewPoint = 0;
		if(mapNewPoint <= -(map->getContentSize().width-visibleSize.width)) mapNewPoint = -(map->getContentSize().width-visibleSize.width);
		map->setPosition(Point(mapNewPoint, mapPoint.y));
		temp = touch->getLocation();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//scheduleUpdate();
	scheduleOnce(schedule_selector(HelloWorld::previewMap), 1.0f);

    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::previewMap(float delta) {
	log("previewMap is Running");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size mapSize = map->getContentSize();
	MoveTo* moveTo = MoveTo::create(5.0f, Vec3(-(mapSize.width-visibleSize.width), 0, 0));
	DelayTime* delay = DelayTime::create(1.0f);
	MoveTo* moveToReverse = MoveTo::create(5.0f, Vec3(0, 0, 0));
	//Vector<FiniteTimeAction*> vector(2);
	//vector.pushBack(moveTo);
	//vector.pushBack(moveToReverse);
	//cocos2d::Sequence* sequence = Sequence::create(vector);
	Sequence* sequence = Sequence::create(moveTo, delay, moveToReverse, nullptr);
	map->runAction(sequence);
}

bool isRuned = false;
void HelloWorld::update(float delta) {
	//if(!isRuned) {
	//	Size visibleSize = Director::getInstance()->getVisibleSize();
	//	Size mapSize = map->getContentSize();
	//	while(map->getPositionX() > -(mapSize.width-visibleSize.width)) {
	//		map->setPosition(map->getPositionX() - 20, 0);
	//	}
	//	while(map->getPositionX() < 0) {
	//		map->setPosition(map->getPositionX() + 20, 0);
	//	}
	//	isRuned = true;
	//}

	if(!isRuned) {
		log("update is Running");
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Size mapSize = map->getContentSize();
		MoveTo* moveTo = MoveTo::create(2.0f, Vec3(-(mapSize.width-visibleSize.width), 0, 0));
		MoveTo* moveToReverse = MoveTo::create(2.0f, Vec3(0, 0, 0));
		Vector<FiniteTimeAction*> vector(2);
		vector.pushBack(moveTo);
		vector.pushBack(moveToReverse);
		cocos2d::Sequence* sequence = Sequence::create(vector);
		map->runAction(sequence);

		isRuned = true;
	}
}
