#pragma once
#include "cocos2d.h"
#include "Rock.h"
#include "SpaceShooter.h"

class GamePlayScene : public cocos2d::Scene
{
private: vector<Rock*> m_Rocks;
		 SpaceShooter* m_spaceShooer;
public:
    static cocos2d::Scene* createScene();
	
    virtual bool init();
	void update(float delaTime);
	void generateRock(float deltaTime);
	bool onTouchBegan(Touch* touch, Event* event);
	bool onTouchEnded(Touch* touch, Event* event);
	bool onTouchMoved(Touch* touch, Event* event);
    CREATE_FUNC(GamePlayScene);
};