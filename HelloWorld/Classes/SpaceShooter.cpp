#include"SpaceShooter.h"
#include"Bullet.h"
using namespace std;

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

	for (int i = 0; i < 20; i++)
	{
		Bullet *bullet = new Bullet(scene);
		this->m_Bullets.push_back(bullet);
		scene->addChild(bullet->getSprite());
		bullet->getSprite()->setVisible(true);

	}
}

SpaceShooter::~SpaceShooter()
{
}

void SpaceShooter::init()
{
}
static float a = 0;
void SpaceShooter::update(float deltaTime)
{
	a += deltaTime;
	
	for (int i = 0; i < m_Bullets.size(); i++)
	{
		this->m_Bullets[i]->update(deltaTime);
		if (!this->m_Bullets[i]->getSprite()->isVisible()==false && a > deltaTime * 10) {
			this->m_Bullets[i]->getSprite()->setVisible(true);
			this->m_Bullets[i]->getSprite()->setPosition(this->getSprite()->getPosition().x, this->getSprite()->getPosition().y);
			a = 0;
			break;
		}
		if (this->m_Bullets[i]->getSprite()->getPosition().y > 1000)
		{
			this->m_Bullets[i]->getSprite()->stopAllActions();
			this->m_Bullets[i]->getSprite()->setVisible(false);
			this->m_Bullets[i]->getSprite()->setPosition(this->getSprite()->getPosition().x, this->getSprite()->getPosition().y);
		}
	}
}

void SpaceShooter::shoot()
{
}

void SpaceShooter::conllision(vector<Rock*>)
{
}
