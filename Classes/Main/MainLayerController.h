//
//  MainController.h
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#ifndef MainLayerController_h
#define MainLayerController_h

class MainLayerController : public cocos2d::Node
{
    
public:
    void Change_LobbyLayer(cocos2d::Ref* pSender);
    void Goto_GameScene(cocos2d::Ref* pSender);
};
#endif /* MainController_h */
