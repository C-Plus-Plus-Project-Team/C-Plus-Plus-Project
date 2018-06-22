#ifndef Game_Scene
#define Game_Scene

#include "cocos2d.h"
#include "MainScene.h"
#include "Soldier.h"
#include "systemheader.h"

class GameScene : public cocos2d::Layer
{
	cocos2d::TMXTiledMap* _tileMap;
	Soldier *_player;
	Tank *tank;
	Dog *dog;
	Test *test;
	ProgressTimer *timm;
	Sprite *blood;
	Base *base;
	Base *enemy_base;
	Explode *explode;
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
	void newtank();//产生坦克
	void movetank();//移动我方坦克
	void newtank(float x, float y);//产生敌方坦克
	void movetank(float x , float y );//移动敌方坦克

	//police dog
	void newdog();
	void movedog();
	void newdog(float x, float y);//产生敌方警犬
	void movedog(float x, float y);//移动敌方警犬

	//soldier
	void newsoldier();
	void movesoldier();
	void newsoldier(float x, float y);//产生敌方士兵
	void movesoldier(float x, float y);//移动敌方士兵

	//产生敌方建筑
	void new_enemy_chariot(float x, float y);//坦克工厂
	void new_enemy_barracks(float x, float y);//兵营
	void new_enemy_powerplant(float x, float y);//电厂
	void new_enemy_kuangchang(float x, float y);//矿场

	//分析敌方鼠标单击位置信息
	void enemyclick(float x, float y);
	//分析敌方鼠标框选区域信息
	void enemySelectArea(float dx, float dy, float ux, float uy);

	//blood reservoir
	void blood_reservoir( Vec2 enemyPos);
	//explode GIF
	void explodeGIF( Vec2 Pos);

	int dogCount;//警犬数量
	int tankCount;//坦克数量
	int count;
	int explodetime;//爆炸效果所持续时间
	
	bool iftocreatemenu;
	bool buildbase;
	bool enemy_buildbase;
	bool canmove;
	bool addbuilding;

	Vec2 startpos;//储存初始位置
	Vec2 mappos;//储存地图位置
	Vec2 mouseDownPosition;//第一次点鼠标时鼠标的位置
	Vec2 mouseUpPosition;//鼠标抬起时的位置
	static cocos2d::Vector<Dog*> vec_chosed_dog;//存储我方选中policeDog的容器
	static cocos2d::Vector<Tank*> vec_chosed_tank;//存储我方选中tank的容器
	static cocos2d::Vector<Soldier*> vec_chosed_soldier;//存储我方选中soldier的容器

	static cocos2d::Vector<Dog*> enemy_chosed_dog;//存储敌方选中policeDog的容器
	static cocos2d::Vector<Tank*> enemy_chosed_tank;//存储敌方选中tank的容器
	static cocos2d::Vector<Soldier*> enemy_chosed_soldier;//存储敌方选中soldier的容器

														  //菜单功能实现
	Vec2 bingyingPosition;//记录坦克兵营位置（产兵就在兵营的位置）
	Vec2 soldierbingyingPosition;//记录步兵工厂位置
	int iftobuild = 1;//菜单选中状况，1为起始状态，2为完成加载状态
	tankbing *createTank;
	tankgongchang *createTankbingying;
	whitecd *white;
	ProgressTimer *progress1;
	caidankuang *caidankuang1;
	bubinggongchang *createbingying;
	fadianchang *createfadianchang;
	shiyouchang *createshiyouchang;
	bubing *createbubing;
	jingquan *createjingquan;

	//void setViewpointCenter(cocos2d::Vec2 position); //set viewpoint center,to move the map
	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif // __HELLOWORLD_SCENE_H__
