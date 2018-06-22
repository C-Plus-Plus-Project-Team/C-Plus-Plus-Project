#ifndef Game_Scene
#define Game_Scene

#include "cocos2d.h"
#include "MainScene.h"
#include "Soldier.h"
#include "systemheader.h"

class GameScene : public cocos2d::Layer
{
	cocos2d::TMXTiledMap* _tileMap;
	Soldier *_player;
	Tank *tank;
	Dog *dog;
	Test *test;
	ProgressTimer *timm;
	Sprite *blood;
	Base *base;
	Base *enemy_base;
	Explode *explode;
	//Vec2 touchLocation;
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	void update(float dt); //detle time
	//void onEnter();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	/*virtual bool onMouseDown(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onMouseMove(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onMouseUp(cocos2d::Touch *touch, cocos2d::Event *event);*/
	
	//tank
	void newtank();//����̹��
	void movetank();//�ƶ��ҷ�̹��
	void newtank(float x, float y);//�����з�̹��
	void movetank(float x , float y );//�ƶ��з�̹��

	//police dog
	void newdog();
	void movedog();
	void newdog(float x, float y);//�����з���Ȯ
	void movedog(float x, float y);//�ƶ��з���Ȯ

	//soldier
	void newsoldier();
	void movesoldier();
	void newsoldier(float x, float y);//�����з�ʿ��
	void movesoldier(float x, float y);//�ƶ��з�ʿ��

	//�����з�����
	void new_enemy_chariot(float x, float y);//̹�˹���
	void new_enemy_barracks(float x, float y);//��Ӫ
	void new_enemy_powerplant(float x, float y);//�糧
	void new_enemy_kuangchang(float x, float y);//��

	//�����з���굥��λ����Ϣ
	void enemyclick(float x, float y);
	//�����з�����ѡ������Ϣ
	void enemySelectArea(float dx, float dy, float ux, float uy);

	//blood reservoir
	void blood_reservoir( Vec2 enemyPos);
	//explode GIF
	void explodeGIF( Vec2 Pos);

	int dogCount;//��Ȯ����
	int tankCount;//̹������
	int count;
	int explodetime;//��ըЧ��������ʱ��
	
	bool iftocreatemenu;
	bool buildbase;
	bool enemy_buildbase;
	bool canmove;
	bool addbuilding;

	Vec2 startpos;//�����ʼλ��
	Vec2 mappos;//�����ͼλ��
	Vec2 mouseDownPosition;//��һ�ε����ʱ����λ��
	Vec2 mouseUpPosition;//���̧��ʱ��λ��
	static cocos2d::Vector<Dog*> vec_chosed_dog;//�洢�ҷ�ѡ��policeDog������
	static cocos2d::Vector<Tank*> vec_chosed_tank;//�洢�ҷ�ѡ��tank������
	static cocos2d::Vector<Soldier*> vec_chosed_soldier;//�洢�ҷ�ѡ��soldier������

	static cocos2d::Vector<Dog*> enemy_chosed_dog;//�洢�з�ѡ��policeDog������
	static cocos2d::Vector<Tank*> enemy_chosed_tank;//�洢�з�ѡ��tank������
	static cocos2d::Vector<Soldier*> enemy_chosed_soldier;//�洢�з�ѡ��soldier������

														  //�˵�����ʵ��
	Vec2 bingyingPosition;//��¼̹�˱�Ӫλ�ã��������ڱ�Ӫ��λ�ã�
	Vec2 soldierbingyingPosition;//��¼��������λ��
	int iftobuild = 1;//�˵�ѡ��״����1Ϊ��ʼ״̬��2Ϊ��ɼ���״̬
	tankbing *createTank;
	tankgongchang *createTankbingying;
	whitecd *white;
	ProgressTimer *progress1;
	caidankuang *caidankuang1;
	bubinggongchang *createbingying;
	fadianchang *createfadianchang;
	shiyouchang *createshiyouchang;
	bubing *createbubing;
	jingquan *createjingquan;

	//void setViewpointCenter(cocos2d::Vec2 position); //set viewpoint center,to move the map
	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif // __HELLOWORLD_SCENE_H__
