//
//  LobbyLayerController.cpp
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#include <stdio.h>
#include "LobbyLayerController.h"
#include "MainLayer.h"
#include "LobbyLayer.h"
#include "PlayerInfomation.h"

USING_NS_CC;

LobbyLayerController::LobbyLayerController(LobbyLayer* layer)
{
    layer->menuItem1_->setCallback(CC_CALLBACK_1(LobbyLayerController::Change_MainLayer, this));
}

void LobbyLayerController::Change_MainLayer(Ref* pSender)
{
    Scene* scene = _director->getRunningScene();
    Layer* view = (Layer*) scene->getChildByName("View");
    view->removeAllChildren();
    
    Layer* layer = MainLayer::createLayer();
    view->addChild(layer,1,"Layer");
}

void LobbyLayerController::TicketBuy(Ref *pSender)
{
    PlayerInfo* playerInfo = PlayerInfo::getInstance();
    if(playerInfo->getTicket() > playerInfo->maxTicket_ - 1)
        return;
    
    playerInfo->setTicket(playerInfo->getTicket() + 1);
    
    Scene* scene = _director->getRunningScene();
    Layer* layer = (Layer*) scene->getChildByName("View")->getChildByName("Layer");
    
    Label* ticketTextLabel = (Label*) layer->getChildByName("TicKet");
    std::string ticketText = std::to_string(playerInfo->getTicket());
    ticketText.append(" / ");
    ticketText.append(std::to_string(playerInfo->maxTicket_));
    ticketTextLabel->setString(ticketText);
}
