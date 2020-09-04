//
//  TitleLayer.cpp
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#include <stdio.h>
#include "SimpleAudioEngine.h"
#include "BasicDefine.h"
#include "TitleLayer.h"
#include "TitleLayerController.h"

USING_NS_CC;

Layer* TitleLayer::createLayer()
{
    return TitleLayer::create();
}

// on "init" you need to initialize your instance
bool TitleLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    TitleLayerController* controller = new TitleLayerController();
    addChild(controller, -1, "Controller");
    
    Label* label = Label::createWithTTF("TitleScene-TitleLayer", FONTNAME, FONTSIZE);
    label->setPosition(WINSIZE_X * 0.5, WINSIZE_Y * 0.5);
    addChild(label);   
    
    MenuItemFont* menuItem1 = MenuItemFont::create("눌러서 로비 화면으로 넘어가세요!", this, menu_selector(TitleLayerController::Goto_LobbyScene));
    menuItem1->setScale(0.3, 0.3);

    Menu* menu = Menu::create(menuItem1, NULL);
    menu->setPosition(Vec2(WINSIZE_X * 0.5, WINSIZE_Y * 0.33));
    
    addChild(menu);
    return true;
}
