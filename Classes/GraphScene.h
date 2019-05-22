#ifndef __GRAPH_SCENE_H__
#define __GRAPH_SCENE_H__

#include "cocos2d.h"

class Graph : public cocos2d::Scene
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Graph);

	void viewMenu1(Ref *sender);

	void viewMenu2(Ref *sender);

	void viewMenu3(Ref *sender);
	
	void viewMenu4(Ref *sender);

	float distance(cocos2d::Vec2 position1, cocos2d::Vec2 position2);

	float angle(cocos2d::Vec2 position1, cocos2d::Vec2 position2);

	bool clickNode(cocos2d::Touch* touch, cocos2d::Event* event);

	void moveNode(cocos2d::Touch* touch, cocos2d::Event* event);

	void createRelation(int indexNode1, int indexNode2);

	void viewMatrixAdjacency(Ref* sender);

	void viewMatrixIncidence(Ref* sender);

	void cameraRight(Ref* pSender);

	void cameraToOrigin(int mode);

	void cameraLeft(Ref* pSender);

	void newRelation(Ref* sender);

	void cameraDown(Ref* pSender);

	void deleteNode(Ref* sender);

	void cameraUp(Ref* pSender);

	void goToMenus(Ref* sender);

	void addNodes(Ref* pSender);

	void addNode(float x, float y);               //para pruebas

	void zoomOut(Ref* pSender);

	void zoomIn(Ref* pSender);

	void addMenu1();

	void addMenu2();

	void addMenu3();

	void addMenu4();

	void newTrajectory(Ref *sender);

	int trajectorySelected;

	void viewTrajectory(Ref *sender);

	int lastPosition;

	void positionLabel(cocos2d::Label* label,cocos2d::Vec2 position1, cocos2d::Vec2 position2);

	struct joint
	{
		int bodyNode;
		int bodyEdge;
	};

	joint _joints[200];

	int jointssize;

	int stat1;

	cocos2d::Menu* _subMenu1;

	cocos2d::Vector<cocos2d::Label*> _MatrixTrajectory;

	cocos2d::Vector<cocos2d::Label*> _MatrixAdjacency;

	cocos2d::Vector<cocos2d::Label*> _MatrixIncidence;

	cocos2d::Vector<cocos2d::Sprite*> _nodes;

	cocos2d::Vector<cocos2d::Sprite*> _edges;

	cocos2d::Vec2 _deviation;

	cocos2d::Camera *_camera;

	cocos2d::Menu* _menu1;

	cocos2d::Menu* _menu2;

	cocos2d::Menu* _menu3;

	cocos2d::Menu* _menu4;

	bool relation_selected;

	int index_selected;

	int index_matrixTrajectory;
};

#endif // __GRAPH_SCENE_H__