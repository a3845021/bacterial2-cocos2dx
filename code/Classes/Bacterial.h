#include "cocos2d.h"

using namespace std;

#pragma once
class Bacterial :
	public cocos2d::Node
{
public:
	Bacterial(void);
	~Bacterial(void);

	virtual bool init();

	static Bacterial *create();
    
    void setLevel(int value);
    int getLevel();
    void setType(int value);
    int getType();
//    void setPositionX(int value);
//    int getPositionX();
//    void setPositionY(int value);
//    int getPositionY();
	virtual void onEnter();
    
    int positionX;
    int positionY;
    float nextEvolution;
    float nextEvolutionCurrent;
    bool inited;
    bool checked;
private:
	int level;
    int type;
	cocos2d::Sprite* bg;
};

