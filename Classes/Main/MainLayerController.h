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
    void Load_Map(cocos2d::Ref* pSender);
    void Goto_MapEditor(cocos2d::Ref* pSender);
    void Select_Map(cocos2d::Ref* pSender);
};
#endif /* MainController_h */
