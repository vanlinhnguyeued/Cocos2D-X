#include "SimpleAudioEngine.h"
#include<string>
#include "ui/CocosGUI.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace std;
class ResourceManager
{
private:
	static ResourceManager* s_instance;
	string m_dataFoderPath;
	Map<int, Sprite*> m_Sprites;
	Map<int, ui::Button*> m_Buttons;
	Map<int, Label*> m_Labels;
	string m_Score;
	int m_HightScore;
	ResourceManager();

	

	
public:
	virtual ~ResourceManager();
	static ResourceManager* getInstance();
	void init(const string path);
	void load(string fileName);
	string getScore();
	void setScore(string);
	int getHighScore();
	void setHighScore(int);
	Sprite* getSpriteByID(int id);
	ui::Button* getButtonByID(int id);
	Label* getLabelByID(int id);
};


