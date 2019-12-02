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


	//Create LayoutSound
	layoutSound = ui::Layout::create();
	layoutSound->setContentSize(cocos2d::Size(250, 50));
	layoutSound->setAnchorPoint(Vec2(0, 1));
	layoutSound->setPosition(Vec2(200, 200));
	addChild(layoutSound);
	//create slider
	auto soundSlider = ui::Slider::create();
	soundSlider->loadBarTexture("Sprites/slider_bar_bg.png");
	soundSlider->loadSlidBallTextures("Sprites/slider_ball_normal.png", "Sprites/slider_ball_pressed.png", "Sprites/slider_ball_disable.png");
	soundSlider->loadProgressBarTexture("Sprites/slider_bar_pressed.png");
	soundSlider->setPercent(75);
	soundSlider->setAnchorPoint(Vec2(0, 1));
	soundSlider->setPosition(Vec2(0, 35));
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
	checkboxSound->setPosition(Vec2(220, 40));
	layoutSound->addChild(checkboxSound);
	layoutSound->setVisible(false);
	
	
	
	//Create Layout About
	layoutAbout = ui::Layout::create();
	layoutAbout->setContentSize(cocos2d::Size(250, 200));
	layoutAbout->setAnchorPoint(Vec2(0, 1));
	layoutAbout->setPosition(Vec2(200, 160));
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
	auto about1 = Label::createWithTTF("Genre(s): Platform", "fonts/VDOMCAS.TTF", 18);
	about1->setAnchorPoint(Vec2(0, 0.5));
	about1->setPosition(Vec2(10, 180));
	scrollView->addChild(about1);
	/*auto about2 = Label::createWithTTF("Developer(s): Nintendo EAD (1985–2015)", "fonts/VDOMCAS.TTF", 18);
	about2->setPosition(Vec2(80, 160));
	scrollView->addChild(about2);
	about2->setPosition(Vec2(scrollView->getContentSize().width / 10, 50));
	scrollView->addChild(about2);
	auto about3 = Label::createWithTTF("Publisher(s): Nintendo", "fonts/VDOMCAS.TTF", 18);
	scrollView->addChild(about3);
	about3->setPosition(Vec2(scrollView->getContentSize().width / 10, 100));
	auto about4 = Label::createWithTTF("Creator(s): Shigeru Miyamoto", "fonts/VDOMCAS.TTF", 18);
	scrollView->addChild(about4);
	about4->setPosition(Vec2(scrollView->getContentSize().width / 10,150));
	auto about5 = Label::createWithTTF("Composer(s): Koji Kondo", "fonts/VDOMCAS.TTF", 18);
	scrollView->addChild(about5);
	about5->setPosition(Vec2(scrollView->getContentSize().width / 10, 200));
	auto about6 = Label::createWithTTF("Latest release: Super Mario Maker 2", "fonts/VDOMCAS.TTF", 18);
	scrollView->addChild(about6);
	about6->setPosition(Vec2(scrollView->getContentSize().width / 10, 250));
	Vector<Label*> labelItem;
	labelItem.pushBack(about1);
	labelItem.pushBack(about2);
	labelItem.pushBack(about3);
	labelItem.pushBack(about4);
	labelItem.pushBack(about5);
	labelItem.pushBack(about6);
	scrollView->addChild(labelItem);
	*/
	layoutAbout->addChild(scrollView);
	layoutAbout->setVisible(false);

	//create menu item
	//create lbSuondItem
	auto lbSuondItem = Label::createWithTTF("Sound:", "fonts/VDOMCAS.TTF", 20);
	lbSuondItem->setAnchorPoint(Vec2(0.5, 0.5));
	lbSuondItem->setColor(cocos2d::Color3B(139, 0, 0));
	lbSuondItem->enableOutline(cocos2d::Color4B::BLACK, 1);
	//create item sound
	auto soundItem = MenuItemLabel::create(lbSuondItem, CC_CALLBACK_1(SettingScene::SoundOnClick, this));
	soundItem->setPosition(Vec2(150, 180));

	//create lbAboutItem
	auto lbAboutItem = Label::createWithTTF("About:", "fonts/VDOMCAS.TTF", 20);
	lbAboutItem->setAnchorPoint(Vec2(0.5, 0.5));
	lbAboutItem->setColor(cocos2d::Color3B(139, 0, 0));
	lbAboutItem->enableOutline(cocos2d::Color4B::BLACK, 1);
	//create aboutItem
	auto aboutItem = MenuItemLabel::create(lbAboutItem, CC_CALLBACK_1(SettingScene::AboutOnClick, this));
	aboutItem->setPosition(Vec2(150, 140));

	//create menu
	Vector<MenuItem*> menuItems;
	menuItems.pushBack(soundItem);
	menuItems.pushBack(aboutItem);
	auto menuSetting = Menu::createWithArray(menuItems);
	menuSetting->setPosition(Vec2(0, 0));
	addChild(menuSetting);


	//add text field
	auto tfNamePlyer = ui::TextField::create("Name player", "fonts/VDOMCAS.TTF", 18);
	tfNamePlyer->setColor(cocos2d::Color3B(255, 6, 6));
	tfNamePlyer->setPosition(Vec2(400, 230));
	addChild(tfNamePlyer);

	auto btnEditName = ui::Button::create("pencil.png", "pencil.png", "pencil.png");
	btnEditName->setPosition(Vec2(450, 230));
	addChild(btnEditName);

	// add button done
	auto lbDone = Label::createWithTTF("Done", "fonts/VDOMCAS.TTF", 20);
	lbDone->setColor(cocos2d::Color3B(139, 0, 0));
	lbDone->enableOutline(cocos2d::Color4B::BLACK, 1);
	auto btnDone = ui::Button::create();
	btnDone->setPosition(Vec2(150, 230));
	btnDone->setTitleLabel(lbDone);
	btnDone->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN: {
			auto sceneMainMenu = MainMenuScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, sceneMainMenu, Color3B(128, 0, 0)));
			break;
		}

		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	addChild(btnDone);

	


	
	scheduleUpdate();
    return true;
}

void SettingScene::update(float deltaTime) {
	
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