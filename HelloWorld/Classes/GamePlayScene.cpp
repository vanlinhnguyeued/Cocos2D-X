#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "GamePlayScene.h"
#include <math.h>
#include "ResourceManager.h"
#include <ctime>

using namespace cocos2d::ui;



USING_NS_CC;

static float a = 0;
SpaceShooter* spaceShooter;
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
	//create background
	auto bgrMainBGR = Sprite::createWithSpriteFrame(ResourceManager::getInstance()->getSpriteByID(0)->getSpriteFrame());
	bgrMainBGR->setPosition(Vec2(0, 0));
	bgrMainBGR->setAnchorPoint(Vec2(0, 0));
	auto targetSizeBGR = Size(visibleSize.width, visibleSize.height);
	auto sizeOrigBgr = bgrMainBGR->getContentSize();
	bgrMainBGR->setScale((targetSizeBGR.width / sizeOrigBgr.width), (targetSizeBGR.height / sizeOrigBgr.height));
	addChild(bgrMainBGR);

	//init rock
	for (int i = 0; i < 10; i++) {
		Rock* rockItem = new Rock(this);
		this->addChild(rockItem->getSprite());
		rockItem->getSprite()->setPosition(Vec2(i * 50, 700));
		rockItem->getSprite()->setVisible(false);
		this->m_Rocks.push_back(rockItem);
	}
	//create spaceShip
	spaceShooter = new SpaceShooter(this);
	auto targetSizePS = Size(75, 75);
	auto sizeOrigPS = spaceShooter->getSprite()->getContentSize();
	spaceShooter->getSprite()->setScale((targetSizePS.width / sizeOrigPS.width), (targetSizePS.height / sizeOrigPS.height));
	spaceShooter->getSprite()->setAnchorPoint(Vec2(0.5, 0.5));
	spaceShooter->getSprite()->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 10));
	this->addChild(spaceShooter->getSprite());
	
	auto controlSpaceShipByTouch = EventListenerTouchOneByOne::create();
	controlSpaceShipByTouch->onTouchBegan = [](Touch* touch, Event* event) {
		auto time = sqrt(pow(touch->getLocation().x - spaceShooter->getSprite()->getPosition().x, 2)+ pow(touch->getLocation().y - spaceShooter->getSprite()->getPosition().y, 2))/1000;
		auto moveSpaceShip = MoveTo::create(time, touch->getLocation());
		spaceShooter->getSprite()->runAction(moveSpaceShip);
		return true;
	};
	//OntouchMoved
	controlSpaceShipByTouch->onTouchMoved = [](Touch* touch, Event* event) {
		spaceShooter->getSprite()->setPosition(spaceShooter->getSprite()->getPosition()+touch->getDelta());
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(controlSpaceShipByTouch, this);

	auto controlSpaceShipByKB = EventListenerKeyboard::create();
	controlSpaceShipByKB->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			spaceShooter->getSprite()->setPosition(Vec2(spaceShooter->getSprite()->getPosition().x - 10.0f, spaceShooter->getSprite()->getPosition().y));
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			spaceShooter->getSprite()->setPosition(Vec2(spaceShooter->getSprite()->getPosition().x , spaceShooter->getSprite()->getPosition().y + 10.0f));
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			spaceShooter->getSprite()->setPosition(Vec2(spaceShooter->getSprite()->getPosition().x, spaceShooter->getSprite()->getPosition().y - 10.0f));
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			spaceShooter->getSprite()->setPosition(Vec2(spaceShooter->getSprite()->getPosition().x + 10.0f, spaceShooter->getSprite()->getPosition().y));
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(controlSpaceShipByKB, this);



	scheduleUpdate();
    return true;
}

void GamePlayScene::update(float deltaTime) {
	this->generateRock(deltaTime);
	spaceShooter->update(deltaTime);
	spaceShooter->conllision(m_Rocks);
}

void GamePlayScene::generateRock(float deltaTime)
{
	a += deltaTime;
	if (a > 40 * deltaTime) {
		for (int i = 0; i < m_Rocks.size(); i++) {
			if (m_Rocks[i]->getSprite()->getPosition().y < -10) {
				m_Rocks[i]->getSprite()->setVisible(false);
				m_Rocks[i]->getSprite()->stopAllActions();
				m_Rocks[i]->getSprite()->setPosition(Vec2(m_Rocks[i]->getSprite()->getPosition().x, 700));
			}
			if (m_Rocks[i]->getSprite()->isVisible() == false) {
				m_Rocks[i]->update(deltaTime);
				m_Rocks[i]->getSprite()->setVisible(true);
				i = m_Rocks.size();
				a = 0;
			}
			
		}
	}
}
