//
//  TitleLayerController.cpp
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#include <stdio.h>
#include "TitleLayerController.h"
#include "LobbyScene.h"

USING_NS_CC;

void TitleLayerController::Goto_LobbyScene(Ref* pSender)
{
    Scene* lobby = LobbyScene::createScene();
    _director->replaceScene(lobby);
}

