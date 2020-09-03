//
//  RewardLayer.cpp
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#include <stdio.h>
#include "RewardLayer.h"
#include "RewardLayerController.h"
#include "PlayerInfomation.h"

USING_NS_CC;

Layer* RewardLayer::createLayer()
{
    return RewardLayer::create();
}

// on "init" you need to initialize your instance
bool RewardLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Label* label = Label::createWithTTF("GameScene-RewardLayer", "fonts/Marker Felt.ttf", fontSize_);
    label->setPosition(x_ * 0.5, y_ * 0.5);
    addChild(label);
    
    RewardLayerController* controller = new RewardLayerController();
    addChild(controller, -1, "Controller");
    
    MenuItemFont* menuItem1 = MenuItemFont::create("눌러서 로비로 넘어가세요!", this, menu_selector(RewardLayerController::Backto_LobbyScene));
    menuItem1->setScale(0.3, 0.3);
    
    Menu* menu = Menu::create(menuItem1, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(x_ * 0.5, y_ * 0.33);
    addChild(menu);
    
    PlayerInfo player = PlayerInfo::getInstance();
    
    std::string scoreText = "Money : ";
    scoreText.append(std::to_string(player.pPlayerInfo_->getMoney()));
    Label* scoreTextLabel = Label::createWithTTF(scoreText, "fonts/Marker Felt.ttf", fontSize_);
    scoreTextLabel->setPosition(x_ * 0.20, y_ * 0.75);
    addChild(scoreTextLabel);
    
    std::string ticketText = std::to_string(player.pPlayerInfo_->getTicket());
    ticketText.append(" / ");
    ticketText.append(std::to_string(player.pPlayerInfo_->maxTicket_));
    Label* ticketTextLabel = Label::createWithTTF(ticketText, "fonts/Marker Felt.ttf", fontSize_);
    ticketTextLabel->setPosition(x_ * 0.75, y_ * 0.75);
    addChild(ticketTextLabel);
    
    return true;
}
