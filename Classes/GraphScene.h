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

	cocos2d::Menu* _menu;

	cocos2d::Camera *_camera;
	
	cocos2d::Vector<cocos2d::Sprite*> _nodes;

	cocos2d::Vec2 _deviation;

	int index_selected;
};

#endif // __GRAPH_SCENE_H__