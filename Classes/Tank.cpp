#include "GameScene.h"
#include "Tank.h"

bool Tank::init() {
	Sprite::init();
	
	auto ctank = Sprite::create("Tank2.png");
	ctank->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(ctank);

	return true;
}



//update
void Tank::update(float dt) {
	

}


