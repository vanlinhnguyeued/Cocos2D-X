#include"Rock.h"
#include "RESOURCEMANAGER.H"
#include "GamePlayScene.h"
#include <ctime>



Rock::Rock(Scene * scene)
{
	Sprite* rockItem = Sprite::createWithSpriteFrame(ResourceManager::getInstance()->getSpriteByID(3)->getSpriteFrame());
	srand(time(NULL));
	this->setSprite(rockItem);
}

Rock::~Rock()
{
}

void Rock::init()
{
}

void Rock::update(float deltaTime)
{
	
	int moveX = rand() % 375 + 1;
	auto moveRock = MoveTo::create(7, Vec2(moveX, -20));
	this->getSprite()->runAction(moveRock);
	if (this->getSprite()->getPosition().y < -10) {
		this->getSprite()->setPosition(Vec2(this->getSprite()->getPosition().x, 700));
		this->getSprite()->stopAllActions();
	}

}
