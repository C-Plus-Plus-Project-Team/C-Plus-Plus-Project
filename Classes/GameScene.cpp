#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_tileMap = TMXTiledMap::create("map/MiddleMap.tmx");
	addChild(_tileMap, 0, 100);

	//add soldier
	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("soldier");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	_player = Soldier::create();
	_player->setPosition(Vec2(x+200, y+200));
	addChild(_player, 2, 200);

	newtank();



	setTouchEnabled(true);
	//设置为单点触
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	scheduleUpdate();

	return true;
}
void GameScene::update(float dt) {
	Vec2 playerPos = _player->getPosition();
	if ((playerPos.x - touchLocation.x > 0) && _player->isrunRight && (abs(playerPos.y - touchLocation.y ) < 5 )) {
		_player->isrunRight = false;
		_player->isrunUp = false;
		_player->isrunDown = false;
		_player->idle();
	}
	if ((playerPos.x - touchLocation.x < 0) && _player->isrunLeft && (abs(playerPos.y - touchLocation.y) < 5)) {
		_player->isrunLeft = false;
		_player->isrunUp = false;
		_player->isrunDown = false;
		_player->idle();
	}
		
	_player->update(dt);
}


bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	log("onTouchBegan");
	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event)
{
	log("onTouchMoved");
}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{
	log("onTouchEnded");
	//获得OpenGL坐标
	touchLocation = touch->getLocation();
	log("touchLocation (%f ,%f) ", touchLocation.x, touchLocation.y);

	//移动士兵
	Vec2 playerPos = _player->getPosition();
	diff = touchLocation - playerPos;
	_player->diff[0] = diff.x;
	_player->diff[1] = diff.y;
		if (diff.x > 0) {
			_player->isrunRight = true;
			_player->isLeft = false;
			
			_player->runAnimation();
			
		}
		else {
			_player->isrunLeft = true;
			_player->isLeft = true;
			_player->runAnimation();

		}
	
		if (diff.y > 0) {
			_player->isrunUp = true;
		}
		else {
			_player->isrunDown = true;

		}
	
		//move tank
		movetank(touchLocation.x, touchLocation.y);

	log("playerPos (%f ,%f) ", playerPos.x, playerPos.y);
}

//newtank
void GameScene::newtank() {
	tank = Tank::create();
	tank->setPosition(500, 200);
	addChild(tank);
}

//move tank
void GameScene::movetank(float px, float py)
{
	Vec2 tankPos = tank->getPosition();
	diff = touchLocation - tankPos;
	tank->diff[0] = diff.x;
	tank->diff[1] = diff.y;

	if (diff.x > 0) {
		tank->isLeft = false;
	}
	else
		tank->isLeft = true;

	tank->setScaleX(tank->isLeft ? 1 : -1);

	float v = sqrt(diff.x * diff.x + diff.y * diff.y) / 100 ;

	tank->runAction( MoveBy::create(v, Vec2(diff.x, diff.y)));

}