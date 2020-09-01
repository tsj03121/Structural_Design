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
#include "GameLayer.h"
#include "EditorScene.h"

USING_NS_CC;

void MainLayerController::Goto_GameScene(Ref* pSender)
{
    PlayerInfo playerInfo = PlayerInfo::getInstance();
    if(playerInfo.pPlayerInfo_->getTicket() > 0)
    {
        playerInfo.pPlayerInfo_->setTicket(playerInfo.pPlayerInfo_->getTicket()-1);
        Scene* game = GameScene::createScene();
        GameLayer* layer = (GameLayer*) game->getChildByName("View")->getChildByName("Layer");
        layer->PlayerCreate();
        layer->CoinCreate();
        _director->pushScene(game);
    }
}

void MainLayerController::Change_LobbyLayer(Ref* pSender)
{
    Scene* scene = _director->getRunningScene();
    Layer* view = (Layer*) scene->getChildByName("View");
    view->removeAllChildren();
    Layer* layer = LobbyLayer::createLayer();
    view->addChild(layer,1,"Layer");
}

void MainLayerController::Load_Map(Ref* pSender)
{
    PlayerInfo playerInfo = PlayerInfo::getInstance();
    if(playerInfo.pPlayerInfo_->getTicket() > 0)
    {
        playerInfo.pPlayerInfo_->setTicket(playerInfo.pPlayerInfo_->getTicket()-1);
        Scene* game = GameScene::createScene();
        GameLayer* layer = (GameLayer*) game->getChildByName("View")->getChildByName("Layer");
        layer->Load();
        _director->pushScene(game);
    }
}

void MainLayerController::Goto_MapEditor(Ref* pSender)
{
    EditorScene* scene = EditorScene::create();
    _director->pushScene(scene);
}
