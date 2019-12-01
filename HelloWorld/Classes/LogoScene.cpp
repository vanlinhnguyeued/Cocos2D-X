

#include "LogoScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "LoadingScene.h"


USING_NS_CC;


cocos2d::Sprite *spriteRocket;
cocos2d::Sprite *spriteSun;
Scene* LogoScene::createScene()
{
    return LogoScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LogoScene::init()
{

    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//set properties for spriteRocket
	spriteRocket =Sprite::create("Sprites/logo/logo.png");
	spriteRocket->setAnchorPoint(Vec2(0.5, 0.5));
	spriteRocket->setPosition(Vec2(150, 150));
	addChild(spriteRocket);

	//set properties for sun
	spriteSun = Sprite::create("Sprites/Parallax/sun.png");
	spriteSun->setAnchorPoint(Vec2(0.5, 0.5));
	spriteSun->setPosition(Vec2(50, visibleSize.height / 2));
	addChild(spriteSun);
	//spriteRocket scale 0.5
	auto scale = ScaleTo::create(2.0f, 0.5f);
	spriteRocket->runAction(scale);

	//spriteRocket move top
	auto moveTop = MoveTo::create(10, Vec2(0, 900));
	spriteRocket->runAction(moveTop);

	//sun rotate360
	auto rotate360 = RotateBy::create(4.0f, 360.0f);
	spriteSun->runAction(rotate360);

	//sun scale by 2
	auto scaleDouble = ScaleTo::create(4.0f, 2.0f);
	spriteSun->runAction(scaleDouble);

	//sun move right
	auto moveRight = MoveBy::create(4, Vec2(1000, 500));
	spriteSun->runAction(moveRight);

	//set ease for rocket
	auto move_ease_elstic = EaseElasticInOut::create(moveRight->clone());
	auto move_ease_in_back = move_ease_elstic->reverse();
	auto delay = DelayTime::create(0.5f);
	auto seq = Sequence::create(move_ease_elstic, delay, move_ease_in_back, delay->clone(), nullptr);
	spriteRocket->runAction(RepeatForever::create(seq));

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(LogoScene::OnTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	this->schedule(schedule_selector(LogoScene::changeLoading), 3.0f);
	scheduleUpdate();
    return true;
}

bool LogoScene::OnTouchBegan(cocos2d::Touch *touch, cocos2d::Event *envent) {
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 255, 255)));

	return true;
}
void LogoScene::update(float deltaTime) {
	
}
void LogoScene::changeLoading(float deltaTime) {
	auto sceneLoading = LoadingScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, sceneLoading, Color3B(128, 0, 0)));
}