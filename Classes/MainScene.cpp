#include "MainScene.h"
#include "ready.h"
#include "SimpleAudioEngine.h"
#include "setting.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* MainScene::createScene()
{
	return MainScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MainScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(20);

	//start(pvp)
	MenuItemFont * startItem = MenuItemFont::create("Start(PVP)", CC_CALLBACK_1(MainScene::menuStartCallback, this));
	startItem->setPosition(Vec2(origin.x + visibleSize.width / 8, origin.y + visibleSize.height / 1.3));

	//setting
	MenuItemFont * settingItem = MenuItemFont::create("Setting", CC_CALLBACK_1(MainScene::menuSettingCallback, this));
	settingItem->setPosition(Vec2(origin.x + visibleSize.width / 8, origin.y + visibleSize.height / 1.8));

	//exit
	MenuItemFont * closeItem = MenuItemFont::create("Exit", CC_CALLBACK_1(MainScene::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width / 8, origin.y + visibleSize.height / 3.3));

	// create menu, it's an autorelease object
	auto menu = Menu::create(startItem, settingItem, closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto label = Label::createWithTTF("Red Alert", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	auto startBackground = Sprite::create("BackGround.png");
	//startBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, 0));
	startBackground->setAnchorPoint(Vec2(0, 0));
	startBackground->setTag(START_BACKGROUND);
	/*this->addChild(startBackground, 0);*/
	this->addChild(startBackground);

	UserDefault * defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("pal4.mp3", true);
	}

	return true;
}

void MainScene::menuSettingCallback(Ref * pSender)
{
	auto sc = setting::createScene();
	Director::getInstance()->pushScene(sc);
}

void MainScene::menuStartCallback(Ref * pSender)
{
	auto sc = ready::createScene();
	Director::getInstance()->pushScene(sc);
}

void MainScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MainScene::onEnter()
{
	Scene::onEnter();
}

void MainScene::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();
}

void MainScene::onExit()
{
	Scene::onExit();
}

void MainScene::onExitTransitionDidStart()
{
	Scene::onExitTransitionDidStart();
}

void MainScene::cleanup()
{
	Scene::cleanup();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("pal4.mp3");
}