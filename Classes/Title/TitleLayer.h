//
//  TitleLayer.h
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#ifndef TitleLayer_h
#define TitleLayer_h

class TitleLayer : public cocos2d::Layer
{
public:
    float x_ = _director->getWinSize().width;
    float y_ = _director->getWinSize().height;
    int fontSize_ = 15;
    
public:
    static cocos2d::Layer* createLayer();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(TitleLayer);
};

#endif /* TitleLayer_h */
