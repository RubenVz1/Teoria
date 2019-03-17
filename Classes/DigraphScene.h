#ifndef __DIGRAPH_SCENE_H__
#define __DIGRAPH_SCENE_H__

#include "cocos2d.h"
#include "GraphScene.h"

class Digraph : public Graph
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Digraph);
};

#endif // __DIGRAPH_SCENE_H__