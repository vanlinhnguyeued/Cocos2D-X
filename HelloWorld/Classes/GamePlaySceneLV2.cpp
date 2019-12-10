#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "GamePlaySceneLV2.h"
#include <math.h>
#include "ResourceManager.h"
#include <ctime>
#include <GameOverScene.h>
#include "SpaceShooter.h"
using namespace CocosDenshion;


USING_NS_CC;




static float a = 0;
TMXTiledMap* map2;
Scene* GamePlaySceneLV2::createScene()
{
    return GamePlaySceneLV2::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GamePlaySceneLV2::init()
{

    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//create background
	auto bgrMainBGR =ResourceManager::getInstance()->getSpriteByID(0);
	bgrMainBGR->removeFromParent();
	bgrMainBGR->setPosition(Vec2(0, 0));
	bgrMainBGR->setAnchorPoint(Vec2(0, 0));
	auto targetSizeBGR = Size(visibleSize.width, visibleSize.height);
	auto sizeOrigBgr = bgrMainBGR->getContentSize();
	bgrMainBGR->setScale((targetSizeBGR.width / sizeOrigBgr.width), (targetSizeBGR.height / sizeOrigBgr.height));
	addChild(bgrMainBGR);

	Label* score = Label::createWithTTF("Your score:", "fonts/VDOMCAS.TTF", 30);
	score->setAnchorPoint(Vec2(0.5, 0.5));
	score->setPosition(Vec2(203, 630));
	addChild(score);

	//set map
	map2 = TMXTiledMap::create("TileMaps/bg.tmx");
	map2->setAnchorPoint(Vec2(0, 0));
	map2->setPosition(Vec2(0, 0));
	auto targetSizeMap = Size(visibleSize.width, visibleSize.height);
	auto sizeOrigMap = map2->getContentSize();
	map2->setScale((targetSizeMap.width / sizeOrigMap.width), (targetSizeMap.height / sizeOrigMap.height));
	this->addChild(map2);
	//init rock
	for (int i = 0; i < 10; i++) {
		Rock* rockItem = new Rock(this);
		this->addChild(rockItem->getSprite());
		rockItem->getSprite()->setPosition(Vec2(i * 50, 700));
		rockItem->getSprite()->setVisible(false);
		this->m_Rocks.push_back(rockItem);
	}
	//create spaceShip
	this->spaceShooter1 = new SpaceShooter(this);
	auto targetSizePS = Size(75, 75);
	auto sizeOrigPS = spaceShooter1->getSprite()->getContentSize();
	spaceShooter1->getSprite()->setScale((targetSizePS.width / sizeOrigPS.width), (targetSizePS.height / sizeOrigPS.height));
	spaceShooter1->getSprite()->setAnchorPoint(Vec2(0.5, 0.5));
	spaceShooter1->getSprite()->setPosition(Vec2(visibleSize.width/2, visibleSize.height/10));
	this->addChild(spaceShooter1->getSprite());

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GamePlaySceneLV2::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GamePlaySceneLV2::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GamePlaySceneLV2::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	
	scheduleUpdate();
    return true;
}

void GamePlaySceneLV2::update(float deltaTime) {
	
		this->generateRock(deltaTime);
		spaceShooter1->update(deltaTime);
		spaceShooter1->conllisionlv2(m_Rocks);
	
}

void GamePlaySceneLV2::generateRock(float deltaTime)
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

bool GamePlaySceneLV2::onTouchBegan(Touch * touch, Event * event)
{
	auto time = sqrt(pow(touch->getLocation().x - spaceShooter1->getSprite()->getPosition().x, 2) + pow(touch->getLocation().y - spaceShooter1->getSprite()->getPosition().y, 2)) / 1000;
	auto moveSpaceShip = MoveTo::create(time, touch->getLocation());
	spaceShooter1->getSprite()->runAction(moveSpaceShip);
	return true;
}

bool GamePlaySceneLV2::onTouchEnded(Touch * touch, Event * event)
{
	return false;
}

bool GamePlaySceneLV2::onTouchMoved(Touch * touch, Event * event)
{
	spaceShooter1->getSprite()->setPosition(spaceShooter1->getSprite()->getPosition() + touch->getDelta());
	return true;
}
