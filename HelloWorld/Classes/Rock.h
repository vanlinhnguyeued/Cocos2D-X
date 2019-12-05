#pragma once
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Objects.h"

class Rock : public Objects
{
public:
	Rock(Scene* scene);
	~Rock();
	void init();
	void update(float deltaTime);

};
