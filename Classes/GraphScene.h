#ifndef __GRAPH_SCENE_H__
#define __GRAPH_SCENE_H__

#include "cocos2d.h"

class Graph : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Graph);

	void NewGrafo(Ref *sender);

	void addNodes(Ref* pSender);

	void zoomIn(Ref* pSender);

	void zoomOut(Ref* pSender);

	void cameraUp(Ref* pSender);

	void cameraDown(Ref* pSender);

	void cameraRight(Ref* pSender);

	void cameraLeft(Ref* pSender);

	void moveNode(cocos2d::Touch* touch, cocos2d::Event* event);

	void addMenus();

	cocos2d::Vector<cocos2d::MenuItem*> _menus;

	cocos2d::Camera *_camera;
	
	cocos2d::Vector<cocos2d::Sprite*> _nodes;
};

#endif // __GRAPH_SCENE_H__