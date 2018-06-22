#include "systemheader.h"
#include "ready.h"
#include "SimpleAudioEngine.h"
#include "systemheader.h"
#include<string>
#include "chat.hpp"
#include "GameScene.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace std;
char player;

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

	//decide1 = false;
	//decide2 = false;

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(20);

	player1Item = MenuItemFont::create("Player1",
		CC_CALLBACK_1(ready::menuPlayer1Callback, this));
	player1Item->setColor(ccc3(255, 255, 255));
	player1Item->setPosition(Director::getInstance()->convertToGL(Vec2(100, 100)));
	player2Item = MenuItemFont::create("Player2",
		CC_CALLBACK_1(ready::menuPlayer2Callback, this));
	player2Item->setColor(ccc3(255, 255, 255));
	player2Item->setPosition(Director::getInstance()->convertToGL(Vec2(250, 100)));

	MenuItemFont * okItem = MenuItemFont::create("Done", CC_CALLBACK_1(ready::menuOkCallback, this));
	okItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4.5));

	auto menu = Menu::create(player1Item, player2Item, okItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto startBackground = Sprite::create("BackGround.png");
	startBackground->setPosition(origin + Vec2(visibleSize.width / 2 + origin.x, 0));
	startBackground->setAnchorPoint(Vec2(0.5, 0));
	startBackground->setTag(START_BACKGROUND);
	this->addChild(startBackground, 0);
	//this->schedule(schedule_selector(ready::updateCustom), 0.1f, kRepeatForever,0);//自定义update函数
	this->scheduleUpdate();//默认update函数

	return true;
}



void ready::update(float dt)
{


}

void ready::menuPlayer1Callback(cocos2d::Ref* pSender)
{
	player = '1';
	cocos2d::log("%c", player);
	player1Item->setColor(ccc3(0, 0, 255));
	player2Item->setColor(ccc3(0, 0, 0));
	//write(player, 1.0f, 0.0f);
	//write(player, 1.0f, 0.0f, 0.0f, 0.0f);
	//write(player, "ok", 0.9f, 0.9f);
}

void ready::menuPlayer2Callback(cocos2d::Ref* pSender)
{
	player = '2';
	cocos2d::log("%c", player);
	player1Item->setColor(ccc3(0, 0, 0));
	player2Item->setColor(ccc3(0, 0, 255));
//	write(player, 2.0f, 0.0f);
}

void ready::menuOkCallback(cocos2d::Ref* pSender)
{
	//Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(TransitionFadeUp::create(0.4f, GameScene::createScene()));
}