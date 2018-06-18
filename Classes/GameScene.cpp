#include "GameScene.h"

USING_NS_CC;
Vector<Dog*> policeDog;
Vector<Tank*> tank_vec;
Vector<Soldier*>soldier_vec;
Vector<Test*>test_vec;

Vector<Dog*> GameScene::vec_chosed_dog;
Vector<Tank*> GameScene::vec_chosed_tank;
Vector<Soldier*>GameScene::vec_chosed_soldier;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_tileMap = TMXTiledMap::create("map/MiddleMap.tmx");
	addChild(_tileMap, 0, 100);
	startpos = _tileMap->getPosition();
	mappos = startpos;

	//newsoldier();
	//newtank();
	//newdog();
	count = 0;
	dogCount = 6;
	tankCount = 3;
	
	setTouchEnabled(true);
	//����Ϊ���㴥
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	
	//onEnter();
	newtest();

	scheduleUpdate();

	return true;

	
}

void GameScene::update(float dt) {
	count++;
	
	//��ѡ�ж�����й���
	if ((vec_chosed_soldier.size() || vec_chosed_tank.size() || vec_chosed_dog.size())
		&& test->attacked && (count % 50 == 0))
	{
		for (int j = 0; j < vec_chosed_soldier.size(); j++)
		{
			_player = vec_chosed_soldier.at(j);
			_player->fireAnimation();

			test->hp--;
		}


		for (int i = 0; i < vec_chosed_tank.size(); i++)
		{
			tank = vec_chosed_tank.at(i);
			tank->fireAnimation();

			test->hp--;
		}

		//_player->fireAnimation();
		//tank->fireAnimation();
	}

	if (test->hp == 0 && test->attacked == true) {
		test->attacked = false;

		for ( int j = 0; j < vec_chosed_soldier.size(); j++)
		{
			_player = vec_chosed_soldier.at(j);
			_player->idle();
		}


		for ( int i = 0; i < vec_chosed_tank.size(); i++)
		{
			tank = vec_chosed_tank.at(i);
			tank->idle();
		}

		test->removeFromParent();
		//test_vec.eraseObject(test_vec.at(0));
	}

	//�ж�ѡ��ʿ���Ƿ񵽴�ָ��λ��
	if (vec_chosed_soldier.size())
	{
		for (int j = 0; j < vec_chosed_soldier.size(); j++)
		{
			_player = vec_chosed_soldier.at(j);
			Vec2 playerPos = _player->getPosition();
			if (playerPos.x == (mouseUpPosition.x + j * 50))
			{
				_player->idle();
			}
		}
	}
	
	if (count % 90 == 0 && policeDog.size() < dogCount)
		newdog();
	if (count % 90 == 0 && tank_vec.size() < tankCount)
		newtank();
	if (count % 90 == 0 && soldier_vec.size() < tankCount)
		newsoldier();
}

/* 
void GameScene::onEnter()
{
	Layer::onEnter();
	auto listener = EventListenerMouse::create();

	listener->onMouseMove = [](Event * event)
	{
		EventMouse * e = (EventMouse *)event;
		
	};
	listener->onMouseScroll = [](Event * event)
	{
		EventMouse * e = (EventMouse *)event;
	
	};
	listener->onMouseDown = []( Event * event)
	{
		EventMouse * e = (EventMouse *)event;
		log("onTouchBegan");
		mouseDownPosition = e->getLocation();
		//return true;
		
	};
	listener->onMouseUp = [](Event * event)
	{
		EventMouse * e = (EventMouse *)event;

	};

	EventDispatcher * eventDispatcher = Director::getInstance()->getEventDispatcher();

	eventDispatcher->addEventListenerWithGraphPriority(listener, this);
}
*/

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	log("onTouchBegan");
	mouseDownPosition = touch->getLocation();
	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event)
{
	log("onTouchMoved");
}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{
	EventMouse* e = (EventMouse*)event;

	log("onTouchEnded");
	//���OpenGL����
	mouseUpPosition = touch->getLocation();
	log("mouseUpPosition (%f ,%f) ", mouseUpPosition.x, mouseUpPosition.y);

	//������º��ɿ���������ͬһ��λ��
	if (sqrt(pow((mouseUpPosition.x - mouseDownPosition.x), 2) + pow((mouseUpPosition.y - mouseDownPosition.y), 2)) <= 5)
	{
		float rectX = mouseDownPosition.x;
		float rectY = mouseDownPosition.y;
		Rect mouseRect(rectX - 100 , rectY - 100 , 200, 200);

		//�ж�����λ���Ƿ��ео�
		if (test_vec.at(0)->getBoundingBox().intersectsRect(mouseRect)  && 
			(vec_chosed_soldier.size() || vec_chosed_tank.size() || vec_chosed_dog.size()))
		{
			test_vec.at(0)->attacked = true;
			//move police dog
			movedog();
			log("attck success");
		}
		else {
			//move sodier
			movesoldier();
			//move tank
			movetank();
			//move police dog
			movedog();
		}
		


	}
	else//�����ɿ�����ͬһλ�ã�����ѡ��
	{
		//if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)//�����������
		//{

		//������껭�ķ���rect
		float rectX = mouseDownPosition.x < mouseUpPosition.x ? mouseDownPosition.x : mouseUpPosition.x;
		float rectY = mouseDownPosition.y < mouseUpPosition.y ? mouseDownPosition.y : mouseUpPosition.y;
		Rect mouseRect(rectX, rectY, abs(mouseDownPosition.x - mouseUpPosition.x), abs(mouseDownPosition.y - mouseUpPosition.y));

			//�ǽ���״̬

			//�ж�ѡ�еľ�Ȯ
			vec_chosed_dog.clear();
			for (int i = 0; i < policeDog.size(); i++)
			{
				//�жϿ�ѡ����Щ
				if (policeDog.at(i)->getBoundingBox().intersectsRect(mouseRect))
				{
					Texture2D* textureYes = Director::getInstance()->getTextureCache()->addImage("CloseNormal.png");
					policeDog.at(i)->setTexture(textureYes);
					vec_chosed_dog.pushBack(policeDog.at(i));
					log("slect success");
				}
				else
				{
					Texture2D* textureNo = Director::getInstance()->getTextureCache()->addImage("CloseSelected.png");
					policeDog.at(i)->setTexture(textureNo);
				}
			}

			//�ж�ѡ�е�̹��
			vec_chosed_tank.clear();
			for (int i = 0; i < tank_vec.size(); i++)
			{
				//�жϿ�ѡ����Щ
				if (tank_vec.at(i)->getBoundingBox().intersectsRect(mouseRect))
				{
					Texture2D* textureYes = Director::getInstance()->getTextureCache()->addImage("CloseNormal.png");
					tank_vec.at(i)->setTexture(textureYes);
					vec_chosed_tank.pushBack(tank_vec.at(i));
				}
				else
				{
					Texture2D* textureNo = Director::getInstance()->getTextureCache()->addImage("CloseSelected.png");
					tank_vec.at(i)->setTexture(textureNo);
				}
			}

			//�ж�ѡ�е�ʿ��
			vec_chosed_soldier.clear();
			for (int i = 0; i < soldier_vec.size(); i++)
			{
				//�жϿ�ѡ����Щ
				if (soldier_vec.at(i)->getBoundingBox().intersectsRect(mouseRect))
				{
					Texture2D* textureYes = Director::getInstance()->getTextureCache()->addImage("CloseNormal.png");
					soldier_vec.at(i)->setTexture(textureYes);
					vec_chosed_soldier.pushBack(soldier_vec.at(i));
				}
				else
				{
					Texture2D* textureNo = Director::getInstance()->getTextureCache()->addImage("CloseSelected.png");
					soldier_vec.at(i)->setTexture(textureNo);
				}
			}


		//};

		

	}
}


//newtank
void GameScene::newtank() {
	int i = tank_vec.size();
	tank = Tank::create();
	tank->setPosition(500 + i * 100, 200);
	addChild(tank);
	tank_vec.pushBack(tank);
}

//move tank
void GameScene::movetank()
{
	Vec2 tankPos;
	Vec2 diff ;
	for (int j = 0; j < vec_chosed_tank.size(); j++)
	{
		auto pd = vec_chosed_tank.at(j);

		tankPos = pd->getPosition();
		diff = mouseUpPosition - tankPos;

		if (diff.x > 0) 
			pd->isLeft = false;
		else
			pd->isLeft = true;

		pd->setScaleX(pd->isLeft ? 1 : -1);

		float v = sqrt(diff.x * diff.x + diff.y * diff.y) / 100;

		if (j == 1)
			pd->runAction(MoveBy::create(v, Vec2(diff.x, diff.y + j * 75))); 
		else {
			if (j % 2)
				pd->runAction(MoveBy::create(v, Vec2(diff.x, diff.y + j * 50)));
			else
				pd->runAction(MoveBy::create(v, Vec2(diff.x, diff.y - j * 50)));

		}
	}

}

//new police dog
void GameScene::newdog() {
	dog = Dog::create();
	int i = policeDog.size(); 
	dog->setPosition(300 + i * 20, 200);
	addChild(dog);
	policeDog.pushBack(dog);
}

//move police dog
void GameScene::movedog()
{
	Vec2 dogPos ;
	Vec2 diff ;
	
	for (int j = 0; j <vec_chosed_dog.size(); j++)
	{
		auto bm = vec_chosed_dog.at(j);

		dogPos = bm->getPosition();
		diff = mouseUpPosition - dogPos;

		if (diff.x > 0) {
			bm->isLeft = false;
		}
		else
			bm->isLeft = true;

		bm->setScaleX(bm->isLeft ? 1 : -1);

		float v = sqrt(diff.x * diff.x + diff.y * diff.y) / 150;

		bm->runAction(MoveBy::create(v, Vec2(diff.x + j * 40 , diff.y)));
	}


}

void GameScene::newsoldier() {
	//add soldier
	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("soldier");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	_player = Soldier::create();
	int i = soldier_vec.size();
	_player->setPosition(Vec2(x + 200 + i * 30, y + 200));
	addChild(_player, 2, 200);
	soldier_vec.pushBack(_player);
}

void GameScene::movesoldier()
{
	Vec2 playerPos;
	Vec2 diff;
	for (int j = 0; j < vec_chosed_soldier.size(); j++)
	{
		_player = vec_chosed_soldier.at(j);

		playerPos = _player->getPosition();
		diff = mouseUpPosition - playerPos;

		if (diff.x > 0) {
			_player->isLeft = false;
		}
		else
			_player->isLeft = true;


		_player->setScaleX(_player->isLeft ? 1 : -1);

		_player->runAnimation();

		float v = sqrt(diff.x * diff.x + diff.y * diff.y) / 150;

		_player->runAction(MoveBy::create(v, Vec2(diff.x + j * 50, diff.y)));
	}
}

//new test
void GameScene::newtest() {
	test = Test::create();
	test->setPosition(400, 300);
	addChild(test);
	test_vec.pushBack(test);

}