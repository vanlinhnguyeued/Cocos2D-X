#include "cocos2d.h"

class MainMenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	void update(float delaTime);
    CREATE_FUNC(MainMenuScene);
};