
#include<string>
#include "ui/CocosGUI.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class ResourceManager
{
private:
	static ResourceManager* s_instance;
	string m_dataFoderPath;
	Map<int, Sprite*> m_Sprites;
	Map<char, ui::Button*> m_Buttons;
	Map<char, Label*> m_Labels;
	ResourceManager();
	

	
public:
	virtual ~ResourceManager();
	static ResourceManager* getInstance();
	void init(const string path);
	void load(string fileName);
	Sprite* getSpriteByID(char id);
	ui::Button* getButtonByID(char id);
	Label* getLabelByID(char id);
};


