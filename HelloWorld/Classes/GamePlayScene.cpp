#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "GamePlayScene.h"
#include <math.h>
#include "ResourceManager.h"
#include <ctime>

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

	auto bgrMainBGR = Sprite::createWithSpriteFrame(ResourceManager::getInstance()->getSpriteByID(0)->getSpriteFrame());
	bgrMainBGR->setPosition(Vec2(0, 0));
	bgrMainBGR->setAnchorPoint(Vec2(0, 0));
	auto targetSizeBGR = Size(visibleSize.width, visibleSize.height);
	auto sizeOrigBgr = bgrMainBGR->getContentSize();
	bgrMainBGR->setScale((targetSizeBGR.width / sizeOrigBgr.width), (targetSizeBGR.height / sizeOrigBgr.height));
	addChild(bgrMainBGR);


	auto spritespaceshipgCache = SpriteFrameCache::getInstance();
	spritespaceshipgCache->addSpriteFramesWithFile("ship.plist", "ship.png");
	const int numSpriteSpaceShip = 8;
	spriteSpaceShip = Sprite::createWithSpriteFrameName("1.png");
	spriteSpaceShip->setPosition(Vec2(280, 50));
	auto targetSizePS = Size(75, 75);
	auto sizeOrigPS = spriteSpaceShip->getContentSize();
	spriteSpaceShip->setScale((targetSizePS.width / sizeOrigPS.width), (targetSizePS.height / sizeOrigPS.height));
	addChild(spriteSpaceShip);
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

	for (int i = 0; i < 10; i++) {
		Rock* rockItem = new Rock(this);
		this->addChild(rockItem->getSprite());
		rockItem->getSprite()->setPosition(Vec2(i*30, 700));
		this->m_Rocks.push_back(rockItem);
	}
	

	scheduleUpdate();
    return true;
}
static float a = 0;
void GamePlayScene::update(float deltaTime) {
	a += deltaTime;
	if (a > 30 * deltaTime)
	{
	for (int i = 0; i < m_Rocks.size(); i++) {
		
			m_Rocks[i]->update(deltaTime);
			a = 0;
		}
		
	}
}
