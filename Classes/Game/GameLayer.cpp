//
//  GameLayer.cpp
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#include <stdio.h>
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "GameLayerController.h"
#include "PlayerInfomation.h"
#include "DataIO.h"

USING_NS_CC;

Layer* GameLayer::createLayer()
{
    return GameLayer::create();
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    PlayerInfo playerInfo = PlayerInfo::getInstance();
    GameLayerController* controller = new GameLayerController();
    addChild(controller, -1, "Controller");
    
    Label* label = Label::createWithTTF("GameScene-GameLayer", "fonts/Marker Felt.ttf", 15);
    if(label != nullptr)
    {
        label->setPosition(Vec2(x_ * 0.5, y_ * 0.5));
        addChild(label);
    }
    
    MenuItemImage* menuItemUP = MenuItemImage::create("upArrow.png","upArrow.png", controller, menu_selector(GameLayerController::MoveUP));
    if(menuItemUP != nullptr)
    {
        menuItemUP->setPosition(0,20);
        menuItemUP->setScale(1.5, 1.5);
    }
    
    MenuItemImage* menuItemDOWN = MenuItemImage::create("downArrow.png","downArrow.png", controller, menu_selector(GameLayerController::MoveDOWN));
    if(menuItemDOWN != nullptr)
    {
        menuItemDOWN->setPosition(0,-20);
        menuItemDOWN->setScale(1.5, 1.5);
    }
    
    MenuItemImage* menuItemLEFT = MenuItemImage::create("leftArrow.png","leftArrow.png", controller, menu_selector(GameLayerController::MoveLEFT));
    if(menuItemLEFT != nullptr)
    {
        menuItemLEFT->setPosition(-20, 0);
        menuItemLEFT->setScale(1.5, 1.5);
    }
    
    MenuItemImage* menuItemRIGHT = MenuItemImage::create("rightArrow.png","rightArrow.png", controller, menu_selector(GameLayerController::MoveRIGHT));
    if(menuItemRIGHT != nullptr)
    {
        menuItemRIGHT->setPosition(20, 0);
        menuItemRIGHT->setScale(1.5, 1.5);
    }
    
    Menu* menu = Menu::create(menuItemUP, menuItemDOWN, menuItemLEFT, menuItemRIGHT, NULL);
    if(menu != nullptr)
    {
        menu->setPosition(40 , y_ - 40);
        addChild(menu, 4, "Menu");
    }
    
    playerInfo.pPlayerInfo_->clearTime_ = 0;
    Label* clearTimelabel = Label::createWithTTF("00 : 00 : 00", "fonts/Marker Felt.ttf", 15);
    if(clearTimelabel != nullptr)
    {
        clearTimelabel->setPosition(x_ * 0.85, y_ * 0.85);
        addChild(clearTimelabel, 2, "ClearTimeLabel");
    }
    this->schedule(schedule_selector(GameLayerController::Timer), 1.0);

    for(int heart_i = 0; heart_i < playerInfo.pPlayerInfo_->playerHp_; ++heart_i)
    {
        Sprite* heartSprite = Sprite::create("heart.png");
        heartSprite->setScale(0.3, 0.3);
        heartSprite->setPosition(x_ * 0.9 + (heart_i * -25), y_ * 0.93);
        addChild(heartSprite, 4, "Heart");
    }
    
    return true;
}

void GameLayer::PlayerCreate()
{
    Sprite* playerSprite = Sprite::create("red.png",Rect(0, 0, spriteSize_, spriteSize_));
    if(playerSprite != nullptr)
    {
        playerSprite->setPosition(20, 20);
        addChild(playerSprite, 2, "Player");
    }
}

void GameLayer::CoinCreate()
{
    int randCoinCount = RandomHelper::random_int(1, maxRandCoinCount_);
    for(int i = 0; i < randCoinCount; ++i)
    {
        int randX = RandomHelper::random_int(spriteSize_, (int)x_);
        int randY = RandomHelper::random_int(spriteSize_, (int)y_);
        
        Sprite* coinSprite = Sprite::create("coin.png");
        if(coinSprite == nullptr)
            continue;
        
        coinSprite->setScale(0.05, 0.05);
        coinSprite->setPosition(randX, randY);
        addChild(coinSprite, 1, "Coin");
    }
}
