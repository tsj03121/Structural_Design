//
//  EditorLayer.cpp
//  Structural_Design_Temp
//
//  Created by CD-parkdaedong on 2020/08/31.
//

#include <stdio.h>
#include "EditorLayer.h"
#include "SimpleAudioEngine.h"
#include "EditorController.h"

USING_NS_CC;

Layer* EditorLayer::createLayer()
{
    return EditorLayer::create();
}

// on "init" you need to initialize your instance
bool EditorLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    float x = _director->getWinSize().width;
    float y = _director->getWinSize().height;
    int spriteSize = 30;
    
    EditorController* pEditorController = new EditorController();
    addChild(pEditorController, -1, "Controller");
    
    MenuItemImage* menuItem1 = MenuItemImage::create("red.png", "red.png", CC_CALLBACK_1(EditorController::PlayerSelect, pEditorController, this));
    menuItem1->setScale(0.3, 0.3);
    MenuItemImage* menuItem2 = MenuItemImage::create("coin.png", "coin.png", CC_CALLBACK_1(EditorController::CoinSelect, pEditorController));
    menuItem2->setScale(0.03, 0.03);
    MenuItemImage* menuItem3 = MenuItemImage::create("trap.png", "trap.png", CC_CALLBACK_1(EditorController::TrapSelect, pEditorController));
    
    Menu* menu = Menu::create(menuItem1, menuItem2, menuItem3, NULL);
    menu->setPosition(x * 0.5, y * 0.95);
    menu->alignItemsHorizontally();
    addChild(menu, 3, "Menu");
    
    MenuItemFont* menuItemFont1 = MenuItemFont::create("저장하기", CC_CALLBACK_1(EditorController::SaveEditor, pEditorController, this));
    menuItemFont1->setScale(0.3, 0.3);
    MenuItemFont* menuItemFont2 = MenuItemFont::create("뒤로가기", CC_CALLBACK_1(EditorController::Goto_Lobby, pEditorController));
    menuItemFont2->setScale(0.3, 0.3);
    MenuItemFont* menuItemFont3 = MenuItemFont::create("불러오기", CC_CALLBACK_1(EditorController::LoadMapList, pEditorController));
    menuItemFont3->setScale(0.3, 0.3);
    
    Menu* menu2 = Menu::create(menuItemFont1, menuItemFont2, menuItemFont3, NULL);
    menu2->setPosition(x * 0.85, y * 0.1);
    menu2->alignItemsHorizontally();
    addChild(menu2, 3, "Menu2");
    
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(EditorController::onTouchBegan, pEditorController);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}
