#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Soldier :public Sprite {
public:
	CREATE_FUNC(Soldier);
	bool init();
	bool isLeft;
	void idle();
	
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

	void fireAnimation();
	Sprite* sptank;
	Action* runtank;

};

class Dog :public Sprite {

public:
	CREATE_FUNC(Dog);
	bool init();
	bool isLeft;

};

class Test :public Sprite {

public:
	CREATE_FUNC(Test);
	bool init();
	int hp;
	bool attacked;
};

