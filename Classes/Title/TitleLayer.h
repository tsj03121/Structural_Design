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
    static cocos2d::Layer* createLayer();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(TitleLayer);
};

#endif /* TitleLayer_h */
