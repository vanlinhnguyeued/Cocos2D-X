#include "GamePlayScene.h"
#include "MainMenuScene.h"
#include "SettingScene.h"
#include "ui/CocosGUI.h"
#include "ResourceManager.h"
#include <ctime>
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;


USING_NS_CC;
auto bgrMusicMM = SimpleAudioEngine::getInstance();

auto bgrMusicPlayGame = SimpleAudioEngine::getInstance();
Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MainMenuScene::init()
{

    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//add music
	bgrMusicMM->playBackgroundMusic("Sounds/title.mp3", true);
	//Set background
	auto bgrMainMenu = Sprite::createWithSpriteFrame(ResourceManager::getInstance()->getSpriteByID(0)->getSpriteFrame());
	bgrMainMenu -> setPosition(Vec2(0, 0));
	bgrMainMenu->setAnchorPoint(Vec2(0, 0));
	auto targetSizeBGR = Size(visibleSize.width, visibleSize.height);
	auto sizeOrigBgr = bgrMainMenu->getContentSize();
	bgrMainMenu->setScale((targetSizeBGR.width / sizeOrigBgr.width), (targetSizeBGR.height / sizeOrigBgr.height));
	addChild(bgrMainMenu);

	//setSprite logo
	auto logoGame = Sprite::createWithSpriteFrame(ResourceManager::getInstance()->getSpriteByID(1)->getSpriteFrame());
	logoGame->setAnchorPoint(Vec2(0.5, 0.5));
	logoGame->setPosition(Vec2(visibleSize.width / 2, 500));
	auto targetSizeLogo = Size(250, 200);
	auto sizeOrigLogo = logoGame->getContentSize();
	logoGame->setScale((targetSizeLogo.width / sizeOrigLogo.width), (targetSizeLogo.height / sizeOrigLogo.height));
	addChild(logoGame);

	//create button Newgame 
	auto btnNewGame = ResourceManager::getInstance()->getButtonByID(0);
	btnNewGame->setAnchorPoint(Vec2(0.5, 0.5));
	btnNewGame->setPosition(Vec2(visibleSize.width/2, visibleSize.height / 2));
	btnNewGame->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
			auto GamePlayScene = GamePlayScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GamePlayScene, Color3B(0, 0, 0)));
			bgrMusicMM->stopBackgroundMusic();
			bgrMusicPlayGame->playBackgroundMusic("Sounds/ingame.mp3");
			break;
		}
		default:
			break;
		}
	});
	auto targetSizeStart = Size(70, 70);
	auto sizeOrigStart = btnNewGame->getContentSize();
	btnNewGame->setScale((targetSizeStart.width / sizeOrigStart.width), (targetSizeStart.height / sizeOrigStart.height));
	addChild(btnNewGame);

	//create button setting
	auto btnSetting = ResourceManager::getInstance()->getButtonByID(3);
	btnSetting->setAnchorPoint(Vec2(0.5, 0.5));
	btnSetting->setPosition(Vec2(9*visibleSize.width / 10, visibleSize.height/20));
	btnSetting->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN: break;
		case ui::Widget::TouchEventType::ENDED: {
			auto sceneSetting = SettingScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5f, sceneSetting, Color3B(0, 0, 0)));
			break;
		}
			
		default:
			break;
		}
	});
	auto targetSizeSetting = Size(50, 50);
	auto sizeOrigSetting = btnSetting->getContentSize();
	btnSetting->setScale((targetSizeSetting.width / sizeOrigSetting.width), (targetSizeSetting.height / sizeOrigSetting.height));
	addChild(btnSetting);

	auto particleMM = ParticleGalaxy::create();
	particleMM->setScale(0.8);
	particleMM->setAnchorPoint(Vec2(0.5, 0.5));
	particleMM->setPosition(Vec2(visibleSize.width / 2+80, 550));
	addChild(particleMM);

	scheduleUpdate();
    return true;
}

void MainMenuScene::update(float deltaTime) {
	
}
//void menuCloseCallback(cocos2d::Ref* pSender) {
//	
//}
