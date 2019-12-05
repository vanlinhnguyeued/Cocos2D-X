#include"Bullet.h"
#include "ResourceManager.h"


Bullet::Bullet(cocos2d::Scene * scene)
{
	Sprite* bullet = Sprite::createWithSpriteFrame(ResourceManager::getInstance()->getSpriteByID(2)->getSpriteFrame());
	this->setSprite(bullet);
}

Bullet::~Bullet()
{
}

void Bullet::init()
{
}

void Bullet::update(float deltaTime)
{
	auto move = MoveBy::create(1.5f, Vec2(0, 700));
	this->getSprite()->runAction(move);
}

