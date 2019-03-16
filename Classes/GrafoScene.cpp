#include "GrafoScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Grafos::createScene()
{
	return Grafos::create();
}

bool Grafos::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	float x = visibleSize.width / 2;
	float y = visibleSize.height / 2;

	auto background = Sprite::create("images/unam_logo.jpg");
	background->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	background->setPosition(x, y);
	background->setScale(0.6f);

	this->addChild(background, 0);

	auto labelExit1 = Label::createWithTTF("Nuevo nodo", "fonts/Marker Felt.ttf", 24);
	labelExit1->enableOutline(Color4B::BLACK, 1);

	auto item_31 = MenuItemLabel::create(labelExit1, CC_CALLBACK_1(Grafos::addNodes, this));
	item_31->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_31->setPosition(Vec2(x, y));

	auto menu1 = Menu::createWithItem(item_31);
	menu1->setPosition(Vec2::ZERO);

	this->addChild(menu1, 1);

	this->getPhysicsWorld()->setGravity(Vec2::ZERO);

	return true;
}

void Grafos::addNodes(Ref* pSender)
{
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
}
