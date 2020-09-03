//
//  LobbyScene.cpp
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#include <stdio.h>
#include "SimpleAudioEngine.h"
#include "LobbyScene.h"
#include "LobbyLayerController.h"
#include "LobbyLayer.h"

USING_NS_CC;

Scene* LobbyScene::createScene()
{
    return LobbyScene::create();
}

// on "init" you need to initialize your instance
bool LobbyScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    Layer* view = Layer::create();
    addChild(view, 1, "View");
    
    Layer* layer = LobbyLayer::createLayer();
    view->addChild(layer,1,"Layer");    
  
    return true;
}

