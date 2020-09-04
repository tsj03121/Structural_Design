//
//  MainLayer.h
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#ifndef MainLayer_h
#define MainLayer_h

class MainLayer : public cocos2d::Layer
{
public:
    static cocos2d::Layer* createLayer();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(MainLayer);
public:
    void MenuCreate();

};

#endif /* MainLayer_h */
