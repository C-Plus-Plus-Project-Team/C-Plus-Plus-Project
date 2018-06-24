#include "GameScene.h"
#include "Soldier.h"

bool Soldier::init() {
	Sprite::init();
	isLeft = false;
	attacked = false;
	hp = 500;
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
	attacked = false;
	hp = 500;

	idle();

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
	attacked = false;
	hp = 500;

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
	hp = 500;
	Sprite* sf = Sprite::create("test.png", Rect(0, 0, 200, 173));
	sf->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(sf);
	return true;
}


bool Base::init() {
	Sprite::init();

	auto s = Sprite::create("base/base-0.png");
	s->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(s);
	sp = s;

	return true;
}

//base buildingAnimation
void Base::buildingAnimation() {
	Vector<SpriteFrame*>allFrames;
	char txt[100] = {};
	for (int i = 1; i < 30; i++) {
		//sprintf_s(txt, "base/fire000%d.png", i);
		sprintf_s(txt, "base/base-%d.png", i);
		SpriteFrame* sf = SpriteFrame::create(txt, Rect(0, 0, 275, 184));
		sf->setAnchorPoint(Vec2(0.5, 0.5));

		allFrames.pushBack(sf);
	}
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);
	run = sp->runAction(Repeat::create(Animate::create(ani),1));

}


bool Explode::init() {
	Sprite::init();

	auto s = Sprite::create("explode/explode-1.png");
	s->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(s);
	sp = s;

	return true;
}

//explode Animation
void Explode::explodeAnimation() {
	Vector<SpriteFrame*>allFrames;
	char txt[100] = {};
	for (int i = 1; i < 18; i++) {
		//sprintf_s(txt, "base/fire000%d.png", i);
		sprintf_s(txt, "explode/explode-%d.png", i);
		SpriteFrame* sf = SpriteFrame::create(txt, Rect(0, 0, 165, 184));
		sf->setAnchorPoint(Vec2(0.5, 0.5));

		allFrames.pushBack(sf);
	}
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);
	run = sp->runAction(Repeat::create(Animate::create(ani), 1 ));

}


//菜单功能
//坦克兵
bool tankbing::init() {
	Sprite::init();

	Vector<SpriteFrame*>allFrames;

	SpriteFrame* sf = SpriteFrame::create("menu/tankmenu.png", Rect(0, 0, 82, 65));
	allFrames.pushBack(sf);
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);

	auto sp = Sprite::create();
	sp->runAction(RepeatForever::create(Animate::create(ani)));
	sp->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(sp);

	return true;
}

//坦克工厂
bool tankgongchang::init() {
	Sprite::init();

	Vector<SpriteFrame*>allFrames;

	SpriteFrame* sf = SpriteFrame::create("menu/redalert0.0.png", Rect(0, 0, 82, 66));
	allFrames.pushBack(sf);
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);

	auto sp = Sprite::create();
	sp->runAction(RepeatForever::create(Animate::create(ani)));
	sp->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(sp);

	return true;
}

//白色的cs计时
bool whitecd::init() {
	Sprite::init();

	Vector<SpriteFrame*>allFrames;

	SpriteFrame* sf = SpriteFrame::create("menu/white.png", Rect(0, 0, 82, 66));
	allFrames.pushBack(sf);
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);

	auto sp = Sprite::create();
	sp->runAction(RepeatForever::create(Animate::create(ani)));
	sp->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(sp);

	return true;
}

//菜单框
bool caidankuang::init() {
	Sprite::init();

	Vector<SpriteFrame*>allFrames;

	SpriteFrame* sf = SpriteFrame::create("menu/caidankuang.png", Rect(0, 0, 211, 595));
	allFrames.pushBack(sf);
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);

	auto sp = Sprite::create();
	sp->runAction(RepeatForever::create(Animate::create(ani)));
	sp->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(sp);

	return true;
}

//兵工厂
bool bubinggongchang::init() {
	Sprite::init();

	Vector<SpriteFrame*>allFrames;

	SpriteFrame* sf = SpriteFrame::create("menu/bingying1.png", Rect(0, 0, 82, 66));
	allFrames.pushBack(sf);
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);

	auto sp = Sprite::create();
	sp->runAction(RepeatForever::create(Animate::create(ani)));
	sp->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(sp);

	return true;
}

//发电厂
bool fadianchang::init() {
	Sprite::init();

	Vector<SpriteFrame*>allFrames;

	SpriteFrame* sf = SpriteFrame::create("menu/dianchang1.png", Rect(0, 0, 82, 66));
	allFrames.pushBack(sf);
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);

	auto sp = Sprite::create();
	sp->runAction(RepeatForever::create(Animate::create(ani)));
	sp->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(sp);

	return true;
}

//石油厂
bool shiyouchang::init() {
	Sprite::init();

	Vector<SpriteFrame*>allFrames;

	SpriteFrame* sf = SpriteFrame::create("menu/redalert0.2.png", Rect(0, 0, 82, 66));
	allFrames.pushBack(sf);
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);

	auto sp = Sprite::create();
	sp->runAction(RepeatForever::create(Animate::create(ani)));
	sp->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(sp);

	return true;
}

//士兵
bool bubing::init() {
	Sprite::init();

	Vector<SpriteFrame*>allFrames;

	SpriteFrame* sf = SpriteFrame::create("menu/soldier1.png", Rect(0, 0, 82, 66));
	allFrames.pushBack(sf);
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);

	auto sp = Sprite::create();
	sp->runAction(RepeatForever::create(Animate::create(ani)));
	sp->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(sp);

	return true;
}

//警犬
bool jingquan::init() {
	Sprite::init();

	Vector<SpriteFrame*>allFrames;

	SpriteFrame* sf = SpriteFrame::create("menu/policeDog1.png", Rect(0, 0, 82, 66));
	allFrames.pushBack(sf);
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);

	auto sp = Sprite::create();
	sp->runAction(RepeatForever::create(Animate::create(ani)));
	sp->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(sp);

	return true;
}
