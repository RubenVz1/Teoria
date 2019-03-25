#include "GraphScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* Graph::createScene()
{
	return Graph::create();
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

	auto item_2 = MenuItemLabel::create(labelNewRelation, CC_CALLBACK_1(Graph::addNodes, this));
	item_2->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_2->setPosition(Vec2(x, y));

	menus.pushBack(item_2);

	x = visibleSize.width / 2;
	y = 5 * visibleSize.height / 8;

	auto labelDeleteNode = Label::createWithTTF("Borrar Nodo", "fonts/Marker Felt.ttf", 24);
	labelDeleteNode->enableOutline(Color4B::BLACK, 1);

	auto item_3 = MenuItemLabel::create(labelDeleteNode, CC_CALLBACK_1(Graph::addNodes, this));
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

	auto item_5 = MenuItemLabel::create(labelViewMatrix, CC_CALLBACK_1(Graph::addNodes, this));
	item_5->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_5->setPosition(Vec2(x, y));

	menus.pushBack(item_5);

	x = visibleSize.width / 2;
	y = 2 * visibleSize.height / 8;

	auto labelReturn = Label::createWithTTF("Regresar", "fonts/Marker Felt.ttf", 24);
	labelReturn->enableOutline(Color4B::BLACK, 1);

	auto item_6 = MenuItemLabel::create(labelReturn, CC_CALLBACK_1(Graph::addNodes, this));
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

	//menus.pushBack(item_7);  bug en listener

	x = 3 * visibleSize.width / 4;
	y = 2 * visibleSize.height / 8;

	auto labelZoomOut = Label::createWithTTF("Zoom Out", "fonts/Marker Felt.ttf", 24);
	labelZoomOut->enableOutline(Color4B::BLACK, 1);

	auto item_8 = MenuItemLabel::create(labelZoomOut, CC_CALLBACK_1(Graph::zoomOut, this));
	item_8->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_8->setPosition(Vec2(x, y));

	//menus.pushBack(item_8);  bug en listener

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

	_menu = Menu::createWithArray(menus);
	_menu->setPosition(Vec2::ZERO);
	_menu->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);

	this->addChild(_menu, 2);
}

bool Graph::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	this->getPhysicsWorld()->setGravity(Vec2::ZERO);

	auto visibleSize = Director::getInstance()->getVisibleSize();

	float x = visibleSize.width / 2;
	float y = visibleSize.height / 2;
	float z = this->getDefaultCamera()->getPositionZ();

	_camera = Camera::createPerspective(60, visibleSize.width / visibleSize.height, 100, 1100);
	_camera->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	_camera->setPosition3D(Vec3(x, y, z));
	_camera->setCameraFlag(CameraFlag::USER1);

	this->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);

	this->addChild(_camera, 3);

	_deviation = Vec2::Vec2(0,0);

	x = visibleSize.width / 2;
	y = visibleSize.height / 2;

	auto background = Sprite::create("images/unam_logo.jpg");
	background->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	background->setPosition(x, y);
	background->setScale(0.6f);
	background->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);

	this->addChild(background, 0);

	addMenus();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch*touch, Event*event) {return true;};
	listener->onTouchMoved = CC_CALLBACK_2(Graph::moveNode, this);
	listener->onTouchEnded = [=](Touch*touch, Event*event) {};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void Graph::moveNode(Touch* touch, Event* event)
{
	auto touchPosition = touch->getLocation();

	touchPosition.x += _deviation.x;
	touchPosition.y += _deviation.y;

	int index = -1;

	for (int i = 0; i != _nodes.size() ;i++)
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
	if (index != -1)
	{
		_nodes.at(index)->setPosition(touchPosition);
		_nodes.at(index)->setScale(0.4f);  // sustituir por segunda funcion
	}
	index_selected = index;
}

void Graph::addNodes(Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	float x = (visibleSize.width / 2) + 60;
	float y = (visibleSize.height / 2) + 60;

	auto node = Sprite::create("images/node_1.png");
	node->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	node->setPosition(x, y);
	node->setScale(0.3f);
	node->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);

	auto r = random(0, 255);
	auto g = random(0, 255);
	auto b = random(0, 255);

	node->setColor(Color3B(r, g, b));

	auto radiu = node->getContentSize().height / 2;
	auto node_body = PhysicsBody::createCircle(radiu, PHYSICSBODY_MATERIAL_DEFAULT, Vec2(x, y));
	node->setPhysicsBody(node_body);

	_nodes.pushBack(node);
	float index = _nodes.size() - 1;
	this->addChild(_nodes.at(index), 1);
}

void Graph::zoomIn(Ref* pSender)
{
	auto position3Ds = _camera->getPosition3D();
	position3Ds.z -= 10.0f;
	_camera->setPosition3D(position3Ds);

	position3Ds = _menu->getPosition3D();
	position3Ds.z -= 10.0f;
	_menu->setPosition3D(position3Ds);
}

void Graph::zoomOut(Ref* pSender)
{
	auto position3Ds = _camera->getPosition3D();
	position3Ds.z += 10.0f;
	_camera->setPosition3D(position3Ds);

	position3Ds = _menu->getPosition3D();
	position3Ds.z += 10.0f;
	_menu->setPosition3D(position3Ds);
}

void Graph::cameraRight(Ref* pSender)
{
	if (_deviation.x >= 530)
	{
		return;
	}
	auto position2Ds = _menu->getPosition();
	position2Ds.x += 10.0f;
	_menu->setPosition(position2Ds);

	auto position3Ds = _camera->getPosition3D();
	position3Ds.x += 10.0f;
	_camera->setPosition3D(position3Ds);

	_deviation.x += 10.0f;
}

void Graph::cameraLeft(Ref* pSender)
{
	if (_deviation.x <= -530)
	{
		return;
	}

	auto position2Ds = _menu->getPosition();
	position2Ds.x -= 10.0f;
	_menu->setPosition(position2Ds);

	auto position3Ds = _camera->getPosition3D();
	position3Ds.x -= 10.0f;
	_camera->setPosition3D(position3Ds);

	_deviation.x -= 10.0f;
}

void Graph::cameraUp(Ref* pSender)
{
	if (_deviation.y >= 530)
	{
		return;
	}

	auto position2Ds = _menu->getPosition();
	position2Ds.y += 10.0f;
	_menu->setPosition(position2Ds);

	auto position3Ds = _camera->getPosition3D();
	position3Ds.y += 10.0f;
	_camera->setPosition3D(position3Ds);

	_deviation.y += 10.0f;
}

void Graph::cameraDown(Ref* pSender)
{
	if (_deviation.y <= -530)
	{
		return;
	}

	auto position2Ds = _menu->getPosition();
	position2Ds.y -= 10.0f;
	_menu->setPosition(position2Ds);

	auto position3Ds = _camera->getPosition3D();
	position3Ds.y -= 10.0f;
	_camera->setPosition3D(position3Ds);

	_deviation.y -= 10.0f;
}