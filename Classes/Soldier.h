#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Soldier :public Sprite {
public:
	CREATE_FUNC(Soldier);
	bool init();
	bool isLeft;
	void idle();
	int hp;
	bool attacked;
	
	void runAnimation();
	void fireAnimation();
	Sprite* sp;
	Action* run;
};

class Tank :public Sprite {

public:
	CREATE_FUNC(Tank);
	bool init();
	bool isLeft;
	void idle();
	int hp;
	bool attacked;

	void fireAnimation();
	Sprite* sptank;
	Action* runtank;

};

class Dog :public Sprite {

public:
	CREATE_FUNC(Dog);
	bool init();
	bool isLeft;
	int hp;
	bool attacked;


};

class Test :public Sprite {

public:
	CREATE_FUNC(Test);
	bool init();
	int hp;
	bool attacked;
};

class Base :public Sprite {
public:
	CREATE_FUNC(Base);
	bool init();

	void buildingAnimation();
	
	Sprite* sp;
	Action* run;
};

class Explode :public Sprite {
public:
	CREATE_FUNC(Explode);
	bool init();

	void explodeAnimation();

	Sprite* sp;
	Action* run;
};

//菜单功能实验1111
//菜单框
class caidankuang :public Sprite {
public:
	CREATE_FUNC(caidankuang);
	bool init();
	bool isLeft;
};


//坦克兵
class tankbing :public Sprite {
public:
	CREATE_FUNC(tankbing);
	bool init();
	bool isLeft;
};

//坦克工厂
class tankgongchang :public Sprite {
public:
	CREATE_FUNC(tankgongchang);
	bool init();
	bool isLeft;
};

//白色的cd计时
class whitecd :public Sprite {
public:
	CREATE_FUNC(whitecd);
	bool init();
	bool isLeft;
};

//步兵工厂
class bubinggongchang :public Sprite {
public:
	CREATE_FUNC(bubinggongchang);
	bool init();
	bool isLeft;
};

//步兵
class bubing :public Sprite {
public:
	CREATE_FUNC(bubing);
	bool init();
	bool isLeft;
};

//警犬
class jingquan :public Sprite {
public:
	CREATE_FUNC(jingquan);
	bool init();
	bool isLeft;
};


//发电厂
class fadianchang :public Sprite {
public:
	CREATE_FUNC(fadianchang);
	bool init();
	bool isLeft;
};

//石油厂
class shiyouchang :public Sprite {
public:
	CREATE_FUNC(shiyouchang);
	bool init();
	bool isLeft;
};
