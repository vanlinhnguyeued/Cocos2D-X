#pragma once

#ifndef __LOGO_SCENE_H__
#define __LOGO_SCENE_H__

#include "cocos2d.h"

class LogoScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	bool OnTouchBegan(cocos2d::Touch *touch, cocos2d::Event *envent);
	void update(float delaTime);
	void changeLoading(float deltaTime);
    
    // implement the "static create()" method manually
    CREATE_FUNC(LogoScene);
};
#endif // __LOGO_SCENE_H__
