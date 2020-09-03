//
//  EditorController.cpp
//  Structural_Design_Temp
//
//  Created by CD-parkdaedong on 2020/08/31.
//

#include <stdio.h>
#include "EditorController.h"
#include "LobbyScene.h"
#include "DataIO.h"
#include "LoadMapLayer.h"
#include "json.h"
#include "SpiderBoss.h"
#include "SansBoss.h"

USING_NS_CC;

void EditorController::PlayerSelect(Ref *pSender, Layer* layer)
{
    mySelect_ = SelectSprite::Player;
    while(layer->getChildByName("Player") != nullptr)
    {
        layer->removeChildByName("Player");
    }
    
    pSprite_ = Sprite::create("red.png", Rect(0, 0, spriteSize_, spriteSize_));
    pSprite_->retain();
    MenuVisibility(false);
}

void EditorController::CoinSelect(Ref *pSender)
{
    mySelect_ = SelectSprite::Coin;
    pSprite_ = Sprite::create("coin.png");
    pSprite_->setScale(0.05, 0.05);
    pSprite_->retain();
    MenuVisibility(false);
}

void EditorController::TrapSelect(Ref *pSender)
{
    mySelect_ = SelectSprite::Trap;
    pSprite_ = Sprite::create("trap.png");
    pSprite_->retain();
    MenuVisibility(false);
}

void EditorController::SpiderBossSelect(Ref *pSender, Layer* layer)
{
    mySelect_ = SelectSprite::Boss;
    while(layer->getChildByName("Boss") != nullptr)
    {
        layer->removeChildByName("Boss");
    }
    
    pSprite_ = Sprite::create("spiderBoss.png");
    pSprite_->setScale(4, 4);
    pSprite_->retain();
    
    SpiderBoss* bossInfo = new SpiderBoss();
    pSprite_->addChild(bossInfo, -1, "BossInfo");
    
    MenuVisibility(false);
}

void EditorController::SansBossSelect(Ref* pSender, Layer* layer)
{
    mySelect_ = SelectSprite::Boss;
    while(layer->getChildByName("Boss") != nullptr)
    {
        layer->removeChildByName("Boss");
    }
    pSprite_ = Sprite::create("sansBoss.png");
    pSprite_->setScale(0.5, 0.5);
    pSprite_->retain();
    
    SansBoss* bossInfo = new SansBoss();
    pSprite_->addChild(bossInfo, -1, "BossInfo");
    
    MenuVisibility(false);
}

bool EditorController::onTouchBegan(Touch *touch, Event *event)
{
    auto touchPoint = touch->getLocation();
    Scene* scene = _director->getRunningScene();
    Layer* layer = (Layer*) scene->getChildByName("View")->getChildByName("Layer");
    
    if(pSprite_ == nullptr)
    {
        Vector<Node*> sprites = layer->getChildren();
        Sprite* lastSprite;
        for(auto sprite : sprites)
        {
            if(sprite->getName() == "Menu2")
                continue;
            
            Rect spriteRect = sprite->getBoundingBox();
            if(spriteRect.containsPoint(touchPoint))
            {
                lastSprite = (Sprite*) sprite;
            }
        }
        
        if(lastSprite != nullptr)
        {
            layer->removeChild(lastSprite);
        }
    }

    if(pSprite_ != nullptr)
    {
        if(mySelect_ == SelectSprite::Player)
        {
            layer->addChild(pSprite_, 2, "Player");
            isPlayerCreate_ = true;
        }
        else if(mySelect_ == SelectSprite::Coin)
        {
            layer->addChild(pSprite_, 1, "Coin");
        }
        else if(mySelect_ == SelectSprite::Trap)
        {
            layer->addChild(pSprite_, 1, "Trap");
        }
        else if(mySelect_ == SelectSprite::Boss)
        {
            layer->addChild(pSprite_, 1, "Boss");
        }
        
        pSprite_->setPosition(touchPoint.x, touchPoint.y);
        
        pSprite_->release();
        pSprite_ = nullptr;
        
        MenuVisibility(true);
    }
    return true;
}

void EditorController::MenuVisibility(bool isVisible)
{
    Scene* scene = _director->getRunningScene();
    Layer* layer = (Layer*) scene->getChildByName("View")->getChildByName("Layer");
    
    Menu* menu = (Menu*) layer->getChildByName("Menu");
    menu->setVisible(isVisible);
    
    Menu* menu2 = (Menu*) layer->getChildByName("Menu2");
    menu2->setVisible(isVisible);
}

void EditorController::SaveEditor(cocos2d::Ref *pSender, Layer* layer)
{
    if((Sprite*)layer->getChildByName("Player") == nullptr)
        return;
    
    DataIO* dataIO = DataIO::getInstance();
    dataIO->writeMapJSON(layer);
    
    Goto_Lobby(pSender);
}

void EditorController::Goto_Lobby(cocos2d::Ref *pSender)
{
    _director->popScene();
}

void EditorController::LoadMapList(cocos2d::Ref *pSender)
{
    Layer* loadLayer = LoadMapLayer::create();
}
