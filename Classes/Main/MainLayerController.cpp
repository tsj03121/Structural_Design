//
//  MainLayerController.cpp
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#include <stdio.h>
#include "MainLayerController.h"
#include "LobbyLayer.h"
#include "GameScene.h"
#include "PlayerInfomation.h"

USING_NS_CC;

void MainLayerController::Goto_GameScene(Ref* pSender)
{
    PlayerInfo playerInfo = PlayerInfo::getInstance();
    if(playerInfo.pPlayerInfo_->getTicket() > 0)
    {
        playerInfo.pPlayerInfo_->setTicket(playerInfo.pPlayerInfo_->getTicket()-1);
        Scene* game = GameScene::createScene();
        _director->pushScene(game);
    }
}

USING_NS_CC;

void MainLayerController::Change_LobbyLayer(Ref* pSender)
{
    Scene* scene = _director->getRunningScene();
    Layer* view = (Layer*) scene->getChildByName("View");
    view->removeAllChildren();
    Layer* layer = LobbyLayer::createLayer();
    view->addChild(layer,1,"Layer");
}
