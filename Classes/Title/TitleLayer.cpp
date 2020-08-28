//
//  TitleLayer.cpp
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#include <stdio.h>
#include "SimpleAudioEngine.h"

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
    float x = _director->getWinSize().width;
    float y = _director->getWinSize().height;
    
    Label* label = Label::createWithTTF("TitleScene-TitleLayer", "fonts/Marker Felt.ttf", 15);
    label->setPosition(x/2, y/2);
    addChild(label);
    
    TitleLayerController* controller = new TitleLayerController();
    addChild(controller, -1, "Controller");
    
    MenuItemFont* menuItem1 = MenuItemFont::create("눌러서 로비 화면으로 넘어가세요!", this, menu_selector(TitleLayerController::Goto_LobbyScene));
    menuItem1->setScale(0.3, 0.3);

    Menu* menu = Menu::create(menuItem1, NULL);
    menu->setPosition(Vec2(x/2, y/3));
    
    addChild(menu);
    log("_director : x , y : %f, %f", x, y);
    log("label : x , y : %f, %f", label->getPosition().x, label->getPosition().y);
    return true;
}
