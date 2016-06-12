#ifndef __FIGHT_SCENE_H__
#define __FIGHT_SCENE_H__

#include "cocos2d.h"
#include <string>

class FightScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(std::string heroName, std::string enemyName);
    virtual bool init();
    virtual void startFight();
    //void menuCloseCallback(cocos2d::Ref* pSender);
    void attackCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(FightScene);
private:
    std::string heroName;
    std::string enemyName;
    cocos2d::Sprite* hero;
    cocos2d::Sprite* enemy;
    FILE *in;
    int cntt;
};

#endif // __HELLOWORLD_SCENE_H__
