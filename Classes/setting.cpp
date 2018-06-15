#include "setting.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* setting::createScene()
{
	return setting::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool setting::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Done
	MenuItemFont * okItem = MenuItemFont::create("Done", CC_CALLBACK_1(setting::menuOkCallback, this));
	okItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4.5));

	//on and off
	auto switchItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(setting::menuSwitchCallback, this),
		MenuItemFont::create("On"),
		MenuItemFont::create("Off"),
		NULL);
	switchItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height/1.62));

	auto menu = Menu::create(okItem,switchItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	UserDefault * defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(SOUND_KEY))
	{
		switchItem->setSelectedIndex(0);
	}
	else
	{
		switchItem->setSelectedIndex(1);
	}

	//voice
	auto voice = Label::createWithTTF("Voice", "fonts/Marker Felt.ttf", 24);
	voice->setPosition(Vec2(origin.x + visibleSize.width/4.5,
		origin.y + visibleSize.height - 100));
	this->addChild(voice, 1);

	//setting
	auto setting = Label::createWithTTF("Setting", "fonts/Marker Felt.ttf", 24);
	setting->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - setting->getContentSize().height));
	this->addChild(setting, 1);

	auto startBackground = Sprite::create("BackGround.png");
	startBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, 0));
	startBackground->setAnchorPoint(Vec2(0.5, 0));
	startBackground->setTag(START_BACKGROUND);
	this->addChild(startBackground, 0);

	return true;
}

void setting::menuOkCallback(Ref * pSender)
{
	Director::getInstance()->popScene();
}

void setting::menuSwitchCallback(Ref * pSender)
{
	auto voiceItem = (MenuItemToggle *)pSender;

	UserDefault * defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(SOUND_KEY))
	{
		defaults->setBoolForKey(SOUND_KEY, false);
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	else
	{
		defaults->setBoolForKey(SOUND_KEY, true);
		SimpleAudioEngine::getInstance()->playBackgroundMusic("pal4.mp3",true);
	}
}

void setting::onEnter()
{
	Scene::onEnter();
}

void setting::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();
}

void setting::onExit()
{
	Scene::onExit();
}

void setting::onExitTransitionDidStart()
{
	Scene::onExitTransitionDidStart();
}

void setting::cleanup()
{
	Scene::cleanup();
}
