#include"SpaceShooter.h"
#include"Bullet.h"
using namespace std;

static float a = 0;
SpaceShooter::SpaceShooter(cocos2d::Scene * scene)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ship.plist", "ship.png");
	auto spriteSpaceShip = Sprite::createWithSpriteFrameName("1.png");
	char loadingFrameByName[30];
	Vector<SpriteFrame*> anmSpaceShip;
	for (int i = 1; i < 9; i++)
	{
		sprintf(loadingFrameByName, "%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(loadingFrameByName);
		anmSpaceShip.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(anmSpaceShip, 0.05f);
	Animate* animate = Animate::create(animation);
	spriteSpaceShip->runAction(RepeatForever::create(animate));
	this->setSprite(spriteSpaceShip);

	for (int i = 0; i < 10; i++)
	{
		Bullet *bullet = new Bullet(scene);
		this->m_Bullets.push_back(bullet);
		scene->addChild(bullet->getSprite());
		bullet->getSprite()->setVisible(false);

	}
}

SpaceShooter::~SpaceShooter()
{
}

void SpaceShooter::init()
{
}

void SpaceShooter::update(float deltaTime)
{	
	this->shoot(deltaTime);
}

void SpaceShooter::shoot(float deltaTime)
{
	a += deltaTime;
	for (int i = 0; i < m_Bullets.size(); i++)
	{
		if (this->m_Bullets[i]->getSprite()->getPosition().y > 700)
		{
			this->m_Bullets[i]->getSprite()->stopAllActions();
			this->m_Bullets[i]->getSprite()->setVisible(false);
			this->m_Bullets[i]->getSprite()->setPosition(this->getSprite()->getPosition().x, this->getSprite()->getPosition().y);
		}
		if (this->m_Bullets[i]->getSprite()->isVisible() == false && a > deltaTime * 15) {
			this->m_Bullets[i]->getSprite()->setVisible(true);
			this->m_Bullets[i]->getSprite()->setPosition(this->getSprite()->getPosition().x, this->getSprite()->getPosition().y);
			this->m_Bullets[i]->update(deltaTime);
			a = 0;
		}
		
	}
}

void SpaceShooter::conllision(vector<Rock*>)
{
}
