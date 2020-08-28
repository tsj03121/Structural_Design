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
    
    float x = _director->getWinSize().width;
    float y = _director->getWinSize().height;
    
    Label* label = Label::createWithTTF("GameScene-RewardLayer", "fonts/Marker Felt.ttf", 15);
    label->setPosition(Vec2(x / 2, y / 2));
    addChild(label);
    
    RewardLayerController* controller = new RewardLayerController();
    addChild(controller, -1, "Controller");
    
    MenuItemImage* menuItem1 = MenuItemImage::create("CloseNormal.png","CloseSelected.png",this,menu_selector(RewardLayerController::Backto_LobbyScene));
    menuItem1->setScale(3, 3);
    Menu* menu = Menu::create(menuItem1, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(Vec2(x/2,y/3));
    addChild(menu);
    
    PlayerInfo player = PlayerInfo::getInstance();
    
    std::string scoreText = "Money : ";
    scoreText.append(std::to_string(player.pPlayerInfo_->getMoney()));
    Label* scoreTextLabel = Label::createWithTTF(scoreText, "fonts/Marker Felt.ttf", 15);
    scoreTextLabel->setPosition(x * 0.20, y * 0.75);
    addChild(scoreTextLabel);
    
    std::string ticketText = std::to_string(player.pPlayerInfo_->getTicket());
    ticketText.append(" / 5");
    Label* ticketTextLabel = Label::createWithTTF(ticketText, "fonts/Marker Felt.ttf", 15);
    ticketTextLabel->setPosition(x * 0.75, y * 0.75);
    addChild(ticketTextLabel);
    
    return true;
}
