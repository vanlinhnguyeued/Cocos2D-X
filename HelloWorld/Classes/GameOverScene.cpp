#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "GameOverScene.h"
#include "ResourceManager.h"
#include "MainMenuScene.h"
#include "GamePlayScene.h"

using namespace cocos2d::ui;



USING_NS_CC;

Scene* GameOverScene::createScene()
{
    return GameOverScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameOverScene::init()
{

    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//create background
	auto bgrMainBGR = Sprite::createWithSpriteFrame(ResourceManager::getInstance()->getSpriteByID(0)->getSpriteFrame());
	bgrMainBGR->setPosition(Vec2(0, 0));
	bgrMainBGR->setAnchorPoint(Vec2(0, 0));
	auto targetSizeBGR = Size(visibleSize.width, visibleSize.height);
	auto sizeOrigBgr = bgrMainBGR->getContentSize();
	bgrMainBGR->setScale((targetSizeBGR.width / sizeOrigBgr.width), (targetSizeBGR.height / sizeOrigBgr.height));
	addChild(bgrMainBGR);

	auto lbGO = Label::createWithTTF("Game Over", "fonts/arial.ttf", 30);
	lbGO->setAnchorPoint(Vec2(0.5, 0.5));
	lbGO->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.7));
	addChild(lbGO);
	auto lbYS = Label::createWithTTF("Your score:", "fonts/VDOMCAS.TTF", 20);
	lbYS->setAnchorPoint(Vec2(0.5, 0.5));
	lbYS->setPosition(Vec2(visibleSize.width / 2.5, visibleSize.height*0.6));
	addChild(lbYS);

	auto score = ResourceManager::getInstance()->getScore();
	log("%s", score.c_str());
	auto lbscore = Label::createWithTTF("Your score:", "fonts/VDOMCAS.TTF", 20);
	lbscore->setString(score);
	lbscore->setAnchorPoint(Vec2(0.5, 0.5));
	lbscore->setPosition(Vec2(visibleSize.width /2.5+60, visibleSize.height*0.6));
	addChild(lbscore);

	//ResourceManager::getInstance()->getButtonByID(2)
	auto btnBackHome = ui::Button::create("Buttons/home_normal.png", "Buttons/home_pressed.png", "Buttons/home_normal.png");
	btnBackHome->setAnchorPoint(Vec2(0.5, 0.5));
	btnBackHome->setPosition(Vec2(visibleSize.width*0.35, visibleSize.height*0.4));
	btnBackHome->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN: {

			break;
		}

		case ui::Widget::TouchEventType::ENDED:
		{
			
			auto MainMenuScene = MainMenuScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5f, MainMenuScene, Color3B(0, 0, 0)));

			break;
		}
		default:
			break;
		}
	});
	auto targetSizebtnBackHome = Size(50, 50);
	auto sizeOrigbtnBackHome = btnBackHome->getContentSize();
	btnBackHome->setScale((targetSizebtnBackHome.width / sizeOrigbtnBackHome.width), (targetSizebtnBackHome.height / sizeOrigbtnBackHome.height));
	addChild(btnBackHome);

	auto btnRS = ui::Button::create("Buttons/resume_normal.png", "Buttons/resume_pressed.png", "Buttons/resume_normal.png");
	btnRS->setAnchorPoint(Vec2(0.5, 0.5));
	btnRS->setPosition(Vec2(visibleSize.width*0.65, visibleSize.height*0.4));
	btnRS->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN: {

			break;
		}

		case ui::Widget::TouchEventType::ENDED:
		{
			removeChild(lbscore);
			auto GamePlayScene = GamePlayScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GamePlayScene, Color3B(0, 0, 0)));
			break;
		}
		default:
			break;
		}
	});
	auto targetSizebtnRS = Size(50, 50);
	auto sizeOrigbtnRS = btnRS->getContentSize();
	btnRS->setScale((targetSizebtnRS.width / sizeOrigbtnRS.width), (targetSizebtnRS.height / sizeOrigbtnRS.height));
	addChild(btnRS);

	scheduleUpdate();
    return true;
}

