#include "Bacterial.h"
#include "define.h"

USING_NS_CC;

Bacterial::Bacterial(void)
{
	level = 0;
    type = 0;
    positionX = 0;
    positionY = 0;
    nextEvolution = ENEMY_EVOLUTION_BASIC_TIME;
    nextEvolutionCurrent = ENEMY_EVOLUTION_BASIC_TIME;
	inited = false;
	checked = false;
}

Bacterial::~Bacterial(void)
{
}

Bacterial* Bacterial::create()
{
    Bacterial *sprite = new (std::nothrow) Bacterial();
    if (sprite && sprite->init())
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool Bacterial::init()
{
	if(Node::init())
	{
		bg = Sprite::create();
		addChild(bg);

		return true;
	}
	return false;
}

void Bacterial::setLevel(int value)
{
	if(level != value && value <= MAXLEVEL)
	{
		level = value;
		SpriteFrameCache* cache = SpriteFrameCache::getInstance();
		if(level > 0)
		{
			inited = true;
			SpriteFrame* frame = cache->getSpriteFrameByName(String::createWithFormat("res/%d%d.png", type, level)->getCString());
			bg->setSpriteFrame(frame);
		}
		else
		{
			inited = false;
		}
	}
}

void Bacterial::onEnter()
{
	Node::onEnter();

	//pMainScene = dynamic_cast<MainScene *>(getParent()->getParent());
}

int Bacterial::getLevel()
{
    return level;
}

void Bacterial::setType(int value)
{
    
}

int Bacterial::getType()
{
    return type;
}