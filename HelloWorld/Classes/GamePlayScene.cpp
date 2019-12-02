#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "GamePlayScene.h"
#include <math.h>

using namespace cocos2d::ui;



USING_NS_CC;

cocos2d::Sprite* spriteSpaceShip;
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
	auto targetSizeBGR = Size(860.0f, 320.0f);
	auto sizeOrigBgr = bgrGP->getContentSize();
	bgrGP->setScale((targetSizeBGR.width / sizeOrigBgr.width), (targetSizeBGR.height / sizeOrigBgr.height));
	addChild(bgrGP);

	auto scaleBGR = ScaleBy::create(5, 1.5);
	auto fadeOut = FadeOut::create(5);
	bgrGP->runAction(fadeOut);
	bgrGP->runAction(RepeatForever::create(scaleBGR));

	auto rock1 = Sprite::create("Sprites/Rock/aestroid_brown.png");
	rock1->setAnchorPoint(Vec2(0, 0));
	rock1->setPosition(Vec2(400, 200));
	addChild(rock1);
	auto fadeInRock = FadeIn::create(3.0f);
	auto scaleRock = ScaleBy::create(3, 3);
	auto moveRock = MoveTo::create(3, Vec2(0, 0));
	auto spRock = Spawn::create(fadeInRock, scaleRock, moveRock, nullptr);
	rock1->runAction(RepeatForever::create(spRock));

	auto spritespaceshipgCache = SpriteFrameCache::getInstance();
	spritespaceshipgCache->addSpriteFramesWithFile("ship.plist", "ship.png");
	const int numSpriteSpaceShip = 8;
	spriteSpaceShip = Sprite::createWithSpriteFrameName("1.png");
	spriteSpaceShip->setPosition(Vec2(280, 50));
	auto targetSizePS = Size(75, 75);
	auto sizeOrigPS = spriteSpaceShip->getContentSize();
	spriteSpaceShip->setScale((targetSizePS.width / sizeOrigPS.width), (targetSizePS.height / sizeOrigPS.height));
	addChild(spriteSpaceShip);
	//create animate
	Vector<SpriteFrame*> anmSpaceShip;
	anmSpaceShip.reserve(numSpriteSpaceShip);
	anmSpaceShip.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("1.png"));
	anmSpaceShip.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("2.png"));
	anmSpaceShip.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("3.png"));
	anmSpaceShip.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("4.png"));
	anmSpaceShip.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("5.png"));
	anmSpaceShip.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("6.png"));
	anmSpaceShip.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("7.png"));
	anmSpaceShip.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("8.png"));
	auto animationSpceShip = Animation::createWithSpriteFrames(anmSpaceShip, 0.05f);
	auto animateSpaceShip = Animate::create(animationSpceShip);
	spriteSpaceShip->runAction(RepeatForever::create(animateSpaceShip));


	//OntouchBeGan
	auto controlSpaceShipByTouch = EventListenerTouchOneByOne::create();
	controlSpaceShipByTouch->onTouchBegan = [](Touch* touch, Event* event) {
		auto time = sqrt(pow(touch->getLocation().x - spriteSpaceShip->getPosition().x, 2)+ pow(touch->getLocation().y - spriteSpaceShip->getPosition().y, 2))/1000;
		auto moveSpaceShip = MoveTo::create(time, touch->getLocation());
		spriteSpaceShip->runAction(moveSpaceShip);
		return true;
	};
	//OntouchMoved
	controlSpaceShipByTouch->onTouchMoved = [](Touch* touch, Event* event) {
		spriteSpaceShip->setPosition(spriteSpaceShip->getPosition()+touch->getDelta());
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(controlSpaceShipByTouch, this);

	auto controlSpaceShipByKB = EventListenerKeyboard::create();
	controlSpaceShipByKB->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			spriteSpaceShip->setPosition(Vec2(spriteSpaceShip->getPosition().x - 10.0f, spriteSpaceShip->getPosition().y));
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			spriteSpaceShip->setPosition(Vec2(spriteSpaceShip->getPosition().x , spriteSpaceShip->getPosition().y + 10.0f));
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			spriteSpaceShip->setPosition(Vec2(spriteSpaceShip->getPosition().x, spriteSpaceShip->getPosition().y - 10.0f));
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			spriteSpaceShip->setPosition(Vec2(spriteSpaceShip->getPosition().x + 10.0f, spriteSpaceShip->getPosition().y));
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(controlSpaceShipByKB, this);

	scheduleUpdate();
    return true;
}

void GamePlayScene::update(float deltaTime) {
	
}
