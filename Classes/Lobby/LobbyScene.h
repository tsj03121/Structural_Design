//
//  LobbyScene.h
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#ifndef LobbyScene_h
#define LobbyScene_h
#include "cocos2d.h"

class LobbyScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(LobbyScene);
};

#endif /* LobbyScene_h */
