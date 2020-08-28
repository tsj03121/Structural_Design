//
//  MainLayer.cpp
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#include <stdio.h>
#include "MainLayer.h"
#include "SimpleAudioEngine.h"
#include "MainLayerController.h"
#include "PlayerInfomation.h"

USING_NS_CC;

Layer* MainLayer::createLayer()
{
    return MainLayer::create();
}

// on "init" you need to initialize your instance
bool MainLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    float x = _director->getWinSize().width;
    float y = _director->getWinSize().height;
    
    Label* label = Label::createWithTTF("LobbyScene-MainLayer", "fonts/Marker Felt.ttf", 15);
    label->setPosition(Vec2(x/2, y/2));
    addChild(label);
    
    MainLayerController* controller = new MainLayerController();
    addChild(controller, -1, "Controller");

    MenuItemFont* menuItem1 = MenuItemFont::create("로비로", this, menu_selector(MainLayerController::Change_LobbyLayer));
    menuItem1->setScale(0.3, 0.3);
    
    MenuItemFont* menuItem2 = MenuItemFont::create("게임 시작", this, menu_selector(MainLayerController::Goto_GameScene));
    menuItem2->setScale(0.3, 0.3);
    
    Menu* menu = Menu::create(menuItem1, menuItem2, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(Vec2(x * 0.9, y * 0.1));
    
    addChild(menu);
    
    return true;
}
