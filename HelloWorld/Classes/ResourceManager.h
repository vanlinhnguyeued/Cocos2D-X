
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
	Map<int, ui::Button*> m_Buttons;
	Map<int, Label*> m_Labels;
	string m_Score;
	int m_HightScore=0;
	ResourceManager();
	

	
public:
	virtual ~ResourceManager();
	static ResourceManager* getInstance();
	void init(const string path);
	void load(string fileName);
	void setScore(string score, string path);
	void setHightScore(int score);
	string getScore();
	string getHightScore(string path);
	void saveHightScore(string path);
	Sprite* getSpriteByID(int id);
	ui::Button* getButtonByID(int id);
	Label* getLabelByID(int id);
};


