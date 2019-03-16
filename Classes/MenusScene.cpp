#include "MenusScene.h"
#include "GrafoScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Menus::createScene()
{
    return Menus::create();
}

void Menus::MainMenu(Ref *sender)
{
	cocos2d::log("-------");
}

void Menus::goToMenu(Ref *sender)
{
	auto scene = Grafos::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
}

void Menus::addMenus()
{

	auto visibleSize = Director::getInstance()->getVisibleSize();
	
	float x = visibleSize.width / 2;
	float y = 7 * visibleSize.height / 8;

	Vector<MenuItem*> MenuItems;

	auto labelMenu = Label::createWithTTF("Menu", "fonts/Marker Felt.ttf", 60);
	labelMenu->enableOutline(Color4B::BLACK, 3);

	auto item = MenuItemLabel::create(labelMenu, CC_CALLBACK_1(Menus::MainMenu, this));
	item->setAnchorPoint(Vec2(0.5f, 0.5f));
	item->setPosition(Vec2(x, y));
	MenuItems.pushBack(item);

	x = visibleSize.width / 2;
	y = 5 * visibleSize.height / 8;

	auto labelNewGrafo = Label::createWithTTF("Nuevo Grafo", "fonts/Marker Felt.ttf", 45);
	labelNewGrafo->enableOutline(Color4B::BLACK, 3);

	auto item_1 = MenuItemLabel::create(labelNewGrafo, CC_CALLBACK_1(Menus::goToMenu, this));
	item_1->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_1->setPosition(Vec2(x, y));
	MenuItems.pushBack(item_1);

	x = visibleSize.width / 2;
	y = 4 * visibleSize.height / 8;

	auto labelNewDigrafo = Label::createWithTTF("Nuevo Digrafo", "fonts/Marker Felt.ttf", 45);
	labelNewDigrafo->enableOutline(Color4B::BLACK, 3);

	auto item_2 = MenuItemLabel::create(labelNewDigrafo, CC_CALLBACK_1(Menus::MainMenu, this));
	item_2->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_2->setPosition(Vec2(x, y));
	MenuItems.pushBack(item_2);

	x = visibleSize.width / 2;
	y = 3 * visibleSize.height / 8;

	auto labelSettings = Label::createWithTTF("Configuraciones", "fonts/Marker Felt.ttf", 45);
	labelSettings->enableOutline(Color4B::BLACK, 3);

	auto item_3 = MenuItemLabel::create(labelSettings, CC_CALLBACK_1(Menus::MainMenu, this));
	item_3->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_3->setPosition(Vec2(x, y));
	MenuItems.pushBack(item_3);

	x = visibleSize.width / 2;
	y = 2 * visibleSize.height / 8;

	auto labelExit = Label::createWithTTF("Salir", "fonts/Marker Felt.ttf", 45);
	labelExit->enableOutline(Color4B::BLACK, 3);

	auto item_4 = MenuItemLabel::create(labelExit, CC_CALLBACK_1(Menus::menuCloseCallback, this));
	item_4->setAnchorPoint(Vec2(0.5f, 0.5f));
	item_4->setPosition(Vec2(x, y));
	MenuItems.pushBack(item_4);

	auto menu = Menu::createWithArray(MenuItems);
	menu->setPosition(Vec2::ZERO);

	this->addChild(menu, 1);
}

bool Menus::init()
{
	if (!Scene::init())
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

	addMenus();

    return true;
}


void Menus::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
