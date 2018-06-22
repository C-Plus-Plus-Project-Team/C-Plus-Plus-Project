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

	
	count = 0;
	dogCount = 2;
	tankCount = 2;
	buildbase = true;
	enemy_buildbase = true;
	iftocreatemenu = false;
	addbuilding = false;


	setTouchEnabled(true);
	//����Ϊ���㴥��
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	
	//onEnter();
	//newtest();
	//blood_reservoir();

	if (player == '1') {
		base = Base::create();
		base->setPosition(100, 120);
		addChild(base);

		enemy_base = Base::create();
		enemy_base->setPosition(500, 500);
		addChild(enemy_base);
	}
	else
	{
		base = Base::create();
		base->setPosition(500, 500);
		addChild(base);

		enemy_base = Base::create();
		enemy_base->setPosition(100, 120);
		addChild(enemy_base);
	}
	
	

	scheduleUpdate();
//	thread_();

	//�˵������
	caidankuang1 = caidankuang::create();
	caidankuang1->setPosition(Vec2(700, 270));
	this->addChild(caidankuang1);

	

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

	//������յ�����Ϣ
	if (whether_read && p != player)
	{
		whether_read = false;
		if (ch_[0] == player)//�ƶ���Ϣ��������Ϣ
		{
			enemyclick(a__, b__);
		}
		else if (ch_[0] == '2')//��ѡ
		{
			enemySelectArea(a_, b_, c_, d_);
		}
		else if (ch_[0] == '3')//����������Ϣ
		{
			log("judge success");
			if (strcmp(msg, "tank") == 0)
			{
				newtank(j, k);
				log("%s", msg);
			}
			if (strcmp(msg, "dog") == 0) {
				newdog(j, k);
				log("%s", msg);
			}
			if (strcmp(msg, "soldier") == 0) {
				newsoldier(j, k);
				log("%s", msg);
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
					_player = vec_chosed_soldier.at(j);
					_player->fireAnimation();
					enemy_attacked_dog.at(i)->hp--;
				}

				//�ҷ�ѡ��̹�˽���fireAnimation
				for (int i = 0; i < vec_chosed_tank.size(); i++)
				{
					tank = vec_chosed_tank.at(i);
					tank->fireAnimation();
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
					_player = vec_chosed_soldier.at(j);
					_player->fireAnimation();
					enemy_attacked_tank.at(i)->hp--;
				}

				//�ҷ�ѡ��̹�˽���fireAnimation
				for (int i = 0; i < vec_chosed_tank.size(); i++)
				{
					tank = vec_chosed_tank.at(i);
					tank->fireAnimation();
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
					_player = vec_chosed_soldier.at(j);
					_player->fireAnimation();
					enemy_attacked_soldier.at(i)->hp--;
				}

				//�ҷ�ѡ��̹�˽���fireAnimation
				for (int i = 0; i < vec_chosed_tank.size(); i++)
				{
					tank = vec_chosed_tank.at(i);
					tank->fireAnimation();
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

			enemy_attacked_tank.at(i)->removeFromParent();
			timm->removeFromParent();
			blood->removeFromParent();

			enemy_attacked_tank.at(i)->setPosition(NULL, NULL);

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
		this->addChild(createTank);

		//̹�˽����˵�
		createTankbingying = tankgongchang::create();
		createTankbingying->setPosition(Vec2(670, 428));
		this->addChild(createTankbingying);

		//��Ӫ�����˵�
		createbingying = bubinggongchang::create();
		createbingying->setPosition(Vec2(750, 428));
		this->addChild(createbingying);

		//���糧�����˵�
		createfadianchang = fadianchang::create();
		createfadianchang->setPosition(Vec2(670, 360));
		this->addChild(createfadianchang);

		//ʯ�ͳ������˵�
		createshiyouchang = shiyouchang::create();
		createshiyouchang->setPosition(Vec2(750, 360));
		this->addChild(createshiyouchang);

		//�����˵�
		createbubing = bubing::create();
		createbubing->setPosition(Vec2(665, 180));
		this->addChild(createbubing);

		//��Ȯ�˵�
		createjingquan = jingquan::create();
		createjingquan->setPosition(Vec2(750, 180));
		this->addChild(createjingquan);
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
//	log("mouseUpPosition (%f ,%f) ", mouseUpPosition.x, mouseUpPosition.y);

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
		this->addChild(white);

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
		this->addChild(progress1, 1);
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
			write(player,"tankchang", mouseUpPosition.x, mouseUpPosition.y);
		}
	}

	//̹�˲˵�
	if ((640 < mouseDownPosition.x) && (mouseDownPosition.x < 700) && (80 < mouseDownPosition.y) && (mouseDownPosition.y < 140) && iftobuild == 1)
	{
		iftobuild = 2;

		//����һ����ɫ��CD��ʱ
		white = whitecd::create();
		white->setPosition(Vec2(665, 100));
		this->addChild(white);
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
		this->addChild(progress1, 1);
	}
	else {
		if ((640 < mouseDownPosition.x) && (mouseDownPosition.x < 700) && (80 < mouseDownPosition.y) && (mouseDownPosition.y < 140) && iftobuild == 2)
		{
			iftobuild = 1;
			progress1->removeFromParent();
			white->removeFromParent();
			newtank();
			write(player,"tank", bingyingPosition.x, bingyingPosition.y);
		}
	}

	//���������˵�
	if ((720 < mouseDownPosition.x) && (mouseDownPosition.x < 780) && (400 < mouseDownPosition.y) && (mouseDownPosition.y < 450) && iftobuild == 1)
	{
		iftobuild = 2;
		//����һ����ɫ��CD��ʱ
		white = whitecd::create();
		white->setPosition(Vec2(750, 428));
		this->addChild(white);

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
		this->addChild(progress1, 1);
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
			write(player,"bingying", mouseUpPosition.x, mouseUpPosition.y);
		}
	}

	//�����˵�
	if ((640 < mouseDownPosition.x) && (mouseDownPosition.x < 700) && (160 < mouseDownPosition.y) && (mouseDownPosition.y < 210) && iftobuild == 1)
	{
		iftobuild = 2;

		//����һ����ɫ��CD��ʱ
		white = whitecd::create();
		white->setPosition(Vec2(665, 180));
		this->addChild(white);
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
		this->addChild(progress1, 1);
	}
	else {
		if ((640 < mouseDownPosition.x) && (mouseDownPosition.x < 700) && (140 < mouseDownPosition.y) && (mouseDownPosition.y < 210) && iftobuild == 2)
		{
			iftobuild = 1;
			progress1->removeFromParent();
			white->removeFromParent();
			newsoldier();
			write(player,"soldier", soldierbingyingPosition.x, soldierbingyingPosition.y);
		}
	}

	//��Ȯ�˵�
	if ((710 < mouseDownPosition.x) && (mouseDownPosition.x < 780) && (140 < mouseDownPosition.y) && (mouseDownPosition.y < 210) && iftobuild == 1)
	{
		iftobuild = 2;

		//����һ����ɫ��CD��ʱ
		white = whitecd::create();
		white->setPosition(Vec2(750, 180));
		this->addChild(white);
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
		this->addChild(progress1, 1);
	}
	else {
		if ((710 < mouseDownPosition.x) && (mouseDownPosition.x < 780) && (120 < mouseDownPosition.y) && (mouseDownPosition.y < 180) && iftobuild == 2)
		{
			iftobuild = 1;
			progress1->removeFromParent();
			white->removeFromParent();
			newdog();
			write(player,"dog", soldierbingyingPosition.x, soldierbingyingPosition.y);
		}
	}


	//���糧�˵�
	if ((650 < mouseDownPosition.x) && (mouseDownPosition.x < 710) && (320 < mouseDownPosition.y) && (mouseDownPosition.y < 400) && iftobuild == 1)
	{
		iftobuild = 2;
		//����һ����ɫ��CD��ʱ
		white = whitecd::create();
		white->setPosition(Vec2(670, 360));
		this->addChild(white);

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
		this->addChild(progress1, 1);
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
			write(player,"dianchang", mouseUpPosition.x, mouseUpPosition.y);
		}
	}

	//ʯ�ͳ��˵�
	if ((710 < mouseDownPosition.x) && (mouseDownPosition.x < 780) && (320 < mouseDownPosition.y) && (mouseDownPosition.y < 400) && iftobuild == 1)
	{
		iftobuild = 2;
		//����һ����ɫ��CD��ʱ
		white = whitecd::create();
		white->setPosition(Vec2(750, 360));
		this->addChild(white);

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
		this->addChild(progress1, 1);
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
			write(player,"kuang", mouseUpPosition.x, mouseUpPosition.y);
		}
	}



	//������º��ɿ���������ͬһ��λ��
	if (sqrt(pow((mouseUpPosition.x - mouseDownPosition.x), 2) + pow((mouseUpPosition.y - mouseDownPosition.y), 2)) <= 5)
	{
		float rectX = mouseDownPosition.x;
		float rectY = mouseDownPosition.y;
		Rect mouseRect(rectX - 100 , rectY - 100 , 200, 200);

		//����
		write(player,rectX, rectY);
		 //log("���͵���λ����Ϣ");

		//�Ƿ������� 
		if (base->getBoundingBox().intersectsRect(mouseRect) && buildbase) {
			base->buildingAnimation();
			iftocreatemenu = true;
			buildbase = false;
			write(player,"base", 1.0f, 1.0f);
		}

		/*if (base->getBoundingBox().intersectsRect(mouseRect))
			write("tank", 500.0f, 200.0f);*/

		//�ж�����λ���Ƿ��ео�

		if (vec_chosed_soldier.size() || vec_chosed_tank.size() || vec_chosed_dog.size())
		{
			if(canmove)
				movedog();
			
			for (int i = 0; i < enemy_policeDog.size(); i++)
			{
				if (enemy_policeDog.at(i)->getBoundingBox().intersectsRect(mouseRect))
				{
					enemy_policeDog.at(i)->attacked = true;

					enemy_attacked_dog.pushBack(enemy_policeDog.at(i));
					blood_reservoir(enemy_policeDog.at(i)->getPosition());
					//log("attck success");
				}
			}

			for (int i = 0; i < enemy_tank_vec.size(); i++)
			{
				if (enemy_tank_vec.at(i)->getBoundingBox().intersectsRect(mouseRect))
				{
					enemy_tank_vec.at(i)->attacked = true;
					enemy_attacked_tank.pushBack(enemy_tank_vec.at(i));
					blood_reservoir(enemy_tank_vec.at(i)->getPosition());
					//log("attck success");
				}
			}

			for (int i = 0; i < enemy_soldier_vec.size(); i++)
			{
				if (enemy_soldier_vec.at(i)->getBoundingBox().intersectsRect(mouseRect))
				{
					enemy_soldier_vec.at(i)->attacked = true;
					enemy_attacked_soldier.pushBack(enemy_soldier_vec.at(i));
					blood_reservoir(enemy_soldier_vec.at(i)->getPosition());//���޸�
					//log("attck success");
				}
			}

			if (enemy_attacked_dog.size() == 0 && enemy_attacked_tank.size() == 0 && enemy_attacked_soldier.size() == 0 && canmove)
			{
				movetank();
				movesoldier();
			}

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


			write(player,mouseDownPosition.x, mouseDownPosition.y, mouseUpPosition.x, mouseUpPosition.y);
			//log("select area");

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
		//if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)//�����������
		//{
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
	addChild(_player, 2, 200);
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
	float opp_x = x;//���x���꣨δ�޸ģ�
	float opp_y = y;//���y���꣨δ�޸ģ�
	tank->setPosition(opp_x + 80 + i * 80, opp_y);
	addChild(tank);
	enemy_tank_vec.pushBack(tank);
}

//move enemy tank
void GameScene::movetank( float x, float y)
{
	Vec2 tankPos;
	Vec2 diff;
	float opp_x = x;//���x���꣨δ�޸ģ�
	float opp_y = y;//���y���꣨δ�޸ģ�
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
	}

}

//new enemy police dog
void GameScene::newdog(float x, float y) {
	float opp_x = x;//���x���꣨δ�޸ģ�
	float opp_y = y;//���y���꣨δ�޸ģ�
	dog = Dog::create();
	int i = enemy_policeDog.size();
	dog->setPosition(opp_x , opp_y + i * 30);
	addChild(dog);
	enemy_policeDog.pushBack(dog);
}

//move enemy police dog
void GameScene::movedog(float x, float y)
{
	Vec2 dogPos;
	Vec2 diff;
	float opp_x = x;//���x���꣨δ�޸ģ�
	float opp_y = y;//���y���꣨δ�޸ģ�

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

	//float px = spawnPoint["x"].asFloat();
	//float py = spawnPoint["y"].asFloat();

	float opp_x = x;//���x���꣨δ�޸ģ�
	float opp_y = y;//���y���꣨δ�޸ģ�

	_player = Soldier::create();
	int i = enemy_soldier_vec.size();
	_player->setPosition(Vec2(opp_x + i * 30, opp_y - 100 ));
	addChild(_player, 2, 200);
	enemy_soldier_vec.pushBack(_player);
}

//�ƶ��з�ʿ��
void GameScene::movesoldier(float x, float y)
{
	Vec2 playerPos;
	Vec2 diff;

	float opp_x = x;//���x���꣨δ�޸ģ�
	float opp_y = y;//���y���꣨δ�޸ģ�
	for (int j = 0; j < vec_chosed_soldier.size(); j++)
	{
		_player = vec_chosed_soldier.at(j);

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
	}
}

//�����з���굥��λ����Ϣ
void GameScene::enemyclick(float x, float y)
{
	float rectX = x;
	float rectY = y;
	Rect mouseRect(rectX - 100, rectY - 100, 200, 200);

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
			}
			else
				movedog(rectX, rectY);
		}

		for (int i = 0; i < tank_vec.size(); i++)
		{
			if (tank_vec.at(i)->getBoundingBox().intersectsRect(mouseRect))
			{
				tank_vec.at(i)->attacked = true;
				attacked_tank.pushBack(tank_vec.at(i));
				//blood_reservoir(tank_vec.at(i)->getPosition());
				//log("attck success");
			}
			else
				movetank(rectX, rectY);
		}

		for (int i = 0; i < soldier_vec.size(); i++)
		{
			if (soldier_vec.at(i)->getBoundingBox().intersectsRect(mouseRect))
			{
				soldier_vec.at(i)->attacked = true;
				attacked_soldier.pushBack(soldier_vec.at(i));
				//blood_reservoir(soldier_vec.at(i)->getPosition());//���޸�
				//log("attck success");
			}
			else
				movesoldier(rectX, rectY);
		}

		if (attacked_dog.size() == 0 && attacked_tank.size() == 0 && attacked_soldier.size() == 0)
		{
			movetank(rectX, rectY);
			movesoldier(rectX, rectY);
		}
	}


}
//�����з�����ѡ������Ϣ
void GameScene::enemySelectArea(float dx, float dy, float ux, float uy)
{
	float rectX = dx < ux ? dx : ux;
	float rectY = dy < uy ? dy : uy;
	Rect mouseRect(rectX, rectY, abs(dx - ux), abs(dy - uy));


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
		//�жϿ�ѡ����Щ
		if (enemy_soldier_vec.at(i)->getBoundingBox().intersectsRect(mouseRect))
		{
			Texture2D* textureYes = Director::getInstance()->getTextureCache()->addImage("CloseNormal.png");
			enemy_soldier_vec.at(i)->setTexture(textureYes);
			enemy_chosed_soldier.pushBack(enemy_soldier_vec.at(i));
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
	Sprite *bingying = Sprite::create("menu/Chariot.png");
	bingying->setPosition(Vec2(x,y));
	this->addChild(bingying, 1);
}
void GameScene::new_enemy_barracks(float x, float y)//��Ӫ
{
	Sprite *bingying = Sprite::create("menu/Barracks.png");
	bingying->setPosition(Vec2(x, y));
	this->addChild(bingying, 1);
}
void GameScene::new_enemy_powerplant(float x, float y)//�糧
{
	Sprite *bingying = Sprite::create("menu/powerplant1.png");
	bingying->setPosition(Vec2(x, y));
	this->addChild(bingying, 1);
}
void GameScene::new_enemy_kuangchang(float x, float y)//��
{
	Sprite *bingying = Sprite::create("menu/test.png");
	bingying->setPosition(Vec2(x, y));
	this->addChild(bingying, 1);
}
