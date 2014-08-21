#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Bacterial.h"
#include "CocosPtr.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	static MainScene* getInstance();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
	virtual void onEnter();
	virtual void onExit();

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onBtnMenuTouchEnded(Ref *ref, Widget::TouchEventType type);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);

	void checkResult();

	void setScore(int);
	int getScore();

	bool generateBacterial(int type);
	bool generateBacterial(int type, int level);
	bool generateBacterial(int type, int x, int y);
	bool generateBacterial(int type, int x, int y, int level);

	void saveGame();
	bool loadGame();
private:
	int _maxLevel;
	double _enemyGenerateTime;
	double _runningTime;
	Node *_container;
	static MainScene *_instance;

	std::vector<std::vector<CocosPtr<Bacterial> *> *> *_bacterialContainer;
	Vector<Bacterial *> *_bacterialList;
	Vector<Bacterial *> *_enemyList;
	std::vector<std::vector<bool> *> *_enemyContainer;

	void setMaxLevel(int);
	void archivedDataWithVector(string &, Vector<Bacterial *>);
	void unarchivedDataWithVector(string &, Vector<Bacterial *> *);
	void prepareStage();
	void prepareGraphics();
	void putNewBacterial(int x, int y);
};

#endif // __HELLOWORLD_SCENE_H__
