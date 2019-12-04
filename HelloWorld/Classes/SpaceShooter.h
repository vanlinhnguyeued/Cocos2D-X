#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Objects.h"
class SpaceShooter : public Objects
{
public:
	SpaceShooter(cocos2d::Scene* scene);
	~SpaceShooter();
	void init();
	void update(float deltaTime);
private:

};
