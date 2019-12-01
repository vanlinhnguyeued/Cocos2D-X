#include "SimpleAudioEngine.h"
#include "SettingScene.h"
#include "ui/CocosGUI.h"



USING_NS_CC;

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

	auto bgrMainMenu = Sprite::create("backgroundMainMenu.png");
	bgrMainMenu -> setPosition(Vec2(0, 0));
	bgrMainMenu->setAnchorPoint(Vec2(0, 0));
	//set size for bgr
	auto targetSizeBGR = Size(560.0f, 320.0f);
	auto sizeOrigBgr = bgrMainMenu->getContentSize();
	bgrMainMenu->setScale((targetSizeBGR.width / sizeOrigBgr.width), (targetSizeBGR.height / sizeOrigBgr.height));
	addChild(bgrMainMenu);

	//create label Setting
	auto lbMenu = Label::createWithTTF("Setting", "fonts/VDOMCAS.TTF", 60);
	lbMenu->setAnchorPoint(Vec2(0.5, 0.5));
	lbMenu->setPosition(Vec2(280, 280));
	lbMenu->setColor(cocos2d::Color3B(139, 0, 0));
	lbMenu->enableOutline(cocos2d::Color4B::BLACK, 1);
	addChild(lbMenu);

	//create menu item
	//create lbSuondItem
	auto lbSuondItem = Label::createWithTTF("Sound:", "fonts/VDOMCAS.TTF", 20);
	lbSuondItem->setAnchorPoint(Vec2(0.5, 0.5));
	lbSuondItem->setColor(cocos2d::Color3B(139, 0, 0));
	lbSuondItem->enableOutline(cocos2d::Color4B::BLACK, 1);
	//create item sound
	auto soundItem = MenuItemLabel::create(lbSuondItem);
	soundItem->setPosition(Vec2(150, 180));

	//create lbAboutItem
	auto lbAboutItem = Label::createWithTTF("About:", "fonts/VDOMCAS.TTF", 20);
	lbAboutItem->setAnchorPoint(Vec2(0.5, 0.5));
	lbAboutItem->setColor(cocos2d::Color3B(139, 0, 0));
	lbAboutItem->enableOutline(cocos2d::Color4B::BLACK, 1);
	//create aboutItem
	auto aboutItem = MenuItemLabel::create(lbAboutItem);
	aboutItem->setPosition(Vec2(150, 140));

	//create menu
	Vector<MenuItem*> menuItems;
	menuItems.pushBack(soundItem);
	menuItems.pushBack(aboutItem);
	auto menuSetting = Menu::createWithArray(menuItems);
	menuSetting->setPosition(Vec2(0, 0));
	addChild(menuSetting);


	//Create Layout
	auto layoutSound = ui::Layout::create();
	layoutSound->setContentSize(cocos2d::Size(250, 100));
	layoutSound->setAnchorPoint(Vec2(0, 1));
	layoutSound->setPosition(Vec2(200, 200));
	addChild(layoutSound);

	//create slider
	static auto soundSlider = ui::Slider::create();
	soundSlider->loadBarTexture("Sprites/slider_bar_bg.png");
	soundSlider->loadSlidBallTextures("Sprites/slider_ball_normal.png", "Sprites/slider_ball_pressed.png", "Sprites/slider_ball_disable.png");
	soundSlider->loadProgressBarTexture("Sprites/slider_bar_pressed.png");
	soundSlider->setPercent(75);
	soundSlider->setAnchorPoint(Vec2(0, 1));
	soundSlider->setPosition(Vec2(0, 85));
	layoutSound->addChild(soundSlider);

	//create checkbox
	auto checkboxSound = ui::CheckBox::create("stop.png","stop.png","checkbox.png","checkbox.png","stop.png");
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
	checkboxSound->setContentSize(cocos2d::Size(20, 20));
	checkboxSound->setAnchorPoint(Vec2(0, 1));
	checkboxSound->setPosition(Vec2(220, 90));
	layoutSound->addChild(checkboxSound);



	


	
	scheduleUpdate();
    return true;
}

void SettingScene::update(float deltaTime) {
	
}
