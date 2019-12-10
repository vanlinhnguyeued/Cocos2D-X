#pragma once
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Objects.h"
class Bullet : public Objects 
{
public:
	Bullet(cocos2d::Scene* scene);
	~Bullet();
	void init();
	void update(float deltaTime);

private:

};
