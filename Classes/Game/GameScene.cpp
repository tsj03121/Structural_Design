//
//  GameScene.cpp
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#include <stdio.h>
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "GameLayer.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    Layer* view = Layer::create();
    addChild(view, 1, "View");
    Layer* layer = GameLayer::createLayer();
    view->addChild(layer,1,"Layer");

  
    return true;
}
