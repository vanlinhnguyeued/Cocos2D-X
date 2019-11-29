

#include "LoadingScene.h"
#include "LogoScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* LoadingScene::createScene()
{
    return LoadingScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LoadingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//input srite sheet
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("listBee.plist", "listBee.png");

	const int numSpriteBee = 3;
	auto spriteBee = Sprite::createWithSpriteFrameName("bee1.png");
	spriteBee->setPosition(200, 200);
	addChild(spriteBee);
	//create animate
	Vector<SpriteFrame*> animationBee;
	animationBee.reserve(numSpriteBee);
	animationBee.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("bee2.png"));
	animationBee.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("bee3.png"));
	auto animation = Animation::createWithSpriteFrames(animationBee, 0.1f);
	auto animate = Animate::create(animation);
	spriteBee->runAction(RepeatForever::create(animate));

	//set rotate for spriteBee
	auto rotate45 = RotateBy::create(3.1f, 45.0f);
	//set move
	auto moveBeeToTop = MoveBy::create(5, Vec2(600, 900));
	//set Ease for spriteBee
	auto move_ease_elstic = EaseElasticInOut::create(moveBeeToTop->clone());
	auto move_ease_elstic2 = EaseElasticInOut::create(rotate45->clone());
	auto move_ease_in_back = move_ease_elstic->reverse();
	//auto move_ease_in_back2 = move_ease_elstic2->reverse();
	auto delay = DelayTime::create(0.5f);
	auto seq = Sequence::create(move_ease_elstic2, delay, move_ease_elstic, delay, move_ease_in_back, delay->clone(), nullptr);
	spriteBee->runAction(RepeatForever::create(seq));

	
	auto mewmew = Sprite::create("Sprites/mySprite.png");
	mewmew->setAnchorPoint(Vec2(0, 0));
	mewmew->setPosition(Vec2(0, 0));
	addChild(mewmew, -1);
	auto moveMewToTop1 = MoveBy::create(5, Vec2(500, 200));
	mewmew->runAction(moveMewToTop1);
	auto scaleDouble = ScaleTo::create(1.0f, 2.0f);
	mewmew->runAction(scaleDouble);
	//create Background
	auto bg = Sprite::create("Sprites/background.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	float scale = MAX(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
	bg->setScale(scale);
	addChild(bg, -2);

	scheduleUpdate();
    return true;
}



void LoadingScene::update(float deltaTime) {
	

}