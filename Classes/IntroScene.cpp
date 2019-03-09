#include "IntroScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Intro::createScene()
{
    return Intro::create();
}

void Intro::changeOpacityLabel(float dt)
{
	float opacity = MenuItems.at(0)->getOpacity();
	if (opacity >= 240)
		return;
	opacity += 20.0;
	for (int i = 0; i < MenuItems.size(); i++)
		MenuItems.at(i)->setOpacity(opacity);
}

void Intro::addCredits()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float x = visibleSize.width / 2;
	float y = 7 * visibleSize.height / 8;

	auto label_1 = Label::createWithTTF("Matematicas Aplicadas y Computacion", "fonts/Marker Felt.ttf", 60);
	label_1->enableOutline(Color4B::BLACK, 3);
	label_1->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	label_1->setPosition(x, y);
	label_1->setOpacity(0);
	MenuItems.pushBack(label_1);


	x = visibleSize.width / 2;
	y = 6 * visibleSize.height / 8;

	auto label_2 = Label::createWithTTF("Teoria de Grafos", "fonts/Marker Felt.ttf", 60);
	label_2->enableOutline(Color4B::BLACK, 3);
	label_2->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	label_2->setPosition(x, y);
	label_2->setOpacity(0);
	MenuItems.pushBack(label_2);


	x = visibleSize.width / 2;
	y = 4.5 * visibleSize.height / 8;

	auto label_3 = Label::createWithTTF("Equipo:", "fonts/Marker Felt.ttf", 45);
	label_3->enableOutline(Color4B::BLACK, 3);
	label_3->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	label_3->setPosition(x, y);
	label_3->setOpacity(0);
	MenuItems.pushBack(label_3);

	x = visibleSize.width / 2;
	y = 4 * visibleSize.height / 8;

	auto label_4 = Label::createWithTTF("Mora Torres Javier", "fonts/Marker Felt.ttf", 40);
	label_4->enableOutline(Color4B::BLACK, 3);
	label_4->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	label_4->setPosition(x, y);
	label_4->setOpacity(0);
	MenuItems.pushBack(label_4);

	x = visibleSize.width / 2;
	y = 3.5 * visibleSize.height / 8;

	auto label_5 = Label::createWithTTF("Ramirez Garcia Cristian Edgar", "fonts/Marker Felt.ttf", 40);
	label_5->enableOutline(Color4B::BLACK, 3);
	label_5->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	label_5->setPosition(x, y);
	label_5->setOpacity(0);
	MenuItems.pushBack(label_5);

	x = visibleSize.width / 2;
	y = 3 * visibleSize.height / 8;

	auto label_6 = Label::createWithTTF("Torres Jimenez Christian", "fonts/Marker Felt.ttf", 40);
	label_6->enableOutline(Color4B::BLACK, 3);
	label_6->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	label_6->setPosition(x, y);
	label_6->setOpacity(0);
	MenuItems.pushBack(label_6);

	x = visibleSize.width / 2;
	y = 2.5 * visibleSize.height / 8;

	auto label_7 = Label::createWithTTF("Vazquez Osorio Hector Ruben", "fonts/Marker Felt.ttf", 40);
	label_7->enableOutline(Color4B::BLACK, 3);
	label_7->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	label_7->setPosition(x, y);
	label_7->setOpacity(0);
	MenuItems.pushBack(label_7);

	x = visibleSize.width / 2;
	y = 1 * visibleSize.height / 8;

	auto label_8 = Label::createWithTTF("2451", "fonts/Marker Felt.ttf", 40);
	label_8->enableOutline(Color4B::BLACK, 3);
	label_8->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	label_8->setPosition(x, y);
	label_8->setOpacity(0);
	MenuItems.pushBack(label_8);

	for (int i = 0; i < MenuItems.size() ; i++)
		this->addChild(MenuItems.at(i), 1);

}

bool Intro::init()
{
    if ( !Scene::init() )
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

	addCredits();

	this->schedule(CC_SCHEDULE_SELECTOR(Intro::changeOpacityLabel), 0.2f);

    return true;
}

