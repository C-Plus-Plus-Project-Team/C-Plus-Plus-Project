#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "setting.h"
#include "systemheader.h"

class MainScene : public cocos2d::Scene
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

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuSettingCallback(cocos2d::Ref* pSender);
	void menuStartCallback(cocos2d::Ref * pSender);

	CREATE_FUNC(MainScene);


};

#endif // __HELLOWORLD_SCENE_H__
