#include "FightScene.h"
#include "SucceedScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* FightScene::createScene(std::string heroName, std::string enemyName)
{
    auto scene = Scene::create();
    auto layer = FightScene::create();
    layer->heroName = heroName;
    layer->enemyName = enemyName;
    scene->addChild(layer);
    layer->startFight();
    return scene;
}

bool FightScene::init()
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


    /*auto sprite = Sprite::create("HelloWorld.png");

    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x + cntt, visibleSize.height/2 + origin.y + cntt));

    this->addChild(sprite, 0);

    in = fopen("Resources/scene01.txt", "r");
    cntt = 0;*/

    return true;
}

void FightScene::startFight()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/fight-role.plist","images/fight-role.png");

    std::string names[2] = {heroName, enemyName};
    for (int i = 0; i < 2; i ++)
    {
        std::string name = names[i];
        auto animation = Animation::create();
        animation->setDelayPerUnit(1.0f / 10.0f);
        for (int j = 0; j < 3; j ++)
        {
            auto sfName = String::createWithFormat("%s-attack%04d.png", name.c_str(), j)->getCString();
            animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(sfName));
        }
        AnimationCache::getInstance()->addAnimation(animation, String::createWithFormat("%s-attack", name.c_str())->getCString());
    }

    SpriteFrame* heroFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("guanyu-stand.png");
    hero = Sprite::createWithSpriteFrame(heroFrame);
    hero->setPosition(origin.x + visibleSize.width/5, origin.y + visibleSize.height/2);
    hero->setName("hero");
    this->addChild(hero);

    SpriteFrame* enemyFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("kongxiu-stand.png");
    enemy = Sprite::createWithSpriteFrame(enemyFrame);
    enemy->setPosition(origin.x + visibleSize.width*4/5, origin.y + visibleSize.height/2);
    enemy->setName("enemy");
    this->addChild(enemy);

    auto label = Label::createWithTTF(heroName, "fonts/simkai.ttf", 24);

    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 1);



    auto closeItem = MenuItemImage::create(
                                           "images/attackNormal.png",
                                           "images/attackSelected.png",
                                           CC_CALLBACK_1(FightScene::attackCallback, this));

    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}


void FightScene::attackCallback(Ref* pSender)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    std::string animationName = heroName + "-attack";
    auto animation = AnimationCache::getInstance()->getAnimation(animationName.c_str());
    auto animate = Repeat::create(Animate::create(animation), 1);
    auto moveTo = MoveTo::create(2, Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    auto func = [&]()
    {
        this->removeChildByName("enemy");
        auto director = Director::getInstance();
        auto scene = SucceedScene::createScene();
        director->replaceScene(scene);
    };
    auto callback = CallFunc::create(func);
    Sequence* seq = Sequence::create(moveTo, animate, animate->reverse(), callback, NULL);

    //hero->runAction(animate);
    hero->runAction(seq);

    /*char s[3025];
    s[0] = 0;
    //fgets(s, 1024, in);
    fscanf(in, "%s" , s);

    if (feof(in))
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        auto label = Label::createWithTTF( "NOT HAHA", "fonts/simkai.ttf", 24);

        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

        this->addChild(label, 1);
        return;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::createWithTTF( s, "fonts/simkai.ttf", 24);

    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    this->removeChildByName("background");
    this->addChild(label, 1);

    //Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
*/
}
