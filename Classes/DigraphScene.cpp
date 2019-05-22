#include "DigraphScene.h"
#include "MenusScene.h"
#include "SimpleAudioEngine.h"
#include <cmath>

USING_NS_CC;

Scene* Digraph::createScene()
{
	return Digraph::create();
}

bool Digraph::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	this->getPhysicsWorld()->setGravity(Vec2::ZERO);

	auto visibleSize = Director::getInstance()->getVisibleSize();

	float x = this->getDefaultCamera()->getPositionX();
	float y = this->getDefaultCamera()->getPositionY();
	float z = this->getDefaultCamera()->getPositionZ();

	_camera = Camera::createPerspective(60, visibleSize.width / visibleSize.height, 100, 1100);
	_camera->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	_camera->setPosition3D(Vec3(x, y, z));
	_camera->setCameraFlag(CameraFlag::USER1);

	this->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);

	this->addChild(_camera, 4);

	_deviation = Vec2::Vec2(0, 0);
	index_selected = -1;

	x = visibleSize.width / 2;
	y = visibleSize.height / 2;

	auto background = Sprite::create("images/unam_logo.jpg");
	background->setAnchorPoint(Vec2(0.5f, 0.5f));
	background->setPosition(x, y);
	background->setScale(0.6f);
	background->setOpacity(80);
	background->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);

	this->addChild(background, 0);

	addMenu1();
	addMenu2();
	addMenu3();
	addMenu4();

	relation_selected = false;

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Digraph::clickNode, this);
	listener->onTouchMoved = CC_CALLBACK_2(Digraph::moveNode, this);
	listener->onTouchEnded = [=](Touch*touch, Event*event) {};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	jointssize = 0;

	index_matrixTrajectory = 0;

	return true;
}

void Digraph::addMenu1()
{
	cocos2d::Vector<cocos2d::MenuItem*> menu;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	float x = visibleSize.width / 4;
	float y = 7 * visibleSize.height / 8;

	auto labelNewNode = Label::createWithTTF("Nuevo Nodo", "fonts/Marker Felt.ttf", 24);
	labelNewNode->enableOutline(Color4B::BLACK, 1);

	auto item_1 = MenuItemLabel::create(labelNewNode, CC_CALLBACK_1(Digraph::addNodes, this));
	item_1->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_1->setPosition(Vec2(x, y));

	menu.pushBack(item_1);

	x = 2 * visibleSize.width / 4;
	y = 7 * visibleSize.height / 8;

	auto labelNewRelation = Label::createWithTTF("Nueva Relacion", "fonts/Marker Felt.ttf", 24);
	labelNewRelation->enableOutline(Color4B::BLACK, 1);

	auto item_2 = MenuItemLabel::create(labelNewRelation, CC_CALLBACK_1(Digraph::newRelation, this));
	item_2->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_2->setPosition(Vec2(x, y));

	menu.pushBack(item_2);

	x = 3 * visibleSize.width / 8;
	y = 7 * visibleSize.height / 8;

	auto labelDeleteNode = Label::createWithTTF("Borrar Nodo", "fonts/Marker Felt.ttf", 24);
	labelDeleteNode->enableOutline(Color4B::BLACK, 1);

	auto item_3 = MenuItemLabel::create(labelDeleteNode, CC_CALLBACK_1(Digraph::deleteNode, this));
	item_3->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_3->setPosition(Vec2(x, y));

	//menu.pushBack(item_3);

	x = 4 * visibleSize.width / 8;
	y = 7 * visibleSize.height / 8;

	auto labelDeleteRelation = Label::createWithTTF("Borrar Relacion", "fonts/Marker Felt.ttf", 24);
	labelDeleteRelation->enableOutline(Color4B::BLACK, 1);

	auto item_4 = MenuItemLabel::create(labelDeleteRelation, CC_CALLBACK_1(Digraph::addNodes, this));
	item_4->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_4->setPosition(Vec2(x, y));

	//menu.pushBack(item_4);

	x = 3 * visibleSize.width / 4;
	y = 7 * visibleSize.height / 8;

	auto labelViewMatrix = Label::createWithTTF("Matriz", "fonts/Marker Felt.ttf", 24);
	labelViewMatrix->enableOutline(Color4B::BLACK, 1);

	auto item_5 = MenuItemLabel::create(labelViewMatrix, CC_CALLBACK_1(Digraph::viewMenu2, this));
	item_5->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_5->setPosition(Vec2(x, y));

	menu.pushBack(item_5);

	x = 6 * visibleSize.width / 8;
	y = 7 * visibleSize.height / 8;

	auto labelViewTrajectories = Label::createWithTTF("Trayectorias", "fonts/Marker Felt.ttf", 24);
	labelViewTrajectories->enableOutline(Color4B::BLACK, 1);

	auto item_6 = MenuItemLabel::create(labelViewTrajectories, CC_CALLBACK_1(Digraph::viewMenu3, this));
	item_6->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_6->setPosition(Vec2(x, y));

	//menu.pushBack(item_6);

	x = 7 * visibleSize.width / 8;
	y = 7 * visibleSize.height / 8;

	auto labelViewCircuits = Label::createWithTTF("Circuitos", "fonts/Marker Felt.ttf", 24);
	labelViewCircuits->enableOutline(Color4B::BLACK, 1);

	auto item_7 = MenuItemLabel::create(labelViewCircuits, CC_CALLBACK_1(Digraph::viewMenu4, this));
	item_7->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_7->setPosition(Vec2(x, y));

	//menu.pushBack(item_7);

	x = 3 * visibleSize.width / 6;
	y = visibleSize.height / 8;

	auto labelReturn = Label::createWithTTF("Regresar", "fonts/Marker Felt.ttf", 24);
	labelReturn->enableOutline(Color4B::BLACK, 1);

	auto item_8 = MenuItemLabel::create(labelReturn, CC_CALLBACK_1(Digraph::goToMenus, this));
	item_8->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_8->setPosition(Vec2(x, y));

	menu.pushBack(item_8);

	x = 2 * visibleSize.width / 6;
	y = visibleSize.height / 8;

	auto labelZoomIn = Label::createWithTTF("Zoom in", "fonts/Marker Felt.ttf", 24);
	labelZoomIn->enableOutline(Color4B::BLACK, 1);

	auto item_9 = MenuItemLabel::create(labelZoomIn, CC_CALLBACK_1(Digraph::zoomIn, this));
	item_9->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_9->setPosition(Vec2(x, y));

	//menu.pushBack(item_9);

	x = 4 * visibleSize.width / 6;
	y = visibleSize.height / 8;

	auto labelZoomOut = Label::createWithTTF("Zoom Out", "fonts/Marker Felt.ttf", 24);
	labelZoomOut->enableOutline(Color4B::BLACK, 1);

	auto item_10 = MenuItemLabel::create(labelZoomOut, CC_CALLBACK_1(Digraph::zoomOut, this));
	item_10->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_10->setPosition(Vec2(x, y));

	//menu.pushBack(item_10);

	x = visibleSize.width / 2;
	y = visibleSize.height / 8;

	auto arrowDown = MenuItemImage::create("images/normal.png", "images/selected.png", CC_CALLBACK_1(Digraph::cameraDown, this));
	arrowDown->setAnchorPoint(Vec2(0.5f, 0.5f));
	arrowDown->setPosition(Vec2(x, y));
	arrowDown->setScale(0.1f);

	//menu.pushBack(arrowDown);

	x = visibleSize.width / 2;
	y = 120 + visibleSize.height / 2;

	auto arrowUp = MenuItemImage::create("images/normal.png", "images/selected.png", CC_CALLBACK_1(Digraph::cameraUp, this));
	arrowUp->setAnchorPoint(Vec2(0.5f, 0.5f));
	arrowUp->setPosition(Vec2(x, y));
	arrowUp->setScale(0.1f);
	arrowUp->setRotation(180);

	//menu.pushBack(arrowUp);

	x = 120 + visibleSize.width / 2;
	y = visibleSize.height / 2;

	auto arrowRight = MenuItemImage::create("images/normal.png", "images/selected.png", CC_CALLBACK_1(Digraph::cameraRight, this));
	arrowRight->setAnchorPoint(Vec2(0.5f, 0.5f));
	arrowRight->setPosition(Vec2(x, y));
	arrowRight->setScale(0.1f);
	arrowRight->setRotation(270);

	//menu.pushBack(arrowRight);

	x = visibleSize.width / 2 - 90;
	y = visibleSize.height / 2;

	auto arrowLeft = MenuItemImage::create("images/normal.png", "images/selected.png", CC_CALLBACK_1(Digraph::cameraLeft, this));
	arrowLeft->setAnchorPoint(Vec2(0.5f, 0.5f));
	arrowLeft->setPosition(Vec2(x, y));
	arrowLeft->setScale(0.1f);
	arrowLeft->setRotation(90);

	//menu.pushBack(arrowLeft);

	_menu1 = Menu::createWithArray(menu);
	_menu1->setPosition(Vec2::ZERO);
	_menu1->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);

	this->addChild(_menu1, 3);
}

void Digraph::addMenu2()
{
	cocos2d::Vector<cocos2d::MenuItem*> menu;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	float x = 7 * visibleSize.width / 8;
	float y = visibleSize.height / 8;

	auto labelBack = Label::createWithTTF("Regresar", "fonts/Marker Felt.ttf", 24);
	labelBack->enableOutline(Color4B::BLACK, 1);

	auto item_1 = MenuItemLabel::create(labelBack, CC_CALLBACK_1(Digraph::viewMenu1, this));
	item_1->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_1->setPosition(Vec2(x, y));

	menu.pushBack(item_1);

	x = visibleSize.width / 3;
	y = 7 * visibleSize.height / 8;

	auto labelIncidence = Label::createWithTTF("Matriz incidencia", "fonts/Marker Felt.ttf", 24);
	labelIncidence->enableOutline(Color4B::BLACK, 1);

	auto item_2 = MenuItemLabel::create(labelIncidence, CC_CALLBACK_1(Digraph::viewMatrixIncidence, this));
	item_2->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_2->setPosition(Vec2(x, y));

	menu.pushBack(item_2);

	x = 2 * visibleSize.width / 3;
	y = 7 * visibleSize.height / 8;

	auto labelAdjacency = Label::createWithTTF("Matriz adyacencia", "fonts/Marker Felt.ttf", 24);
	labelAdjacency->enableOutline(Color4B::BLACK, 1);

	auto item_3 = MenuItemLabel::create(labelAdjacency, CC_CALLBACK_1(Digraph::viewMatrixAdjacency, this));
	item_3->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_3->setPosition(Vec2(x, y));

	menu.pushBack(item_3);

	_menu2 = Menu::createWithArray(menu);
	_menu2->setPosition(Vec2::ZERO);
	_menu2->setOpacity(0.0f);
	_menu2->setScale(0.0f);
	_menu2->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);

	this->addChild(_menu2, 3);
}

void Digraph::addMenu3()
{
	cocos2d::Vector<cocos2d::MenuItem*> menu;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	float x = 7 * visibleSize.width / 8;
	float y = visibleSize.height / 8;

	auto labelBack = Label::createWithTTF("Regresar1111111", "fonts/Marker Felt.ttf", 24);
	labelBack->enableOutline(Color4B::BLACK, 1);

	auto item_1 = MenuItemLabel::create(labelBack, CC_CALLBACK_1(Digraph::viewMenu1, this));
	item_1->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_1->setPosition(Vec2(x, y));

	menu.pushBack(item_1);

	x = visibleSize.width / 3;
	y = 7 * visibleSize.height / 8;

	auto labelIncidence = Label::createWithTTF("Nueva Trayectoria", "fonts/Marker Felt.ttf", 24);
	labelIncidence->enableOutline(Color4B::BLACK, 1);

	auto item_2 = MenuItemLabel::create(labelIncidence, CC_CALLBACK_1(Digraph::newTrajectory, this));
	item_2->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_2->setPosition(Vec2(x, y));

	menu.pushBack(item_2);

	x = 2 * visibleSize.width / 3;
	y = 7 * visibleSize.height / 8;

	auto labelAdjacency = Label::createWithTTF("Matriz trayectoria", "fonts/Marker Felt.ttf", 24);
	labelAdjacency->enableOutline(Color4B::BLACK, 1);

	auto item_3 = MenuItemLabel::create(labelAdjacency, CC_CALLBACK_1(Digraph::viewTrajectory, this));
	item_3->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_3->setPosition(Vec2(x, y));

	menu.pushBack(item_3);

	_menu3 = Menu::createWithArray(menu);
	_menu3->setPosition(Vec2::ZERO);
	_menu3->setOpacity(0.0f);
	_menu3->setScale(0.0f);
	_menu3->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);

	this->addChild(_menu3, 3);

	trajectorySelected = 0;

	x = visibleSize.width / 2;
	y = visibleSize.height / 8;

	auto labelBack1 = Label::createWithTTF("Regresar", "fonts/Marker Felt.ttf", 24);
	labelBack1->enableOutline(Color4B::BLACK, 1);

	auto item = MenuItemLabel::create(labelBack1, CC_CALLBACK_1(Digraph::newTrajectory, this));
	item->setAnchorPoint(Vec2(0.5f, 0.5f));
	item->setPosition(Vec2(x, y));

	_subMenu1 = Menu::createWithItem(item);

	_subMenu1->setPosition(Vec2::ZERO);
	_subMenu1->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);
	_subMenu1->setOpacity(0.0f);
	_subMenu1->setScale(0.0f);
	this->addChild(_subMenu1, 4);
}

void Digraph::addMenu4()
{
	cocos2d::Vector<cocos2d::MenuItem*> menus_2;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	float x = 7 * visibleSize.width / 8;
	float y = visibleSize.height / 8;

	auto labelBack = Label::createWithTTF("Regresar", "fonts/Marker Felt.ttf", 24);
	labelBack->enableOutline(Color4B::BLACK, 1);

	auto item_1 = MenuItemLabel::create(labelBack, CC_CALLBACK_1(Digraph::viewMenu1, this));
	item_1->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_1->setPosition(Vec2(x, y));

	menus_2.pushBack(item_1);

	x = visibleSize.width / 3;
	y = 7 * visibleSize.height / 8;

	auto labelIncidence = Label::createWithTTF("Nuevo Circuito", "fonts/Marker Felt.ttf", 24);
	labelIncidence->enableOutline(Color4B::BLACK, 1);

	auto item_2 = MenuItemLabel::create(labelIncidence, CC_CALLBACK_1(Digraph::addNodes, this));
	item_2->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_2->setPosition(Vec2(x, y));

	menus_2.pushBack(item_2);

	x = 2 * visibleSize.width / 3;
	y = 7 * visibleSize.height / 8;

	auto labelAdjacency = Label::createWithTTF("Matriz Circuitos", "fonts/Marker Felt.ttf", 24);
	labelAdjacency->enableOutline(Color4B::BLACK, 1);

	auto item_3 = MenuItemLabel::create(labelAdjacency, CC_CALLBACK_1(Digraph::addNodes, this));
	item_3->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_3->setPosition(Vec2(x, y));

	menus_2.pushBack(item_3);

	_menu4 = Menu::createWithArray(menus_2);
	_menu4->setPosition(Vec2::ZERO);
	_menu4->setOpacity(0.0f);
	_menu4->setScale(0.0f);
	_menu4->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);

	this->addChild(_menu4, 3);
}

void Digraph::newTrajectory(Ref *sender)
{
	if (trajectorySelected == 0)
	{
		_menu3->setOpacity(0.0f);
		_menu3->setScale(0.0f);
		_subMenu1->setOpacity(255.0f);
		_subMenu1->setScale(1.0f);

		for (int i = 0; i < _nodes.size(); i++)
			_nodes.at(i)->setOpacity(255.0f);
		for (int i = 0; i < _edges.size(); i++)
			_edges.at(i)->setOpacity(255.0f);

		auto visibleSize = Director::getInstance()->getVisibleSize();

		float x = visibleSize.width / 2;
		float y = 7 * visibleSize.height / 8;

		trajectorySelected = 1;

		if (_MatrixTrajectory.size() == 0)
		{
			x = 370;
			y = 570;
		}
		else
		{
			x = _MatrixTrajectory.at(lastPosition)->getPositionX();
			y = _MatrixTrajectory.at(lastPosition)->getPositionY() - 25.0f;
		}
		index_matrixTrajectory++;
		char name[17];
		cocos2d::log("Trayectoria %d:", index_matrixTrajectory);
		sprintf(name, "Trayectoria %d:", index_matrixTrajectory);
		Label* label1 = Label::createWithTTF(name, "fonts/Marker Felt.ttf", 16);
		label1->enableOutline(Color4B::BLACK, 2);
		label1->setAnchorPoint(Vec2(1.0f, 0.5f));
		label1->setPosition(x, y);
		_MatrixTrajectory.pushBack(label1);
		lastPosition = _MatrixTrajectory.size() - 1;
	}
	else
	{
		char name[17];

		cocos2d::log("se va a eliminar --> Trayectoria %d:", index_matrixTrajectory);
		sprintf(name, "Trayectoria %d:", index_matrixTrajectory);

		auto aux = _MatrixTrajectory.size() - 1;
		if (_MatrixTrajectory.at(aux)->getString() == name)
		{
			this->removeChild(_MatrixTrajectory.at(aux));
			index_matrixTrajectory--;
		}

		_menu3->setOpacity(255.0f);
		_menu3->setScale(1.0f);
		_subMenu1->setOpacity(0.0f);
		_subMenu1->setScale(0.0f);

		for (int i = 0; i < _nodes.size(); i++)
			_nodes.at(i)->setOpacity(127.0f);
		for (int i = 0; i < _edges.size(); i++)
			_edges.at(i)->setOpacity(127.0f);
		trajectorySelected = 0;
	}
	for (int i = 0; i < _MatrixTrajectory.size();i++)
		this->removeChild(_MatrixTrajectory.at(i));
}

void Digraph::viewTrajectory(Ref *sender)
{
	for (int i = 0; i < _MatrixTrajectory.size();i++)
	{
		this->removeChild(_MatrixTrajectory.at(i));
		this->addChild(_MatrixTrajectory.at(i));
	}
}

void Digraph::newRelation(Ref* sender)
{
	if (index_selected != -1)
	{
		relation_selected = true;
	}
}

bool Digraph::clickNode(Touch* touch, Event* event)
{
	cameraToOrigin(0);

	auto touchPosition = touch->getLocation();

	touchPosition.x += _deviation.x;
	touchPosition.y += _deviation.y;

	int index = -1;

	for (int i = 0; i != _nodes.size();i++)
	{
		if (_nodes.at(i)->getBoundingBox().containsPoint(touchPosition))
		{
			index = i;
		}
		if (index_selected != index)
		{
			for (int i = 0; i != _nodes.size(); i++)
			{
				_nodes.at(i)->setScale(0.2f);
			}
		}
	}
	if (index == -1 || index_selected == -1)
	{
		relation_selected = false;
	}
	if (relation_selected)
	{
		if(index_selected != index)
			createRelation(index_selected, index);
		relation_selected = false;
		return true;
	}
	if (trajectorySelected)
	{
		cocos2d::log("Se añadio el nodo V%d", index + 1);
		char name[4];
		sprintf(name, "V%d", (index + 1));
		int aux = _MatrixTrajectory.size() - 1;
		float x = _MatrixTrajectory.at(aux)->getPositionX() + 25.0f;
		float y = _MatrixTrajectory.at(aux)->getPositionY();
		auto label = Label::createWithTTF(name, "fonts/Marker Felt.ttf", 16);
		label->enableOutline(Color4B::BLACK, 2);
		label->setAnchorPoint(Vec2(0.5f, 0.5f));
		label->setPosition(x, y);
		_MatrixTrajectory.pushBack(label);
	}
	if (index != -1)
	{
		_nodes.at(index)->setScale(0.26f);
	}

	index_selected = index;

	return true;
}

float Digraph::distance(Vec2 position1, Vec2 position2)
{
	auto x = position1.x - position2.x;
	auto y = position1.y - position2.y;

	auto distance = sqrt(pow(x, 2) + pow(y, 2));

	return distance;
}

void Digraph::positionLabel(Label* label, Vec2 position1, Vec2 position2)
{
	auto x = (position1.x + position2.x) / 2;
	auto y = (position1.y + position2.y) / 2;

	label->setPosition(x, y);
}

float Digraph::angle(Vec2 position1, Vec2 position2)
{
	auto delta_position = position1;

	position1.x -= delta_position.x;
	position1.y -= delta_position.y;
	position2.x -= delta_position.x;
	position2.y -= delta_position.y;

	auto angle = atan(position2.y / position2.x);
	angle = angle * (360 / (M_PI * 2));

	auto condition = (position2.x < 0 && position2.y > 0) || (position2.x < 0 && position2.y < 0);
	if (condition)
		angle = 180 + angle;
	return -1 * angle;
}

void Digraph::createRelation(int indexNode1, int indexNode2)
{
	if (_edges.size() == 20)
	{
		return;
	}
	auto relation = Sprite::create("images/arrow.png");
	auto rect = relation->getContentSize();
	auto relationBody = PhysicsBody::createBox(rect, PHYSICSBODY_MATERIAL_DEFAULT, Vec2::ZERO);
	relationBody->setDynamic(false);
	relationBody->setCategoryBitmask(0x02);
	relationBody->setCollisionBitmask(0x01);
	relation->setPhysicsBody(relationBody);


	auto position1 = _nodes.at(indexNode1)->getPosition();
	auto position2 = _nodes.at(indexNode2)->getPosition();

	float aux = distance(position1, position2) / relation->getBoundingBox().size.width;
	float angleNodes = angle(position1, position2);

	relation->setScaleX(aux);
	relation->setRotation(angleNodes);
	relation->setPosition(position1);
	relation->setAnchorPoint(Vec2(0.0f, 0.5f));
	relation->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);

	auto r = random(0, 255), g = random(0, 255), b = random(0, 255);
	relation->setColor(Color3B(r, g, b));

	char name[4];
	sprintf(name, "e%d", (_edges.size() + 1));
	auto label = Label::createWithTTF(name, "fonts/Marker Felt.ttf", 24);
	label->enableOutline(Color4B::BLACK, 2);
	label->setAnchorPoint(Vec2(0.5f, 0.5f));
	positionLabel(label, position1, position2);

	auto labelBody = PhysicsBody::createBox(label->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 10.0f), Vec2::ZERO);
	labelBody->setCategoryBitmask(0x02);
	labelBody->setCollisionBitmask(0x01);
	label->setPhysicsBody(labelBody);
	this->addChild(label, 2);

	auto joint = PhysicsJointPin::construct(relationBody, labelBody, position1);
	joint->setCollisionEnable(false);
	getPhysicsWorld()->addJoint(joint);

	//******************************************************************************************//

	auto node1Body = _nodes.at(indexNode1)->getPhysicsBody();
	auto node2Body = _nodes.at(indexNode2)->getPhysicsBody();

	auto joint1 = PhysicsJointPin::construct(node1Body, relationBody, position1);
	joint1->setCollisionEnable(false);
	getPhysicsWorld()->addJoint(joint1);

	_joints[jointssize].bodyEdge = _edges.size();
	_joints[jointssize].bodyNode = indexNode1;
	_joints[jointssize].value = 1;

	auto joint2 = PhysicsJointPin::construct(node2Body, relationBody, position2);
	joint2->setCollisionEnable(false);
	getPhysicsWorld()->addJoint(joint2);

	_joints[jointssize + 1].bodyEdge = _edges.size();
	_joints[jointssize + 1].bodyNode = indexNode2;
	_joints[jointssize + 1].value = -1;

	//******************************************************************************************//

	_edges.pushBack(relation);
	float index = _edges.size() - 1;
	this->addChild(_edges.at(index), 1);

	jointssize += 2;
}

void Digraph::moveNode(Touch* touch, Event* event)
{
	if (index_selected != -1)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();

		auto touchPosition = touch->getLocation();
		
		if (touchPosition.x <= 0 || touchPosition.x >= visibleSize.width)
			return;

		if (touchPosition.y <= 0 || touchPosition.y >= visibleSize.height)
			return;

		touchPosition.x += _deviation.x;
		touchPosition.y += _deviation.y;

		_nodes.at(index_selected)->setPosition(touchPosition);

		//updateEdge();
	}
}

void Digraph::addNodes(Ref* pSender)
{
	cameraToOrigin(1);

	if (_nodes.size() == 20)
	{
		return;
	}

	auto node = Sprite::create("images/node_1.png");
	auto position = _camera->getPosition();
	node->setPosition(position);
	node->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	node->setScale(0.2f);
	node->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);

	auto radiu = node->getContentSize().height / 2;
	auto nodeBody = PhysicsBody::createCircle(radiu, PHYSICSBODY_MATERIAL_DEFAULT, Vec2::ZERO);
	//nodeBody->setDynamic(false);
	nodeBody->setCategoryBitmask(0x02);
	nodeBody->setCollisionBitmask(0x01);
	node->setPhysicsBody(nodeBody);

	auto r = random(0, 255), g = random(0, 255), b = random(0, 255);
	node->setColor(Color3B(r, g, b));

	char name[4];
	sprintf(name, "v%d", (_nodes.size() + 1));
	auto label = Label::createWithTTF(name, "fonts/Marker Felt.ttf", 19);
	label->enableOutline(Color4B::BLACK, 2);
	label->setAnchorPoint(Vec2(0.5f, 0.5f));
	label->setPosition(position);

	auto labelBody = PhysicsBody::createBox(label->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 10.0f), Vec2::ZERO);
	labelBody->setCategoryBitmask(0x02);
	labelBody->setCollisionBitmask(0x01);
	label->setPhysicsBody(labelBody);

	auto joint = PhysicsJointPin::construct(nodeBody, labelBody, position);
	joint->setCollisionEnable(false);
	getPhysicsWorld()->addJoint(joint);

	_nodes.pushBack(node);
	float index = _nodes.size() - 1;
	this->addChild(_nodes.at(index), 2);
	this->addChild(label, 3);
}

void Digraph::addNode(float x, float y)
{
	cameraToOrigin(1);

	if (_nodes.size() == 20)
	{
		return;
	}

	auto node = Sprite::create("images/node_1.png");
	node->setPosition(x, y);
	node->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	node->setScale(0.2f);
	node->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);

	auto radiu = node->getContentSize().height / 2;
	auto nodeBody = PhysicsBody::createCircle(radiu, PHYSICSBODY_MATERIAL_DEFAULT, Vec2::ZERO);
	nodeBody->setCategoryBitmask(0x02);
	nodeBody->setCollisionBitmask(0x01);
	node->setPhysicsBody(nodeBody);

	auto r = random(0, 255), g = random(0, 255), b = random(0, 255);
	node->setColor(Color3B(r, g, b));

	char name[4];
	sprintf(name, "v%d", (_nodes.size() + 1));
	auto label = Label::createWithTTF(name, "fonts/Marker Felt.ttf", 19);
	label->enableOutline(Color4B::BLACK, 2);
	label->setAnchorPoint(Vec2(0.5f, 0.5f));
	label->setPosition(x, y);

	auto labelBody = PhysicsBody::createBox(label->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 10.0f), Vec2::ZERO);
	labelBody->setCategoryBitmask(0x02);
	labelBody->setCollisionBitmask(0x01);
	label->setPhysicsBody(labelBody);

	auto joint = PhysicsJointPin::construct(nodeBody, labelBody, Vec2(x, y));
	joint->setCollisionEnable(false);
	getPhysicsWorld()->addJoint(joint);

	_nodes.pushBack(node);
	float index = _nodes.size() - 1;
	this->addChild(_nodes.at(index), 2);
	this->addChild(label, 3);
}

void Digraph::cameraToOrigin(int mode)
{
	float x = this->getDefaultCamera()->getPositionX();
	float y = this->getDefaultCamera()->getPositionY();
	float z = this->getDefaultCamera()->getPositionZ();
	if (mode)
	{
		while (x < _camera->getPositionX())
		{
			cameraLeft(this);
		}
		while (x > _camera->getPositionX())
		{
			cameraRight(this);
		}
		while (y < _camera->getPositionY())
		{
			cameraDown(this);
		}
		while (y > _camera->getPositionY())
		{
			cameraUp(this);
		}
		cameraToOrigin(0);
	}
	else
	{
		while (z < _camera->getPositionZ())
		{
			zoomIn(this);
		}
		while (z > _camera->getPositionZ())
		{
			zoomOut(this);
		}
	}
}

void Digraph::zoomIn(Ref* pSender)
{
	auto position3Ds = _camera->getPosition3D();
	position3Ds.z -= 10.0f;
	_camera->setPosition3D(position3Ds);

	position3Ds = _menu1->getPosition3D();
	position3Ds.z -= 10.0f;
	_menu1->setPosition3D(position3Ds);
	_menu2->setPosition3D(position3Ds);
}

void Digraph::zoomOut(Ref* pSender)
{
	auto position3Ds = _camera->getPosition3D();
	position3Ds.z += 10.0f;
	_camera->setPosition3D(position3Ds);

	position3Ds = _menu1->getPosition3D();
	position3Ds.z += 10.0f;
	_menu1->setPosition3D(position3Ds);
	_menu2->setPosition3D(position3Ds);
}

void Digraph::cameraRight(Ref* pSender)
{
	if (_deviation.x >= 530)
	{
		return;
	}
	auto position2Ds = _menu1->getPosition();
	position2Ds.x += 10.0f;
	_menu1->setPosition(position2Ds);
	_menu2->setPosition(position2Ds);

	auto position3Ds = _camera->getPosition3D();
	position3Ds.x += 10.0f;
	_camera->setPosition3D(position3Ds);

	_deviation.x += 10.0f;

	for (int i = 0; i < _nodes.size(); i++)
	{
		auto positionNode = _nodes.at(i)->getPhysicsBody()->getPositionOffset();
		positionNode.x -= 10.0f;
		_nodes.at(i)->getPhysicsBody()->setPositionOffset(positionNode);
	}
}

void Digraph::cameraLeft(Ref* pSender)
{
	if (_deviation.x <= -530)
	{
		return;
	}

	auto position2Ds = _menu1->getPosition();
	position2Ds.x -= 10.0f;
	_menu1->setPosition(position2Ds);
	_menu2->setPosition(position2Ds);

	auto position3Ds = _camera->getPosition3D();
	position3Ds.x -= 10.0f;
	_camera->setPosition3D(position3Ds);

	_deviation.x -= 10.0f;

	for (int i = 0; i < _nodes.size(); i++)
	{
		auto positionNode = _nodes.at(i)->getPhysicsBody()->getPositionOffset();
		positionNode.x += 10.0f;
		_nodes.at(i)->getPhysicsBody()->setPositionOffset(positionNode);
	}
}

void Digraph::cameraUp(Ref* pSender)
{
	if (_deviation.y >= 530)
	{
		return;
	}

	auto position2Ds = _menu1->getPosition();
	position2Ds.y += 10.0f;
	_menu1->setPosition(position2Ds);
	_menu2->setPosition(position2Ds);

	auto position3Ds = _camera->getPosition3D();
	position3Ds.y += 10.0f;
	_camera->setPosition3D(position3Ds);

	_deviation.y += 10.0f;

	for (int i = 0; i < _nodes.size(); i++)
	{
		auto positionNode = _nodes.at(i)->getPhysicsBody()->getPositionOffset();
		positionNode.y -= 10.0f;
		_nodes.at(i)->getPhysicsBody()->setPositionOffset(positionNode);
	}
}

void Digraph::cameraDown(Ref* pSender)
{
	if (_deviation.y <= -530)
	{
		return;
	}

	auto position2Ds = _menu1->getPosition();
	position2Ds.y -= 10.0f;
	_menu1->setPosition(position2Ds);
	_menu2->setPosition(position2Ds);

	auto position3Ds = _camera->getPosition3D();
	position3Ds.y -= 10.0f;
	_camera->setPosition3D(position3Ds);

	_deviation.y -= 10.0f;

	for (int i = 0; i < _nodes.size(); i++)
	{
		auto positionNode = _nodes.at(i)->getPhysicsBody()->getPositionOffset();
		positionNode.y += 10.0f;
		_nodes.at(i)->getPhysicsBody()->setPositionOffset(positionNode);
	}
}

void Digraph::goToMenus(Ref *sender)
{
	auto scene = Menus::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
}

void Digraph::deleteNode(Ref *sender)
{
	if (index_selected != -1)
	{
		this->removeChild(_nodes.at(index_selected));
	}
	cocos2d::log("index: %d", index_selected);
	index_selected = -1;
}

void Digraph::viewMatrixAdjacency(Ref* sender)
{
	for (int i = 0; i < _MatrixAdjacency.size(); i++)
		this->removeChild(_MatrixAdjacency.at(i));
	_MatrixAdjacency.clear();

	for (int i = 0; i < _MatrixIncidence.size(); i++)
		this->removeChild(_MatrixIncidence.at(i));
	_MatrixIncidence.clear();

	float x = 0;
	float y = 0;
	for (int i = 0; i < _nodes.size(); i++)
	{
		for (int j = 0; j < _nodes.size(); j++)
		{
			Label* label = NULL;
			label = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 16);
			label->enableOutline(Color4B::BLACK, 2);
			label->setAnchorPoint(Vec2(0.5f, 0.5f));
			label->setColor(Color3B(250, 252, 180));
			label->setPosition(x, y);
			_MatrixAdjacency.pushBack(label);
			x += 25.0f;
		}
		x = 0;
		y -= 25.0f;
	}


	int aux = _MatrixAdjacency.size() - 1;
	float centerX = (_MatrixAdjacency.at(aux)->getPosition().x - _MatrixAdjacency.at(0)->getPosition().x) / 2;
	float centerY = (_MatrixAdjacency.at(0)->getPosition().y - _MatrixAdjacency.at(aux)->getPosition().y) / 2;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	for (int i = 0; i < _MatrixAdjacency.size(); i++)
	{
		auto positionX = _MatrixAdjacency.at(i)->getPositionX() + ((visibleSize.width / 2) - centerX);
		_MatrixAdjacency.at(i)->setPositionX(positionX);
		auto positionY = _MatrixAdjacency.at(i)->getPositionY() + ((visibleSize.height / 2) + centerY);
		_MatrixAdjacency.at(i)->setPositionY(positionY);
	}

	for (int i = 0; i < jointssize; i++)
	{
		for (int j = i + 1; j < jointssize; j++)
		{
			if (_joints[i].bodyEdge == _joints[j].bodyEdge)
			{
				int k = _joints[i].bodyNode;
				int l = _joints[j].bodyNode;
				int size = _nodes.size();
				_MatrixAdjacency.at(k + l * size)->setString("0");
				_MatrixAdjacency.at(l + k * size)->setString("1");
			}
		}
	}


	for (int i = 0; i < _nodes.size(); i++)
	{
		auto x = _MatrixAdjacency.at(i * _nodes.size())->getPositionX() - 25;
		auto y = _MatrixAdjacency.at(i * _nodes.size())->getPositionY();
		char name[4];
		sprintf(name, "v%d", (i + 1));
		auto label = Label::createWithTTF(name, "fonts/Marker Felt.ttf", 16);
		label->enableOutline(Color4B::BLACK, 2);
		label->setAnchorPoint(Vec2(0.5f, 0.5f));
		label->setColor(Color3B(255,0,0));
		label->setPosition(x, y);
		_MatrixAdjacency.pushBack(label);

		x = _MatrixAdjacency.at(i)->getPositionX();
		y = _MatrixAdjacency.at(i)->getPositionY() + 25;
		label = Label::createWithTTF(name, "fonts/Marker Felt.ttf", 16);
		label->enableOutline(Color4B::BLACK, 2);
		label->setAnchorPoint(Vec2(0.5f, 0.5f));
		label->setColor(Color3B(255, 0, 0));
		label->setPosition(x, y);
		_MatrixAdjacency.pushBack(label);
	}


	for (int i = 0; i < _MatrixAdjacency.size(); i++)
	{
		this->addChild(_MatrixAdjacency.at(i),3);
	}
}

void Digraph::viewMatrixIncidence(Ref* sender)
{
	
	for (int i = 0; i < _MatrixAdjacency.size(); i++)
		this->removeChild(_MatrixAdjacency.at(i));
	_MatrixAdjacency.clear();

	for (int i = 0; i < _MatrixIncidence.size(); i++)
		this->removeChild(_MatrixIncidence.at(i));
	_MatrixIncidence.clear();

	if (!_edges.size())
	{
		cocos2d::log("no hay aristas");
		return;
	}

	float x = 0;
	float y = 0;
	for (int i = 0; i < _nodes.size(); i++)
	{
		for (int j = 0; j < _edges.size(); j++)
		{
			auto label = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 16);
			label->enableOutline(Color4B::BLACK, 2);
			label->setAnchorPoint(Vec2(0.5f, 0.5f));
			label->setColor(Color3B(250, 252, 180));
			label->setPosition(x, y);
			_MatrixIncidence.pushBack(label);
			x += 25.0f;
		}
		x = 0;
		y -= 25.0f;
	}

	int aux = _MatrixIncidence.size() - 1;
	float centerX = (_MatrixIncidence.at(aux)->getPosition().x - _MatrixIncidence.at(0)->getPosition().x) / 2;
	float centerY = (_MatrixIncidence.at(0)->getPosition().y - _MatrixIncidence.at(aux)->getPosition().y) / 2;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	for (int i = 0; i < _MatrixIncidence.size(); i++)
	{
		auto positionY = _MatrixIncidence.at(i)->getPositionY() + ((visibleSize.height / 2) + centerY);
		_MatrixIncidence.at(i)->setPositionY(positionY);
		auto positionX = _MatrixIncidence.at(i)->getPositionX() + ((visibleSize.width / 2) - centerX);
		_MatrixIncidence.at(i)->setPositionX(positionX);
	}

	for (int i = 0; i < jointssize; i++)
	{
		int k = _joints[i].bodyEdge;
		int l = _joints[i].bodyNode;
		int size = _edges.size();
		if(_joints[i].value == 1)
			_MatrixIncidence.at(k + l * size)->setString("1");
		else
			_MatrixIncidence.at(k + l * size)->setString("-1");
	}

	for (int i = 0; i < _nodes.size(); i++)
	{
		auto x = _MatrixIncidence.at(i * _edges.size())->getPositionX() - 25;
		auto y = _MatrixIncidence.at(i * _edges.size())->getPositionY();
		char name[4];
		sprintf(name, "v%d", (i + 1));
		auto label = Label::createWithTTF(name, "fonts/Marker Felt.ttf", 16);
		label->enableOutline(Color4B::BLACK, 2);
		label->setAnchorPoint(Vec2(0.5f, 0.5f));
		label->setColor(Color3B(255, 0, 0));
		label->setPosition(x, y);
		_MatrixIncidence.pushBack(label);
	}

	for (int i = 0; i < _edges.size(); i++)
	{
		auto x = _MatrixIncidence.at(i)->getPositionX();
		auto y = _MatrixIncidence.at(i)->getPositionY() + 25;
		char name[4];
		sprintf(name, "e%d", (i + 1));
		auto label = Label::createWithTTF(name, "fonts/Marker Felt.ttf", 16);
		label->enableOutline(Color4B::BLACK, 2);
		label->setAnchorPoint(Vec2(0.5f, 0.5f));
		label->setColor(Color3B(255, 0, 0));
		label->setPosition(x, y);
		_MatrixIncidence.pushBack(label);
	}


	for (int i = 0; i < _MatrixIncidence.size(); i++)
	{
		this->addChild(_MatrixIncidence.at(i), 3);
	}
}

void Digraph::viewMenu1(Ref *sender)
{
	_menu1->setOpacity(255.0f);
	_menu1->setScale(1.0f);
	_menu2->setOpacity(0.0f);
	_menu2->setScale(0.0f);
	_menu3->setOpacity(0.0f);
	_menu3->setScale(0.0f);
	_menu4->setOpacity(0.0f);
	_menu4->setScale(0.0f);

	for (int i = 0; i < _MatrixAdjacency.size(); i++)
		this->removeChild(_MatrixAdjacency.at(i));
	_MatrixAdjacency.clear();

	for (int i = 0; i < _MatrixIncidence.size(); i++)
		this->removeChild(_MatrixIncidence.at(i));
	_MatrixIncidence.clear();

	for (int i = 0; i < _nodes.size(); i++)
		_nodes.at(i)->setOpacity(255.0f);

	for (int i = 0; i < _edges.size(); i++)
		_edges.at(i)->setOpacity(255.0f);

	for (int i = 0; i < _MatrixTrajectory.size();i++)
		this->removeChild(_MatrixTrajectory.at(i));
}

void Digraph::viewMenu2(Ref *sender)
{
	_menu1->setOpacity(0.0f);
	_menu1->setScale(0.0f);
	_menu2->setOpacity(255.0f);
	_menu2->setScale(1.0f);

	for (int i = 0; i < _nodes.size(); i++)
		_nodes.at(i)->setOpacity(127.0f);

	for (int i = 0; i < _edges.size(); i++)
		_edges.at(i)->setOpacity(127.0f);
}

void Digraph::viewMenu3(Ref *sender)
{
	_menu1->setOpacity(0.0f);
	_menu1->setScale(0.0f);
	_menu3->setOpacity(255.0f);
	_menu3->setScale(1.0f);

	for (int i = 0; i < _nodes.size(); i++)
		_nodes.at(i)->setOpacity(127.0f);

	for (int i = 0; i < _edges.size(); i++)
		_edges.at(i)->setOpacity(127.0f);
}

void Digraph::viewMenu4(Ref *sender)
{
	_menu1->setOpacity(0.0f);
	_menu1->setScale(0.0f);
	_menu4->setOpacity(255.0f);
	_menu4->setScale(1.0f);

	for (int i = 0; i < _nodes.size(); i++)
		_nodes.at(i)->setOpacity(127.0f);

	for (int i = 0; i < _edges.size(); i++)
		_edges.at(i)->setOpacity(127.0f);
}