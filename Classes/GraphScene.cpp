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
	cocos2d::Vector<cocos2d::MenuItem*> _menus;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	float x = visibleSize.width / 2;
	float y = 7 * visibleSize.height / 8;

	auto labelNewNode = Label::createWithTTF("Nuevo Nodo", "fonts/Marker Felt.ttf", 24);
	labelNewNode->enableOutline(Color4B::BLACK, 1);

	auto item_1 = MenuItemLabel::create(labelNewNode, CC_CALLBACK_1(Graph::addNodes, this));
	item_1->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_1->setPosition(Vec2(x, y));

	_menus.pushBack(item_1);

	x = visibleSize.width / 2;
	y = 6 * visibleSize.height / 8;

	auto labelNewRelation = Label::createWithTTF("Nueva Relacion", "fonts/Marker Felt.ttf", 24);
	labelNewRelation->enableOutline(Color4B::BLACK, 1);

	auto item_2 = MenuItemLabel::create(labelNewRelation, CC_CALLBACK_1(Graph::addNodes, this));
	item_2->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_2->setPosition(Vec2(x, y));

	_menus.pushBack(item_2);

	x = visibleSize.width / 2;
	y = 5 * visibleSize.height / 8;

	auto labelDeleteNode = Label::createWithTTF("Borrar Nodo", "fonts/Marker Felt.ttf", 24);
	labelDeleteNode->enableOutline(Color4B::BLACK, 1);

	auto item_3 = MenuItemLabel::create(labelDeleteNode, CC_CALLBACK_1(Graph::addNodes, this));
	item_3->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_3->setPosition(Vec2(x, y));

	_menus.pushBack(item_3);

	x = visibleSize.width / 2;
	y = 4 * visibleSize.height / 8;

	auto labelDeleteRelation = Label::createWithTTF("Borrar Relacion", "fonts/Marker Felt.ttf", 24);
	labelDeleteRelation->enableOutline(Color4B::BLACK, 1);

	auto item_4 = MenuItemLabel::create(labelDeleteRelation, CC_CALLBACK_1(Graph::addNodes, this));
	item_4->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_4->setPosition(Vec2(x, y));

	_menus.pushBack(item_4);

	x = visibleSize.width / 2;
	y = 3 * visibleSize.height / 8;

	auto labelViewMatrix = Label::createWithTTF("Matriz", "fonts/Marker Felt.ttf", 24);
	labelViewMatrix->enableOutline(Color4B::BLACK, 1);

	auto item_5 = MenuItemLabel::create(labelViewMatrix, CC_CALLBACK_1(Graph::addNodes, this));
	item_5->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_5->setPosition(Vec2(x, y));

	_menus.pushBack(item_5);

	x = visibleSize.width / 2;
	y = 2 * visibleSize.height / 8;

	auto labelReturn = Label::createWithTTF("Regresar", "fonts/Marker Felt.ttf", 24);
	labelReturn->enableOutline(Color4B::BLACK, 1);

	auto item_6 = MenuItemLabel::create(labelReturn, CC_CALLBACK_1(Graph::addNodes, this));
	item_6->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_6->setPosition(Vec2(x, y));

	_menus.pushBack(item_6);

	x = visibleSize.width / 2;
	y = 60 + visibleSize.height / 2;

	auto arrowDown = MenuItemImage::create("images/normal.png", "images/selected.png", CC_CALLBACK_1(Graph::cameraDown, this));
	arrowDown->setAnchorPoint(Vec2(0.5f, 0.5f));
	arrowDown->setPosition(Vec2(x, y));
	arrowDown->setScale(0.1f);
	_menus.pushBack(arrowDown);

	x = visibleSize.width / 2;
	y = 120 + visibleSize.height / 2;

	auto arrowUp = MenuItemImage::create("images/normal.png", "images/selected.png", CC_CALLBACK_1(Graph::cameraUp, this));
	arrowUp->setAnchorPoint(Vec2(0.5f, 0.5f));
	arrowUp->setPosition(Vec2(x, y));
	arrowUp->setScale(0.1f);
	arrowUp->setRotation(180);
	_menus.pushBack(arrowUp);

	x = 120 + visibleSize.width / 2;
	y = visibleSize.height / 2;

	auto arrowRight = MenuItemImage::create("images/normal.png", "images/selected.png", CC_CALLBACK_1(Graph::cameraRight, this));
	arrowRight->setAnchorPoint(Vec2(0.5f, 0.5f));
	arrowRight->setPosition(Vec2(x, y));
	arrowRight->setScale(0.1f);
	arrowRight->setRotation(270);
	_menus.pushBack(arrowRight);

	x = visibleSize.width / 2 - 90;
	y = visibleSize.height / 2;

	auto arrowLeft = MenuItemImage::create("images/normal.png", "images/selected.png", CC_CALLBACK_1(Graph::cameraLeft, this));
	arrowLeft->setAnchorPoint(Vec2(0.5f, 0.5f));
	arrowLeft->setPosition(Vec2(x, y));
	arrowLeft->setScale(0.1f);
	arrowLeft->setRotation(90);
	_menus.pushBack(arrowLeft);

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

	x = 7 * visibleSize.width / 8;
	y = visibleSize.height / 2;

	auto slider = ui::Slider::create();
	slider->loadBarTexture("Slider_Back.png");
	slider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
	slider->loadProgressBarTexture("Slider_PressBar.png");
	slider->setPosition(Vec2(x, y));
	slider->setRotation(270);

	slider->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		case ui::Widget::TouchEventType::MOVED:
			cocos2d::log("slider moved2");
			break;
		default:
			break;
		}
	});

	this->addChild(slider);

	return true;
}

void Graph::moveNode(Touch* touch, Event* event)
{
	auto touchPosition = touch->getLocation();

	int index = -1;

	for (int i = 0; i != _nodes.size() ;i++)
	{
		if (_nodes.at(i)->getBoundingBox().containsPoint(touchPosition))
		{
			index = i;
		}
	}
	if (index != -1)
	{
		_nodes.at(index)->setPosition(touchPosition);
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