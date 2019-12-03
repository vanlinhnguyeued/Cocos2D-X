#include "SimpleAudioEngine.h"
#include "SettingScene.h"
#include "ui/CocosGUI.h"
#include "MainMenuScene.h"

using namespace cocos2d::ui;



USING_NS_CC;

static cocos2d::ui::Layout* layoutSound;
static cocos2d::ui::Layout* layoutAbout;
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


	//Create LayoutSound
	layoutSound = ui::Layout::create();
	layoutSound->setContentSize(cocos2d::Size(200, 50));
	layoutSound->setAnchorPoint(Vec2(0, 1));
	layoutSound->setPosition(Vec2(visibleSize.width / 5 + 50, 300));
	addChild(layoutSound);
	//create slider
	auto soundSlider = ui::Slider::create();
	soundSlider->loadBarTexture("Sprites/slider_bar_bg.png");
	soundSlider->loadSlidBallTextures("Sprites/slider_ball_normal.png", "Sprites/slider_ball_pressed.png", "Sprites/slider_ball_disable.png");
	soundSlider->loadProgressBarTexture("Sprites/slider_bar_pressed.png");
	soundSlider->setPercent(75);
	soundSlider->setAnchorPoint(Vec2(0, 1));
	soundSlider->setPosition(Vec2(0,100));
	soundSlider->setSize(Size(200, 10));
	layoutSound->addChild(soundSlider);
	//create checkbox
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
	checkboxSound->setAnchorPoint(Vec2(0, 1));
	checkboxSound->setPosition(Vec2(210, 105));
	layoutSound->addChild(checkboxSound);
	layoutSound->setVisible(false);
	
	
	
	//Create Layout About
	layoutAbout = ui::Layout::create();
	layoutAbout->setContentSize(cocos2d::Size(250, 200));
	layoutAbout->setAnchorPoint(Vec2(0, 1));
	layoutAbout->setPosition(Vec2(visibleSize.width / 5+50, 300));
	addChild(layoutAbout);
	//Create ScrollView
	auto scrollView = ui::ScrollView::create();
	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	scrollView->setContentSize(Size(layoutAbout->getContentSize().width, layoutAbout->getContentSize().height));
	scrollView->setBounceEnabled(true);
	scrollView->setAnchorPoint(Vec2(0, 1));
	scrollView->setPosition(Vec2(0, 200));
	scrollView->setInnerContainerSize(Size(250, 200));
	//add item to scroll
	auto about1 = Label::createWithTTF("Developer(s): NVLinh\nPublisher(s): Nintendo\nCreator(s): Shigeru Miyamoto\nComposer(s): Koji Kondo", "fonts/VDOMCAS.TTF", 16);
	about1->setAnchorPoint(Vec2(0, 0.5));
	about1->setPosition(Vec2(10, 180));
	scrollView->addChild(about1);
	layoutAbout->addChild(scrollView);
	layoutAbout->setVisible(false);

	//create menu item
	//create lbSuondItem
	auto lbSuondItem = Label::createWithTTF("Sound", "fonts/VDOMCAS.TTF", 35);
	lbSuondItem->setAnchorPoint(Vec2(0.5, 0.5));
	lbSuondItem->setColor(cocos2d::Color3B(180, 209, 218));
	lbSuondItem->enableOutline(cocos2d::Color4B::BLACK, 2);
	//create item sound
	auto soundItem = MenuItemLabel::create(lbSuondItem, CC_CALLBACK_1(SettingScene::SoundOnClick, this));
	soundItem->setPosition(Vec2(visibleSize.width/2, 350));

	//create lbAboutItem
	auto lbAboutItem = Label::createWithTTF("About:", "fonts/VDOMCAS.TTF", 35);
	lbAboutItem->setAnchorPoint(Vec2(0.5, 0.5));
	lbAboutItem->setColor(cocos2d::Color3B(180, 209, 218));
	lbAboutItem->enableOutline(cocos2d::Color4B::BLACK, 2);
	//create aboutItem
	auto aboutItem = MenuItemLabel::create(lbAboutItem, CC_CALLBACK_1(SettingScene::AboutOnClick, this));
	aboutItem->setPosition(Vec2(visibleSize.width / 2, 280));

	//create menu
	Vector<MenuItem*> menuItems;
	menuItems.pushBack(soundItem);
	menuItems.pushBack(aboutItem);
	auto menuSetting = Menu::createWithArray(menuItems);
	menuSetting->setPosition(Vec2(0, 0));
	addChild(menuSetting);


	//add text field
	auto tfNamePlyer = ui::TextField::create("Name player", "fonts/VDOMCAS.TTF", 25);
	tfNamePlyer->setColor(cocos2d::Color3B(180, 209, 218));
	tfNamePlyer->setAnchorPoint(Vec2(0.5, 0.5));
	tfNamePlyer->setPosition(Vec2(visibleSize.width/2, 210));
	addChild(tfNamePlyer);

	scheduleUpdate();
    return true;
}

void SettingScene::createSoundLayer(Ref * pSender)
{
}

void SettingScene::createAboutLayer(Ref * pSender)
{
}
void SettingScene::SoundOnClick(Ref* pSender) {

		
		if (layoutSound->isVisible() == false) {
			layoutSound->setVisible(true);
		}
		else layoutSound->setVisible(false);

}
void SettingScene::AboutOnClick(Ref* pSender) {
	
	if (layoutAbout->isVisible() == false) {
		layoutAbout->setVisible(true);
	}
	else layoutAbout->setVisible(false);
}

void SettingScene::ChangePlayerName(Ref * pSender)
{
}
