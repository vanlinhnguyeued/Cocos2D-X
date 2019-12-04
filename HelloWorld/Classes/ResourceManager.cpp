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
				string s1 = numOfImage;
				log("%s", s1.c_str());
				i++;
				istringstream iis(SS[i]);
				iis >> text >> numOfImage;
				string s2 = numOfImage;

				j--;
			}
		}
	}

	
}

Sprite * ResourceManager::getSpriteByID(char id)
{
	
	return nullptr;
}

ui::Button * ResourceManager::getButtonByID(char id)
{
	return nullptr;
}

Label * ResourceManager::getLabelByID(char id)
{
	return nullptr;
}

