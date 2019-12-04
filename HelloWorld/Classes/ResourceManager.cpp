#include "RESOURCEMANAGER.H"
#include <stdio.h>
using namespace std;

ResourceManager* ResourceManager::s_instance;
ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

ResourceManager * ResourceManager::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new ResourceManager();

	}
	return s_instance;
}

void ResourceManager::init(const string path)
{
	m_dataFoderPath = path;
	load(m_dataFoderPath);
}

void ResourceManager::load(string fileName)
{
	bool isExist = FileUtils::getInstance()->isFileExist(fileName);
	string read = FileUtils::getInstance()->getStringFromFile(fileName);
	log("%s", read.c_str());
	char* cstr = const_cast<char*>(read.c_str());
	vector<string> SS;
	string text;
	string numOfImage;
	char* pch = strtok(cstr ,"\n");
	while (pch != NULL)
	{
		
		SS.push_back(pch);
		pch = strtok(NULL, "\n");
	}
	for (int i = 0; i < SS.size(); i++)
	{
		istringstream is(SS[i]);
		is >> text >> numOfImage;
		if (text == "#SPRITE") {
			int j = stoi(numOfImage);
			
			while (j > 0) {
				i++;
				istringstream is(SS[i]);
				is >> text >> numOfImage;
				int s1 = stoi(numOfImage);
				i++;
				istringstream iis(SS[i]);
				iis >> text >> numOfImage;
				string s2 = numOfImage;
				Sprite* sprite = Sprite::create(s2);
				m_Sprites.insert(s1, sprite);

				j--;
			}
		}
		if (text == "#BUTTON") {
			int j = stoi(numOfImage);

			while (j > 0) {
				i++;
				istringstream is(SS[i]);
				is >> text >> numOfImage;
				log("%s", numOfImage.c_str());
				int s1 = stoi(numOfImage);
				i++;
				istringstream iis(SS[i]);
				iis >> text >> numOfImage;
				string s2 = numOfImage;
				i++;
				istringstream iiis(SS[i]);
				iiis >> text >> numOfImage;
				string s3 = numOfImage;
				ui::Button* button = ui::Button::create(s2, s3, s2);
				m_Buttons.insert(s1, button);

				j--;
			}
			
		}
	}

	
}

Sprite * ResourceManager::getSpriteByID(int id)
{
	
	return m_Sprites.at(id);
}

ui::Button * ResourceManager::getButtonByID(int id)
{
	return m_Buttons.at(id);
}

Label * ResourceManager::getLabelByID(int id)
{
	return nullptr;
}

