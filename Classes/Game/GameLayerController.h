//
//  GameLayerController.h
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/27.
//

#ifndef GameLayerController_h
#define GameLayerController_h
#include "PlayerInfomation.h"
class GameLayerController : public cocos2d::Node
{
public:
    int moveSpeed_ = 10;
    
public:
    void Timer(float dt);
    void MoveUP(cocos2d::Ref* pSender);
    void MoveDOWN(cocos2d::Ref* pSender);
    void MoveLEFT(cocos2d::Ref* pSender);
    void MoveRIGHT(cocos2d::Ref* pSender);
    void Change_ResultLayer(cocos2d::Ref* pSender);
    void CoinCheck(cocos2d::Layer* gameLayer, cocos2d::Sprite* coinSprite);
    void PlayerInfoUpdate(PlayerInfo playerInfo);
    
    std::string TimerPrint(int t);
};
#endif /* GameLayerController_h */
