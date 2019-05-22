#ifndef __MENUS_SCENE_H__
#define __MENUS_SCENE_H__

#include "cocos2d.h"

class Menus : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(Menus);

	void goToIntro(Ref *sender);

	void menuCloseCallback(cocos2d::Ref* pSender);

	void goToGraph(Ref *sender);

	void goToDigraph(Ref *sender);

	void MainMenu(Ref *sender);

	void addMenus();
};

#endif // __MENUS_SCENE_H__
