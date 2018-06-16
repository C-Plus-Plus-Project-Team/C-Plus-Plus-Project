#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Tank :public Sprite {
	
public:
	CREATE_FUNC(Tank);
	bool init();
	bool isLeft;

	float diff[2];
	Sprite* sp;

	void update(float dt);
};
#pragma once
