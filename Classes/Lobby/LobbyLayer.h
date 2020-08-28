//
//  LobbyLayer.h
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#ifndef LobbyLayer_h
#define LobbyLayer_h


class LobbyLayer : public cocos2d::Layer
{
public:
    cocos2d::MenuItemFont* menuItem1_;
    
public:
    static cocos2d::Layer* createLayer();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(LobbyLayer);
    
public:
    void Log(cocos2d::Ref* pSender);
};

#endif /* LobbyLayer_h */
