#pragma once
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Objects.h"
#include "Rock.h"
using namespace std;
class SpaceShooter : public Objects
{
public:
	SpaceShooter(cocos2d::Scene* scene);
	~SpaceShooter();
	void init();
	void update(float deltaTime);
	void shoot();
	void conllision(vector<Rock*>);
private:
	vector<Objects*> m_Bullets;
};
