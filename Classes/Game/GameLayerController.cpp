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
    PlayerInfo* playerInfo = PlayerInfo::getInstance();
    playerInfo->TotalUpdate();
    int nowScore = playerInfo->getNowScore();
    playerInfo->setHighScore(nowScore);
    playerInfo->setShortClearTime(playerInfo->clearTime_);
    playerInfo->playMapNumber_ = -1;
    
    DataIO* pDataIO = DataIO::getInstance();
    
    int data[5];
    data[0] = playerInfo->getHighScore();
    data[1] = playerInfo->getTotalScore();
    data[2] = playerInfo->shortClearTime_;
    data[3] = playerInfo->getTotalMoney();
    data[4] = playerInfo->getTicket();
    
    pDataIO->writeJSON();
    
    Scene* scene = _director->getRunningScene();
    Layer* view = (Layer*) scene->getChildByName("View");
    Layer* layer = ResultLayer::createLayer();
    playerInfo->setNowScore(0);
    
    view->removeAllChildren();
    view->addChild(layer, 1, "Layer");
}

void GameLayerController::MoveUP(cocos2d::Ref* pSender)
{
    Scene* scene = _director->getRunningScene();
    Layer* layer = (Layer*) scene->getChildByName("View")->getChildByName("Layer");
    Sprite* player = (Sprite*) layer->getChildByName("Player");

    if(player->getPosition().y + (player->getContentSize().height * 0.5) + moveSpeed_ > _director->getWinSize().height)
    {
        int posY = _director->getWinSize().height - (player->getContentSize().height * 0.5) - moveSpeed_;
        player->setPositionY(posY);
    }
        
    player->setPosition(player->getPosition().x, player->getPosition().y + moveSpeed_);
    CollisionChecks(layer, player);
}

void GameLayerController::MoveDOWN(cocos2d::Ref* pSender)
{
    Scene* scene = _director->getRunningScene();
    Layer* layer = (Layer*) scene->getChildByName("View")->getChildByName("Layer");
    Sprite* player = (Sprite*) layer->getChildByName("Player");

    if(player->getPosition().y - (player->getContentSize().height * 0.5) - moveSpeed_ < 0)
    {
        int posY = (player->getContentSize().height * 0.5) + moveSpeed_;
        player->setPositionY(posY);
    }
    
    player->setPosition(player->getPosition().x, (player->getPosition().y - moveSpeed_));
    CollisionChecks(layer, player);
}

void GameLayerController::MoveRIGHT(cocos2d::Ref* pSender)
{
    Scene* scene = _director->getRunningScene();
    Layer* layer = (Layer*) scene->getChildByName("View")->getChildByName("Layer");
    Sprite* player = (Sprite*) layer->getChildByName("Player");

    if(player->getPosition().x + (player->getContentSize().width * 0.5) + moveSpeed_ > _director->getWinSize().width)
    {
        int posX = _director->getWinSize().width - (player->getContentSize().width * 0.5) - moveSpeed_;
        player->setPositionX(posX);
    }
    
    player->setPosition(player->getPosition().x + moveSpeed_, player->getPosition().y);
    CollisionChecks(layer, player);
}

void GameLayerController::MoveLEFT(cocos2d::Ref* pSender)
{
    Scene* scene = _director->getRunningScene();
    Layer* layer = (Layer*) scene->getChildByName("View")->getChildByName("Layer");
    Sprite* player = (Sprite*) layer->getChildByName("Player");
    
    if(player->getPosition().x - (player->getContentSize().width * 0.5) - moveSpeed_ < 0)
    {
        int posX = (player->getContentSize().width * 0.5) + moveSpeed_;
        player->setPositionX(posX);
    }
    
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
    
    if(coin == nullptr && boss == nullptr)
    {
        NextMap(layer);
        return;
    }
    
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
            coin = (Sprite*) layer->getChildByName("Coin");
            
            PlayerInfo* playerInfo = PlayerInfo::getInstance();
            int coinScore = playerInfo->coinScore_;
            int coinMoney = playerInfo->coinMoney_;
            playerInfo->PlayGameUpdate(coinScore, coinMoney);
            
            if(coin == nullptr && boss == nullptr)
            {
                NextMap(layer);
                return;
            }
        }
    }
    
    if(coin == nullptr && boss != nullptr)
    {
        int curHp = bossinfo->getHp();
        bossinfo->setHp(--curHp);

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
            PlayerInfo* playerInfo = PlayerInfo::getInstance();
            int hp = playerInfo->getPlayerHp();
            hp -= 1;
            playerInfo->setPlayerHp(hp);
            layer->removeChildByName("Hp");
            
            if(hp <= 0)
            {
                playerInfo->playMapNumber_ = -1;
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
            PlayerInfo* playerInfo = PlayerInfo::getInstance();
            int hp = playerInfo->getPlayerHp();
            hp -= 1;
            playerInfo->setPlayerHp(hp);
            
            layer->removeChildByName("Hp");
            
            if(hp <= 0)
            {
                playerInfo->playMapNumber_ = -1;
                playerInfo->setPlayerHp(3);
                _director->popScene();
            }
        }
    }
}

void GameLayerController::NextMap(Layer* layer)
{
    PlayerInfo* playerInfo = PlayerInfo::getInstance();
    DataIO* dataIO = DataIO::getInstance();
    
    std::string fileName = "";
    fileName.append("Stage");
    fileName.append(std::to_string(playerInfo->playMapNumber_ + 1));
    fileName.append(".json");
    
    std::string filePath = FileUtils::getInstance()->getWritablePath();
    filePath.append(fileName);
    
    bool isFileCheck = FileUtils::getInstance()->isFileExist(filePath);

    if(!isFileCheck)
    {
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
    
    int hp = playerInfo->getPlayerHp();
    int maxHp = playerInfo->maxHp_;
    for(int heart_i = hp; heart_i > 0; --heart_i)
    {
        Sprite* heartSprite = Sprite::create("heart.png");
        heartSprite->setScale(0.3, 0.3);
        heartSprite->setPosition(x * 0.9 + ((maxHp - heart_i) * -25), y * 0.93);
        layer->addChild(heartSprite, 4, "Hp");
    }
    
    playerInfo->playMapNumber_ += 1;
    dataIO->readMapJSON(layer, fileName);
}

void GameLayerController::Timer(float dt)
{
    PlayerInfo* playerInfo = PlayerInfo::getInstance();
    playerInfo->clearTime_ += 1;
    
    Scene* scene = _director->getRunningScene();
    Layer* layer = (Layer*) scene->getChildByName("View")->getChildByName("Layer");
    Label* clearTimeLabel = (Label*) layer->getChildByName("ClearTimeLabel");
    clearTimeLabel->setString(playerInfo->TimerPrint(playerInfo->clearTime_));
}


