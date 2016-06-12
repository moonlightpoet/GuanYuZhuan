#include "MainScene.h"
#include "StoryScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* background = Sprite::create("images/fight_scene_background.jpg");
    background->setPosition(origin + visibleSize/2);
    background->setName("background");
    this->addChild(background);

    auto item1 = MenuItemImage::create("images/donglingguan_title.png",
                                        "images/donglingguan_title.png",
                                        CC_CALLBACK_1(MainScene::donglingguanCallback, this));

    auto item2 = MenuItemImage::create("images/zhanyanliang_title.png",
                                        "images/zhanyanliang_title.png",
                                        CC_CALLBACK_1(MainScene::yanliangCallback, this));

    item1->setPosition(Vec2(origin.x + visibleSize.width/3, origin.y + visibleSize.height/2));
    item2->setPosition(Vec2(origin.x + visibleSize.width*2/3, origin.y + visibleSize.height/2));

    auto menu = Menu::create(item1, item2, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = Label::createWithTTF("三国关羽传--月光诗人", "fonts/simkai.ttf", 40);

    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height*4/5));
    this->addChild(label);

    return true;
}


void MainScene::donglingguanCallback(Ref* pSender)
{
    auto director = Director::getInstance();
    std::string sceneName = "donglingguan";
    auto scene = StoryScene::createScene(sceneName);
    director->replaceScene(scene);
}

void MainScene::yanliangCallback(Ref* pSender)
{
    auto director = Director::getInstance();
    std::string sceneName = "yanliang";
    auto scene = StoryScene::createScene(sceneName);
    director->replaceScene(scene);
}
