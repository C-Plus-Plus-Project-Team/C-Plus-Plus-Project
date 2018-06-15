#ifndef Game_Scene
#define Game_Scene

#include "cocos2d.h"
#include "MainScene.h"
#include "Soldier.h"

class GameScene : public cocos2d::Layer
{
	cocos2d::TMXTiledMap* _tileMap;
	Soldier *_player;
	Vec2 touchLocation;
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	Vec2 diff;

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	void update(float dt); //detle time

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif // __HELLOWORLD_SCENE_H__
