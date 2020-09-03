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
#include "DataIO.h"
#include "SpiderBoss.h"
#include "GameLayer.h"
#include "Boss.h"

USING_NS_CC;


void GameLayerController::Change_ResultLayer(Ref* pSender)
{
    PlayerInfo pPlayerInfo = PlayerInfo::getInstance();
    DataIO* pDataIO = DataIO::getInstance();
    
    int data[5];
    data[0] = pPlayerInfo.pPlayerInfo_->getHighScore();
    data[1] = pPlayerInfo.pPlayerInfo_->getTotalScore();
    data[2] = pPlayerInfo.pPlayerInfo_->shortClearTime_;
    data[3] = pPlayerInfo.pPlayerInfo_->getMoney();
    data[4] = pPlayerInfo.pPlayerInfo_->getTicket();
    
    pDataIO->writeJSON();
    
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
    
    if(player->getPosition().y + moveSpeed_ > _director->getWinSize().height - (player->getContentSize().height * 0.1))
        return;
    
    player->setPosition(player->getPosition().x, player->getPosition().y + moveSpeed_);
    CollisionChecks(layer, player);
}

void GameLayerController::MoveDOWN(cocos2d::Ref* pSender)
{
    Scene* scene = _director->getRunningScene();
    Layer* layer = (Layer*) scene->getChildByName("View")->getChildByName("Layer");
    Sprite* player = (Sprite*) layer->getChildByName("Player");

    if(player->getPosition().y - moveSpeed_ < (player->getContentSize().height * 0.1))
        return;
    
    player->setPosition(player->getPosition().x, (player->getPosition().y - moveSpeed_));
    CollisionChecks(layer, player);
}

void GameLayerController::MoveRIGHT(cocos2d::Ref* pSender)
{
    Scene* scene = _director->getRunningScene();
    Layer* layer = (Layer*) scene->getChildByName("View")->getChildByName("Layer");
    Sprite* player = (Sprite*) layer->getChildByName("Player");

    if(player->getPosition().x + moveSpeed_ > _director->getWinSize().width - (player->getContentSize().width * 0.1))
        return;
    
    player->setPosition(player->getPosition().x + moveSpeed_, player->getPosition().y);
    CollisionChecks(layer, player);
}

void GameLayerController::MoveLEFT(cocos2d::Ref* pSender)
{
    Scene* scene = _director->getRunningScene();
    Layer* layer = (Layer*) scene->getChildByName("View")->getChildByName("Layer");
    Sprite* player = (Sprite*) layer->getChildByName("Player");
    
    if(player->getPosition().x - moveSpeed_ < (player->getContentSize().width * 0.1))
        return;
    
    player->setPosition(player->getPosition().x - moveSpeed_, player->getPosition().y);
    CollisionChecks(layer, player);
}

void GameLayerController::CollisionChecks(Layer* layer, Sprite* player)
{
    TrapCheck(layer, player);
    BossCheck(layer, player);
    CoinCheck(layer, player);
}

void GameLayerController::CoinCheck(Layer* layer, Sprite* player)
{
    Sprite* coin = (Sprite*) layer->getChildByName("Coin");
    Sprite* boss = (Sprite*) layer->getChildByName("Boss");
    Boss* bossinfo;
    
    if(boss != nullptr)
    {
        bossinfo = (Boss*) boss->getChildByName("BossInfo");
    }
    Vector<Node*> children = layer->getChildren();
    
    if(coin == nullptr && boss == nullptr)
    {
        NextMap(layer);
        return;
    }
    
    for(auto child : children)
    {
        if(child->getName() != "Coin")
            continue;
        
        Rect playerBox = player->getBoundingBox();
        Rect coinBox = child->getBoundingBox();
        
        if(playerBox.intersectsRect(coinBox))
        {
            layer->removeChild(child);
            coin = (Sprite*) layer->getChildByName("Coin");
            PlayerInfo playerInfo = PlayerInfo::getInstance();
            PlayerInfoUpdate(playerInfo);
            break;
        }
    }
    
    if(coin == nullptr && boss != nullptr)
    {
        int curHp = bossinfo->getHp();
        bossinfo->setHp(--curHp);
        log("boss HP : %d", curHp);
        
        if (curHp <= 0)
        {
            layer->removeChild(boss);
            boss = nullptr;
        }
        if(boss != nullptr)
        {
            ((GameLayer*) layer)->CoinCreate();
        }
        else
        {
            NextMap(layer);
            return;
        }
    }
    
}

void GameLayerController::TrapCheck(Layer* layer, Sprite* player)
{
    Vector<Node*> children = layer->getChildren();
    
    for(auto child : children)
    {
        if(child->getName() != "Trap")
            continue;
        
        Rect playerBox = player->getBoundingBox();
        Rect trapBox = child->getBoundingBox();
        
        if(playerBox.intersectsRect(trapBox))
        {
            PlayerInfo playerInfo = PlayerInfo::getInstance();
            playerInfo.pPlayerInfo_->playerHeart_ -= 1;
            
            layer->removeChildByName("Heart");
            
            if(playerInfo.pPlayerInfo_->playerHeart_ <= 0)
            {
                playerInfo.pPlayerInfo_->playMapCount_ = -1;
                _director->popScene();
            }
        }
    }
}

void GameLayerController::BossCheck(Layer* layer, Sprite* player)
{
    Sprite* boss = (Sprite*) layer->getChildByName("Boss");
    Vector<Node*> children = layer->getChildren();
    
    for(auto child : children)
    {
        if(child->getName() != "Boss")
            continue;
        
        Rect playerBox = player->getBoundingBox();
        Rect bossBox = child->getBoundingBox();
        
        if(playerBox.intersectsRect(bossBox))
        {
            PlayerInfo playerInfo = PlayerInfo::getInstance();
            playerInfo.pPlayerInfo_->playerHeart_ -= 1;
            
            layer->removeChildByName("Heart");
            
            if(playerInfo.pPlayerInfo_->playerHeart_ <= 0)
            {
                playerInfo.pPlayerInfo_->playMapCount_ = -1;
                _director->popScene();
            }
        }
    }
}

void GameLayerController::NextMap(Layer* layer)
{
    PlayerInfo playerInfo = PlayerInfo::getInstance();
    DataIO* dataIO = DataIO::getInstance();
    
    std::string fileName = "";
    fileName.append("Save");
    fileName.append(std::to_string(playerInfo.pPlayerInfo_->playMapCount_ + 1));
    fileName.append(".json");
    
    std::string filePath = FileUtils::getInstance()->getWritablePath();
    filePath.append(fileName);
    
    bool isFileCheck = FileUtils::getInstance()->isFileExist(filePath);

    if(!isFileCheck)
    {
        int nowScore = playerInfo.pPlayerInfo_->getNowScore();
        playerInfo.pPlayerInfo_->addTotalScore(nowScore);
        playerInfo.pPlayerInfo_->setHighScore(nowScore);
        playerInfo.pPlayerInfo_->setShortClearTime(playerInfo.pPlayerInfo_->clearTime_);
        playerInfo.pPlayerInfo_->playMapCount_ = -1;
        Change_ResultLayer(layer);
        return;
    }
    
    Vector<Node*> nodes = layer->getChildren();
    for(auto childSprite : nodes)
    {
        if(childSprite == layer->getChildByName("ClearTimeLabel"))
            continue;
        if(childSprite == layer->getChildByName("Controller"))
            continue;
        if(childSprite == layer->getChildByName("Menu"))
            continue;
        
        layer->removeChild(childSprite);
    }
    
    float x = _director->getWinSize().width;
    float y = _director->getWinSize().height;
    
    for(int heart_i = 0; heart_i < playerInfo.pPlayerInfo_->playerHeart_; ++heart_i)
    {
        Sprite* heartSprite = Sprite::create("heart.png");
        heartSprite->setScale(0.3, 0.3);
        heartSprite->setPosition(x * 0.9 + (heart_i * -25), y * 0.93);
        layer->addChild(heartSprite, 4, "Heart");
    }
    
    playerInfo.pPlayerInfo_->playMapCount_ += 1;
    dataIO->readMapJSON(layer, fileName);
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


