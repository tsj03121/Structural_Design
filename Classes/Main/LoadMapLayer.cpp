//
//  LoadMapLayer.cpp
//  Structural_Design_Temp
//
//  Created by CD-parkdaedong on 2020/09/01.
//

#include <stdio.h>
#include "LoadMapLayer.h"
#include "DataIO.h"
#include "LoadMapLayerController.h"
#include <cocos-ext.h>

USING_NS_CC;
USING_NS_CC_EXT;

Layer* LoadMapLayer::createLayer()
{
    return LoadMapLayer::create();
}

// on "init" you need to initialize your instance
bool LoadMapLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    log("X = %d, Y = %d", this->getContentSize().width, this->getContentSize().height);
    float x = _director->getWinSize().width;
    float y = _director->getWinSize().height;
    
    LoadMapLayerController* controller = new LoadMapLayerController();
    addChild(controller, -1, "Controller");
    
    Scene* scene = _director->getRunningScene();
    Layer* layer = (Layer*) scene->getChildByName("View")->getChildByName("Layer");
    Label* label = (Label*) layer->getChildByName("Label");
    
    if(label != nullptr)
    {
        label->setVisible(false);
    }
    
    if(layer->getChildByName("LoadLayer") != nullptr)
    {
        layer->removeChildByName("LoadLayer");
    }
    layer->addChild(this, 4, "LoadLayer");
    
    Vector<MenuItem*> menuItems;
    DataIO* dataIO = DataIO::getInstance();
    std::list<std::string> fileNames = dataIO->FileExist();
    
    for(std::string fileName : fileNames)
    {
        MenuItem* menuItem = MenuItemFont::create(fileName ,CC_CALLBACK_1(LoadMapLayerController::Select_Map, controller));
        menuItem->setName(fileName);
        menuItem->setAnchorPoint(Vec2(0.5, 0.5));
        menuItems.pushBack(menuItem);
        log("%s \n", fileName.c_str());
    }
    
    ScrollView* scrollView = ScrollView::create(Size(x * 0.7, y));
    scrollView->setDirection(ScrollView::Direction::VERTICAL);
    
    Menu* menu = Menu::createWithArray(menuItems);
    menu->setAnchorPoint(Vec2(0.5, 0.5));
    menu->alignItemsVertically();
    scrollView->addChild(menu);
    addChild(scrollView);
    
    return true;
}
