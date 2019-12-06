#include "SimpleAudioEngine.h"
#include "SettingScene.h"
#include "ui/CocosGUI.h"
#include "MainMenuScene.h"
#include "ResourceManager.h"

using namespace cocos2d::ui;



USING_NS_CC;

static cocos2d::LayerColor* soundLayer;
static cocos2d::LayerColor* aboutLayer;

Scene* SettingScene::createScene()
{
    return SettingScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool SettingScene::init()
{

    if ( !Scene::init() )
    {
        return false;
    }
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bgrMainMenu = Sprite::create("Sprites/background.png");
	bgrMainMenu->setPosition(Vec2(0, 0));
	bgrMainMenu->setAnchorPoint(Vec2(0, 0));
	//set size for bgr
	auto targetSizeBGR = Size(visibleSize.width, visibleSize.height);
	auto sizeOrigBgr = bgrMainMenu->getContentSize();
	bgrMainMenu->setScale((targetSizeBGR.width / sizeOrigBgr.width), (targetSizeBGR.height / sizeOrigBgr.height));
	addChild(bgrMainMenu);

	//create label Setting
	auto lbMenu = Label::createWithSystemFont("SETTING", "Arial", 50);
	lbMenu->setAnchorPoint(Vec2(0.5, 0.5));
	lbMenu->setPosition(Vec2(visibleSize.width/2, 500));
	lbMenu->setColor(cocos2d::Color3B(180, 209, 218));
	lbMenu->enableOutline(cocos2d::Color4B::BLACK, 1);
	addChild(lbMenu);

	//create menu item
	//create lbSuondItem
	auto lbSoundItem = Label::createWithTTF("Sound", "fonts/VDOMCAS.TTF", 35);
	lbSoundItem->setAnchorPoint(Vec2(0.5, 0.5));
	lbSoundItem->setColor(cocos2d::Color3B(180, 209, 218));
	lbSoundItem->enableOutline(cocos2d::Color4B::BLACK, 2);
	//create item sound
	auto soundItem = MenuItemLabel::create(lbSoundItem, CC_CALLBACK_1(SettingScene::createSoundLayer, this));
	soundItem->setPosition(Vec2(visibleSize.width/2, 350));
	//create lbAboutItem
	auto lbAboutItem = Label::createWithTTF("About", "fonts/VDOMCAS.TTF", 35);
	lbAboutItem->setAnchorPoint(Vec2(0.5, 0.5));
	lbAboutItem->setColor(cocos2d::Color3B(180, 209, 218));
	lbAboutItem->enableOutline(cocos2d::Color4B::BLACK, 2);
	//create aboutItem
	auto aboutItem = MenuItemLabel::create(lbAboutItem, CC_CALLBACK_1(SettingScene::createAboutLayer, this));
	aboutItem->setPosition(Vec2(visibleSize.width / 2, 280));

	//create menu
	Vector<MenuItem*> menuItems;
	menuItems.pushBack(soundItem);
	menuItems.pushBack(aboutItem);
	auto menuSetting = Menu::createWithArray(menuItems);
	menuSetting->setPosition(Vec2(0, 0));
	addChild(menuSetting);

	auto btnBack = ResourceManager::getInstance()->getButtonByID(4);
	btnBack->setAnchorPoint(Vec2(0.5, 0.5));
	btnBack->setPosition(Vec2(20, 500));
	btnBack->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN: {

			break;
		}

		case ui::Widget::TouchEventType::ENDED:
		{
			auto MainMenuScene = MainMenuScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, MainMenuScene, Color3B(128, 0, 0)));
			break;
		}
		default:
			break;
		}
	});
	auto targetSizeStart = Size(30, 30);
	auto sizeOrigStart = btnBack->getContentSize();
	btnBack->setScale((targetSizeStart.width / sizeOrigStart.width), (targetSizeStart.height / sizeOrigStart.height));
	addChild(btnBack);

	//add text field
	auto tfNamePlyer = ui::TextField::create("Name player", "fonts/VDOMCAS.TTF", 25);
	tfNamePlyer->setColor(cocos2d::Color3B(180, 209, 218));
	tfNamePlyer->setAnchorPoint(Vec2(0.5, 0.5));
	tfNamePlyer->setPosition(Vec2(visibleSize.width/2, 210));
	addChild(tfNamePlyer);

	//create Sound layer
	soundLayer = cocos2d::LayerColor::create(Color4B(255, 208, 97, 255));
	soundLayer->setPosition(Vec2(0, visibleSize.height*0.1f));
	soundLayer->setContentSize(cocos2d::Size(visibleSize.width, visibleSize.height*0.8));
	//ResourceManager::getInstance()->getLabelByID(1)
	auto lbSound = Label::createWithTTF("Sound", "fonts/VDOMCAS.TTF", 35);
	lbSound->setAnchorPoint(Vec2(0.5, 0.5));
	lbSound->setColor(cocos2d::Color3B(180, 209, 218));
	lbSound->enableOutline(cocos2d::Color4B::BLACK, 2);
	lbSound->setPosition(Vec2(soundLayer->getContentSize().width / 2, soundLayer->getContentSize().height*0.8));
	soundLayer->addChild(lbSound);

	auto lbMusic = Label::createWithTTF("Music:", "fonts/VDOMCAS.TTF", 20);
	lbMusic->setAnchorPoint(Vec2(0.5, 0.5));
	lbMusic->setColor(cocos2d::Color3B(180, 209, 218));
	lbMusic->enableOutline(cocos2d::Color4B::BLACK, 2);
	lbMusic->setPosition(Vec2(soundLayer->getContentSize().width *0.25, soundLayer->getContentSize().height*0.5));
	soundLayer->addChild(lbMusic);

	auto checkboxMusic = ui::CheckBox::create("stop.png", "stop.png", "checkbox.png", "checkbox.png", "stop.png");
	checkboxMusic->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			log("checkbox 1 clicked");
			break;
		default:
			break;
		}
	});
	checkboxMusic->setAnchorPoint(Vec2(0.5, .5));
	checkboxMusic->setPosition(Vec2(soundLayer->getContentSize().width *0.75, soundLayer->getContentSize().height*0.5));
	soundLayer->addChild(checkboxMusic);

	auto lbSoundCB = Label::createWithTTF("Sound:", "fonts/VDOMCAS.TTF", 20);
	lbSoundCB->setAnchorPoint(Vec2(0.5, 0.5));
	lbSoundCB->setColor(cocos2d::Color3B(180, 209, 218));
	lbSoundCB->enableOutline(cocos2d::Color4B::BLACK, 2);
	lbSoundCB->setPosition(Vec2(soundLayer->getContentSize().width *0.25, soundLayer->getContentSize().height*0.6));
	soundLayer->addChild(lbSoundCB);

	auto checkboxSound = ui::CheckBox::create("stop.png", "stop.png", "checkbox.png", "checkbox.png", "stop.png");
	checkboxSound->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			log("checkbox 1 clicked");
			break;
		default:
			break;
		}
	});
	checkboxSound->setAnchorPoint(Vec2(0.5, .5));
	checkboxSound->setPosition(Vec2(soundLayer->getContentSize().width *0.75, soundLayer->getContentSize().height*0.6));
	soundLayer->addChild(checkboxSound);

	auto lbVolume = Label::createWithTTF("Volume:", "fonts/VDOMCAS.TTF", 20);
	lbVolume->setAnchorPoint(Vec2(0.5, 0.5));
	lbVolume->setColor(cocos2d::Color3B(180, 209, 218));
	lbVolume->enableOutline(cocos2d::Color4B::BLACK, 2);
	lbVolume->setPosition(Vec2(soundLayer->getContentSize().width *0.25, soundLayer->getContentSize().height*0.4));
	soundLayer->addChild(lbVolume);

	auto soundSlider = ui::Slider::create();
	soundSlider->loadBarTexture("Sprites/slider_bar_bg.png");
	soundSlider->loadSlidBallTextures("Sprites/slider_ball_normal.png", "Sprites/slider_ball_pressed.png", "Sprites/slider_ball_disable.png");
	soundSlider->loadProgressBarTexture("Sprites/slider_bar_pressed.png");
	soundSlider->setPercent(75);
	soundSlider->setAnchorPoint(Vec2(0.5, 1));
	soundSlider->setPosition(Vec2(soundLayer->getContentSize().width *0.6, soundLayer->getContentSize().height*0.4));
	soundLayer->addChild(soundSlider);
	addChild(soundLayer);
	soundLayer->setVisible(false);
	//end sound layer

	//crate about layer
	aboutLayer = cocos2d::LayerColor::create(Color4B(255, 208, 97, 255));
	aboutLayer->setPosition(Vec2(0, visibleSize.height*0.1f));
	aboutLayer->setContentSize(cocos2d::Size(visibleSize.width, visibleSize.height*0.8));

	auto lbAbout = Label::createWithTTF("About", "fonts/VDOMCAS.TTF", 35);
	lbAbout->setAnchorPoint(Vec2(0.5, 0.5));
	lbAbout->setColor(cocos2d::Color3B(180, 209, 218));
	lbAbout->enableOutline(cocos2d::Color4B::BLACK, 2);
	lbAbout->setPosition(Vec2(aboutLayer->getContentSize().width / 2, aboutLayer->getContentSize().height*0.8));
	aboutLayer->addChild(lbAbout);

	//Create ScrollView
	auto scrollView = ui::ScrollView::create();
	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	scrollView->setContentSize(Size(aboutLayer->getContentSize().width*0.8, aboutLayer->getContentSize().height*0.5));
	scrollView->setBounceEnabled(true);
	scrollView->setAnchorPoint(Vec2(0.5, 0.5));
	scrollView->setPosition(Vec2(aboutLayer->getContentSize().width*0.5, aboutLayer->getContentSize().height*0.5));
	scrollView->setInnerContainerSize(Size(250, 200));
	//add item to scroll
	auto about1 = Label::createWithTTF("Developer(s): NVLinh\nPublisher(s): Nintendo\nCreator(s): Shigeru Miyamoto\nComposer(s): Koji Kondo", "fonts/VDOMCAS.TTF", 16);
	about1->setAnchorPoint(Vec2(0.5, .5));
	about1->setPosition(Vec2(scrollView->getContentSize().width/2, scrollView->getContentSize().height/2));
	scrollView->addChild(about1);
	aboutLayer->addChild(scrollView);
	addChild(aboutLayer);
	aboutLayer->setVisible(false);
	//end about layer


	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event) {
		if (soundLayer->isVisible() == true) {
			soundLayer->setVisible(false);
		}

		if (aboutLayer->isVisible() == true) {
			aboutLayer->setVisible(false);
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);



	scheduleUpdate();
    return true;
}

void SettingScene::createSoundLayer(Ref * pSender)
{
	if (soundLayer->isVisible() == false) {
		soundLayer->setVisible(true);
	}
}

void SettingScene::createAboutLayer(Ref * pSender)
{
	if (aboutLayer->isVisible() == false) {
		aboutLayer->setVisible(true);
	}
}
void SettingScene::SoundOnClick(Ref* pSender) {

}
