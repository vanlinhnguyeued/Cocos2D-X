#include "cocos2d.h"

class SpriteScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void update(float deltaTime);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SpriteScene);
};


