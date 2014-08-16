#include "cocos2d.h"
#include <string>

using namespace std;

#pragma once
class Bacterial :
	public cocos2d::Sprite
{
public:
	Bacterial(void);
	~Bacterial(void);
    
    static string encode(Bacterial *)
    {
        return NULL;
    }
    
    static Bacterial * decode(string s)
    {
        return NULL;
    }
    
    void setLevel(int value);
    int getLevel();
    void setType(int value);
    int getType();
//    void setPositionX(int value);
//    int getPositionX();
//    void setPositionY(int value);
//    int getPositionY();
    
    int positionX;
    int positionY;
    float nextEvolution;
    float nextEvolutionCurrent;
    bool inited = false;
    bool checked = false;
private:
	int level;
    int type;
};

