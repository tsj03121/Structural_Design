//
//  LobbyLayerController.h
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#ifndef LobbyLayerController_h
#define LobbyLayerController_h
#include "cocos2d.h"
#include "LobbyLayer.h"

class LobbyLayerController : public cocos2d::Node
{
    
public:
    void Change_MainLayer(cocos2d::Ref* pSender);
    
public:
    LobbyLayerController(LobbyLayer* layer);
};

#endif /* LobbyLayerController_h */
