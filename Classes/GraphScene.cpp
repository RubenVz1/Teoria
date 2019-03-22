#include "GraphScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Graph::createScene()
{
	return Graph::create();
}

void Graph::addMenus()
{
	cocos2d::Vector<cocos2d::MenuItem*> _menus;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	float x = visibleSize.width / 2;
	float y = 7 * visibleSize.height / 8;

	auto labelNewNodo = Label::createWithTTF("Nuevo Nodo", "fonts/Marker Felt.ttf", 24);
	labelNewNodo->enableOutline(Color4B::BLACK, 1);

	auto item = MenuItemLabel::create(labelNewNodo, CC_CALLBACK_1(Graph::addNodes, this));
	item->setAnchorPoint(Vec2(0.5f, 0.5f));
	item->setPosition(Vec2(x, y));

	_menus.pushBack(item);

	x = visibleSize.width / 2;
	y = 20 + visibleSize.height / 2;

	auto labelNewRelacion = Label::createWithTTF("Nueva Relacion", "fonts/Marker Felt.ttf", 24);
	labelNewRelacion->enableOutline(Color4B::BLACK, 1);

	auto item_1 = MenuItemLabel::create(labelNewRelacion, CC_CALLBACK_1(Graph::addNodes, this));
	item_1->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_1->setPosition(Vec2(x, y));

	_menus.pushBack(item_1);

	x = visibleSize.width / 2;
	y = 40 + visibleSize.height / 2;

	auto labelDeletNodo = Label::createWithTTF("Borrar Nodo", "fonts/Marker Felt.ttf", 24);
	labelDeletNodo->enableOutline(Color4B::BLACK, 1);

	auto item_2 = MenuItemLabel::create(labelDeletNodo, CC_CALLBACK_1(Graph::addNodes, this));
	item_2->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_2->setPosition(Vec2(x, y));

	_menus.pushBack(item_2);


	x = visibleSize.width / 2;
	y = 90 + visibleSize.height / 2;

	auto labelDeletRelacion = Label::createWithTTF("Borrar Relacion", "fonts/Marker Felt.ttf", 24);
	labelDeletRelacion->enableOutline(Color4B::BLACK, 1);

	auto item_3 = MenuItemLabel::create(labelDeletRelacion, CC_CALLBACK_1(Graph::addNodes, this));
	item_3->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_3->setPosition(Vec2(x, y));

	_menus.pushBack(item_3);


	x = visibleSize.width / 2;
	y = 125 + visibleSize.height / 2;

	auto labelViweMatriz = Label::createWithTTF("Matriz", "fonts/Marker Felt.ttf", 24);
	labelViweMatriz->enableOutline(Color4B::BLACK, 1);

	auto item_4 = MenuItemLabel::create(labelViweMatriz, CC_CALLBACK_1(Graph::addNodes, this));
	item_4->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_4->setPosition(Vec2(x, y));

	_menus.pushBack(item_4);

	x = visibleSize.width / 2;
	y = 150 + visibleSize.height / 2;

	auto labelReturn = Label::createWithTTF("Regresar", "fonts/Marker Felt.ttf", 24);
	labelReturn->enableOutline(Color4B::BLACK, 1);

	auto item_5 = MenuItemLabel::create(labelReturn, CC_CALLBACK_1(Graph::addNodes, this));
	item_5->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_5->setPosition(Vec2(x, y));

	_menus.pushBack(item_5);


	//imagenes

	x = visibleSize.width / 2;
	y = visibleSize.height / 2;

	auto flechaDown = MenuItemImage::create("images/normal.png", "images/selected.png", CC_CALLBACK_1(Graph::cameraDown, this));
	flechaDown->setAnchorPoint(Vec2(0.5f, 0.5f));
	flechaDown->setPosition(Vec2(x, y));
	flechaDown->setScale(0.2f);
	_menus.pushBack(flechaDown);


	x = visibleSize.width / 2;
	y = 120+visibleSize.height / 2;

	auto flechaUp = MenuItemImage::create("images/normal.png", "images/selected.png", CC_CALLBACK_1(Graph::cameraUp, this));
	flechaUp->setAnchorPoint(Vec2(0.5f, 0.5f));
	flechaUp->setPosition(Vec2(x, y));
	flechaUp->setScale(0.2f);
	flechaUp->setRotation(180);
	_menus.pushBack(flechaUp);

	x = 120+visibleSize.width / 2;
	y = visibleSize.height / 2;

	auto flechaRight = MenuItemImage::create("images/normal.png", "images/selected.png", CC_CALLBACK_1(Graph::cameraRight, this));
	flechaRight->setAnchorPoint(Vec2(0.5f, 0.5f));
	flechaRight->setPosition(Vec2(x, y));
	flechaRight->setScale(0.2f);
	flechaRight->setRotation(270);
	_menus.pushBack(flechaRight);

	x = visibleSize.width / 2 -90;
	y = visibleSize.height / 2;

	auto flechaLeft = MenuItemImage::create("images/normal.png", "images/selected.png", CC_CALLBACK_1(Graph::cameraLeft, this));
	flechaLeft->setAnchorPoint(Vec2(0.5f, 0.5f));
	flechaLeft->setPosition(Vec2(x, y));
	flechaLeft->setScale(0.2f);
	flechaLeft->setRotation(90);
	_menus.pushBack(flechaLeft);

	auto menu = Menu::createWithArray(_menus);
	menu->setPosition(Vec2::ZERO);

	this->addChild(menu, 1);
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

	auto background = Sprite::create("images/unam_logo.jpg");
	background->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	background->setPosition(x, y);
	background->setScale(0.6f);

	this->addChild(background, 0);

	x = visibleSize.width / 2;
	y = visibleSize.height / 2;
	float z = this->getDefaultCamera()->getPositionZ();

	this->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);

	_camera = Camera::createPerspective(60, visibleSize.width / visibleSize.height, 100, 1100);
	_camera->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	_camera->setPosition3D(Vec3(x, y, z));
	_camera->setCameraFlag(CameraFlag::USER1);

	this->addChild(_camera, 3);

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
	auto posicionToque = touch->getLocation();

	for (int i = 0; i != _nodes.size() - 1;i++)
	{
		if (_nodes.at(i)->getBoundingBox().containsPoint(posicionToque))
		{
			_nodes.at(i)->setPosition(posicionToque);
		}
	}
}

void Graph::addNodes(Ref* pSender)
{
	this->setCameraMask(static_cast<unsigned short> (CameraFlag::DEFAULT), true);

	auto visibleSize = Director::getInstance()->getVisibleSize();

	float x = (visibleSize.width / 2) + 60;
	float y = (visibleSize.height / 2) + 60;

	auto node = Sprite::create("images/nodo.png");
	node->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	node->setPosition(x, y);
	node->setScale(2.0f);

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

	this->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);
}

void Graph::zoomIn(Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float x = visibleSize.width / 2;
	float y = visibleSize.height / 2;
	float z = _camera->getPositionZ() + 10.0f;
	_camera->setPosition3D(Vec3(x, y, z));
}

void Graph::zoomOut(Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float x = visibleSize.width / 2;
	float y = visibleSize.height / 2;
	float z = _camera->getPositionZ() - 10.0f;
	_camera->setPosition3D(Vec3(x, y, z));
}

void Graph::cameraRight(Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float x = _camera->getPositionX() + 10.0f;
	float y = _camera->getPositionY();
	float z = _camera->getPositionZ();
	_camera->setPosition3D(Vec3(x, y, z));
}

void Graph::cameraLeft(Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float x = _camera->getPositionX() - 10.0f;
	float y = _camera->getPositionY();
	float z = _camera->getPositionZ();
	_camera->setPosition3D(Vec3(x, y, z));
}

void Graph::cameraUp(Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float x = _camera->getPositionX();
	float y = _camera->getPositionY() + 10.0f;
	float z = _camera->getPositionZ();
	_camera->setPosition3D(Vec3(x, y, z));
}

void Graph::cameraDown(Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float x = _camera->getPositionX();
	float y = _camera->getPositionY() - 10.0f ;
	float z = _camera->getPositionZ();
	_camera->setPosition3D(Vec3(x, y, z));
}