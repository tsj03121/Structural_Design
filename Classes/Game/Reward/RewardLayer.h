//
//  RewardLayer.h
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#ifndef RewardLayer_h
#define RewardLayer_h

class RewardLayer : public cocos2d::Layer
{
public:
    static cocos2d::Layer* createLayer();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(RewardLayer);
};

#endif /* RewardLayer_h */
