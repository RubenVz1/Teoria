#include "DigraphScene.h"
#include "SimpleAudioEngine.h"

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

	auto item_1 = MenuItemLabel::create(labelExit, CC_CALLBACK_1(Digraph::addNodes, this));
	item_1->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_1->setPosition(Vec2(x, y));

	auto menu = Menu::createWithItem(item_1);
	menu->setPosition(Vec2::ZERO);

	this->addChild(menu, 1);

	x = visibleSize.width / 2;
	y = 60 + visibleSize.height / 2;

	auto labelExit1 = Label::createWithTTF("ZoomIn", "fonts/Marker Felt.ttf", 24);
	labelExit1->enableOutline(Color4B::BLACK, 1);

	auto item_11 = MenuItemLabel::create(labelExit1, CC_CALLBACK_1(Digraph::zoomIn, this));
	item_11->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_11->setPosition(Vec2(x, y));

	auto menu1 = Menu::createWithItem(item_11);
	menu1->setPosition(Vec2::ZERO);

	this->addChild(menu1, 1);

	x = visibleSize.width / 2;
	y = 120 + visibleSize.height / 2;

	auto labelExit111 = Label::createWithTTF("ZoomOut", "fonts/Marker Felt.ttf", 24);
	labelExit111->enableOutline(Color4B::BLACK, 1);

	auto item_112 = MenuItemLabel::create(labelExit111, CC_CALLBACK_1(Digraph::zoomOut, this));
	item_112->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_112->setPosition(Vec2(x, y));

	auto menu122 = Menu::createWithItem(item_112);
	menu122->setPosition(Vec2::ZERO);

	this->addChild(menu122, 1);
	
	//////////  Espacio de pruebas  //////////
	//  Eliminar cuando se termine el menu  //
	
	return true;
}