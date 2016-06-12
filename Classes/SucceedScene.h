#ifndef __SUCCEED_SCENE_H__
#define __SUCCEED_SCENE_H__

#include "cocos2d.h"
#include <cstdio>

class SucceedScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void backCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(SucceedScene);
private:
    FILE *in;
    int cntt;
};

#endif // __HELLOWORLD_SCENE_H__
