//
//  TitleScene.cpp
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#include <stdio.h>
#include "SimpleAudioEngine.h"
#include "TitleScene.h"
#include "TitleLayerController.h"
#include "TitleLayer.h"

USING_NS_CC;

Scene* TitleScene::createScene()
{
    return TitleScene::create();
}

// on "init" you need to initialize your instance
bool TitleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    Layer* view = Layer::create();
    addChild(view, 1, "View");
    Layer* layer = TitleLayer::createLayer();
    view->addChild(layer,1,"Layer");
    
    Node* titleController = TitleLayerController::create();
    layer->addChild(titleController, -1, "TitleLayerController");
    
    return true;
}
