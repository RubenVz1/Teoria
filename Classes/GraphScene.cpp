#include "GraphScene.h"
#include "MenusScene.h"
#include "SimpleAudioEngine.h"
#include <cmath>

USING_NS_CC;

Scene* Graph::createScene()
{

	//******************* prueba *******************//
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Graph::create();
	scene->addChild(layer);
	return scene;
	//******************* prueba *******************//

	//return Graph::create(); **** Agregar cuando la prueba termine ****
}

void Graph::addMenus()
{
	cocos2d::Vector<cocos2d::MenuItem*> menus;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	float x = visibleSize.width / 2;
	float y = 7 * visibleSize.height / 8;

	auto labelNewNode = Label::createWithTTF("Nuevo Nodo", "fonts/Marker Felt.ttf", 24);
	labelNewNode->enableOutline(Color4B::BLACK, 1);

	auto item_1 = MenuItemLabel::create(labelNewNode, CC_CALLBACK_1(Graph::addNodes, this));
	item_1->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_1->setPosition(Vec2(x, y));

	menus.pushBack(item_1);

	x = visibleSize.width / 2;
	y = 6 * visibleSize.height / 8;

	auto labelNewRelation = Label::createWithTTF("Nueva Relacion", "fonts/Marker Felt.ttf", 24);
	labelNewRelation->enableOutline(Color4B::BLACK, 1);

	auto item_2 = MenuItemLabel::create(labelNewRelation, CC_CALLBACK_1(Graph::newRelation, this));
	item_2->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_2->setPosition(Vec2(x, y));

	menus.pushBack(item_2);

	x = visibleSize.width / 2;
	y = 5 * visibleSize.height / 8;

	auto labelDeleteNode = Label::createWithTTF("Borrar Nodo", "fonts/Marker Felt.ttf", 24);
	labelDeleteNode->enableOutline(Color4B::BLACK, 1);

	auto item_3 = MenuItemLabel::create(labelDeleteNode, CC_CALLBACK_1(Graph::deleteNode, this));
	item_3->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_3->setPosition(Vec2(x, y));

	menus.pushBack(item_3);

	x = visibleSize.width / 2;
	y = 4 * visibleSize.height / 8;

	auto labelDeleteRelation = Label::createWithTTF("Borrar Relacion", "fonts/Marker Felt.ttf", 24);
	labelDeleteRelation->enableOutline(Color4B::BLACK, 1);

	auto item_4 = MenuItemLabel::create(labelDeleteRelation, CC_CALLBACK_1(Graph::addNodes, this));
	item_4->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_4->setPosition(Vec2(x, y));

	menus.pushBack(item_4);

	x = visibleSize.width / 2;
	y = 3 * visibleSize.height / 8;

	auto labelViewMatrix = Label::createWithTTF("Matriz", "fonts/Marker Felt.ttf", 24);
	labelViewMatrix->enableOutline(Color4B::BLACK, 1);

	auto item_5 = MenuItemLabel::create(labelViewMatrix, CC_CALLBACK_1(Graph::viewMatrix, this));
	item_5->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_5->setPosition(Vec2(x, y));

	menus.pushBack(item_5);

	x = visibleSize.width / 2;
	y = 2 * visibleSize.height / 8;

	auto labelReturn = Label::createWithTTF("Regresar", "fonts/Marker Felt.ttf", 24);
	labelReturn->enableOutline(Color4B::BLACK, 1);

	auto item_6 = MenuItemLabel::create(labelReturn, CC_CALLBACK_1(Graph::goToMenus, this));
	item_6->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_6->setPosition(Vec2(x, y));

	menus.pushBack(item_6);

	x = visibleSize.width / 4;
	y = 2 * visibleSize.height / 8;

	auto labelZoomIn = Label::createWithTTF("Zoom in", "fonts/Marker Felt.ttf", 24);
	labelZoomIn->enableOutline(Color4B::BLACK, 1);

	auto item_7 = MenuItemLabel::create(labelZoomIn, CC_CALLBACK_1(Graph::zoomIn, this));
	item_7->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_7->setPosition(Vec2(x, y));

	//menus.pushBack(item_7);

	x = 3 * visibleSize.width / 4;
	y = 2 * visibleSize.height / 8;

	auto labelZoomOut = Label::createWithTTF("Zoom Out", "fonts/Marker Felt.ttf", 24);
	labelZoomOut->enableOutline(Color4B::BLACK, 1);

	auto item_8 = MenuItemLabel::create(labelZoomOut, CC_CALLBACK_1(Graph::zoomOut, this));
	item_8->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_8->setPosition(Vec2(x, y));

	//menus.pushBack(item_8);

	x = visibleSize.width / 2;
	y = 60 + visibleSize.height / 2;

	auto arrowDown = MenuItemImage::create("images/normal.png", "images/selected.png", CC_CALLBACK_1(Graph::cameraDown, this));
	arrowDown->setAnchorPoint(Vec2(0.5f, 0.5f));
	arrowDown->setPosition(Vec2(x, y));
	arrowDown->setScale(0.1f);

	menus.pushBack(arrowDown);

	x = visibleSize.width / 2;
	y = 120 + visibleSize.height / 2;

	auto arrowUp = MenuItemImage::create("images/normal.png", "images/selected.png", CC_CALLBACK_1(Graph::cameraUp, this));
	arrowUp->setAnchorPoint(Vec2(0.5f, 0.5f));
	arrowUp->setPosition(Vec2(x, y));
	arrowUp->setScale(0.1f);
	arrowUp->setRotation(180);

	menus.pushBack(arrowUp);

	x = 120 + visibleSize.width / 2;
	y = visibleSize.height / 2;

	auto arrowRight = MenuItemImage::create("images/normal.png", "images/selected.png", CC_CALLBACK_1(Graph::cameraRight, this));
	arrowRight->setAnchorPoint(Vec2(0.5f, 0.5f));
	arrowRight->setPosition(Vec2(x, y));
	arrowRight->setScale(0.1f);
	arrowRight->setRotation(270);

	menus.pushBack(arrowRight);

	x = visibleSize.width / 2 - 90;
	y = visibleSize.height / 2;

	auto arrowLeft = MenuItemImage::create("images/normal.png", "images/selected.png", CC_CALLBACK_1(Graph::cameraLeft, this));
	arrowLeft->setAnchorPoint(Vec2(0.5f, 0.5f));
	arrowLeft->setPosition(Vec2(x, y));
	arrowLeft->setScale(0.1f);
	arrowLeft->setRotation(90);

	menus.pushBack(arrowLeft);

	_menu_1 = Menu::createWithArray(menus);
	_menu_1->setPosition(Vec2::ZERO);
	_menu_1->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);

	this->addChild(_menu_1, 3);

	/*******************************************************************************************************/
	cocos2d::Vector<cocos2d::MenuItem*> menus_2;

	x = 3 * visibleSize.width / 4;
	y = 6 * visibleSize.height / 8;

	auto labelBack = Label::createWithTTF("Regresar", "fonts/Marker Felt.ttf", 24);
	labelBack->enableOutline(Color4B::BLACK, 1);

	auto item_12 = MenuItemLabel::create(labelBack, CC_CALLBACK_1(Graph::viewMatrix, this));
	item_12->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_12->setPosition(Vec2(x, y));

	menus_2.pushBack(item_12);

	_menu_2 = Menu::createWithArray(menus_2);
	_menu_2->setPosition(Vec2::ZERO);
	_menu_2->setOpacity(0.0f);
	_menu_2->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);

	this->addChild(_menu_2, 3);
}

bool Graph::init()
{
	//if (!Scene::initWithPhysics()) **** Agregar cuando la prueba termine ****
	if(!Scene::init())
	{
		return false;
	}

	//this->getPhysicsWorld()->setGravity(Vec2::ZERO);  **** Agregar cuando la prueba termine ****

	auto visibleSize = Director::getInstance()->getVisibleSize();

	float x = visibleSize.width / 2;
	float y = visibleSize.height / 2;
	float z = this->getDefaultCamera()->getPositionZ();

	_camera = Camera::createPerspective(60, visibleSize.width / visibleSize.height, 100, 1100);
	_camera->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	_camera->setPosition3D(Vec3(x, y, z));
	_camera->setCameraFlag(CameraFlag::USER1);

	this->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);

	this->addChild(_camera, 4);

	_deviation = Vec2::Vec2(0,0);
	index_selected = -1;

	x = visibleSize.width / 2;
	y = visibleSize.height / 2;

	auto background = Sprite::create("images/unam_logo.jpg");
	background->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	background->setPosition(x, y);
	background->setScale(0.6f);
	background->setOpacity(80);
	background->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);

	this->addChild(background, 0);

	addMenus();

	relation_selected = false;

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Graph::clickNode, this);
	listener->onTouchMoved = CC_CALLBACK_2(Graph::moveNode, this);
	listener->onTouchEnded = [=](Touch*touch, Event*event) {};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void Graph::newRelation(Ref* sender)
{
	if (index_selected != -1)
	{
		relation_selected = true;
	}
}

bool Graph::clickNode(Touch* touch, Event* event)
{
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
				_nodes.at(i)->setScale(0.3f); //sustituir por primera funcion
			}
		}
	}
	if (index == -1 || index_selected == -1)
	{
		relation_selected = false;
	}
	if (relation_selected)
	{
		createRelation(index_selected, index);
		relation_selected = false;
		return true;
	}
	if (index != -1)
	{
		_nodes.at(index)->setScale(0.4f);  // sustituir por segunda funcion
	}

	index_selected = index;

	return true;
}

float Graph::distance(int indexNode1, int indexNode2)
{
	auto position1 = _nodes.at(indexNode1)->getPosition();
	auto position2 = _nodes.at(indexNode2)->getPosition();

	auto x = position1.x - position2.x;
	auto y = position1.y - position2.y;

	auto distance = sqrt(pow(x, 2) + pow(y, 2));

	return distance;
}

float Graph::angle(int indexNode1, int indexNode2)
{
	auto position1 = _nodes.at(indexNode1)->getPosition();
	auto position2 = _nodes.at(indexNode2)->getPosition();
	auto delta_position = position1;
	
	position1.x -= delta_position.x;
	position1.y -= delta_position.y;
	position2.x -= delta_position.x;
	position2.y -= delta_position.y;
	
	auto angle = atan(position2.y / position2.x);
	angle = angle*(360 / (M_PI * 2));

	auto condition = (position2.x < 0 && position2.y > 0) || (position2.x < 0 && position2.y < 0);
	if (condition)
		angle = 180 + angle;
	return angle;
}

void Graph::createRelation(int indexNode1, int indexNode2)
{
	auto position1 = _nodes.at(indexNode1)->getPosition();
	auto relation = Sprite::create("images/arrow.png");
	relation->setAnchorPoint(Vec2(0.0f, 0.5f));
	relation->setPosition(position1);
	float aux = distance(indexNode1, indexNode2) / relation->getBoundingBox().size.width;
	float angleNodes = -1*angle(indexNode1, indexNode2);
	relation->setRotation(angleNodes);
	relation->setScaleX(aux);
	relation->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);

	auto rect = relation->getContentSize();
	auto positionNode = Vec2::ZERO;

	auto r = random(0, 255);
	auto g = random(0, 255);
	auto b = random(0, 255);

	relation->setColor(Color3B(r, g, b));
	this->addChild(relation, 1);
}

void Graph::moveNode(Touch* touch, Event* event)
{
	if (index_selected != -1)
	{
		auto touchPosition = touch->getLocation();

		touchPosition.x += _deviation.x;
		touchPosition.y += _deviation.y;

		_nodes.at(index_selected)->setPosition(touchPosition);
	}
}

void Graph::addNodes(Ref* pSender)
{
	auto position = _camera->getPosition();

	auto node = Sprite::create("images/node_1.png");
	node->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	node->setPosition(position);
	node->setScale(0.3f);
	node->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);

	auto r = random(0, 255);
	auto g = random(0, 255);
	auto b = random(0, 255);

	node->setColor(Color3B(r, g, b));

	auto radiu = node->getContentSize().height / 2;
	auto positionNode = Vec2::ZERO; //issue
	auto node_body = PhysicsBody::createCircle(radiu, PHYSICSBODY_MATERIAL_DEFAULT, positionNode);
	node->setPhysicsBody(node_body);
	

	_nodes.pushBack(node);
	float index = _nodes.size() - 1;
	this->addChild(_nodes.at(index), 2);
}

void Graph::zoomIn(Ref* pSender)
{
	auto position3Ds = _camera->getPosition3D();
	position3Ds.z -= 10.0f;
	_camera->setPosition3D(position3Ds);

	position3Ds = _menu_1->getPosition3D();
	position3Ds.z -= 10.0f;
	_menu_1->setPosition3D(position3Ds);
}

void Graph::zoomOut(Ref* pSender)
{
	auto position3Ds = _camera->getPosition3D();
	position3Ds.z += 10.0f;
	_camera->setPosition3D(position3Ds);

	position3Ds = _menu_1->getPosition3D();
	position3Ds.z += 10.0f;
	_menu_1->setPosition3D(position3Ds);
}

void Graph::cameraRight(Ref* pSender)
{
	if (_deviation.x >= 530)
	{
		return;
	}
	auto position2Ds = _menu_1->getPosition();
	position2Ds.x += 10.0f;
	_menu_1->setPosition(position2Ds);
	_menu_2->setPosition(position2Ds);

	auto position3Ds = _camera->getPosition3D();
	position3Ds.x += 10.0f;
	_camera->setPosition3D(position3Ds);

	_deviation.x += 10.0f;

	for (int i = 0 ; i < _nodes.size() ; i++)
	{
		auto positionNode = _nodes.at(i)->getPhysicsBody()->getPositionOffset();
		positionNode.x -= 10.0f;
		_nodes.at(i)->getPhysicsBody()->setPositionOffset(positionNode);
	}
}

void Graph::cameraLeft(Ref* pSender)
{
	if (_deviation.x <= -530)
	{
		return;
	}

	auto position2Ds = _menu_1->getPosition();
	position2Ds.x -= 10.0f;
	_menu_1->setPosition(position2Ds);
	_menu_2->setPosition(position2Ds);

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

void Graph::cameraUp(Ref* pSender)
{
	if (_deviation.y >= 530)
	{
		return;
	}

	auto position2Ds = _menu_1->getPosition();
	position2Ds.y += 10.0f;
	_menu_1->setPosition(position2Ds);
	_menu_2->setPosition(position2Ds);

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

void Graph::cameraDown(Ref* pSender)
{
	if (_deviation.y <= -530)
	{
		return;
	}

	auto position2Ds = _menu_1->getPosition();
	position2Ds.y -= 10.0f;
	_menu_1->setPosition(position2Ds);
	_menu_2->setPosition(position2Ds);

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

void Graph::goToMenus(Ref *sender)
{
	auto scene = Menus::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
}

void Graph::deleteNode(Ref *sender)
{
	if (index_selected != -1)
	{
		this->removeChild(_nodes.at(index_selected));
	}
	cocos2d::log("index: %d", index_selected);
	index_selected = -1;
}

void Graph::viewMatrix(Ref *sender)
{
	auto condition = (_menu_1->getOpacity() == 0.0f);
	if (condition)
	{
		_menu_1->setOpacity(255.0f);
		_menu_2->setOpacity(0.0f);
	}
	else
	{
		_menu_1->setOpacity(0.0f);
		_menu_2->setOpacity(255.0f);
	}
}