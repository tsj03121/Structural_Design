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
    
    float x = _director->getWinSize().width;
    float y = _director->getWinSize().height;
    

    
    Label* label = Label::createWithTTF("LobbyScene-LobbyLayer", "fonts/Marker Felt.ttf", 15);
    label->setPosition(x / 2, y * 0.75);
    addChild(label);
    
    menuItem1_ = MenuItemFont::create("메 인 화 면");
    menuItem1_->setScale(0.3, 0.3);
    
    Menu* menu = Menu::create(menuItem1_, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(x/2, y/4);
    addChild(menu);
    
    LobbyLayerController* controller = new LobbyLayerController(this);
    addChild(controller, -1, "Controller");
    
    MenuItemFont* menuItem2_ = MenuItemFont::create("입장권 구매(무료)", CC_CALLBACK_1(LobbyLayerController::TicketBuy, controller));
    menuItem2_->setScale(0.3, 0.3);
    
    Menu* menu2 = Menu::create(menuItem2_, NULL);
    menu2->alignItemsHorizontally();
    menu2->setPosition(x * 0.9, y * 0.75);
    addChild(menu2, 2);
    
    
    PlayerInfo player = PlayerInfo::getInstance();
    
    std::string scoreText = "TotalScore : ";
    scoreText.append(std::to_string(player.pPlayerInfo_->getTotalScore()));
    Label* scoreTextLabel = Label::createWithTTF(scoreText, "fonts/Marker Felt.ttf", 15);
    scoreTextLabel->setPosition(x * 0.20, y * 0.75);
    addChild(scoreTextLabel, 2);
    
    std::string highScoreText = "HighScore : ";
    highScoreText.append(std::to_string(player.pPlayerInfo_->getHighScore()));
    Label* highScoreTextLabel = Label::createWithTTF(highScoreText, "fonts/Marker Felt.ttf", 15);
    highScoreTextLabel->setPosition(x * 0.20, y * 0.60);
    addChild(highScoreTextLabel, 2);
    
    std::string moneyText = "Money : ";
    moneyText.append(std::to_string(player.pPlayerInfo_->getMoney()));
    Label* moneyTextLabel = Label::createWithTTF(moneyText, "fonts/Marker Felt.ttf", 15);
    moneyTextLabel->setPosition(x * 0.20, y * 0.45);
    addChild(moneyTextLabel, 2);

    std::string ticketText = std::to_string(player.pPlayerInfo_->getTicket());
    ticketText.append(" / 5");
    Label* ticketTextLabel = Label::createWithTTF(ticketText, "fonts/Marker Felt.ttf", 15);
    ticketTextLabel->setPosition(x * 0.75, y * 0.75);
    addChild(ticketTextLabel, 2, "TicKet");
    
    std::string clearTimeText = player.pPlayerInfo_->TimerPrint(player.pPlayerInfo_->shortClearTime_);
    Label* clearTextLabel = Label::createWithTTF(clearTimeText, "fonts/Marker Felt.ttf", 15);
    clearTextLabel->setPosition(x * 0.75, y * 0.60);
    addChild(clearTextLabel, 2);
    
    return true;
}

