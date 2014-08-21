#include "cocos2d.h"
#include "json/document.h"

USING_NS_CC;
using namespace rapidjson;

#pragma once
class DataStorageManager
{
public:
	~DataStorageManager(void);
	static DataStorageManager* getInstance()
	{
		if(!_instance)
		{
			_instance = new DataStorageManager();
		}
		return _instance;
	};
	void saveData();
	bool loadData();

	int score;
	int gold;
	int killerCount;
	int uperCount;
	int stepCount;
	bool guide;
	int guideStep;
	Document config;
private:
	DataStorageManager(void);

	static DataStorageManager* _instance;
};

