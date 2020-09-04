//
//  LobbyLayer.cpp
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#include <stdio.h>
#include "LobbyLayer.h"
#include "SimpleAudioEngine.h"
#include "LobbyLayerController.h"
#include "PlayerInfomation.h"

USING_NS_CC;

Layer* LobbyLayer::createLayer()
{
    return LobbyLayer::create();
}

// on "init" you need to initialize your instance
bool LobbyLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Label* label = Label::createWithTTF("LobbyScene-LobbyLayer", "fonts/Marker Felt.ttf", 15);
    label->setPosition(x_ * 0.5, y_ * 0.75);
    addChild(label);
    
    menuItem1_ = MenuItemFont::create("메 인 화 면");
    menuItem1_->setScale(0.3, 0.3);
    
    Menu* menu = Menu::create(menuItem1_, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(x_ * 0.5, y_ * 0.25);
    addChild(menu);
    
    LobbyLayerController* controller = new LobbyLayerController(this);
    addChild(controller, -1, "Controller");
    
    MenuItemFont* menuItem2_ = MenuItemFont::create("입장권 구매(무료)", CC_CALLBACK_1(LobbyLayerController::TicketBuy, controller));
    menuItem2_->setScale(0.3, 0.3);
    
    Menu* menu2 = Menu::create(menuItem2_, NULL);
    menu2->alignItemsHorizontally();
    menu2->setPosition(x_ * 0.9, y_ * 0.75);
    addChild(menu2, 2);
    
    PlayerInfo* playerInfo = PlayerInfo::getInstance();
    
    std::string scoreText = "TotalScore : ";
    scoreText.append(std::to_string(playerInfo->getTotalScore()));
    Label* scoreTextLabel = Label::createWithTTF(scoreText, "fonts/Marker Felt.ttf", fontSize_);
    scoreTextLabel->setPosition(x_ * 0.20, y_ * 0.75);
    addChild(scoreTextLabel, 2);
    
    std::string highScoreText = "HighScore : ";
    highScoreText.append(std::to_string(playerInfo->getHighScore()));
    Label* highScoreTextLabel = Label::createWithTTF(highScoreText, "fonts/Marker Felt.ttf", fontSize_);
    highScoreTextLabel->setPosition(x_ * 0.20, y_ * 0.60);
    addChild(highScoreTextLabel, 2);
    
    std::string moneyText = "Money : ";
    moneyText.append(std::to_string(playerInfo->getTotalMoney()));
    Label* moneyTextLabel = Label::createWithTTF(moneyText, "fonts/Marker Felt.ttf", fontSize_);
    moneyTextLabel->setPosition(x_ * 0.20, y_ * 0.45);
    addChild(moneyTextLabel, 2);

    std::string ticketText = std::to_string(playerInfo->getTicket());
    ticketText.append(" / ");
    ticketText.append(std::to_string(playerInfo->maxTicket_));
    Label* ticketTextLabel = Label::createWithTTF(ticketText, "fonts/Marker Felt.ttf", fontSize_);
    ticketTextLabel->setPosition(x_ * 0.75, y_ * 0.75);
    addChild(ticketTextLabel, 2, "TicKet");
    
    std::string clearTimeText = playerInfo->TimerPrint(playerInfo->shortClearTime_);
    Label* clearTextLabel = Label::createWithTTF(clearTimeText, "fonts/Marker Felt.ttf", fontSize_);
    clearTextLabel->setPosition(x_ * 0.75, y_ * 0.60);
    addChild(clearTextLabel, 2);
    
    return true;
}

