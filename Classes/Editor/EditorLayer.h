//
//  EditorLayer.h
//  Structural_Design_Temp
//
//  Created by CD-parkdaedong on 2020/08/31.
//

#ifndef EditorLayer_h
#define EditorLayer_h

class EditorLayer : public cocos2d::Layer
{
public:
    float x_ = _director->getWinSize().width;
    float y_ = _director->getWinSize().height;

public:
    static cocos2d::Layer* createLayer();

    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(EditorLayer);\
    
public:
    void Timer(float dt);
};


#endif /* EditorLayer_h */
