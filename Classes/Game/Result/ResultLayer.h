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
    static cocos2d::Layer* createLayer();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(ResultLayer);
public:
    void LabelCreate();
};
#endif /* ResultLayer_h */
