#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "MainMenuScene.h"
#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"



USING_NS_CC;

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

	auto bgrMainMenu = Sprite::create("backgroundMainMenu.png");
	bgrMainMenu -> setPosition(Vec2(0, 0));
	bgrMainMenu->setAnchorPoint(Vec2(0, 0));
	//set size for bgr
	auto targetSizeBGR = Size(560.0f, 320.0f);
	auto sizeOrigBgr = bgrMainMenu->getContentSize();
	bgrMainMenu->setScale((targetSizeBGR.width / sizeOrigBgr.width), (targetSizeBGR.height / sizeOrigBgr.height));
	addChild(bgrMainMenu);

	//set label
	auto lbMenu = Label::createWithTTF("Menu", "fonts/VDOMCAS.TTF", 60);
	lbMenu->setAnchorPoint(Vec2(0.5, 0.5));
	lbMenu->setPosition(Vec2(280, 280));
	lbMenu->setColor(cocos2d::Color3B(139, 0, 0));
	lbMenu->enableOutline(cocos2d::Color4B::BLACK, 1);
	addChild(lbMenu);


	//set label Newgame
	auto lbNewGame = Label::createWithTTF("New Game", "fonts/VDOMCAS.TTF", 30);
	lbNewGame->setAnchorPoint(Vec2(0.5, 0.5));
	lbNewGame->setColor(cocos2d::Color3B(139, 0, 0));
	lbNewGame->enableOutline(cocos2d::Color4B::BLACK, 1);
	//set button Newgame "Buttons/setting_normal.png","Buttons/setting_pressed.png"
	auto btnNewGame = ui::Button::create();
	btnNewGame->setAnchorPoint(Vec2(0.5, 0.5));
	btnNewGame->setPosition(Vec2(280, 200));
	btnNewGame->setTitleLabel(lbNewGame);
	btnNewGame->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:{
			auto sceneHelloWorld = HelloWorld::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, sceneHelloWorld, Color3B(128, 0, 0)));
			break; 
		}
			
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	addChild(btnNewGame);

	//set label setting
	auto lbSetting = Label::createWithTTF("Setting", "fonts/VDOMCAS.TTF", 30);
	lbSetting->setAnchorPoint(Vec2(0.5, 0.5));
	lbSetting->setColor(cocos2d::Color3B(139, 0, 0));
	lbSetting->enableOutline(cocos2d::Color4B::BLACK, 1);
	//set button setting
	auto btnSetting = ui::Button::create();
	btnSetting->setAnchorPoint(Vec2(0.5, 0.5));
	btnSetting->setPosition(Vec2(280, 160));
	btnSetting->setTitleLabel(lbSetting);
	btnSetting->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	addChild(btnSetting);

	//set label Exit
	auto lbExit = Label::createWithTTF("Exit", "fonts/VDOMCAS.TTF", 30);
	lbExit->setAnchorPoint(Vec2(0.5, 0.5));
	lbExit->setColor(cocos2d::Color3B(139, 0, 0));
	lbExit->enableOutline(cocos2d::Color4B::BLACK, 1);
	//set button Exit
	auto btnExit = ui::Button::create();
	btnExit->setAnchorPoint(Vec2(0.5, 0.5));
	btnExit->setPosition(Vec2(280, 120));
	btnExit->setTitleLabel(lbExit);
	btnExit->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN: {
			Director::getInstance()->end();
			break;
		}
			
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	addChild(btnExit);


	
	scheduleUpdate();
    return true;
}

void MainMenuScene::update(float deltaTime) {
	
}
//void menuCloseCallback(cocos2d::Ref* pSender) {
//	
//}
