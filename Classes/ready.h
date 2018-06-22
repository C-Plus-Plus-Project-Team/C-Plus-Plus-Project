
#ifndef __READY_SCENE_H__
#define __READY_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "systemheader.h"

class ready : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	const int START_BACKGROUND = 101;

	virtual bool init();
	virtual void update(float dt);
	//virtual void updateCustom(float dt);

	void menuPlayer1Callback(cocos2d::Ref* pSender);
	void menuPlayer2Callback(cocos2d::Ref* pSender);
	void menuOkCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(ready);
private:
	cocos2d::MenuItemFont *player1Item;
	cocos2d::MenuItemFont *player2Item;
};

#endif // __REAYD_SCENE_H__
