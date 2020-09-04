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
#include "BasicDefine.h"

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
    
    LabelCreate();
    
    RewardLayerController* controller = new RewardLayerController();
    addChild(controller, -1, "Controller");
    
    MenuItemFont* menuItem1 = MenuItemFont::create("눌러서 로비로 넘어가세요!", this, menu_selector(RewardLayerController::Backto_LobbyScene));
    menuItem1->setScale(0.3, 0.3);
    
    Menu* menu = Menu::create(menuItem1, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(WINSIZE_X * 0.5, WINSIZE_Y * 0.33);
    addChild(menu);
    
    return true;
}

void RewardLayer::LabelCreate()
{
    PlayerInfo* playerInfo = PlayerInfo::getInstance();
    
    Label* label = Label::createWithTTF("GameScene-RewardLayer", FONTNAME, FONTSIZE);
    label->setPosition(WINSIZE_X * 0.5, WINSIZE_Y * 0.5);
    addChild(label);

    std::string scoreText = "Money : ";
    scoreText.append(std::to_string(playerInfo->getNowMoney()));
    Label* scoreTextLabel = Label::createWithTTF(scoreText, FONTNAME, FONTSIZE);
    scoreTextLabel->setPosition(WINSIZE_X * 0.20, WINSIZE_Y * 0.75);
    addChild(scoreTextLabel);
    
    std::string ticketText = std::to_string(playerInfo->getTicket());
    ticketText.append(" / ");
    ticketText.append(std::to_string(playerInfo->maxTicket_));
    Label* ticketTextLabel = Label::createWithTTF(ticketText, FONTNAME, FONTSIZE);
    ticketTextLabel->setPosition(WINSIZE_X * 0.75, WINSIZE_Y * 0.75);
    addChild(ticketTextLabel);
}
