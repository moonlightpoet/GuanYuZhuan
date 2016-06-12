#ifndef __STORY_SCENE_H__
#define __STORY_SCENE_H__

#include "cocos2d.h"
#include <cstdio>
#include <iostream>
#include <string>

class StoryScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(std::string directoryName);
    virtual bool init();
    void startStory();
    void menuContinueCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(StoryScene);
private:
    std::string directoryName;
    std::vector<std::string> vec;
    int lineNum = 0;
    void solveString(std::string s);
};

#endif // __HELLOWORLD_SCENE_H__
