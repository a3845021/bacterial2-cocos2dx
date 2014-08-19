#include "Bacterial.h"

USING_NS_CC;

Bacterial::Bacterial(void)
{
	level = 0;
    type = 0;
    positionX = 0;
    positionY = 0;
    nextEvolution = 0;
    nextEvolutionCurrent = 0;
	inited = false;
	checked = false;
}


Bacterial::~Bacterial(void)
{
}

void Bacterial::setLevel(int value)
{
	if(level != value)
	{
		level = value;
		if(level == 0)
		{
			inited = false;
		}
	}
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