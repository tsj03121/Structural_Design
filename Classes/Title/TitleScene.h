//
//  TitleScene.h
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#ifndef TitleScene_h
#define TitleScene_h

#include "cocos2d.h"

class TitleScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(TitleScene);
};

#endif /* TitleScene_h */
