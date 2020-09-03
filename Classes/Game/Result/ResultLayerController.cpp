//
//  ResultLayerController.cpp
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#include <stdio.h>
#include "ResultLayerController.h"
#include "RewardLayer.h"

USING_NS_CC;

void ResultLayerController::Change_RewardLayer(Ref* pSender)
{
    Scene* scene = _director->getRunningScene();
    Layer* view = (Layer*) scene->getChildByName("View");
    Layer* layer = RewardLayer::createLayer();
    
    view->removeAllChildren();
    view->addChild(layer,1,"Layer");
}
