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

USING_NS_CC;



void EditorController::PlayerSelect(Ref *pSender, Layer* layer)
{
    mySelect_ = SelectSprite::Player;
    while(layer->getChildByName("Player") != nullptr)
    {
        layer->removeChildByName("Player");
    }
    
    pSprite_ = Sprite::create("red.png", Rect(0, 0, spriteSize, spriteSize));
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
            if(sprite->getName() == "Coin")
            {
                Rect coinRect = sprite->getBoundingBox();
                if(coinRect.containsPoint(touchPoint))
                {
                    lastSprite = (Sprite*) sprite;
                }
            }
        }
        layer->removeChild(lastSprite);
    }
    
    log("onTouchBegan id = %d, x = %f, y = %f", touch->getID(), touchPoint.x, touchPoint.y);
    
    if(pSprite_ != nullptr)
    {
        if(mySelect_ == SelectSprite::Player)
        {
            layer->addChild(pSprite_, 2, "Player");
            isPlayerCreate_ = true;
        }
        else
        {
            layer->addChild(pSprite_, 1, "Coin");
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
