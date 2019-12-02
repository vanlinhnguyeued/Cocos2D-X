#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "GamePlayScene.h"

using namespace cocos2d::ui;



USING_NS_CC;

Scene* GamePlayScene::createScene()
{
    return GamePlayScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GamePlayScene::init()
{

    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bgrGP = Sprite::create("Sprites/background.png");
	bgrGP->setPosition(Vec2(0, 0));
	bgrGP->setAnchorPoint(Vec2(0, 0));
	//set size for bgr
	auto targetSizeBGR = Size(560.0f, 320.0f);
	auto sizeOrigBgr = bgrGP->getContentSize();
	bgrGP->setScale((targetSizeBGR.width / sizeOrigBgr.width), (targetSizeBGR.height / sizeOrigBgr.height));
	addChild(bgrGP);

	auto spritespaceshipgCache = SpriteFrameCache::getInstance();
	spritespaceshipgCache->addSpriteFramesWithFile("ship.plist", "ship.png");
	const int numSpritePaceShip = 8;
	auto spritePaceShip = Sprite::createWithSpriteFrameName("1.png");
	spritePaceShip->setPosition(Vec2(280, 50));
	auto targetSizePS = Size(75, 75);
	auto sizeOrigPS = spritePaceShip->getContentSize();
	spritePaceShip->setScale((targetSizePS.width / sizeOrigPS.width), (targetSizePS.height / sizeOrigPS.height));
	addChild(spritePaceShip);
	//create animate
	Vector<SpriteFrame*> anmPaceShip;
	anmPaceShip.reserve(numSpritePaceShip);
	anmPaceShip.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("1.png"));
	anmPaceShip.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("2.png"));
	anmPaceShip.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("3.png"));
	anmPaceShip.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("4.png"));
	anmPaceShip.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("5.png"));
	anmPaceShip.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("6.png"));
	anmPaceShip.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("7.png"));
	anmPaceShip.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("8.png"));
	auto animationPAceShip = Animation::createWithSpriteFrames(anmPaceShip, 0.05f);
	auto animatePaceShip = Animate::create(animationPAceShip);
	spritePaceShip->runAction(RepeatForever::create(animatePaceShip));

	scheduleUpdate();
    return true;
}

void GamePlayScene::update(float deltaTime) {
	
}