#include "MainScene.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
	/*
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
	*/
	
	auto pNode = SceneReader::getInstance()->createNodeWithSceneFile("publish/MainScene.json");
	auto pUI = pNode->getChildByTag(10004);
	auto pPanel = pUI->getChildByName("panel");
	Button *pBtnMenu = (Button *)pPanel->getChildByName("btnMenu");
	pBtnMenu->addTouchEventListener(Widget::ccWidgetTouchCallback(CC_CALLBACK_2(MainScene::onBtnMenuTouchEnded, this)));

	addChild(pNode);
	
	auto listener = EventListenerTouchOneByOne::create();  
	listener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
    return true;
}

void MainScene::onBtnMenuTouchEnded(Ref *ref, Widget::TouchEventType type)
{
	switch(type)
	{
	case Widget::TouchEventType::ENDED:
		CCLog("%s", "btnMenu touched!");
		break;
	}
}

bool MainScene::onTouchBegan(Touch *touch, Event *event)
{
	Vec2 p = touch->getLocation();
	
    int x = p.x / 60.5f;
    int y = p.y / 60.5f;

	if (x > 4 || y > 5 || x < 0 || y < 0)
    {
        return false;
    }

	putNewBacterial(x, y);
	return true;
}

void MainScene::putNewBacterial(int x, int y)
{

}

bool MainScene::generateBacterial(int type)
{
	return generateBacterial(type, 1);
}

bool MainScene::generateBacterial(int type, int level)
{
	if(type == 0 || type == 1)
	{

	}

	return false;
}
