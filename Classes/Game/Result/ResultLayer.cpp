//
//  ResultLayer.cpp
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#include <stdio.h>
#include "ResultLayer.h"
#include "ResultLayerController.h"
#include "PlayerInfomation.h"'

USING_NS_CC;

Layer* ResultLayer::createLayer()
{
    return ResultLayer::create();
}

// on "init" you need to initialize your instance
bool ResultLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Label* label = Label::createWithTTF("GameScene-ResultLayer", "fonts/Marker Felt.ttf", 15);
    label->setPosition(x_ * 0.5, y_ * 0.5);
    addChild(label);
    
    ResultLayerController* controller = new ResultLayerController();
    addChild(controller, -1, "Controller");
    
    MenuItemFont* menuItem1 = MenuItemFont::create("눌러서 보상화면으로 넘어가세요!", this, menu_selector(ResultLayerController::Change_RewardLayer));
    menuItem1->setScale(0.3, 0.3);

    Menu* menu = Menu::create(menuItem1, NULL);
    menu->setPosition(x_ * 0.5, y_ * 0.33);
    addChild(menu);
    
    PlayerInfo* playerInfo = PlayerInfo::getInstance();
    
    std::string scoreText = "Score : ";
    scoreText.append(std::to_string(playerInfo->getNowScore()));
    Label* scoreTextLabel = Label::createWithTTF(scoreText, "fonts/Marker Felt.ttf", 15);
    scoreTextLabel->setPosition(x_ * 0.20, y_ * 0.75);
    addChild(scoreTextLabel);

    std::string highScoreText = "HighScore : ";
    highScoreText.append(std::to_string(playerInfo->getHighScore()));
    Label* highScoreTextLabel = Label::createWithTTF(highScoreText, "fonts/Marker Felt.ttf", 15);
    highScoreTextLabel->setPosition(x_ * 0.20, y_ * 0.60);
    addChild(highScoreTextLabel);
    
    playerInfo->setNowScore(0);
    
    return true;
}
