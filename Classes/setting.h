
#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "systemheader.h"

class setting : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	const int START_BACKGROUND = 101;

	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();

	void menuOkCallback(cocos2d::Ref* pSender);
	void menuSwitchCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(setting);
};

#endif // __SETTIBG_SCENE_H__

