//
//  GameLayerController.cpp
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#include <stdio.h>
#include "GameLayerController.h"
#include "ResultLayer.h"
#include "RewardLayer.h"
#include "LobbyScene.h"
#include "PlayerInfomation.h"

USING_NS_CC;


void GameLayerController::Change_ResultLayer(Ref* pSender)
{
    Scene* scene = _director->getRunningScene();
    Layer* view = (Layer*) scene->getChildByName("View");
    view->removeAllChildren();
    Layer* layer = ResultLayer::createLayer();
    view->addChild(layer,1,"Layer");
}

void GameLayerController::MoveUP(cocos2d::Ref* pSender)
{
    Scene* scene = _director->getRunningScene();
    Layer* layer = (Layer*) scene->getChildByName("View")->getChildByName("Layer");
    Sprite* player = (Sprite*) layer->getChildByName("Player");
    player->setPosition(player->getPosition().x, player->getPosition().y + moveSpeed_);
    
    CoinCheck(layer, player);
}
void GameLayerController::MoveDOWN(cocos2d::Ref* pSender)
{
    Scene* scene = _director->getRunningScene();
    Layer* layer = (Layer*) scene->getChildByName("View")->getChildByName("Layer");
    Sprite* player = (Sprite*) layer->getChildByName("Player");
    player->setPosition(player->getPosition().x, (player->getPosition().y - moveSpeed_));

    CoinCheck(layer, player);
}
void GameLayerController::MoveLEFT(cocos2d::Ref* pSender)
{
    Scene* scene = _director->getRunningScene();
    Layer* layer = (Layer*) scene->getChildByName("View")->getChildByName("Layer");
    Sprite* player = (Sprite*) layer->getChildByName("Player");
    player->setPosition(player->getPosition().x - moveSpeed_, player->getPosition().y);
    
    CoinCheck(layer, player);
}
void GameLayerController::MoveRIGHT(cocos2d::Ref* pSender)
{
    Scene* scene = _director->getRunningScene();
    Layer* layer = (Layer*) scene->getChildByName("View")->getChildByName("Layer");
    Sprite* player = (Sprite*) layer->getChildByName("Player");
    player->setPosition(player->getPosition().x + moveSpeed_, player->getPosition().y);
    
    CoinCheck(layer, player);
}

void GameLayerController::CoinCheck(Layer* layer, Sprite* player)
{
    Sprite* coin = (Sprite*) layer->getChildByName("Coin");
    Vector<Node*> children = layer->getChildren();
    
    for(auto child : children)
    {
        if(child->getName() != "Coin")
            continue;
        
        Rect playerBox = player->getBoundingBox();
        Rect coinBox = child->getBoundingBox();
        
        if(playerBox.intersectsRect(coinBox))
        {
            layer->removeChild(child);
            PlayerInfo playerInfo = PlayerInfo::getInstance();
            PlayerInfoUpdate(playerInfo);
            
            Sprite* nextCoin = (Sprite*) layer->getChildByName("Coin");
            if(nextCoin == nullptr)
            {
                int nowScore = playerInfo.pPlayerInfo_->getNowScore();
                playerInfo.pPlayerInfo_->addTotalScore(nowScore);
                playerInfo.pPlayerInfo_->setHighScore(nowScore);
                playerInfo.pPlayerInfo_->setShortClearTime(playerInfo.pPlayerInfo_->clearTime_);
                Change_ResultLayer(layer);
            }
        }
    }
}

void GameLayerController::PlayerInfoUpdate(PlayerInfo playerInfo)
{
    playerInfo.pPlayerInfo_->addNowScore(playerInfo.pPlayerInfo_->coinScore_);
    playerInfo.pPlayerInfo_->addMoney(playerInfo.pPlayerInfo_->coinMoney_);
}

void GameLayerController::Timer(float dt)
{
    PlayerInfo playerInfo = PlayerInfo::getInstance();
    playerInfo.pPlayerInfo_->clearTime_ += 1;
    
    Scene* scene = _director->getRunningScene();
    Layer* layer = (Layer*) scene->getChildByName("View")->getChildByName("Layer");
    Label* clearTimeLabel = (Label*) layer->getChildByName("ClearTimeLabel");
    clearTimeLabel->setString(playerInfo.pPlayerInfo_->TimerPrint(playerInfo.pPlayerInfo_->clearTime_));
}


