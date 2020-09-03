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

    Label* label = Label::createWithTTF("LobbyScene-MainLayer", "fonts/Marker Felt.ttf", fontSize_);
    label->setPosition(x_ * 0.5, y_ * 0.5);
    addChild(label, 0, "Label");
    
    MainLayerController* controller = new MainLayerController();
    addChild(controller, -1, "Controller");

    MenuItemFont* menuItem1 = MenuItemFont::create("로비로", this, menu_selector(MainLayerController::Change_LobbyLayer));
    menuItem1->setScale(0.3, 0.3);
    
    MenuItemFont* menuItem2 = MenuItemFont::create("게임 시작", this, menu_selector(MainLayerController::Goto_GameScene));
    menuItem2->setScale(0.3, 0.3);
    
    MenuItemFont* menuItem3 = MenuItemFont::create("맵 불러오기", this, menu_selector(MainLayerController::Load_Map));
    menuItem3->setScale(0.3, 0.3);
    
    MenuItemFont* menuItem4 = MenuItemFont::create("맵 만들기", this, menu_selector(MainLayerController::Goto_MapEditor));
    menuItem4->setScale(0.3, 0.3);
    
    Menu* menu = Menu::create(menuItem1, menuItem2, menuItem3, menuItem4, NULL);
    menu->alignItemsVertically();
    menu->setPosition(Vec2(x_ * 0.9, y_ * 0.2));
    
    addChild(menu);    
    return true;
}
