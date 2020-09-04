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
#include "PlayerInfomation.h"

USING_NS_CC;

void LoadMapLayerController::Select_Map(Ref* pSender)
{
    PlayerInfo* playerInfo = PlayerInfo::getInstance();
    DataIO* dataIO = DataIO::getInstance();
    
    MenuItem* menuItem = (MenuItemFont*) pSender;
    std::string fileName = menuItem->getName().c_str();

    if(_director->getRunningScene()->getName() == "Lobby")
    {
        if(playerInfo->getTicket() <= 0)
            return;
        
        Scene* scene = GameScene::createScene();
        Layer* layer = (Layer*) scene->getChildByName("View")->getChildByName("Layer");
        std::string nextFileName = "Stage1.json";
        bool isPlayMapCheck = false;
        int count = 1;
        
        playerInfo->setTicket(playerInfo->getTicket() - 1);
        dataIO->readMapJSON(layer, fileName);
        
        while(!isPlayMapCheck)
        {
            if(fileName == nextFileName)
            {
                isPlayMapCheck = true;
                playerInfo->playMapNumber_ = count;
            }
            
            count += 1;
            nextFileName = "";
            nextFileName.append("Stage");
            nextFileName.append(std::to_string(count));
            nextFileName.append(".json");
        }
        
        _director->pushScene(scene);
    }
    else
    {
        Scene* scene = _director->getRunningScene();
        Layer* layer = (Layer*) scene->getChildByName("View")->getChildByName("Layer");
        layer->removeChildByName("LoadLayer");
        
        Vector<Node*> children = layer->getChildren();
        for(auto childrenSprite : children)
        {
            if(childrenSprite->getName() == "Menu")
                continue;
            if(childrenSprite->getName() == "Menu2")
                continue;
            
            layer->removeChild(childrenSprite);
        }
        
        dataIO->openFileName = ((MenuItem*) pSender)->getName();
        dataIO->readMapJSON(layer, fileName);
    }
}


