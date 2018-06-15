
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

	void menuReadyCallback(cocos2d::Ref* pSender);
	void menuOkCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(ready);
};

#endif // __REAYD_SCENE_H__
