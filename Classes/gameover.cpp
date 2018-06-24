
#include "gameover.h"
#include "SimpleAudioEngine.h"
//#include "function.h"
#include "MainScene.h"
string str1;
bool whetherWin;

USING_NS_CC;
using namespace CocosDenshion;

Scene* gameover::createScene()
{
	return gameover::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool gameover::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(20);

	MenuItemFont * mainmenuItem = MenuItemFont::create("Mainmenu", CC_CALLBACK_1(gameover::menuMainmenuCallback, this));
	mainmenuItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4.5));

	if (whetherWin)
	{
		str1 = "Win";
	}
	else
	{
		str1 = "Lose";
	}

	MenuItemFont * WinItem = MenuItemFont::create(str1, CC_CALLBACK_1(gameover::menuWinmenuCallback, this));
	WinItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2.5));

	// create menu, it's an autorelease object
	auto menu = Menu::create(mainmenuItem, WinItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto startBackground = Sprite::create("BackGround.png");
	startBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, 0));
	startBackground->setAnchorPoint(Vec2(0.5, 0));
	startBackground->setTag(START_BACKGROUND);
	this->addChild(startBackground, 0);

	UserDefault * defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("pal4.mp3", true);
	}

	
	return true;
}

void gameover::menuMainmenuCallback(cocos2d::Ref* pSender)
{
	auto sc = MainScene::createScene();
	Director::getInstance()->pushScene(sc);
}

void gameover::menuWinmenuCallback(cocos2d::Ref* pSender)
{

}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
