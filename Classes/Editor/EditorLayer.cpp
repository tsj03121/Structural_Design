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
#include "BasicDefine.h"

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
    this->setName("EditorLayer");
    
    EditorController* pEditorController = new EditorController();
    addChild(pEditorController, -1, "Controller");
 
    UnitMenuCreate();
    MenuCreate();
    
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(EditorController::onTouchBegan, pEditorController);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void EditorLayer::UnitMenuCreate()
{
    EditorController* pEditorController = (EditorController*) getChildByName("Controller");
    
    MenuItemImage* menuItem1 = MenuItemImage::create("player.png", "player.png", CC_CALLBACK_1(EditorController::PlayerSelect, pEditorController, this));
    menuItem1->setScale(0.7, 0.7);
    
    MenuItemImage* menuItem2 = MenuItemImage::create("coin.png", "coin.png", CC_CALLBACK_1(EditorController::CoinSelect, pEditorController));
    menuItem2->setScale(0.03, 0.03);
    
    MenuItemImage* menuItem3 = MenuItemImage::create("trap.png", "trap.png", CC_CALLBACK_1(EditorController::TrapSelect, pEditorController));
    MenuItemImage* menuItem4 = MenuItemImage::create("spiderBoss.png", "spiderBoss.png", CC_CALLBACK_1(EditorController::SpiderBossSelect, pEditorController, this));
    
    MenuItemImage* menuItem5 = MenuItemImage::create("sansBoss.png", "sansBoss.png", CC_CALLBACK_1(EditorController::SansBossSelect, pEditorController, this));
    menuItem5->setScale(0.05, 0.05);
    
    Menu* menu = Menu::create(menuItem1, menuItem2, menuItem3, menuItem4, menuItem5, NULL);
    menu->setPosition(WINSIZE_X * 0.5, WINSIZE_Y * 0.95);
    menu->alignItemsHorizontally();
    addChild(menu, 3, "Menu");
}

void EditorLayer::MenuCreate()
{
    EditorController* pEditorController = (EditorController*) getChildByName("Controller");
    
    MenuItemFont* menuItemFont1 = MenuItemFont::create("저장하기", CC_CALLBACK_1(EditorController::SaveEditor, pEditorController, this));
    menuItemFont1->setScale(0.3, 0.3);
    MenuItemFont* menuItemFont2 = MenuItemFont::create("뒤로가기", CC_CALLBACK_1(EditorController::Goto_Lobby, pEditorController));
    menuItemFont2->setScale(0.3, 0.3);
    MenuItemFont* menuItemFont3 = MenuItemFont::create("불러오기", CC_CALLBACK_1(EditorController::LoadMapList, pEditorController));
    menuItemFont3->setScale(0.3, 0.3);
    
    Menu* menu2 = Menu::create(menuItemFont1, menuItemFont2, menuItemFont3, NULL);
    menu2->setPosition(WINSIZE_X * 0.85, WINSIZE_Y * 0.1);
    menu2->alignItemsHorizontally();
    addChild(menu2, 3, "Menu2");
}
