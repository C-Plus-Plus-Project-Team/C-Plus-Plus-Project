#ifndef Game_Scene
#define Game_Scene

#include "cocos2d.h"
#include "MainScene.h"
#include "Soldier.h"
//#include "Tank.h"

class GameScene : public cocos2d::Layer
{
	cocos2d::TMXTiledMap* _tileMap;
	Soldier *_player;
	Tank *tank;
	Dog *dog;
	Test *test;
	//Vec2 touchLocation;
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	void update(float dt); //detle time
	//void onEnter();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	/*virtual bool onMouseDown(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onMouseMove(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onMouseUp(cocos2d::Touch *touch, cocos2d::Event *event);*/
	
	//tank
	void newtank();
	void movetank();

	//police dog
	void newdog();
	void movedog();

	//soldier
	void newsoldier();
	void movesoldier();

	//test
	void newtest();

	int dogCount;//警犬数量
	int tankCount;//坦克数量
	int count;

	Vec2 startpos;//储存初始位置
	Vec2 mappos;//储存地图位置
	Vec2 mouseDownPosition;//第一次点鼠标时鼠标的位置
	Vec2 mouseUpPosition;//鼠标抬起时的位置
	static cocos2d::Vector<Dog*> vec_chosed_dog;//存储我方选中policeDog的容器
	static cocos2d::Vector<Tank*> vec_chosed_tank;//存储我方选中tank的容器
	static cocos2d::Vector<Soldier*> vec_chosed_soldier;//存储我方选中soldier的容器

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif // __HELLOWORLD_SCENE_H__
