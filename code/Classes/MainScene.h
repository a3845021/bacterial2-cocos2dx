#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Bacterial.h"
#include "ui\CocosGUI.h"

USING_NS_CC;
using namespace ui;

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onBtnMenuTouchEnded(Ref *ref, Widget::TouchEventType type);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);

	bool generateBacterial(int type);
	bool generateBacterial(int type, int level);
	bool generateBacterial(int type, int x, int y);
	bool generateBacterial(int type, int x, int y, int level);
private:
	Vector<Vector<Bacterial>> *_bacterialContainer;
	Vector<Bacterial> *_bacterialList;
	Vector<Bacterial> *_enemyList;
	Vector<Vector<Bacterial>> *_enemyContainer;
	void putNewBacterial(int x, int y);
};

#endif // __HELLOWORLD_SCENE_H__
