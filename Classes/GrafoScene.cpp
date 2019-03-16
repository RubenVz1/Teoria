#include "GrafoScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Grafos::createScene()
{
	return Grafos::create();
}

void Grafos::addMenus()
{
	cocos2d::log("hola");
}

bool Grafos::init()
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

	auto item_1 = MenuItemLabel::create(labelExit, CC_CALLBACK_1(Grafos::addNodes, this));
	item_1->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_1->setPosition(Vec2(x, y));

	auto menu = Menu::createWithItem(item_1);
	menu->setPosition(Vec2::ZERO);

	this->addChild(menu, 1);

	x = visibleSize.width / 2;
	y = 60 + visibleSize.height / 2;

	auto labelExit1 = Label::createWithTTF("ZoomIn", "fonts/Marker Felt.ttf", 24);
	labelExit1->enableOutline(Color4B::BLACK, 1);

	auto item_11 = MenuItemLabel::create(labelExit1, CC_CALLBACK_1(Grafos::zoomIn, this));
	item_11->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_11->setPosition(Vec2(x, y));

	auto menu1 = Menu::createWithItem(item_11);
	menu1->setPosition(Vec2::ZERO);

	this->addChild(menu1, 1);

	x = visibleSize.width / 2;
	y = 120 + visibleSize.height / 2;

	auto labelExit111 = Label::createWithTTF("ZoomOut", "fonts/Marker Felt.ttf", 24);
	labelExit111->enableOutline(Color4B::BLACK, 1);

	auto item_112 = MenuItemLabel::create(labelExit111, CC_CALLBACK_1(Grafos::zoomOut, this));
	item_112->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_112->setPosition(Vec2(x, y));

	auto menu122 = Menu::createWithItem(item_112);
	menu122->setPosition(Vec2::ZERO);

	this->addChild(menu122, 1);
	
	//////////  Espacio de pruebas  //////////
	//  Eliminar cuando se termine el menu  //
	
	return true;
}

void Grafos::addNodes(Ref* pSender)
{
	this->setCameraMask(static_cast<unsigned short> (CameraFlag::DEFAULT), true);

	auto visibleSize = Director::getInstance()->getVisibleSize();

	float x = (visibleSize.width / 2) + 60;
	float y = (visibleSize.height / 2) + 60;

	auto nodo = Sprite::create("images/nodo.png");
	nodo->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	nodo->setPosition(x, y);
	nodo->setScale(2.0f);

	auto r = random(0, 255);
	auto g = random(0, 255);
	auto b = random(0, 255);

	nodo->setColor(Color3B(r, g, b));

	auto radiu = nodo->getContentSize().height / 2;

	auto nodo_body = PhysicsBody::createCircle(radiu, PHYSICSBODY_MATERIAL_DEFAULT, Vec2(x, y));

	nodo->setPhysicsBody(nodo_body);

	this->addChild(nodo, 1);

	this->setCameraMask(static_cast<unsigned short> (CameraFlag::USER1), true);
}

void Grafos::zoomIn(Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float x = visibleSize.width / 2;
	float y = visibleSize.height / 2;
	float z = _camera->getPositionZ() + 10.0f;
	_camera->setPosition3D(Vec3(x, y, z));
}

void Grafos::zoomOut(Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float x = visibleSize.width / 2;
	float y = visibleSize.height / 2;
	float z = _camera->getPositionZ() - 10.0f;
	_camera->setPosition3D(Vec3(x, y, z));
}

void Grafos::cameraRight(Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float x = _camera->getPositionX() + 10.0f;
	float y = _camera->getPositionY();
	float z = _camera->getPositionZ();
	_camera->setPosition3D(Vec3(x, y, z));
}

void Grafos::cameraLeft(Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float x = _camera->getPositionX() - 10.0f;
	float y = _camera->getPositionY();
	float z = _camera->getPositionZ();
	_camera->setPosition3D(Vec3(x, y, z));
}

void Grafos::cameraUp(Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float x = _camera->getPositionX();
	float y = _camera->getPositionY() + 10.0f;
	float z = _camera->getPositionZ();
	_camera->setPosition3D(Vec3(x, y, z));
}

void Grafos::cameraDown(Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float x = _camera->getPositionX();
	float y = _camera->getPositionY() - 10.0f ;
	float z = _camera->getPositionZ();
	_camera->setPosition3D(Vec3(x, y, z));
}