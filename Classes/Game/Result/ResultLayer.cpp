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
    float x = _director->getWinSize().width;
    float y = _director->getWinSize().height;
    
    Label* label = Label::createWithTTF("GameScene-ResultLayer", "fonts/Marker Felt.ttf", 15);
    label->setPosition(Vec2(x/2,y/2));
    addChild(label);
    
    ResultLayerController* controller = new ResultLayerController();
    addChild(controller, -1, "Controller");
    
    MenuItemImage* menuItem1 = MenuItemImage::create("CloseNormal.png","CloseSelected.png",this,menu_selector(ResultLayerController::Change_RewardLayer));
    menuItem1->setScale(3, 3);
    Menu* menu = Menu::create(menuItem1, NULL);
    menu->setPosition(Vec2(x/2,y/3));
    addChild(menu);
    
    PlayerInfo player = PlayerInfo::getInstance();
    
    std::string scoreText = "Score : ";
    scoreText.append(std::to_string(player.pPlayerInfo_->getNowScore()));
    Label* scoreTextLabel = Label::createWithTTF(scoreText, "fonts/Marker Felt.ttf", 15);
    scoreTextLabel->setPosition(x * 0.20, y * 0.75);
    addChild(scoreTextLabel);

    std::string highScoreText = "HighScore : ";
    highScoreText.append(std::to_string(player.pPlayerInfo_->getHighScore()));
    Label* highScoreTextLabel = Label::createWithTTF(highScoreText, "fonts/Marker Felt.ttf", 15);
    highScoreTextLabel->setPosition(x * 0.20, y * 0.60);
    addChild(highScoreTextLabel);
    
    player.pPlayerInfo_->setNowScore(0);
    
    return true;
}
