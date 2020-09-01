//
//  EditorScene.cpp
//  Structural_Design_Temp
//
//  Created by CD-parkdaedong on 2020/08/31.
//

#include <stdio.h>
#include "EditorScene.h"
#include "SimpleAudioEngine.h"
#include "EditorLayer.h"

USING_NS_CC;

Scene* EditorScene::createScene()
{
    return EditorScene::create();
}

// on "init" you need to initialize your instance
bool EditorScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    Layer* view = Layer::create();
    addChild(view, 1, "View");
    
    Layer* layer = EditorLayer::createLayer();
    view->addChild(layer,1,"Layer");
      
    return true;
}

