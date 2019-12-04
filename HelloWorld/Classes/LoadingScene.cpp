

#include "LoadingScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* LoadingScene::createScene()
{
    return LoadingScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LoadingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Sprites/Loading/loading3.plist", "Sprites/Loading/loading3.png");
	auto loadingFrame = Sprite::createWithSpriteFrameName("spritesheet0.png");
	loadingFrame->setPosition(Vec2(visibleSize.width / 10, visibleSize.height / 5));
	char loadingFrameByName[30] = { 0 };
	Vector<SpriteFrame*> animLoading;
	for (int i =0; i < 4; i++)
	{
		sprintf(loadingFrameByName, "spritesheet%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(loadingFrameByName);
		animLoading.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(animLoading, 0.1f);
	Animate* animate = Animate::create(animation);
	auto targetSizeLoading = Size(50, 50);
	auto sizeOrigLoading = loadingFrame->getContentSize();
	loadingFrame->setScale((targetSizeLoading.width / sizeOrigLoading.width), (targetSizeLoading.height / sizeOrigLoading.height));
	addChild(loadingFrame);
	auto moveLoading = MoveTo::create(3.0f, Vec2(9 * visibleSize.width / 10, visibleSize.height / 5));
	loadingFrame->runAction(moveLoading);
	loadingFrame->runAction(RepeatForever::create(animate));

	auto spLogo = Sprite::create("Sprites/Logo/logo__.png");
	spLogo->setAnchorPoint(Vec2(0.5, 0.5));
	spLogo->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(spLogo);
	auto targetSizeLogo = Size(10, 10);
	auto sizeOrigLogo = spLogo->getContentSize();
	spLogo->setScale((targetSizeLogo.width / sizeOrigLogo.width), (targetSizeLogo.height / sizeOrigLogo.height));
	auto scaleLogo = ScaleTo::create(3.0f, 1);
	spLogo->runAction(scaleLogo);
	

	schedule(schedule_selector(LoadingScene::changeScene), 3.0f);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event) {
		auto scene = MainMenuScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene, Color3B(0, 0, 0)));

		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();
	
    return true;
}

void LoadingScene::update(float deltaTime) {

}
void LoadingScene::changeScene(float deltaTime) {
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.5f, scene, Color3B(0, 0, 0)));
}