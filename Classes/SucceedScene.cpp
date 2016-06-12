#include "SucceedScene.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"

USING_NS_CC;

Scene* SucceedScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SucceedScene::create();
    scene->addChild(layer);
    return scene;
}

bool SucceedScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* background = Sprite::create("images/succeed_scene_background.jpg");
    background->setPosition(origin + visibleSize/2);
    background->setName("background");
    this->addChild(background);

    auto backItem = MenuItemImage::create(
                                           "images/succeedNormal.png",
                                           "images/succeedSelected.png",
                                           CC_CALLBACK_1(SucceedScene::backCallback, this));

    backItem->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height/2));

    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}


void SucceedScene::backCallback(Ref* pSender)
{
    auto director = Director::getInstance();
    auto scene = MainScene::createScene();
    director->replaceScene(scene);
    return;

    //Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
}
