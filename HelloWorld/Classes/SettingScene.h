#include "cocos2d.h"

class SettingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	void update(float delaTime);
	void SoundOnClick(Ref* pSender);
	void AboutOnClick(Ref* pSender);
    CREATE_FUNC(SettingScene);
};