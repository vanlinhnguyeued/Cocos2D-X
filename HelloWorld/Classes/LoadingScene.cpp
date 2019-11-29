/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

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
	auto rotate45 = RotateBy::create(1.1f, 45.0f);
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

	//create Background
	auto mewmew = Sprite::create("Sprites/image2.png");
	mewmew->setAnchorPoint(Vec2(0, 0));
	mewmew->setPosition(Vec2(0, 0));
	addChild(mewmew, -1);
	auto moveMewToTop1 = MoveBy::create(5, Vec2(500, 200));
	mewmew->runAction(moveMewToTop1);
	scheduleUpdate();
    return true;
}



void LoadingScene::update(float deltaTime) {
	

}