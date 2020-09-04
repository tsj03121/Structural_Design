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
#include "BasicDefine.h"

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
    
    LabelCreate();

    menuItem1_ = MenuItemFont::create("메 인 화 면");
    menuItem1_->setScale(0.3, 0.3);
    
    Menu* menu = Menu::create(menuItem1_, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(WINSIZE_X * 0.5, WINSIZE_Y * 0.25);
    addChild(menu);
    
    LobbyLayerController* controller = new LobbyLayerController(this);
    addChild(controller, -1, "Controller");
    
    MenuItemFont* menuItem2_ = MenuItemFont::create("입장권 구매(무료)", CC_CALLBACK_1(LobbyLayerController::TicketBuy, controller));
    menuItem2_->setScale(0.3, 0.3);
    
    Menu* menu2 = Menu::create(menuItem2_, NULL);
    menu2->alignItemsHorizontally();
    menu2->setPosition(WINSIZE_X * 0.9, WINSIZE_Y * 0.75);
    addChild(menu2, 2);
   
    return true;
}

void LobbyLayer::LabelCreate()
{
    PlayerInfo* playerInfo = PlayerInfo::getInstance();

    Label* label = Label::createWithTTF("LobbyScene-LobbyLayer", FONTNAME, FONTSIZE);
    label->setPosition(WINSIZE_X * 0.5, WINSIZE_Y * 0.75);
    addChild(label);
    
    std::string scoreText = "TotalScore : ";
    scoreText.append(std::to_string(playerInfo->getTotalScore()));
    Label* scoreTextLabel = Label::createWithTTF(scoreText, FONTNAME, FONTSIZE);
    scoreTextLabel->setPosition(WINSIZE_X * 0.20, WINSIZE_Y * 0.75);
    addChild(scoreTextLabel, 2);
    
    std::string highScoreText = "HighScore : ";
    highScoreText.append(std::to_string(playerInfo->getHighScore()));
    Label* highScoreTextLabel = Label::createWithTTF(highScoreText, FONTNAME, FONTSIZE);
    highScoreTextLabel->setPosition(WINSIZE_X * 0.20, WINSIZE_Y * 0.60);
    addChild(highScoreTextLabel, 2);
    
    std::string moneyText = "Money : ";
    moneyText.append(std::to_string(playerInfo->getTotalMoney()));
    Label* moneyTextLabel = Label::createWithTTF(moneyText, FONTNAME, FONTSIZE);
    moneyTextLabel->setPosition(WINSIZE_X * 0.20, WINSIZE_Y * 0.45);
    addChild(moneyTextLabel, 2);

    std::string ticketText = std::to_string(playerInfo->getTicket());
    ticketText.append(" / ");
    ticketText.append(std::to_string(playerInfo->maxTicket_));
    Label* ticketTextLabel = Label::createWithTTF(ticketText, FONTNAME, FONTSIZE);
    ticketTextLabel->setPosition(WINSIZE_X * 0.75, WINSIZE_Y * 0.75);
    addChild(ticketTextLabel, 2, "TicKet");
    
    std::string clearTimeText = playerInfo->TimerPrint(playerInfo->shortClearTime_);
    Label* clearTextLabel = Label::createWithTTF(clearTimeText, FONTNAME, FONTSIZE);
    clearTextLabel->setPosition(WINSIZE_X * 0.75, WINSIZE_Y * 0.60);
    addChild(clearTextLabel, 2);
}

