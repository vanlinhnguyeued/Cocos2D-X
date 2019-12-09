#include"Bullet.h"
#include "ResourceManager.h"
#include"SimpleAudioEngine.h"
using namespace CocosDenshion;

auto audioFire = SimpleAudioEngine::getInstance();
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
	auto move = MoveBy::create(deltaTime*30, Vec2(0, 700));
	audioFire->playEffect("Sounds/fire.wav", false, 2.0f, 2.0f, 2.0f);
	this->getSprite()->runAction(move);
}

