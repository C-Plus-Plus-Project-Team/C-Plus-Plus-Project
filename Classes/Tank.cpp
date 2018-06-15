#include "GameScene.h"
#include "Tank.h"

bool Tank::init() {
	Sprite::init();
	isLeft = false;
	isrunLeft = false;
	isrunRight = false;
	isrunUp = false;
	isDown = false;
	isrunDown = false;

	idle();


	return true;
}



//update
void Tank::update(float dt) {
	//if (!isDown) {
	if (isrunLeft)
		runLeft(dt);
	if (isrunRight)
		runRight(dt);
	if (isrunUp)
		runUp(dt);
	if (isrunDown)
		runDown(dt);
	//}

}


//idle
void Tank::idle() {
	this->removeAllChildren();
	auto s = Sprite::create("tex/hero/idle.png");
	s->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(s);
	sp = s;
	sp->setScaleX(isLeft ? 1 : -1);

}

