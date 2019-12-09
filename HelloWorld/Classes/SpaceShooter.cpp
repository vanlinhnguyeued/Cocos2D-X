#include"SpaceShooter.h"
#include"Bullet.h"
#include "GameOverScene.h"
#include "ResourceManager.h"
#include"SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace std;
auto audioKilled = SimpleAudioEngine::getInstance();

static float a = 0;
int score = 0;
string s;
Label* lbscore;
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
	lbscore = Label::createWithTTF("0", "fonts/VDOMCAS.TTF", 30);
	lbscore->setPosition(Vec2(283, 630));
	this->scene->addChild(lbscore);
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
		if (this->m_Bullets[i]->getSprite()->isVisible() == false && a > deltaTime * 20) {
			this->m_Bullets[i]->getSprite()->setVisible(true);
			this->m_Bullets[i]->getSprite()->setPosition(this->getSprite()->getPosition().x, this->getSprite()->getPosition().y);
			this->m_Bullets[i]->update(deltaTime);
			a = 0;
		}
		
	}
}
Sprite* blue;
void SpaceShooter::conllision(vector<Rock*> rock)
{
	for (int i = 0; i < rock.size(); i++) {
		auto spriteRock = rock[i]->getSprite();
		for (int j = 0; j < m_Bullets.size(); j++) {
			auto spriteBullet = m_Bullets[j]->getSprite();
			if (spriteBullet->getBoundingBox().intersectsRect(spriteRock->getBoundingBox())&& spriteRock->isVisible() && spriteBullet->isVisible()) {
				audioKilled->playEffect("Sounds/killed.wav", false, 1.0f, 1.0f, 1.0f);
				auto particle = CCParticleSystemQuad::create("Sprites/particle_texture.plist");
				particle->setScale(0.7);
				particle->setPosition(Vec2(spriteRock->getPosition().x, spriteRock->getPosition().y));
				this->scene->addChild(particle);
		
				score++;
				s = to_string(score);
				lbscore->setString(s);
				spriteRock->setPosition(spriteRock->getPosition().x, -10);
				spriteBullet->setPosition(spriteBullet->getPosition().x, 700);
				spriteBullet->setVisible(false);
				spriteRock->setVisible(false);
				
			}
			if (spriteRock->getBoundingBox().intersectsRect(this->getSprite()->getBoundingBox()) && spriteRock->isVisible()) {
				ResourceManager::getInstance()->setScore(s);
				if (score > ResourceManager::getInstance()->getHighScore()) {
					ResourceManager::getInstance()->setHighScore(score);
				}
					
				score = 0;
				auto scene = GameOverScene::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene, Color3B(0, 0, 0)));

			}
			
		}
	}
	if (score == 10) {

		auto map = TMXTiledMap::create("TileMaps/bg.tmx");
		map->setPosition(Vec2(0,0));
		map->setScaleX(0.7);
		this->scene->addChild(map, 1);

	}
}
