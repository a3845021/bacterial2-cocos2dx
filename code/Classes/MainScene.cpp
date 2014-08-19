#include "MainScene.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "define.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace rapidjson;

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

	_maxLevel = 0;
	_enemyGenerateTime = 0;
	_runningTime = 0;
	
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

void MainScene::onEnter()
{
	Layer::onEnter();
	prepareStage();
}

void MainScene::onExit()
{
	Layer::onExit();
	saveGame();
}

void MainScene::prepareStage()
{
	int capacityX = 5;
	int capacityY = 6;

	_bacterialContainer = new std::vector<std::vector<CocosPtr<Bacterial> *> *>(capacityX);
	_enemyContainer = new std::vector<std::vector<bool> *>(capacityX);
	_bacterialList = new Vector<Bacterial *>();
	_enemyList = new Vector<Bacterial *>();

	for(int i = 0; i < capacityX; i++)
	{
		auto tmp = new std::vector<CocosPtr<Bacterial> *>(capacityY);
		auto tmp1 = new std::vector<bool>(capacityY);
		for(int j = 0; j < capacityY; j++)
		{
			tmp->push_back(new CocosPtr<Bacterial>(new Bacterial()));
			tmp1->push_back(true);
		}
		_bacterialContainer->push_back(tmp);
		_enemyContainer->push_back(tmp1);
	}

	if(loadGame())
	{
		for(auto b : *_bacterialList)
		{
			if(b->getType() == 1)
			{
				_enemyList->pushBack(b);
			}
			b->setAnchorPoint(ccp(0.5f, 0.5f));
/*
			CocosPtr<Bacterial> *ptr = _bacterialContainer->at(b->positionX)->at(b->positionY);
			delete ptr;
			ptr = NULL;
*/
			std::vector<CocosPtr<Bacterial> *>::iterator it = _bacterialContainer->at(b->positionX)->begin() + b->positionY;
			_bacterialContainer->at(b->positionX)->erase(it);
			_bacterialContainer->at(b->positionX)->insert(it, new CocosPtr<Bacterial>(b));
		}
	}
}

void MainScene::onBtnMenuTouchEnded(Ref *ref, Widget::TouchEventType type)
{
	switch(type)
	{
	case Widget::TouchEventType::ENDED:
		log("%s", "btnMenu touched!");
		saveGame();
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

bool MainScene::generateBacterial(int type, int x, int y)
{
	return generateBacterial(type, x, y, 1);
}

bool MainScene::generateBacterial(int type, int x, int y, int level)
{
	if(type == 0 || type == 1)
	{
		level = std::max(1, std::min(MAXLEVEL, level));
		std::vector<CocosPtr<Bacterial> *> *tmp = _bacterialContainer->at(x);
		
	}
	return false;
}

void MainScene::archivedDataWithVector(string &s, cocos2d::Vector<Bacterial *> list)
{
	Document doc;
	Document::AllocatorType &allocator = doc.GetAllocator();
	
	doc.SetArray();
	for(auto b : list)
	{
		rapidjson::Value object(kObjectType);
		object.AddMember("level", b->getLevel(), allocator);
		object.AddMember("type", b->getType(), allocator);
		object.AddMember("positionX", b->positionX, allocator);
		object.AddMember("positionY", b->positionY, allocator);
		object.AddMember("nextEvolution", b->nextEvolution, allocator);
		object.AddMember("nextEvolutionCurrent", b->nextEvolutionCurrent, allocator);
		object.AddMember("inited", b->inited, allocator);
		object.AddMember("checked", b->checked, allocator);
		doc.PushBack(object, allocator);
	}
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	doc.Accept(writer);

	s = buffer.GetString();
}

void MainScene::unarchivedDataWithVector(string &s, cocos2d::Vector<Bacterial *> *list)
{
	Document doc;
	doc.Parse<0>(s.c_str());
	if(doc.HasParseError())
	{
		log("GetParserError %s\n", doc.GetParseError());
	}

	if(doc.IsArray())
	{
		int count = doc.Size();
		for(int i = 0; i<count; i++)
		{
			rapidjson::Value object(kObjectType);
			object = doc[i];
			if(object.HasMember("level") && object.HasMember("type") &&
				object.HasMember("positionX") && object.HasMember("positionY"))
			{
				Bacterial *b = new Bacterial();
				b->setType(object["type"].GetInt());
				b->setLevel(object["level"].GetInt());
				b->positionX = object["positionX"].GetInt();
				b->positionY = object["positionY"].GetInt();
				b->nextEvolution = object["nextEvolution"].GetDouble();
				b->nextEvolutionCurrent = object["nextEvolutionCurrent"].GetDouble();
				b->inited = object["inited"].GetBool();
				b->checked = object["checked"].GetBool();
				list->pushBack(b);
			}
		}
	}
}

void MainScene::saveGame()
{
	UserDefault *userDefault = UserDefault::getInstance();

	userDefault->setIntegerForKey("maxLevel", _maxLevel);
	userDefault->setDoubleForKey("enemyGenerateTime", _enemyGenerateTime);
	userDefault->setDoubleForKey("runningTime", _runningTime);

	std::string bacterials;
	archivedDataWithVector(bacterials, *_bacterialList);
	log("%s", bacterials.c_str());
	userDefault->setStringForKey("bacterials", bacterials);
	userDefault->flush();
}

bool MainScene::loadGame()
{
	UserDefault *userDefault = UserDefault::getInstance();
	if(userDefault->isXMLFileExist())
	{
		_maxLevel = userDefault->getIntegerForKey("maxLevel", 0);
		_enemyGenerateTime = userDefault->getDoubleForKey("enemyGenerateTime", 0.f);
		_runningTime = userDefault->getDoubleForKey("runningTime", 0.f);

		std::string bacterials = userDefault->getStringForKey("bacterials", "[]");
		unarchivedDataWithVector(bacterials, _bacterialList);

		return true;
	}
	return false;
}
