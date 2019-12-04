#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Objects.h"
class Rock : public Objects
{
public:
	Rock(cocos2d::Scene* scene);
	~Rock();
	void init();
	void update(float deltaTime);
private:

};
