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
    int maxRandCoinCount_ = 8;
    
public:
    static cocos2d::Layer* createLayer();
    virtual bool init();
    CREATE_FUNC(GameLayer);
    
public:
    void ArrowKeyCreate();
    void HpImgCreate();
    void LabelCreate();
    void PlayerCreate();
    void CoinCreate();
    void Timer(float dt);
};

#endif /* GameLayer_h */
