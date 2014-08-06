#include "HelloWorldScene.h"
#include "editor-support/cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

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

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
	/*
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
	*/

	//this->setTouchEnabled(true);
	
	auto pNode = SceneReader::getInstance()->createNodeWithSceneFile("publish/MainScene.json");
	auto b = pNode->getChildByName("Button_2");
	this->addChild(pNode);
	 
	auto listener = EventListenerTouchOneByOne::create();  
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	listener->setSwallowTouches(true);//不向下传递触摸  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	Layer::onTouchBegan(touch, event);

	Vec2 p = touch->getLocationInView();
	CCLOG("x=%f, y=%f", p.x, p.y);

	return true;
}

void HelloWorld::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{

}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{

}

void HelloWorld::menuCloseCallback(Ref* pSender)
{

}
/*
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
*/
