#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void donglingguanCallback(cocos2d::Ref* pSender);
    void yanliangCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
};

#endif // __HELLOWORLD_SCENE_H__
