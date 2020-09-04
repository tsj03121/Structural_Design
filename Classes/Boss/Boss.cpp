//
//  Boss.cpp
//  Structural_Design_Temp
//
//  Created by CD-parkdaedong on 2020/09/02.
//

#include <stdio.h>
#include "Boss.h"
#include "PlayerInfomation.h"

USING_NS_CC;

void Boss::BossAttack(float dt)
{
    Layer* layer = (Layer*) _director->getRunningScene()->getChildByName("View")->getChildByName("Layer");
    Sprite* playerSprite = (Sprite*) layer->getChildByName("Player");
    Sprite* bossSprite = (Sprite*) layer->getChildByName("Boss");
    
    Sprite* fireAttackSprite = (Sprite*) layer->getChildByName("FireAttack");
    
    if(fireAttackSprite == nullptr)
    {
        float fireAttackDir = bossSprite->getPositionX() - playerSprite->getPositionX();
        fireAttackSprite = Sprite::create("fireAttack.png");
        fireAttackSprite->setPositionY(bossSprite->getPositionY() + bossSprite->getContentSize().height * 0.5);
        fireAttackSprite->setScale(1, 1);
        
        if(fireAttackDir >= 0)
        {
            fireAttackSprite->setPositionX(bossSprite->getPositionX());
            fireAttackSprite->setRotation(90);
        }
        else
        {
            fireAttackSprite->setPositionX(bossSprite->getPositionX() + bossSprite->getContentSize().width);
            fireAttackSprite->setRotation(-90);
        }
        
        layer->addChild(fireAttackSprite, 1, "FireAttack");
    }
    
    
    float fireX = fireAttackSprite->getPositionX();

    if(fireAttackSprite->getRotation() == 90)
    {
        fireAttackSprite->setPositionX(fireX - 10);
        if(fireX <= 0)
        {
            layer->removeChild(fireAttackSprite);
            fireAttackSprite = nullptr;
            return;
        }
    }
    else
    {
        fireAttackSprite->setPositionX(fireX + 10);

        if(fireX >= _director->getWinSize().width)
        {
            layer->removeChild(fireAttackSprite);
            fireAttackSprite = nullptr;
            return;
        }
    }
    
    Rect fireAttackBox = fireAttackSprite->getBoundingBox();
    Rect playerBox = playerSprite->getBoundingBox();
    
    if(fireAttackBox.intersectsRect(playerBox))
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
