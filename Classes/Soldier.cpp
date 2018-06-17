#include "GameScene.h"
#include "Soldier.h"

bool Soldier::init() {
	Sprite::init();
	isLeft = false;
	idle();

	return true;
}

//idle
void Soldier::idle() {
	this->removeAllChildren();
	auto s = Sprite::create("tex/hero/idle.png");
	s->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(s);
	sp = s;
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
}


bool Tank::init() {
	Sprite::init();


	Vector<SpriteFrame*>allFrames;

	SpriteFrame* sf = SpriteFrame::create("tank2.png", Rect(0, 0, 170, 104));
	allFrames.pushBack(sf);
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);

	auto sp = Sprite::create();
	sp->runAction(RepeatForever::create(Animate::create(ani)));
	sp->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(sp);

	return true;
}

bool Dog::init() {
	Sprite::init();

	Vector<SpriteFrame*>allFrames;

	SpriteFrame* sf = SpriteFrame::create("dog.png", Rect(0, 0, 35, 48));
	allFrames.pushBack(sf);
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);

	auto sp = Sprite::create();
	sp->runAction(RepeatForever::create(Animate::create(ani)));
	sp->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(sp);

	return true;
}


