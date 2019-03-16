#ifndef __GRAFOS_SCENE_H__
#define __GRAFOS_SCENE_H__

#include "cocos2d.h"

class Grafos : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Grafos);

	void NewGrafo(Ref *sender);

	void addNodes(Ref* pSender);
};

#endif // __GRAFOS_SCENE_H__