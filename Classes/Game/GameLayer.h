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
    float x_ = _director->getWinSize().width;
    float y_ = _director->getWinSize().height;
    int spriteSize_ = 30;
    int maxRandCoinCount_ = 8;
    
public:
    static cocos2d::Layer* createLayer();
    virtual bool init();
    CREATE_FUNC(GameLayer);
    
public:
    void PlayerCreate();
    void CoinCreate();
    void Timer(float dt);
};

#endif /* GameLayer_h */
