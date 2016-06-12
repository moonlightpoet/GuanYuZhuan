#include "StoryScene.h"
#include "SimpleAudioEngine.h"
#include "FightScene.h"

USING_NS_CC;

Scene* StoryScene::createScene(std::string _directoryName)
{
    auto scene = Scene::create();
    auto layer = StoryScene::create();
    layer->directoryName = _directoryName;
    layer->startStory();
    scene->addChild(layer);
    return scene;
}

void StoryScene::solveString(std::string s)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    int index = s.find_first_of(":", 0);
    std::string s1 = s.substr(0, index);
    std::string s2 = s.substr(index+1);
    if (s1 == "scene") {
        if (this->getChildByName("background"))
            this->removeChildByName("background");
        std::string s = "images/" + s2 + ".jpg";
        Sprite* background = Sprite::create(s.c_str());
        background->setPosition(origin + visibleSize/2);
        background->setName("background");
        this->addChild(background);
    } else {
        if (this->getChildByName("word"))
            this->removeChildByName("word");
        auto label = Label::createWithTTF(s2, "fonts/simkai.ttf", 40);

        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2));

        label->setName("word");
        this->addChild(label);

        if (this->getChildByName("speaker"))
            this->removeChildByName("speaker");
        if (s1 != "background") {
            std::string s = "images/" + s1 + ".png";
            Sprite* speaker = Sprite::create(s.c_str());
            if (s1 != "guanyu")
                speaker->setPosition(origin + speaker->getContentSize()/2);
            else
                speaker->setPosition(origin.x + visibleSize.width - speaker->getContentSize().width/2,
                                        origin.y + speaker->getContentSize().width/2);
            speaker->setName("speaker");
            this->addChild(speaker);
        }
    }

    auto continueItem = MenuItemImage::create(
                                           "images/continueNormal.png",
                                           "images/continueSelected.png",
                                           CC_CALLBACK_1(StoryScene::menuContinueCallback, this));

    continueItem->setPosition(Vec2(origin.x + visibleSize.width - continueItem->getContentSize().width/2 ,
                                origin.y + continueItem->getContentSize().height/2));

    auto menu = Menu::create(continueItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void StoryScene::startStory()
{
    std::string sceneFileName = "Resources/" + directoryName + "/scene.txt";
    FILE* in = fopen(sceneFileName.c_str(), "r");
    char ch[1010];
    std::string s;
    vec.clear();
    while (fscanf(in, "%s", ch) != EOF)
    {
        s = ch;
        vec.push_back(s);
    }
    solveString(vec[lineNum++]);
}

bool StoryScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }


    //auto label = Label::createWithTTF("你好，世界", "fonts/simkai.ttf", 24);
    /*auto label = Label::createWithTTF(directoryName, "fonts/simkai.ttf", 24);

    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 1);

    auto sprite = Sprite::create("HelloWorld.png");

    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    this->addChild(sprite, 0);*/

    return true;
}


void StoryScene::menuContinueCallback(Ref* pSender)
{
    if (lineNum >= vec.size())
    {
        auto director = Director::getInstance();
        std::string heroName = "guanyu";
        std::string enemyName = "kongxiu";
        auto scene = FightScene::createScene(heroName, enemyName);
        director->replaceScene(scene);
        return;
    }
    std::string s = vec[lineNum++];
    solveString(s);
}


