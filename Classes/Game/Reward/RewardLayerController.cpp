//
//  RewardLayerController.cpp
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#include <stdio.h>
#include "LobbyScene.h"
#include "RewardLayerController.h"

USING_NS_CC;

void RewardLayerController::Backto_LobbyScene(Ref* pSender)
{
    Scene* lobby = LobbyScene::createScene();
    _director->popScene();
}
