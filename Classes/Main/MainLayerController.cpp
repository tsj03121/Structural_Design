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
#include "DataIO.h"
#include "LoadMapLayer.h"

USING_NS_CC;

void MainLayerController::Goto_GameScene(Ref* pSender)
{
    PlayerInfo* playerInfo = PlayerInfo::getInstance();
    if(playerInfo->getTicket() > 0)
    {
        playerInfo->setTicket(playerInfo->getTicket() - 1);
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
    Layer* layer = LobbyLayer::createLayer();
    
    view->removeAllChildren();
    view->addChild(layer,1,"Layer");
}

void MainLayerController::Load_Map(Ref* pSender)
{
    Layer* loadLayer = LoadMapLayer::create();
}

void MainLayerController::Goto_MapEditor(Ref* pSender)
{
    EditorScene* scene = EditorScene::create();
    scene->setName("Editor");
    _director->pushScene(scene);
}
