#include "GameScene.h"
#include "Soldier.h"

bool Soldier::init() {
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
void Soldier::update(float dt) {
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
void Soldier::idle() {
	this->removeAllChildren();
	auto s = Sprite::create("tex/hero/idle.png");
	s->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(s);
	sp = s;
	sp->setScaleX(isLeft ? 1 : -1);

}

//down
void Soldier::down() {
	this->removeAllChildren();
	auto s = Sprite::create("tex/hero/down.png");
	s->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(s);
	s->setScaleX(isLeft ? 1 : -1);
}

//runAnimation
void Soldier::runAnimation() {
	Vector<SpriteFrame*>allFrames;
	char txt[100] = {};
	for (int i = 1; i < 4; i++) {
		sprintf_s(txt, "tex/hero/run_left000%d.png", i);
		SpriteFrame* sf = SpriteFrame::create(txt, Rect(0, 0, 55, 55));
		allFrames.pushBack(sf);
	}
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);
	run = sp->runAction(RepeatForever::create(Animate::create(ani)));
	sp->setScaleX(isLeft ? 1 : -1);
}




//Run Left
void Soldier::runLeft(float dt) {  
	//isLeft = true;
	float d;
	if (abs(diff[0]) >= abs(diff[1]))
		d = dt * 200;
	else
		d = dt * 150 * diff[0] / diff[1];
	setPositionX(getPositionX() - abs(d));
}

//Run Right
void Soldier::runRight(float dt) {
	//isLeft = false;
	float d;
	if (abs(diff[0]) >= abs(diff[1]))
		d = dt * 200;
	else
		d = dt * 150 * diff[0] / diff[1];
	setPositionX(getPositionX() + abs(d));
}

void Soldier::runUp(float dt) {
	float d;
	if (abs(diff[0]) >= abs(diff[1]))
		d = dt * 200 * diff[1] / diff[0];
	else
		d = dt * 100;
	setPositionY(getPositionY() + abs(d));
}

void Soldier::runDown(float dt) {
	float d;
	if (abs(diff[0]) >= abs(diff[1]))
		d = dt * 200 * diff[1] / diff[0];
	else
		d = dt * 100;

	setPositionY(getPositionY() - abs(d));
}