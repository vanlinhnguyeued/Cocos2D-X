#pragma once
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#pragma once
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
	void shoot(float deltaTime);
	void conllision(vector<Rock*>);
	void conllisionlv2(vector<Rock*> rock);
private:
	vector<Objects*> m_Bullets;
	Scene* scene;
};
