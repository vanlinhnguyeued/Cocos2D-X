#include"Rock.h"
#include "RESOURCEMANAGER.H"
#include "GamePlayScene.h"
#include <ctime>



Rock::Rock(Scene * scene)
{
	Sprite* rockItem = DuplicateSprite(ResourceManager::getInstance()->getSpriteByID(3));
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
	auto moveRock = MoveTo::create(deltaTime*200, Vec2(moveX, -20));
	this->getSprite()->runAction(moveRock);
	

}
