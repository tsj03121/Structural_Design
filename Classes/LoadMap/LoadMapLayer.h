//
//  LoadMapLayer.h
//  Structural_Design_Temp
//
//  Created by CD-parkdaedong on 2020/09/01.
//

#ifndef LoadMapLayer_h
#define LoadMapLayer_h

class LoadMapLayer : public cocos2d::Layer
{
public:
    float x_ = _director->getWinSize().width;
    float y_ = _director->getWinSize().height;
    
public:
    static cocos2d::Layer* createLayer();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(LoadMapLayer);
};

#endif /* LoadMapLayer_h */
