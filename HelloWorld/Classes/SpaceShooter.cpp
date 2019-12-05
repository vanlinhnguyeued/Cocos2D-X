#include"SpaceShooter.h"
#include"Bullet.h"
#include "GameOverScene.h"
using namespace std;

static float a = 0;
SpaceShooter::SpaceShooter(cocos2d::Scene * scene)
{
	this->scene = scene;
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
		if (this->m_Bullets[i]->getSprite()->isVisible() == false && a > deltaTime * 8) {
			this->m_Bullets[i]->getSprite()->setVisible(true);
			this->m_Bullets[i]->getSprite()->setPosition(this->getSprite()->getPosition().x, this->getSprite()->getPosition().y);
			this->m_Bullets[i]->update(deltaTime);
			a = 0;
		}
		
	}
}
int score = 1;
string s;
Label* lbscore;
void SpaceShooter::conllision(vector<Rock*> rock)
{
	for (int i = 0; i < rock.size(); i++) {
		auto spriteRock = rock[i]->getSprite();
		
		for (int j = 1; j < m_Bullets.size(); j++) {
			
			auto spriteBullet = m_Bullets[i]->getSprite();
			lbscore = Label::createWithTTF("0", "fonts/VDOMCAS.TTF", 30);
			if (spriteRock->getBoundingBox().intersectsRect(spriteBullet->getBoundingBox())&& spriteRock->isVisible() && spriteBullet->isVisible()) {
				
				SpriteFrameCache::getInstance()->addSpriteFramesWithFile("red.plist", "red.png");
				Sprite* red = Sprite::createWithSpriteFrameName("1_15.png");
				char loadingFrameByName1[30];
				Vector<SpriteFrame*> redship;
				for (int i = 1; i < 14; i++)
				{
					sprintf(loadingFrameByName1, "1_%d.png", i);
					auto frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(loadingFrameByName1);
					redship.pushBack(frame1);
				}
				Animation* animation = Animation::createWithSpriteFrames(redship, 0.05f);
				Animate* animate = Animate::create(animation);
				red->setAnchorPoint(Vec2(0.5, 0.5));
				red->setPosition(Vec2(spriteRock->getPosition().x, spriteRock->getPosition().y));
				red->runAction(Repeat::create(animate, 1));
				this->scene->addChild(red);
				score++;
				s = to_string(score);
				lbscore->setString(s);
				lbscore->setPosition(Vec2(283, 630));
				this->scene->addChild(lbscore);
				spriteRock->setPosition(spriteRock->getPosition().x, -10);
				spriteBullet->setPosition(spriteBullet->getPosition().x, 700);
				spriteBullet->setVisible(false);
				spriteRock->setVisible(false);
			}
			//this->scene->removeChild(lbscore);
			if (spriteRock->getBoundingBox().intersectsRect(this->getSprite()->getBoundingBox()) && spriteRock->isVisible()) {
				auto scene = GameOverScene::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene, Color3B(0, 0, 0)));
			}
			
		}
	}

}
