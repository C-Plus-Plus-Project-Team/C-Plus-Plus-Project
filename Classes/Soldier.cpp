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

//soldier fireAnimation
void Soldier::fireAnimation() {
	Vector<SpriteFrame*>allFrames;
	char txt[100] = {};
	for (int i = 1; i < 3; i++) {
		sprintf_s(txt, "tex/hero/fire000%d.png", i);
		SpriteFrame* sf = SpriteFrame::create(txt, Rect(0, 0, 51, 45));
		allFrames.pushBack(sf);
	}
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);
	run = sp->runAction(RepeatForever::create(Animate::create(ani)));
}


bool Tank::init() {
	Sprite::init();
	idle();

	/*Vector<SpriteFrame*>allFrames;

	SpriteFrame* sf = SpriteFrame::create("Tank2.png", Rect(0, 0, 130, 80));
	allFrames.pushBack(sf);
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);

	auto s = Sprite::create();
	s->runAction(RepeatForever::create(Animate::create(ani)));
	s->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(s);
	sptank = s;*/

	return true;
}

void Tank::idle() {
	this->removeAllChildren();

	Vector<SpriteFrame*>allFrames;

	SpriteFrame* sf = SpriteFrame::create("Tank2.png", Rect(0, 0, 130, 80));
	allFrames.pushBack(sf);
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);

	auto s = Sprite::create();
	s->runAction(RepeatForever::create(Animate::create(ani)));
	s->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(s);
	sptank = s;

}

//tank fireAnimation
void Tank::fireAnimation() {
	Vector<SpriteFrame*>allFrame;
	char txt[100] = {};
	for (int i = 1; i < 3; i++) {
		sprintf_s(txt, "Tank_fire000%d.png", i);
		SpriteFrame* sf = SpriteFrame::create(txt, Rect(0, 0, 156, 80));
		allFrame.pushBack(sf);
	}
	Animation* an = Animation::createWithSpriteFrames(allFrame, 0.1);
	runtank = sptank->runAction(RepeatForever::create(Animate::create(an)));
}


bool Dog::init() {
	Sprite::init();

	Vector<SpriteFrame*>allFrames;

	SpriteFrame* sf = SpriteFrame::create("dog30.png", Rect(0, 0, 30, 30));
	allFrames.pushBack(sf);
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);

	auto sp = Sprite::create();
	sp->runAction(RepeatForever::create(Animate::create(ani)));
	sp->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(sp);

	return true;
}

bool Test::init() {
	Sprite::init();
	attacked = false;
	hp = 20;

	Vector<SpriteFrame*>allFrames;

	SpriteFrame* sf = SpriteFrame::create("test.png", Rect(0, 0, 200, 173));
	allFrames.pushBack(sf);
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);

	auto sp = Sprite::create();
	sp->runAction(RepeatForever::create(Animate::create(ani)));
	sp->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(sp);

	return true;
}


