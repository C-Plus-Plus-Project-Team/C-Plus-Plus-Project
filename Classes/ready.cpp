#include "systemheader.h"
#include "ready.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* ready::createScene()
{
	return ready::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool ready::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(20);

	MenuItemFont * readyItem = MenuItemFont::create("Ready", CC_CALLBACK_1(ready::menuReadyCallback, this));
	readyItem->setPosition(Vec2(origin.x + visibleSize.width / 8, origin.y + visibleSize.height / 1.3));

	MenuItemFont * okItem = MenuItemFont::create("Done", CC_CALLBACK_1(ready::menuOkCallback, this));
	okItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4.5));

	auto menu = Menu::create(readyItem,okItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto startBackground = Sprite::create("BackGround.png");
	startBackground->setPosition(origin + Vec2(visibleSize.width / 2 + origin.x, 0));
	startBackground->setAnchorPoint(Vec2(0.5, 0));
	startBackground->setTag(START_BACKGROUND);
	this->addChild(startBackground, 0);

	return true;
}

void ready::menuReadyCallback(cocos2d::Ref* pSender)
{
	//auto  sc = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFadeUp::create(0.4f, GameScene::createScene()));
//	Director::getInstance()->pushScene(sc);
}

void ready::menuOkCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}

