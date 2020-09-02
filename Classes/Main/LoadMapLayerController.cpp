//
//  LoadMapLayerController.cpp
//  Structural_Design_Temp
//
//  Created by CD-parkdaedong on 2020/09/01.
//

#include <stdio.h>
#include "LoadMapLayerController.h"
#include "DataIO.h"
#include "GameScene.h"

USING_NS_CC;

void LoadMapLayerController::Select_Map(Ref* pSender)
{
    MenuItem* menuItem = (MenuItemFont*) pSender;
    std::string fileName = menuItem->getName().c_str();
    DataIO* dataIO = DataIO::getInstance();
    log("이름 입니다. : %s", _director->getRunningScene()->getName().c_str());
    if(_director->getRunningScene()->getName() == "Lobby")
    {
        Scene* scene = GameScene::createScene();
        Layer* layer = (Layer*) scene->getChildByName("View")->getChildByName("Layer");
        dataIO->readMapJSON(layer, fileName);
        _director->pushScene(scene);
    }
    else
    {
        Scene* scene = _director->getRunningScene();
        Layer* layer = (Layer*) scene->getChildByName("View")->getChildByName("Layer");
        layer->removeChildByName("LoadLayer");
        
        while(layer->getChildByName("Player") != nullptr)
        {
            layer->removeChildByName("Player");
        }
        
        while(layer->getChildByName("Coin") != nullptr)
        {
            layer->removeChildByName("Coin");
        }
        
        dataIO->openFileName = ((MenuItem*) pSender)->getName();
        dataIO->readMapJSON(layer, fileName);
    }
    
}


