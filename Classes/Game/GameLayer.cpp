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


    Label* label = Label::createWithTTF("GameScene-GameLayer", "fonts/Marker Felt.ttf", 15);
    if(label != nullptr)
    {
        label->setPosition(Vec2(x / 2,y / 2));
        addChild(label);
    }
    
    GameLayerController* controller = new GameLayerController();
    addChild(controller, -1, "Controller");
    
    MenuItemImage* menuItemUP = MenuItemImage::create("CloseNormal.png","CloseSelected.png", controller, menu_selector(GameLayerController::MoveUP));
    if(menuItemUP != nullptr)
    {
        menuItemUP->setPosition(0,20);
        menuItemUP->setScale(2,2);
    }
    MenuItemImage* menuItemDOWN = MenuItemImage::create("CloseNormal.png","CloseSelected.png", controller, menu_selector(GameLayerController::MoveDOWN));
    if(menuItemDOWN != nullptr)
    {
        menuItemDOWN->setPosition(0,-20);
        menuItemDOWN->setScale(2,2);
    }
    MenuItemImage* menuItemLEFT = MenuItemImage::create("CloseNormal.png","CloseSelected.png", controller, menu_selector(GameLayerController::MoveLEFT));
    if(menuItemLEFT != nullptr)
    {
        menuItemLEFT->setPosition(-20, 0);
        menuItemLEFT->setScale(2,2);
    }
    MenuItemImage* menuItemRIGHT = MenuItemImage::create("CloseNormal.png","CloseSelected.png", controller, menu_selector(GameLayerController::MoveRIGHT));
    if(menuItemRIGHT != nullptr)
    {
        menuItemRIGHT->setPosition(20, 0);
        menuItemRIGHT->setScale(2,2);
    }
    Menu* menu = Menu::create(menuItemUP, menuItemDOWN, menuItemLEFT, menuItemRIGHT, NULL);
    if(menu != nullptr)
    {
        menu->setPosition(40 , y - 40);
        addChild(menu, 2);
    }
    
    PlayerInfo playerInfo = PlayerInfo::getInstance();
    playerInfo.pPlayerInfo_->clearTime_ = 0;
    Label* clearTimelabel = Label::createWithTTF("00 : 00 : 00", "fonts/Marker Felt.ttf", 15);
    if(clearTimelabel != nullptr)
    {
        clearTimelabel->setPosition(x * 0.85, y * 0.85);
        addChild(clearTimelabel, 2, "ClearTimeLabel");
    }
    
    this->schedule(schedule_selector(GameLayerController::Timer), 1.0);
    
    return true;
}

void GameLayer::PlayerCreate()
{
    Sprite* playerSprite = Sprite::create("red.png",Rect(0, 0, spriteSize, spriteSize));
    if(playerSprite != nullptr)
    {
        playerSprite->setPosition(20,20);
        addChild(playerSprite, 1, "Player");
    }
}

void GameLayer::CoinCreate()
{
    int randCoinCount = RandomHelper::random_int(1, 8);
    for(int i = 0; i < randCoinCount; ++i)
    {
        int randX = RandomHelper::random_int(spriteSize, (int)x);
        int randY = RandomHelper::random_int(spriteSize, (int)y);
        
        Sprite* coinSprite = Sprite::create("coin.png");
        if(coinSprite == nullptr)
            continue;
        
        coinSprite->setScale(0.05, 0.05);
        coinSprite->setPosition(randX, randY);
        addChild(coinSprite, 1, "Coin");
    }
}
