#include "GameScene.h"

USING_NS_CC;
//�ҷ�
Vector<Dog*> policeDog;//���澯Ȯ��vector
Vector<Tank*> tank_vec;//����̹�˵�vector
Vector<Soldier*>soldier_vec;//��������vector


Vector<Soldier*>enemy_attacked_soldier;//����з�������Ŀ���vector
Vector<Tank*>enemy_attacked_tank;//����з�������Ŀ���vector
Vector<Dog*>enemy_attacked_dog;//����з�������Ŀ���vector

Vector<Soldier*>attacked_soldier;//�����ҷ�������Ŀ���vector
Vector<Tank*>attacked_tank;//�����ҷ�������Ŀ���vector
Vector<Dog*>attacked_dog;//�����ҷ�������Ŀ���vector



Vector<Dog*> GameScene::vec_chosed_dog;//����ѡ�о�Ȯ��vector
Vector<Tank*> GameScene::vec_chosed_tank;//����ѡ��̹�˵�vector
Vector<Soldier*>GameScene::vec_chosed_soldier;//����ѡ�д����vector
//�з�
Vector<Dog*> enemy_policeDog;//����з���Ȯ��vector
Vector<Tank*> enemy_tank_vec;//����з�̹�˵�vector
Vector<Soldier*>enemy_soldier_vec;//����з������vector
Vector<Test*>enemy_test_vec;//���汻����Ŀ���vector

Vector<Dog*> GameScene::enemy_chosed_dog;//����ѡ�о�Ȯ��vector
Vector<Tank*> GameScene::enemy_chosed_tank;//����ѡ��̹�˵�vector
Vector<Soldier*>GameScene::enemy_chosed_soldier;//����ѡ�д����vector


Vector<Sprite*>building_vec;//�ҷ�����
Vector<Sprite*>enemy_building;//�з�����
bool attacked_building;//�ҷ�����������
Vector<Sprite*>enemy_attacked_building;//�з��������Ľ���
bool if_attacked;
bool attack_enemy;//�Ƿ��ео�������
int hp[10];

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

	/*connect();*/

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//���ɵ�ͼ
	_tileMap = TMXTiledMap::create("map/MiddleMap.tmx");
	addChild(_tileMap, 0, 100);
	startpos = _tileMap->getPosition();
	mappos = startpos;

	for (int k = 0; k < 10; k++)
	{
		hp[k] = 500;
	}
	
	HP = 1000;
	if_attacked = false;
	count = 0;
	dogCount = 2;
	tankCount = 2;
	base_expolde = 0;
	buildbase = true;
	enemy_buildbase = true;
	iftocreatemenu = false;
	addbuilding = false;
	attacked_building = false;
	attack_enemy = false;
	whetherWin = false;
	gameover = false;
	attack_base = false;


	setTouchEnabled(true);
	//����Ϊ���㴥��
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	
	//onEnter();
	//newtest();
	//blood_reservoir();

	
	if (player == '1') {
		base = Base::create();
		base->setPosition(100, 120);
		addChild(base,101);

		enemy_base = Base::create();
		enemy_base->setPosition(1400, 850);
		addChild(enemy_base,101);


		log("enemy_base->getPosition: %f %f  ", enemy_base->getPositionX(), enemy_base->getPositionY());
	}
	else
	{
		_tileMap->setPosition(-1000, -450);
		base = Base::create();
		base->setPosition(400, 400);
		addChild(base,101);

		enemy_base = Base::create();
		enemy_base->setPosition(-900, -330);
		addChild(enemy_base,101);
	}
	
	

	scheduleUpdate();

	//�˵������
	caidankuang1 = caidankuang::create();
	caidankuang1->setPosition(Vec2(700, 270));
	this->addChild(caidankuang1,100);
	

	return true;

	
}

void GameScene::update(float dt)
{
	count++;
	explodetime--;
	if (count > 1000000) count = 0;
	if (explodetime < -100000)explodetime = -1;
	if (explodetime == 0) {
		explode->removeFromParent();
	}

	if (gameover)
	{
		if (base_expolde <= 0) {
			auto sc = gameover::createScene();
			Director::getInstance()->pushScene(sc);
			log("Director::getInstance()->pushScene(sc);");
		}
		base_expolde--;
	}


	//������յ�����Ϣ
	if (whether_read && p != player)
	{
		whether_read = false;
		if (ch_[0] == '1')//�ƶ���Ϣ��������Ϣ
		{
			enemyclick(a__, b__);
		}
		else if (ch_[0] == '2')//��ѡ
		{
			enemySelectArea(a_, b_, c_, d_);
			log("read kuangxuan ");
		}
		else if (ch_[0] == '3')//����������Ϣ
		{
			log("judge success");
			if (strcmp(msg, "tank") == 0)
			{
				newtank(j, k);
				log("GameScene:  %s", msg);
			}
			if (strcmp(msg, "dog") == 0) {
				newdog(j, k);
				log("%s", msg);
			}
			if (strcmp(msg, "soldier") == 0) {
				newsoldier(j, k);
				log("GameScene : %s", msg);
			}
			if (strcmp(msg, "base") == 0) {
				enemy_base->buildingAnimation();
				log("%s", msg);
			}
			if (strcmp(msg, "tankchang") == 0) {
				new_enemy_chariot(j, k);
				log("%s", msg);
			}
			if (strcmp(msg, "bingying") == 0) {
				new_enemy_barracks(j, k);
				log("%s", msg);
			}
			if (strcmp(msg, "dianchang") == 0) {
				new_enemy_powerplant(j, k);
				log("%s", msg);
			}
			if (strcmp(msg, "kuang") == 0) {
				new_enemy_kuangchang(j, k);
				log("%s", msg);
			}
			if (strcmp(msg, "kill") == 0) {
				cleanbuilding(j, k);
				log("%s", msg);
			}
			if (strcmp(msg, "attackedB") == 0) {
				attacked_building = true;
				for (int i = 0; i < enemy_chosed_tank.size(); i++)
				{
					tank = enemy_chosed_tank.at(i);
					tank->fireAnimation();
				}
				for (int i = 0; i < enemy_chosed_soldier.size(); i++)
				{
					_player = enemy_chosed_soldier.at(i);
					_player->fireAnimation();
				}
				log("%s", msg);
			}
			if (strcmp(msg, "lose") == 0) {
				gameover = true;
				whetherWin = false;
				log("%s", msg);
			}
		}

	}
	
	if (attack_base)
	{
		//�ҷ�ѡ��ʿ������fire
		for (int j = 0; j < vec_chosed_soldier.size(); j++)
		{
			HP--;
		}

		//�ҷ�ѡ��̹�˽���fire
		for (int j = 0; j < vec_chosed_tank.size(); j++)
		{
			HP--;
			HP--;
		}
		//����Ѫ�۲���
		base_timm->setPercentage((1000 - HP) / 10);


		//�жϽ����Ƿ񱻴ݻ�
		if (HP < 0)
		{
			gameover = true;
			whetherWin = true;
			attack_base = false;
			Vec2 Pos = enemy_base->getPosition();
			explodeGIF(Pos);
			base_expolde = 50;
			for (int j = 0; j < vec_chosed_soldier.size(); j++)
			{
				_player = vec_chosed_soldier.at(j);
				_player->idle();
			}
			for (int i1 = 0; i1 < vec_chosed_tank.size(); i1++)
			{
				tank = vec_chosed_tank.at(i1);
				tank->idle();
				log("tank idle");
			}
			write(player, "lose", 1.0f, 1.0f);
			enemy_base->removeFromParent();
			base_timm->removeFromParent();
			baseblood->removeFromParent();
		}
	}



	//��ѡ�ео����й���
	if (vec_chosed_soldier.size() || vec_chosed_tank.size() || vec_chosed_dog.size())
	{
		for (int i = 0; i < enemy_attacked_dog.size(); i++)
			if (enemy_attacked_dog.at(i)->attacked && (count % 6 == 0))
			{
				//�ҷ�ѡ��ʿ������fireAnimation
				for (int j = 0; j < vec_chosed_soldier.size(); j++)
				{
					enemy_attacked_dog.at(i)->hp--;
				}

				//�ҷ�ѡ��̹�˽���fireAnimation
				for (int i = 0; i < vec_chosed_tank.size(); i++)
				{
					enemy_attacked_dog.at(i)->hp--;
					enemy_attacked_dog.at(i)->hp--;
				}
				//����Ѫ�۲���
				timm->setPercentage((500 - enemy_attacked_dog.at(i)->hp) / 5);
				//timm->setPercentage(timm->getPercentage() + 0.1);
			}



		for (int i = 0; i < enemy_attacked_tank.size(); i++)
			if (enemy_attacked_tank.at(i)->attacked && (count % 6 == 0))
			{
				//�ҷ�ѡ��ʿ������fireAnimation
				for (int j = 0; j < vec_chosed_soldier.size(); j++)
				{
					enemy_attacked_tank.at(i)->hp--;
				}

				//�ҷ�ѡ��̹�˽���fireAnimation
				for (int i = 0; i < vec_chosed_tank.size(); i++)
				{
					enemy_attacked_tank.at(i)->hp--;
					enemy_attacked_tank.at(i)->hp--;
				}
				//����Ѫ�۲���
				timm->setPercentage((500 - enemy_attacked_tank.at(i)->hp) / 5);
				//timm->setPercentage(timm->getPercentage() + 0.1);
			}

		for (int i = 0; i < enemy_attacked_soldier.size(); i++)
			if (enemy_attacked_soldier.at(i)->attacked && (count % 6 == 0))
			{
				//�ҷ�ѡ��ʿ������fireAnimation
				for (int j = 0; j < vec_chosed_soldier.size(); j++)
				{
					enemy_attacked_soldier.at(i)->hp--;
				}

				//�ҷ�ѡ��̹�˽���fireAnimation
				for (int i = 0; i < vec_chosed_tank.size(); i++)
				{
					enemy_attacked_soldier.at(i)->hp--;
					enemy_attacked_soldier.at(i)->hp--;
				}
				//����Ѫ�۲���
				timm->setPercentage((500 - enemy_attacked_soldier.at(i)->hp) / 5);
				//timm->setPercentage(timm->getPercentage() + 0.1);
			}
	}

	//�жϵо��Ƿ�over��if��over����thenֹͣfireAnimation������о�
	for (int i = 0; i < enemy_attacked_soldier.size(); i++)
	{
		if (enemy_attacked_soldier.at(i)->hp < 0 && enemy_attacked_soldier.at(i)->attacked == true) {
			enemy_attacked_soldier.at(i)->attacked = false;
			Vec2 Pos = enemy_attacked_soldier.at(i)->getPosition();
			explodeGIF(Pos);
			explodetime = 40;

			for (int j = 0; j < vec_chosed_soldier.size(); j++)
			{
				_player = vec_chosed_soldier.at(j);
				_player->idle();
			}

			for (int i = 0; i < vec_chosed_tank.size(); i++)
			{
				tank = vec_chosed_tank.at(i);
				tank->idle();
			}

			enemy_attacked_soldier.at(i)->removeFromParent();
			timm->removeFromParent();
			blood->removeFromParent();

			enemy_attacked_soldier.at(i)->setPosition(NULL, NULL);

		}
	}

	for (int i = 0; i < enemy_attacked_tank.size(); i++)
	{
		if (enemy_attacked_tank.at(i)->hp < 0 && enemy_attacked_tank.at(i)->attacked == true) {
			enemy_attacked_tank.at(i)->attacked = false;
			Vec2 Pos = enemy_attacked_tank.at(i)->getPosition();
			explodeGIF(Pos);
			explodetime = 40;


			for (int j = 0; j < vec_chosed_soldier.size(); j++)
			{
				_player = vec_chosed_soldier.at(j);
				_player->idle();
			}

			for (int i = 0; i < vec_chosed_tank.size(); i++)
			{
				tank = vec_chosed_tank.at(i);
				tank->idle();
			}

			enemy_attacked_tank.at(i)->setPosition(NULL, NULL);
			enemy_attacked_tank.at(i)->removeFromParent();
			timm->removeFromParent();
			blood->removeFromParent();

			

		}
	}


	//�Եз�ѡ�н������й���
	for (int i = 0; i < enemy_attacked_building.size(); i++)
		if (if_attacked && count % 6 == 0)
		{
			//�ҷ�ѡ��ʿ������fire
			for (int j = 0; j < vec_chosed_soldier.size(); j++)
			{
				hp[i]--;
			}

			//�ҷ�ѡ��̹�˽���fire
			for (int j = 0; j < vec_chosed_tank.size(); j++)
			{
				hp[i]--;
				hp[i]--;
			}
			//����Ѫ�۲���
			timm->setPercentage((500 - hp[i]) / 5);


			//�жϽ����Ƿ񱻴ݻ�
			if (hp[i] < 0)
			{
				if_attacked = false;

				Vec2 Pos = enemy_attacked_building.at(i)->getPosition();
				explodeGIF(Pos);
				explodetime = 40;

				for (int j = 0; j < vec_chosed_soldier.size(); j++)
				{
					_player = vec_chosed_soldier.at(j);
					_player->idle();
				}

				for (int i1 = 0; i1 < vec_chosed_tank.size(); i1++)
				{
					tank = vec_chosed_tank.at(i1);
					tank->idle();
					log("tank idle");
				}

				hp[i] = 500;
				Vec2 attackedpos = enemy_attacked_building.at(i)->getPosition();
				write(player, "kill", attackedpos.x + abs(_tileMap->getPositionX()) , attackedpos.y + abs(_tileMap->getPositionY()));

				
				enemy_attacked_building.at(i)->setPosition(NULL, NULL);
				enemy_attacked_building.at(i)->removeFromParent();
				enemy_attacked_building.clear();
				timm->removeFromParent();
				blood->removeFromParent();
				
			}
	
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
			//setViewpointCenter(_player->getPosition());
		}
	}
	//�жϵз�ѡ��ʿ���Ƿ񵽴�ָ��λ��
	if (enemy_chosed_soldier.size())
	{
		for (int j = 0; j < enemy_chosed_soldier.size(); j++)
		{
			_player = enemy_chosed_soldier.at(j);
			Vec2 playerPos = _player->getPosition();
			if (playerPos.x == (a__ + j * 50))
			{
				_player->idle();
			}
			//setViewpointCenter(_player->getPosition());
		}
	}



	//��ʱ������
	if (iftobuild == 2)
	{
		float cu = progress1->getPercentage();  //��ȡ�ٷֱ�     
		cu = cu + 1.0f;  //���������� ÿ�μ�1%      
		progress1->setPercentage(cu);

		if (cu <= 100)    //�������С�ڵ���100%  
		{
			auto str1 = String::createWithFormat("%.2f%%", cu);
		}
		//����������ﵽ100%����ֹͣ
	}


	if (iftocreatemenu) {

		//̹�˱��˵�
		int iftobuild = 1;
		createTank = tankbing::create();
		createTank->setPosition(Vec2(665, 100));
		this->addChild(createTank,101);

		//̹�˽����˵�
		createTankbingying = tankgongchang::create();
		createTankbingying->setPosition(Vec2(670, 428));
		this->addChild(createTankbingying,101);

		//��Ӫ�����˵�
		createbingying = bubinggongchang::create();
		createbingying->setPosition(Vec2(750, 428));
		this->addChild(createbingying,101);

		//���糧�����˵�
		createfadianchang = fadianchang::create();
		createfadianchang->setPosition(Vec2(670, 360));
		this->addChild(createfadianchang,101);

		//ʯ�ͳ������˵�
		createshiyouchang = shiyouchang::create();
		createshiyouchang->setPosition(Vec2(750, 360));
		this->addChild(createshiyouchang,101);

		//�����˵�
		createbubing = bubing::create();
		createbubing->setPosition(Vec2(665, 180));
		this->addChild(createbubing,101);

		//��Ȯ�˵�
		createjingquan = jingquan::create();
		createjingquan->setPosition(Vec2(750, 180));
		this->addChild(createjingquan,101);
		iftocreatemenu = false;
	}


}



//������ʼ
bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	//log("onTouchBegan");
	mouseDownPosition = touch->getLocation();
	return true;
}
//�����ƶ�
void GameScene::onTouchMoved(Touch *touch, Event *event)
{
	//log("onTouchMoved");
}
//����ֹͣ
void GameScene::onTouchEnded(Touch *touch, Event *event)
{
	EventMouse* e = (EventMouse*)event;

//	log("onTouchEnded");
	//���OpenGL����
	mouseUpPosition = touch->getLocation();
	log("mouseUpPosition (%f ,%f) ", mouseUpPosition.x, mouseUpPosition.y);

	if (mouseUpPosition.x > 589)
		canmove = false;
	else
		canmove = true;


	//̹�˹����˵�
	if ((650 < mouseDownPosition.x) && (mouseDownPosition.x < 700) && (400 < mouseDownPosition.y) && (mouseDownPosition.y < 460) && iftobuild == 1)
	{
		iftobuild = 2;
		//����һ����ɫ��CD��ʱ
		white = whitecd::create();
		white->setPosition(Vec2(670, 428));
		this->addChild(white, 101);

		//����һ������������ 
		auto *sp = Sprite::create("menu/redalert0.01.png");
		progress1 = ProgressTimer::create(sp);
		progress1->setType(kCCProgressTimerTypeRadial);
		progress1->setPosition(Vec2(670, 428));
		//���ȶ����˶����򣬿��Զ��Լ���ֵ������Ч��  
		progress1->setMidpoint(Vec2(0.5, 0.5));
		//��������߱仯  
		progress1->setReverseProgress(false); //˳ʱ��
		progress1->setPercentage(0); //���ý������ٷֱ�Ϊ0%     
		this->addChild(progress1, 101);
	}
	else {
		if ((650 < mouseDownPosition.x) && (mouseDownPosition.x < 700) && (400 < mouseDownPosition.y) && (mouseDownPosition.y < 460) && iftobuild == 2)
		{
			addbuilding = true;
			bingyingPosition.x = mouseUpPosition.x;
			bingyingPosition.y = mouseUpPosition.y;
			iftobuild = 1;
			white->removeFromParent();
			progress1->removeFromParent();
			Sprite *bingying = Sprite::create("menu/Chariot.png");
			bingying->setPosition(Vec2(mouseUpPosition.x, mouseUpPosition.y));
			this->addChild(bingying, 1);
			//
			(player, "tankchang", mouseUpPosition.x, mouseUpPosition.y);
			write(player, "tankchang", mouseUpPosition.x + abs(_tileMap->getPositionX()), mouseUpPosition.y + abs(_tileMap->getPositionY()));
			building_vec.pushBack(bingying);

		}
	}

	//̹�˲˵�
	if ((640 < mouseDownPosition.x) && (mouseDownPosition.x < 700) && (80 < mouseDownPosition.y) && (mouseDownPosition.y < 140) && iftobuild == 1)
	{
		iftobuild = 2;

		//����һ����ɫ��CD��ʱ
		white = whitecd::create();
		white->setPosition(Vec2(665, 100));
		this->addChild(white, 101);
		//����һ������������ 

		auto *sp = Sprite::create("menu/tankmenu.png");
		progress1 = ProgressTimer::create(sp);
		progress1->setType(kCCProgressTimerTypeRadial);
		progress1->setPosition(Vec2(665, 100));
		//���ȶ����˶����򣬿��Զ��Լ���ֵ������Ч��  
		progress1->setMidpoint(Vec2(0.5, 0.5));
		//��������߱仯  
		progress1->setReverseProgress(false); //˳ʱ��
		progress1->setPercentage(0); //���ý������ٷֱ�Ϊ0%     
		this->addChild(progress1, 101);
	}
	else {
		if ((640 < mouseDownPosition.x) && (mouseDownPosition.x < 700) && (80 < mouseDownPosition.y) && (mouseDownPosition.y < 140) && iftobuild == 2)
		{
			iftobuild = 1;
			progress1->removeFromParent();
			white->removeFromParent();
			newtank();
			write(player, "tank", bingyingPosition.x + abs(_tileMap->getPositionX()), bingyingPosition.y + abs(_tileMap->getPositionY()));
			log("create tank  pos %f  %f ", bingyingPosition.x, bingyingPosition.y);
		}
	}

	//���������˵�
	if ((720 < mouseDownPosition.x) && (mouseDownPosition.x < 780) && (400 < mouseDownPosition.y) && (mouseDownPosition.y < 450) && iftobuild == 1)
	{
		iftobuild = 2;
		//����һ����ɫ��CD��ʱ
		white = whitecd::create();
		white->setPosition(Vec2(750, 428));
		this->addChild(white, 101);

		//����һ������������ 
		auto *sp = Sprite::create("menu/bingying2.png");
		progress1 = ProgressTimer::create(sp);
		progress1->setType(kCCProgressTimerTypeRadial);
		progress1->setPosition(Vec2(750, 428));
		//���ȶ����˶����򣬿��Զ��Լ���ֵ������Ч��  
		progress1->setMidpoint(Vec2(0.5, 0.5));
		//��������߱仯  
		progress1->setReverseProgress(false); //˳ʱ��
		progress1->setPercentage(0); //���ý������ٷֱ�Ϊ0%     
		this->addChild(progress1, 101);
	}
	else {
		if ((720 < mouseDownPosition.x) && (mouseDownPosition.x < 780) && (400 < mouseDownPosition.y) && (mouseDownPosition.y < 450) && iftobuild == 2)
		{
			addbuilding = true;
			soldierbingyingPosition.x = mouseUpPosition.x;
			soldierbingyingPosition.y = mouseUpPosition.y;
			iftobuild = 1;
			white->removeFromParent();
			progress1->removeFromParent();
			Sprite *bingying = Sprite::create("menu/Barracks.png");
			bingying->setPosition(Vec2(mouseUpPosition.x, mouseUpPosition.y));
			this->addChild(bingying, 1);
			write(player, "bingying", mouseUpPosition.x + abs(_tileMap->getPositionX()), mouseUpPosition.y + abs(_tileMap->getPositionY()));
			building_vec.pushBack(bingying);

		}
	}

	//�����˵�
	if ((640 < mouseDownPosition.x) && (mouseDownPosition.x < 700) && (160 < mouseDownPosition.y) && (mouseDownPosition.y < 210) && iftobuild == 1)
	{
		iftobuild = 2;

		//����һ����ɫ��CD��ʱ
		white = whitecd::create();
		white->setPosition(Vec2(665, 180));
		this->addChild(white, 101);
		//����һ������������ 

		auto *sp = Sprite::create("menu/soldier2.png");
		progress1 = ProgressTimer::create(sp);
		progress1->setType(kCCProgressTimerTypeRadial);
		progress1->setPosition(Vec2(665, 180));
		//���ȶ����˶����򣬿��Զ��Լ���ֵ������Ч��  
		progress1->setMidpoint(Vec2(0.5, 0.5));
		//��������߱仯  
		progress1->setReverseProgress(false); //˳ʱ��
		progress1->setPercentage(0); //���ý������ٷֱ�Ϊ0%     
		this->addChild(progress1, 101);
	}
	else {
		if ((640 < mouseDownPosition.x) && (mouseDownPosition.x < 700) && (140 < mouseDownPosition.y) && (mouseDownPosition.y < 210) && iftobuild == 2)
		{
			iftobuild = 1;
			progress1->removeFromParent();
			white->removeFromParent();
			newsoldier();
			write(player, "soldier", soldierbingyingPosition.x + abs(_tileMap->getPositionX()), soldierbingyingPosition.y + abs(_tileMap->getPositionY()));
			log("create soldier pos : %f %f ", soldierbingyingPosition.x, soldierbingyingPosition.y);
		}
	}

	//��Ȯ�˵�
	if ((710 < mouseDownPosition.x) && (mouseDownPosition.x < 780) && (140 < mouseDownPosition.y) && (mouseDownPosition.y < 210) && iftobuild == 1)
	{
		iftobuild = 2;

		//����һ����ɫ��CD��ʱ
		white = whitecd::create();
		white->setPosition(Vec2(750, 180));
		this->addChild(white, 101);
		//����һ������������ 

		auto *sp = Sprite::create("menu/policeDog2.png");
		progress1 = ProgressTimer::create(sp);
		progress1->setType(kCCProgressTimerTypeRadial);
		progress1->setPosition(Vec2(750, 180));
		//���ȶ����˶����򣬿��Զ��Լ���ֵ������Ч��  
		progress1->setMidpoint(Vec2(0.5, 0.5));
		//��������߱仯  
		progress1->setReverseProgress(false); //˳ʱ��
		progress1->setPercentage(0); //���ý������ٷֱ�Ϊ0%     
		this->addChild(progress1, 101);
	}
	else {
		if ((710 < mouseDownPosition.x) && (mouseDownPosition.x < 780) && (140 < mouseDownPosition.y) && (mouseDownPosition.y < 210) && iftobuild == 2)
		{
			iftobuild = 1;
			progress1->removeFromParent();
			white->removeFromParent();
			newdog();
			write(player, "dog", soldierbingyingPosition.x + abs(_tileMap->getPositionX()), soldierbingyingPosition.y + abs(_tileMap->getPositionY()));
		}
	}


	//���糧�˵�
	if ((650 < mouseDownPosition.x) && (mouseDownPosition.x < 710) && (320 < mouseDownPosition.y) && (mouseDownPosition.y < 400) && iftobuild == 1)
	{
		iftobuild = 2;
		//����һ����ɫ��CD��ʱ
		white = whitecd::create();
		white->setPosition(Vec2(670, 360));
		this->addChild(white, 101);

		//����һ������������ 
		auto *sp = Sprite::create("menu/dianchang2.png");
		progress1 = ProgressTimer::create(sp);
		progress1->setType(kCCProgressTimerTypeRadial);
		progress1->setPosition(Vec2(670, 360));
		//���ȶ����˶����򣬿��Զ��Լ���ֵ������Ч��  
		progress1->setMidpoint(Vec2(0.5, 0.5));
		//��������߱仯  
		progress1->setReverseProgress(false); //˳ʱ��
		progress1->setPercentage(0); //���ý������ٷֱ�Ϊ0%     
		this->addChild(progress1, 101);
	}
	else {
		if ((650 < mouseDownPosition.x) && (mouseDownPosition.x < 710) && (320 < mouseDownPosition.y) && (mouseDownPosition.y < 400) && iftobuild == 2)
		{
			addbuilding = true;
			iftobuild = 1;
			white->removeFromParent();
			progress1->removeFromParent();
			Sprite *bingying = Sprite::create("menu/powerplant1.png");
			bingying->setPosition(Vec2(mouseUpPosition.x, mouseUpPosition.y));
			this->addChild(bingying, 1);
			write(player, "dianchang", mouseUpPosition.x + abs(_tileMap->getPositionX()), mouseUpPosition.y + abs(_tileMap->getPositionY()));
			building_vec.pushBack(bingying);

		}
	}

	//ʯ�ͳ��˵�
	if ((710 < mouseDownPosition.x) && (mouseDownPosition.x < 780) && (320 < mouseDownPosition.y) && (mouseDownPosition.y < 400) && iftobuild == 1)
	{
		iftobuild = 2;
		//����һ����ɫ��CD��ʱ
		white = whitecd::create();
		white->setPosition(Vec2(750, 360));
		this->addChild(white, 101);

		//����һ������������ 
		auto *sp = Sprite::create("menu/redalert0.3.png");
		progress1 = ProgressTimer::create(sp);
		progress1->setType(kCCProgressTimerTypeRadial);
		progress1->setPosition(Vec2(750, 360));
		//���ȶ����˶����򣬿��Զ��Լ���ֵ������Ч��  
		progress1->setMidpoint(Vec2(0.5, 0.5));
		//��������߱仯  
		progress1->setReverseProgress(false); //˳ʱ��
		progress1->setPercentage(0); //���ý������ٷֱ�Ϊ0%     
		this->addChild(progress1, 101);
	}
	else {
		if ((710 < mouseDownPosition.x) && (mouseDownPosition.x < 780) && (320 < mouseDownPosition.y) && (mouseDownPosition.y < 400) && iftobuild == 2)
		{
			addbuilding = true;
			iftobuild = 1;
			white->removeFromParent();
			progress1->removeFromParent();
			Sprite *bingying = Sprite::create("menu/test.png");
			bingying->setPosition(Vec2(mouseUpPosition.x, mouseUpPosition.y));
			this->addChild(bingying, 1);
			write(player, "kuang", mouseUpPosition.x + abs(_tileMap->getPositionX()), mouseUpPosition.y + abs(_tileMap->getPositionY()));
			building_vec.pushBack(bingying);


		}
	}


	//������º��ɿ���������ͬһ��λ��
	if (sqrt(pow((mouseUpPosition.x - mouseDownPosition.x), 2) + pow((mouseUpPosition.y - mouseDownPosition.y), 2)) <= 5)
	{

		float rectX = mouseDownPosition.x;
		float rectY = mouseDownPosition.y;
		Rect mouseRect(rectX - 20 , rectY - 20 , 40, 40);

		attack_enemy = false;
		
		 //log("���͵���λ����Ϣ");

		//�����з�����
		if (vec_chosed_soldier.size() || vec_chosed_tank.size() || vec_chosed_dog.size())
			if (enemy_base->getBoundingBox().intersectsRect(mouseRect)) {
				base_blood(enemy_base->getPosition());
				log("enemy_base->getPosition: %f %f  ", enemy_base->getPositionX(), enemy_base->getPositionY());
				attack_base = true;
				log("ATTACK ENEMY BASE SUCCESS");
				for (int j = 0; j < vec_chosed_soldier.size(); j++)
				{
					_player = vec_chosed_soldier.at(j);
					_player->fireAnimation();
				
				}

				//�ҷ�ѡ��̹�˽���fire
				for (int j = 0; j < vec_chosed_tank.size(); j++)
				{
					tank = vec_chosed_tank.at(j);
					tank->fireAnimation();
				
				}
			}


		//�Ƿ������� 
		if (base->getBoundingBox().intersectsRect(mouseRect) && buildbase) {
			base->buildingAnimation();
			//base_blood(enemy_base->getPosition());
				
			iftocreatemenu = true;
			buildbase = false;
			write(player,"base", 1.0f, 1.0f);
		}
		
		//�ж������λ���Ƿ��ео�����
		if( enemy_building.size() ) {
			for (int i = 0; i < enemy_building.size(); i++)
			{
				//mouseRect.containsPoint(enemy_building.at(i)->getPosition());
				if (enemy_building.at(i)->getBoundingBox().intersectsRect(mouseRect))
				{
					attack_enemy = true;
					log("there is a building");
					write(player, "attackedB", enemy_building.at(i)->getPositionX() + abs(_tileMap->getPositionX()), 
						enemy_building.at(i)->getPositionY() + abs(_tileMap->getPositionY()));
					enemy_attacked_building.pushBack(enemy_building.at(i));
					if_attacked = true;
					blood_reservoir(enemy_building.at(i)->getPosition());

					for (int i = 0; i < vec_chosed_tank.size(); i++)
					{
						tank = vec_chosed_tank.at(i);
						tank->fireAnimation();
					}
					for (int i = 0; i < vec_chosed_soldier.size(); i++)
					{
						_player = vec_chosed_soldier.at(i);
						_player->fireAnimation();
					}
				}
			}
		}
		

		//�ж�����λ���Ƿ��ео�
		if (vec_chosed_soldier.size() || vec_chosed_tank.size() || vec_chosed_dog.size())
		{
			if(canmove)
				movedog();
			
			for (int i = 0; i < enemy_policeDog.size(); i++)
			{
				
				if (enemy_policeDog.at(i)->getBoundingBox().intersectsRect(mouseRect))
				{
					attack_enemy = true;
					enemy_policeDog.at(i)->attacked = true;

					enemy_attacked_dog.pushBack(enemy_policeDog.at(i));
					blood_reservoir(enemy_policeDog.at(i)->getPosition());
					//log("attck success");
					for (int i = 0; i < vec_chosed_tank.size(); i++)
					{
						tank = vec_chosed_tank.at(i);
						tank->fireAnimation();
					}
					for (int i = 0; i < vec_chosed_soldier.size(); i++)
					{
						_player = vec_chosed_soldier.at(i);
						_player->fireAnimation();
					}

				}
			}

			for (int i = 0; i < enemy_tank_vec.size(); i++)
			{
				if (enemy_tank_vec.at(i)->getBoundingBox().intersectsRect(mouseRect))
				{
					attack_enemy = true;
					enemy_tank_vec.at(i)->attacked = true;
					enemy_attacked_tank.pushBack(enemy_tank_vec.at(i));
					blood_reservoir(enemy_tank_vec.at(i)->getPosition());
					//log("attck success");
					for (int i = 0; i < vec_chosed_tank.size(); i++)
					{
						tank = vec_chosed_tank.at(i);
						tank->fireAnimation();
					}
					for (int i = 0; i < vec_chosed_soldier.size(); i++)
					{
						_player = vec_chosed_soldier.at(i);
						_player->fireAnimation();
					}
				}
			}

			for (int i = 0; i < enemy_soldier_vec.size(); i++)
			{
				if (enemy_soldier_vec.at(i)->getBoundingBox().intersectsRect(mouseRect))
				{
					attack_enemy = true;
					enemy_soldier_vec.at(i)->attacked = true;
					enemy_attacked_soldier.pushBack(enemy_soldier_vec.at(i));
					blood_reservoir(enemy_soldier_vec.at(i)->getPosition());//���޸�
					//log("attck success");
					for (int i = 0; i < vec_chosed_tank.size(); i++)
					{
						tank = vec_chosed_tank.at(i);
						tank->fireAnimation();
					}
					for (int i = 0; i < vec_chosed_soldier.size(); i++)
					{
						_player = vec_chosed_soldier.at(i);
						_player->fireAnimation();
					}
				}
			}
		}
		
		//if (enemy_attacked_building.size() ==0  && enemy_attacked_dog.size() == 0 
		//&& enemy_attacked_tank.size() == 0 && enemy_attacked_soldier.size() == 0 && canmove)
		if(!attack_enemy && rectX< 590)
		{
			movetank();
			movesoldier();
		}
		if(iftocreatemenu == false)
			if (rectX < 590)
			{
				write(player, rectX + abs(_tileMap->getPositionX()), rectY + abs(_tileMap->getPositionY()));
				log("danji");
			}
				

	}
	else//�����ɿ�����ͬһλ�ã�����ѡ��
	{
		if (addbuilding == false)
		{
			//������껭�ķ���rect
			float rectX = mouseDownPosition.x < mouseUpPosition.x ? mouseDownPosition.x : mouseUpPosition.x;
			float rectY = mouseDownPosition.y < mouseUpPosition.y ? mouseDownPosition.y : mouseUpPosition.y;
			Rect mouseRect(rectX, rectY, abs(mouseDownPosition.x - mouseUpPosition.x), abs(mouseDownPosition.y - mouseUpPosition.y));


		//	write(player,mouseDownPosition.x + abs(_tileMap->getPositionX()), mouseDownPosition.y + abs(_tileMap->getPositionY()),
			//	mouseUpPosition.x + abs(_tileMap->getPositionX()), mouseUpPosition.y + abs(_tileMap->getPositionY()));
			write(player, mouseDownPosition.x, mouseDownPosition.y,
				mouseUpPosition.x, mouseUpPosition.y );
			log("select area");

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
					//log("slect success");
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
	addbuilding = false;
}



//blood resevoir����Ѫ�ۼ��䶯��
void GameScene::blood_reservoir( Vec2 enemyPos)
{
	auto s = Sprite::create("blood/bloodReservoir1.png");
	s->setAnchorPoint(Vec2(0.5, 0));

	//s->setPosition(Vec2(mouseUpPosition.x, mouseUpPosition.y + 50));
	s->setPosition(Vec2(enemyPos.x, enemyPos.y + 50));
	addChild(s);
	blood = s;

	CCSprite *sp = CCSprite::create("blood/bloodReservoir2.png");
	timm = CCProgressTimer::create(sp);//����CCProgressTimer

	timm->setAnchorPoint(Vec2(0.5, 0));
	timm->setPosition(Vec2(enemyPos.x, enemyPos.y + 50));
	//timm->setPosition(mouseUpPosition.x, mouseUpPosition.y + 50);//����CCProgressTimerλ��
	timm->setType(kCCProgressTimerTypeBar);//��������
	timm->setPercentage(0);//���õ�ǰ��ʼֵ
	timm->setMidpoint(CCPoint(1, 0));//���ý��ȿ�ʼ��λ��
	timm->setBarChangeRate(CCPoint(1, 0));//���ý�����ռ����
	addChild(timm);//��ӵ� layer
}



//blood resevoir��������Ѫ�ۼ��䶯��
void GameScene::base_blood(Vec2 basePos)
{
	auto s = Sprite::create("blood/bloodReservoir1.png");
	s->setAnchorPoint(Vec2(0.5, 0.5));
	log("CREATE BLOOD SUCCESS");
	
	s->setPosition(Vec2(basePos.x -100, basePos.y - 30));
	base->addChild(s);
	baseblood = s;

	CCSprite *sp = CCSprite::create("blood/bloodReservoir2.png");
	base_timm = CCProgressTimer::create(sp);//����CCProgressTimer

	base_timm->setAnchorPoint(Vec2(0.5, 0.5));
	base_timm->setPosition(Vec2(basePos.x -100, basePos.y -30));
	base_timm->setType(kCCProgressTimerTypeBar);//��������
	base_timm->setPercentage(0);//���õ�ǰ��ʼֵ
	base_timm->setMidpoint(CCPoint(1, 0));//���ý��ȿ�ʼ��λ��
	base_timm->setBarChangeRate(CCPoint(1, 0));//���ý�����ռ����
	base->addChild(base_timm);//��ӵ� layer
}

//��ը����
void GameScene::explodeGIF(Vec2 Pos) {
	explode = Explode::create();
	explode->setPosition(Pos.x, Pos.y);
	addChild(explode);
	explode->explodeAnimation();
}

//newtank
void GameScene::newtank() {
	int i = tank_vec.size();
	tank = Tank::create();
	tank->setPosition(bingyingPosition.x + 80 + i * 80, bingyingPosition.y);
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
			pd->runAction(MoveTo::create(v, Vec2(diff.x, diff.y + j * 75))); 
		else {
			if (j % 2)
				pd->runAction(MoveTo::create(v, Vec2(mouseUpPosition.x, mouseUpPosition.y + j * 50)));
			else
				pd->runAction(MoveTo::create(v, Vec2(mouseUpPosition.x, mouseUpPosition.y - j * 50)));

		}
	}

}

//new police dog
void GameScene::newdog() {
	dog = Dog::create();
	int i = policeDog.size(); 
	dog->setPosition(soldierbingyingPosition.x, soldierbingyingPosition.y  + 40 + i * 20);
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

		bm->runAction(MoveTo::create(v, Vec2(mouseUpPosition.x + j * 40 , mouseUpPosition.y)));
	}


}

//new soldier
void GameScene::newsoldier() {
	//add soldier
	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("soldier");

	//float x = spawnPoint["x"].asFloat();
	//float y = spawnPoint["y"].asFloat();

	_player = Soldier::create();
	int i = soldier_vec.size();
	//_player->setPosition(Vec2(x + 200 + i * 30, y + 200));
	_player->setPosition(Vec2(soldierbingyingPosition.x + i * 30, soldierbingyingPosition.y - 100));
	addChild(_player);
	soldier_vec.pushBack(_player);
}

//move soldier
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

		_player->runAction(MoveTo::create(v, Vec2(mouseUpPosition.x + j * 50, mouseUpPosition.y)));
	}
}



//new enemy tank
void GameScene::newtank( float x, float y) {
	int i = enemy_tank_vec.size();
	tank = Tank::create();
	float opp_x = x + _tileMap->getPositionX();
	float opp_y = y + _tileMap->getPositionY();
	tank->setPosition(opp_x + 80 + i * 80, opp_y);
	addChild(tank);
	enemy_tank_vec.pushBack(tank);
	log("new enemy tank   %f %f",x ,y);
}

//move enemy tank
void GameScene::movetank( float x, float y)
{
	log("GameScene::movetank");
	Vec2 tankPos;
	Vec2 diff;
	float opp_x = x + _tileMap->getPositionX();
	float opp_y = y + _tileMap->getPositionY();
	for (int j = 0; j < enemy_chosed_tank.size(); j++)
	{
		auto pd = enemy_chosed_tank.at(j);

		tankPos = pd->getPosition();
		//diff = mouseUpPosition - tankPos;
		diff.x = opp_x - tankPos.x;
		diff.y = opp_y - tankPos.y;

		if (diff.x > 0)
			pd->isLeft = false;
		else
			pd->isLeft = true;

		pd->setScaleX(pd->isLeft ? 1 : -1);

		float v = sqrt(diff.x * diff.x + diff.y * diff.y) / 100;

		if (j == 1)
			pd->runAction(MoveTo::create(v, Vec2(opp_x, opp_y + j * 75)));
		else {
			if (j % 2)
				pd->runAction(MoveTo::create(v, Vec2(opp_x, opp_y + j * 50)));
			else
				pd->runAction(MoveTo::create(v, Vec2(opp_x, opp_y - j * 50)));

		}
		log("move success");
	}

}

//new enemy police dog
void GameScene::newdog(float x, float y) {
	float opp_x = x + _tileMap->getPositionX();
	float opp_y = y + _tileMap->getPositionY();
	dog = Dog::create();
	int i = enemy_policeDog.size();
	dog->setPosition(opp_x , opp_y + 40 + i * 20);
	addChild(dog);
	enemy_policeDog.pushBack(dog);
}

//move enemy police dog
void GameScene::movedog(float x, float y)
{
	Vec2 dogPos;
	Vec2 diff;
	float opp_x = x + _tileMap->getPositionX();
	float opp_y = y + _tileMap->getPositionY();

	for (int j = 0; j <enemy_chosed_dog.size(); j++)
	{
		auto bm = enemy_chosed_dog.at(j);

		dogPos = bm->getPosition();
		diff.x = opp_x - dogPos.x;
		diff.y = opp_y - dogPos.y;

		if (diff.x > 0) {
			bm->isLeft = false;
		}
		else
			bm->isLeft = true;

		bm->setScaleX(bm->isLeft ? 1 : -1);

		float v = sqrt(diff.x * diff.x + diff.y * diff.y) / 150;

		bm->runAction(MoveTo::create(v, Vec2(opp_x + j * 40, opp_y)));
	}


}
//�����з�ʿ��
void GameScene::newsoldier(float x, float y) {
	//add soldier
	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("soldier");


	float opp_x = x + _tileMap->getPositionX();
	float opp_y = y + _tileMap->getPositionY();

	_player = Soldier::create();
	int i = enemy_soldier_vec.size();
	_player->setPosition(Vec2(opp_x + i * 30, opp_y - 100 ));
	addChild(_player);
	enemy_soldier_vec.pushBack(_player);

	log("create soldier success");
}

//�ƶ��з�ʿ��
void GameScene::movesoldier(float x, float y)
{
	Vec2 playerPos;
	Vec2 diff;

	float opp_x = x + _tileMap->getPositionX();
	float opp_y = y + _tileMap->getPositionY();
	for (int j = 0; j < enemy_chosed_soldier.size(); j++)
	{
		_player = enemy_chosed_soldier.at(j);

		playerPos = _player->getPosition();
		diff.x = opp_x - playerPos.x;
		diff.y = opp_y - playerPos.y;

		if (diff.x > 0) {
			_player->isLeft = false;
		}
		else
			_player->isLeft = true;


		_player->setScaleX(_player->isLeft ? 1 : -1);

		_player->runAnimation();

		float v = sqrt(diff.x * diff.x + diff.y * diff.y) / 150;

		_player->runAction(MoveTo::create(v, Vec2(opp_x + j * 50, opp_y)));
		log("move soldier success");

	}
}

//�����з���굥��λ����Ϣ
void GameScene::enemyclick(float x, float y)
{
	float rectX = x + _tileMap->getPositionX();
	float rectY = y + _tileMap->getPositionY();
	
	Rect mouseRect(rectX - 100, rectY - 100, 200, 200);
	
	log("enemy click");
	if (enemy_chosed_soldier.size() || enemy_chosed_tank.size() || enemy_chosed_dog.size())
	{
		movedog(rectX, rectY);
		for (int i = 0; i <policeDog.size(); i++)
		{
			if (policeDog.at(i)->getBoundingBox().intersectsRect(mouseRect))
			{
				policeDog.at(i)->attacked = true;

				attacked_dog.pushBack(policeDog.at(i));
				//blood_reservoir(policeDog.at(i)->getPosition());
				//log("attck success");

				//��ʼfireAnimation()
				for (int i = 0; i < enemy_chosed_tank.size(); i++)
				{
					tank = enemy_chosed_tank.at(i);
					tank->fireAnimation();
				}
				for (int i = 0; i < enemy_chosed_soldier.size(); i++)
				{
					_player = enemy_chosed_soldier.at(i);
					_player->fireAnimation();
				}
			}
		}

		for (int i = 0; i < tank_vec.size(); i++)
		{
			if (tank_vec.at(i)->getBoundingBox().intersectsRect(mouseRect))
			{
				tank_vec.at(i)->attacked = true;
				attacked_tank.pushBack(tank_vec.at(i));
				//blood_reservoir(tank_vec.at(i)->getPosition());
				//log("attck success");

				//��ʼfireAnimation()
				for (int i = 0; i < enemy_chosed_tank.size(); i++)
				{
					tank = enemy_chosed_tank.at(i);
					tank->fireAnimation();
				}
				for (int i = 0; i < enemy_chosed_soldier.size(); i++)
				{
					_player = enemy_chosed_soldier.at(i);
					_player->fireAnimation();
				}
			}
		}

		for (int i = 0; i < soldier_vec.size(); i++)
		{
			if (soldier_vec.at(i)->getBoundingBox().intersectsRect(mouseRect))
			{
				soldier_vec.at(i)->attacked = true;
				attacked_soldier.pushBack(soldier_vec.at(i));
				//blood_reservoir(soldier_vec.at(i)->getPosition());//���޸�
				//log("attck success");

				//��ʼfireAnimation()
				for (int i = 0; i < enemy_chosed_tank.size(); i++)
				{
					tank = enemy_chosed_tank.at(i);
					tank->fireAnimation();
				}
				for (int i = 0; i < enemy_chosed_soldier.size(); i++)
				{
					_player = enemy_chosed_soldier.at(i);
					_player->fireAnimation();
				}
			}
		}

		if ((attacked_building == false) && (attacked_dog.size() == 0 ) && (attacked_tank.size() == 0 )&& (attacked_soldier.size() == 0))
		{
			movetank(rectX, rectY);
			movesoldier(rectX, rectY);
			log("enemy click : movetank");
		}
	}


}
//�����з�����ѡ������Ϣ
void GameScene::enemySelectArea(float dx, float dy, float ux, float uy)
{
	float rectX = dx < ux ? dx : ux;
	float rectY = dy < uy ? dy : uy;

	rectX = rectX + _tileMap->getPositionX();
	rectY = rectY + +_tileMap->getPositionY();
	Rect mouseRect(rectX, rectY, abs(dx - ux), abs(dy - uy));
	log("GameScene select area");

	//�ж�ѡ�еľ�Ȯ
	enemy_chosed_dog.clear();
	for (int i = 0; i < enemy_policeDog.size(); i++)
	{
		//�жϿ�ѡ����Щ
		if (enemy_policeDog.at(i)->getBoundingBox().intersectsRect(mouseRect))
		{
			Texture2D* textureYes = Director::getInstance()->getTextureCache()->addImage("CloseNormal.png");
			enemy_policeDog.at(i)->setTexture(textureYes);
			enemy_chosed_dog.pushBack(enemy_policeDog.at(i));
			//log("slect success");
		}
		else
		{
			Texture2D* textureNo = Director::getInstance()->getTextureCache()->addImage("CloseSelected.png");
			enemy_policeDog.at(i)->setTexture(textureNo);
		}
	}

	//�ж�ѡ�е�̹��
	enemy_chosed_tank.clear();
	for (int i = 0; i < enemy_tank_vec.size(); i++)
	{
		//�жϿ�ѡ����Щ
		if (enemy_tank_vec.at(i)->getBoundingBox().intersectsRect(mouseRect))
		{
			Texture2D* textureYes = Director::getInstance()->getTextureCache()->addImage("CloseNormal.png");
			enemy_tank_vec.at(i)->setTexture(textureYes);
			enemy_chosed_tank.pushBack(enemy_tank_vec.at(i));
			log("select tank success");
		}
		else
		{
			Texture2D* textureNo = Director::getInstance()->getTextureCache()->addImage("CloseSelected.png");
			enemy_tank_vec.at(i)->setTexture(textureNo);
		}
	}

	//�ж�ѡ�е�ʿ��
	enemy_chosed_soldier.clear();
	for (int i = 0; i < enemy_soldier_vec.size(); i++)
	{
		log("enemy_soldier_vec.size() %d ", i);
		//�жϿ�ѡ����Щ
		if (enemy_soldier_vec.at(i)->getBoundingBox().intersectsRect(mouseRect))
		{
			Texture2D* textureYes = Director::getInstance()->getTextureCache()->addImage("CloseNormal.png");
			enemy_soldier_vec.at(i)->setTexture(textureYes);
			enemy_chosed_soldier.pushBack(enemy_soldier_vec.at(i));
			log("kuangxuan soldier sucess");
		}
		else
		{
			Texture2D* textureNo = Director::getInstance()->getTextureCache()->addImage("CloseSelected.png");
			enemy_soldier_vec.at(i)->setTexture(textureNo);
		}
	}

}

void GameScene::new_enemy_chariot(float x, float y)
{
	float px = x + _tileMap->getPositionX();
	float py = y + _tileMap->getPositionY();

	Sprite *bingying = Sprite::create("menu/Chariot.png");
	bingying->setPosition(Vec2(px,py));
	this->addChild(bingying, 101);
	enemy_building.pushBack(bingying);
	
}
void GameScene::new_enemy_barracks(float x, float y)//��Ӫ
{
	float px = x + _tileMap->getPositionX();
	float py = y + _tileMap->getPositionY();

	Sprite *bingying = Sprite::create("menu/Barracks.png");
	bingying->setPosition(Vec2(px, py));
	this->addChild(bingying, 101);
	enemy_building.pushBack(bingying);
}
void GameScene::new_enemy_powerplant(float x, float y)//�糧
{
	float px = x + _tileMap->getPositionX();
	float py = y + _tileMap->getPositionY();

	Sprite *bingying = Sprite::create("menu/powerplant1.png");
	bingying->setPosition(Vec2(px, py));
	this->addChild(bingying, 101);
	enemy_building.pushBack(bingying);
	
}
void GameScene::new_enemy_kuangchang(float x, float y)//��
{
	float px = x + _tileMap->getPositionX();
	float py = y + _tileMap->getPositionY();

	Sprite *bingying = Sprite::create("menu/test.png");
	bingying->setPosition(Vec2(px, py));
	this->addChild(bingying, 101);
	enemy_building.pushBack(bingying);
}

void GameScene::cleanbuilding(float x, float y)
{
	attacked_building = false;
	float px = x + _tileMap->getPositionX();
	float py = y + _tileMap->getPositionY();

	for (int i = 0; i < building_vec.size(); i++)
	{
		log("clean building ");
		Vec2 position = building_vec.at(i)->getPosition();
		if (abs(position.x - px) < 50 && abs(position.y - py) < 50)
		{
			log("clean success ");
			explodeGIF(position);
			//auto delayTime = DelayTime::create(3.0f);
			explodetime = 40;
			//explode->removeFromParent();
			building_vec.at(i)->removeFromParent();
			building_vec.at(i)->setPosition(NULL, NULL);
		}

		for (int i = 0; i < attacked_tank.size(); i++) {
			explodeGIF(position);
			explodetime = 40;
			attacked_tank.at(i)->removeFromParent();
			attacked_tank.at(i)->setPosition(NULL, NULL);
		}
		for (int i = 0; i < attacked_soldier.size(); i++) {
			explodeGIF(position);
			explodetime = 40;
			attacked_soldier.at(i)->removeFromParent();
			attacked_soldier.at(i)->setPosition(NULL, NULL);
		}
		for (int i = 0; i < attacked_dog.size(); i++) {
			explodeGIF(position);
			explodetime = 40;
			attacked_dog.at(i)->removeFromParent();
			attacked_dog.at(i)->setPosition(NULL, NULL);
		}

		for (int i = 0; i < enemy_chosed_tank.size(); i++)
		{
			tank = enemy_chosed_tank.at(i);
			tank->idle();
		}
		for (int i = 0; i < enemy_chosed_soldier.size(); i++)
		{
			_player = enemy_chosed_soldier.at(i);
			_player->idle();
		}
	}
}



void GameScene::upAndDown_map(int j)    //�����Ƶ�ͼ�����־������ͼ��Ծ�ֹ��jΪ�������ƣ�������
{
	enemy_base->setPosition(enemy_base->getPositionX(), enemy_base->getPositionY() - j);//�̶��з�����
	base->setPosition(base->getPositionX(), base->getPositionY() - j);//�̶�����

	for (int i = 0; i < building_vec.size(); i++)//�̶�����
	{
		building_vec.at(i)->setPosition(building_vec.at(i)->getPositionX(), building_vec.at(i)->getPositionY() - j);
	}
	for (int i = 0; i < enemy_building.size(); i++)//�̶��з�����
	{
		enemy_building.at(i)->setPosition(enemy_building.at(i)->getPositionX(), enemy_building.at(i)->getPositionY() - j);
	}

	for (int i = 0; i < soldier_vec.size(); i++)//�̶�ʿ��
	{
		soldier_vec.at(i)->setPosition(soldier_vec.at(i)->getPositionX(), soldier_vec.at(i)->getPositionY() - j);
	}
	for (int i = 0; i < enemy_soldier_vec.size(); i++)//�̶��з�ʿ��
	{
		enemy_soldier_vec.at(i)->setPosition(enemy_soldier_vec.at(i)->getPositionX(), enemy_soldier_vec.at(i)->getPositionY() - j);
	}

	for (int i = 0; i < policeDog.size(); i++)//�̶���Ȯ
	{
		policeDog.at(i)->setPosition(policeDog.at(i)->getPositionX(), policeDog.at(i)->getPositionY() - j);
	}
	for (int i = 0; i < enemy_policeDog.size(); i++)//�̶��з���Ȯ
	{
		enemy_policeDog.at(i)->setPosition(enemy_policeDog.at(i)->getPositionX(), enemy_policeDog.at(i)->getPositionY() - j);
	}

	for (int i = 0; i < tank_vec.size(); i++)//�̶�̹��
	{
		tank_vec.at(i)->setPosition(tank_vec.at(i)->getPositionX(), tank_vec.at(i)->getPositionY() - j);
	}
	for (int i = 0; i <enemy_tank_vec.size(); i++)//�̶��з�̹��
	{
		enemy_tank_vec.at(i)->setPosition(enemy_tank_vec.at(i)->getPositionX(), enemy_tank_vec.at(i)->getPositionY() - j);
	}

	_tileMap->setPosition(_tileMap->getPositionX(), _tileMap->getPositionY() - j);
}



void GameScene::leftAndRight_map(int j)//�����ƶ���ͼ���̶������;��飬jΪ�������ƣ�������
{

	enemy_base->setPosition(enemy_base->getPositionX() + j, enemy_base->getPositionY());//�̶��з�����
	base->setPosition(base->getPositionX() + j, base->getPositionY());//�̶�����

	for (int i = 0; i < building_vec.size(); i++)//�̶�����
	{
		building_vec.at(i)->setPosition(building_vec.at(i)->getPositionX() + j, building_vec.at(i)->getPositionY());
	}
	for (int i = 0; i < enemy_building.size(); i++)//�̶��з�����
	{
		enemy_building.at(i)->setPosition(enemy_building.at(i)->getPositionX() + j, enemy_building.at(i)->getPositionY());
	}

	for (int i = 0; i < soldier_vec.size(); i++)//�̶�ʿ��
	{
		soldier_vec.at(i)->setPosition(soldier_vec.at(i)->getPositionX() + j, soldier_vec.at(i)->getPositionY());
	}
	for (int i = 0; i < enemy_soldier_vec.size(); i++)//�̶��з�ʿ��
	{
		enemy_soldier_vec.at(i)->setPosition(enemy_soldier_vec.at(i)->getPositionX() + j, enemy_soldier_vec.at(i)->getPositionY());
	}
	for (int i = 0; i < policeDog.size(); i++)//�̶���Ȯ
	{
		policeDog.at(i)->setPosition(policeDog.at(i)->getPositionX() + j, policeDog.at(i)->getPositionY());
	}
	for (int i = 0; i < enemy_policeDog.size(); i++)//�̶��з���Ȯ
	{
		enemy_policeDog.at(i)->setPosition(enemy_policeDog.at(i)->getPositionX() + j, enemy_policeDog.at(i)->getPositionY());
	}
	for (int i = 0; i < tank_vec.size(); i++)//�̶�̹��
	{
		tank_vec.at(i)->setPosition(tank_vec.at(i)->getPositionX() + j, tank_vec.at(i)->getPositionY());
	}
	for (int i = 0; i <enemy_tank_vec.size(); i++)//�̶��з�̹��
	{
		enemy_tank_vec.at(i)->setPosition(enemy_tank_vec.at(i)->getPositionX() + j, enemy_tank_vec.at(i)->getPositionY());
	}
	_tileMap->setPosition(_tileMap->getPositionX() + j, _tileMap->getPositionY());
}

void GameScene::onEnter()       //��Lamdaд�����¼�
{
	Layer::onEnter();
	log("GameScene onEnter");
	log("enemy_base->getPosition: %f %f  ", enemy_base->getPositionX(), enemy_base->getPositionY());
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		log("Key with keycode %d pressed", keyCode);
		if ((int)keyCode == 28 && _tileMap->getPositionY() - 64 >= -450)//���Ϸ����
		{
			log("enemy_base->getPosition: %f %f  ", enemy_base->getPositionX(), enemy_base->getPositionY());
			upAndDown_map(64);
		}
		else if ((int)keyCode == 29 && _tileMap->getPositionY() + 64 <= 35)//���·����
		{
			upAndDown_map(-64);
		}
		else if ((int)keyCode == 26 && _tileMap->getPositionX() + 100 <= 0)//�������
		{
			leftAndRight_map(100);
		}
		else if ((int)keyCode == 27 && _tileMap->getPositionX() - 100 >= -1000)//���ҷ����
		{
			log("enemy_base->getPosition: %f %f  ", enemy_base->getPositionX(), enemy_base->getPositionY());
			leftAndRight_map(-100);
		}
		else if ((int)keyCode == 59)//���¿ո��ӽǻص�����λ��
		{
			if (player == '1')
			{
				while ((_tileMap->getPositionX() <= -1 || _tileMap->getPositionY() <= 34))
				{
					if (_tileMap->getPositionY() + 1 <= 35)
					{
						upAndDown_map(-1);
					}
					if (_tileMap->getPositionX() + 1 <= 0)
					{
						leftAndRight_map(1);
					}
				}
			}
			//һ����Ƭ�Ŀ��Ϊ50��-1000Ϊ�ұ߽�xֵ��0,35�����£�-1000,35������
			//��-1000��-450��Ϊ���Ͻǣ���0��-450��Ϊ���Ͻ�
			else
			{
				while ((_tileMap->getPositionX() >= -999 || _tileMap->getPositionY() >= -449))
				{
					if (_tileMap->getPositionY() - 1 >= -450)
					{
						upAndDown_map(1);
					}
					if (_tileMap->getPositionX() - 1 >= -1000)
					{
						leftAndRight_map(-1);
					}
				}
			}
		}
	};

	listener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		log("Key with keycode %d released", keyCode);
	};

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


void GameScene::onExit()   //��������¼� 
{
	Layer::onExit();
	log("GameScene onExit");
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}
