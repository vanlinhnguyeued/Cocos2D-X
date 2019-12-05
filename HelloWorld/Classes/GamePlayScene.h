#pragma once
#include "cocos2d.h"
#include "Rock.h"

class GamePlayScene : public cocos2d::Scene
{
private: vector<Rock*> m_Rocks;
public:
    static cocos2d::Scene* createScene();
	
    virtual bool init();
	void update(float delaTime);
    CREATE_FUNC(GamePlayScene);
};