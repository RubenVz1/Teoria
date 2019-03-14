#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__

#include "cocos2d.h"

class Intro : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Intro);

	cocos2d::Vector<cocos2d::Node*> MenuItems;
	void addCredits();
	void changeOpacityLabel(float dt);
	void goToMenu(float dt);
	void addNodes(Ref* pSender);
};

#endif // __INTRO_SCENE_H__
