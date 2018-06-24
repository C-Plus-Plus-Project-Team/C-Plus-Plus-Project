

#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "systemheader.h"
#include <string>

class gameover : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	const int START_BACKGROUND = 101;

	virtual bool init();

	void menuMainmenuCallback(cocos2d::Ref* pSender);
	void menuWinmenuCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(gameover);
};

#endif // __GAMEOVER_SCENE_H__


