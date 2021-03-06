//
//  EditorController.h
//  Structural_Design_Temp
//
//  Created by CD-parkdaedong on 2020/08/31.
//

#ifndef EditorController_h
#define EditorController_h

enum SelectSprite
{
    Player,
    Coin,
    Trap,
    Boss
};

class EditorController : public cocos2d::Node
{
public:
    bool isPlayerCreate_ = false;
    cocos2d::Sprite* pSprite_ = nullptr;
    SelectSprite mySelect_;

public:
    void MenuVisibility(bool isVisible);
    
    void Goto_Lobby(cocos2d::Ref* pSender);
    void LoadMapList(cocos2d::Ref* pSender);
    void CoinSelect(cocos2d::Ref* pSender);
    void TrapSelect(cocos2d::Ref* pSender);
    
    void PlayerSelect(cocos2d::Ref* pSender, cocos2d::Layer* layer);
    void SpiderBossSelect(cocos2d::Ref* pSender, cocos2d::Layer* layer);
    void SansBossSelect(cocos2d::Ref* pSender, cocos2d::Layer* layer);
    void SaveEditor(cocos2d::Ref* pSender, cocos2d::Layer* layer);

public:
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif /* EditorController_h */
