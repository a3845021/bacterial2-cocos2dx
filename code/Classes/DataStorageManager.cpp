#include "DataStorageManager.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

using namespace rapidjson;

DataStorageManager* DataStorageManager::_instance = nullptr;

DataStorageManager::DataStorageManager(void)
{
	score = 0;
	gold = 1000;
	killerCount = 10;
	uperCount = 10;
	stepCount = 500;
	guide = true;
	guideStep = 1;
	config.SetObject();
}


DataStorageManager::~DataStorageManager(void)
{
}

void DataStorageManager::saveData()
{
	UserDefault *userDefault = UserDefault::getInstance();

	userDefault->setIntegerForKey("score", score);
	userDefault->setIntegerForKey("gold", gold);
	userDefault->setIntegerForKey("killerCount", killerCount);
	userDefault->setIntegerForKey("uperCount", uperCount);
	userDefault->setIntegerForKey("stepCount", stepCount);
	userDefault->setBoolForKey("guide", guide);
	userDefault->setIntegerForKey("guideStep", guideStep);
	
	StringBuffer buf;
	Writer<StringBuffer> writer(buf);
	config.Accept(writer);
	userDefault->setStringForKey("config", buf.GetString());

	userDefault->flush();
}

bool DataStorageManager::loadData()
{
	UserDefault *userDefault = UserDefault::getInstance();

	if(userDefault->isXMLFileExist())
	{
		score = userDefault->getIntegerForKey("score", 0);
		gold = userDefault->getIntegerForKey("gold", 1000);
		killerCount = userDefault->getIntegerForKey("killerCount", 10);
		uperCount = userDefault->getIntegerForKey("uperCount", 10);
		stepCount = userDefault->getIntegerForKey("stepCount", 500);
		guide = userDefault->getBoolForKey("guide", true);
		guideStep = userDefault->getIntegerForKey("guideStep", 1);
		config.Parse<0>((userDefault->getStringForKey("config", "{}")).c_str());

		return true;
	}
	return false;
}