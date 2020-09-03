//
//  ResultLayer.h
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#ifndef ResultLayer_h
#define ResultLayer_h

class ResultLayer : public cocos2d::Layer
{
public:
    float x_ = _director->getWinSize().width;
    float y_ = _director->getWinSize().height;
    
public:
    static cocos2d::Layer* createLayer();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(ResultLayer);
};
#endif /* ResultLayer_h */
