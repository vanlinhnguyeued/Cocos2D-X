#include "RESOURCEMANAGER.H"
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

