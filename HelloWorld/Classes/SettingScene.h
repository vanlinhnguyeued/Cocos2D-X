#include "cocos2d.h"

class SettingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	void createSoundLayer(Ref* pSender);
	void createAboutLayer(Ref* pSender);
	void SoundOnClick(Ref* pSender);
	void AboutOnClick(Ref* pSender);
	void ChangePlayerName(Ref* pSender);
    CREATE_FUNC(SettingScene);
};