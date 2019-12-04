#include "ui/CocosGUI.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class Objects {
private: 
	Sprite* m_Sprite;
public:
	Objects();
	~Objects();
	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;
};