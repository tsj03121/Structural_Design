//
//  GameLayer.h
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#ifndef GameLayer_h
#define GameLayer_h

class GameLayer : public cocos2d::Layer
{
public:
    static cocos2d::Layer* createLayer();

    virtual bool init();    
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);\
    
public:
    void Timer(float dt);
};

#endif /* GameLayer_h */
