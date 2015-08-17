#include "CocosStudioTest.h"
#include "CocostudioParserJsonTest.h"
#include "cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "../CocostudioParserTest.h"
#include "../CustomWidget/CustomImageView.h"
#include "../CustomWidget/CustomImageViewReader.h"
#include "../CustomWidget/CustomParticleWidgetReader.h"
#include "../CustomWidget/CustomParticleWidget.h"

USING_NS_CC;

Scene* CocosStudioTest::create()
{
	Scene* scene = Scene::create();
	Layer* layer = CocosStudioTest::create();
	scene->addChild(layer);
	return scene;
}

bool CocosStudioTest::init()
{

}

void CocosStudioTest::onEnter()
{
	Layer::onEnter();

	GUIReader* guiReader = GUIReader::getInstance();
	guiReader->registerTypeAndCallBack("CustomImageView",
		&CustomImageView::createInstance,
		CustomImageViewReader::getInstance(),
		parseselector(CustomImageViewReader::setProperties));
	guiReader->registerTypeAndCallBack("CustomParticleWidget",
		&CustomParticleWidget::createInstance,
		CustomParticleWidgetReader::getInstance(),
		parseselector(CustomParticleWidgetReader::setProperties));

	Layout* layout = static_cast<Layout*>(guiReader->widgetFromJsonFile(_jsonFile.c_str()));
	layout->setScale(0.5);
	addChild(layout);
}
