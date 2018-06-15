#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Tank :public Sprite {
public:
	CREATE_FUNC(Tank);
	bool init();
	bool isLeft;
	void idle();
	void runLeft(float dt);
	void runRight(float dt);
	void runUp(float dt);
	void runDown(float dt);

	float diff[2];

	bool isDown;
	bool isrunUp;
	bool isrunLeft;
	bool isrunRight;
	bool isrunDown;

	void runAnimation();
	Sprite* sp;

	Action* run;

	void update(float dt);
};
#pragma once
