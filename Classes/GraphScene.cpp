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
	cocos2d::log("hola");
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

	addMenus(); // Aqui se llamara a la funcion Menus

	//////////  Espacio de pruebas  //////////
	//  Eliminar cuando se termine el menu  //

	auto labelExit = Label::createWithTTF("Nuevo nodo", "fonts/Marker Felt.ttf", 24);
	labelExit->enableOutline(Color4B::BLACK, 1);

	auto item_1 = MenuItemLabel::create(labelExit, CC_CALLBACK_1(Graph::addNodes, this));
	item_1->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_1->setPosition(Vec2(x, y));

	auto menu = Menu::createWithItem(item_1);
	menu->setPosition(Vec2::ZERO);

	this->addChild(menu, 1);

	x = visibleSize.width / 2;
	y = 60 + visibleSize.height / 2;

	auto labelExit1 = Label::createWithTTF("ZoomIn", "fonts/Marker Felt.ttf", 24);
	labelExit1->enableOutline(Color4B::BLACK, 1);

	auto item_11 = MenuItemLabel::create(labelExit1, CC_CALLBACK_1(Graph::zoomIn, this));
	item_11->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_11->setPosition(Vec2(x, y));

	auto menu1 = Menu::createWithItem(item_11);
	menu1->setPosition(Vec2::ZERO);

	this->addChild(menu1, 1);

	x = visibleSize.width / 2;
	y = 120 + visibleSize.height / 2;

	auto labelExit111 = Label::createWithTTF("ZoomOut", "fonts/Marker Felt.ttf", 24);
	labelExit111->enableOutline(Color4B::BLACK, 1);

	auto item_112 = MenuItemLabel::create(labelExit111, CC_CALLBACK_1(Graph::zoomOut, this));
	item_112->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_112->setPosition(Vec2(x, y));

	auto menu122 = Menu::createWithItem(item_112);
	menu122->setPosition(Vec2::ZERO);

	this->addChild(menu122, 1);
	
	//////////  Espacio de pruebas  //////////
	//  Eliminar cuando se termine el menu  //
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch*touch, Event*event) {return true;};
	listener->onTouchMoved = CC_CALLBACK_2(Graph::moveNode, this);
	listener->onTouchEnded = [=](Touch*touch, Event*event) {};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	x = visibleSize.width / 2;
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