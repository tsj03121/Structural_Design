//
//  EditorScene.h
//  Structural_Design_Temp
//
//  Created by CD-parkdaedong on 2020/08/31.
//

#ifndef EditorScene_h
#define EditorScene_h

class EditorScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(EditorScene);
};


#endif /* EditorScene_h */
