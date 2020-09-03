//
//  Boss.h
//  Structural_Design_Temp
//
//  Created by CD-parkdaedong on 2020/09/02.
//

#ifndef Boss_h
#define Boss_h

class Boss : public cocos2d::Node
{
private:
    int hp_;
    int bossType_;
    std::string bossImgName_;
    
public:
    inline void setHp(int value) { hp_ = value; }
    inline void setBossType(int value) { bossType_ = value; }
    inline void setbossImgName(std::string value) { bossImgName_ = value; }

public:
    inline int getHp() { return hp_; }
    inline int getBossType() { return bossType_; }
    inline std::string getbossImgName() { return bossImgName_; }
    
public:
    virtual void bossInit(){};
};

#endif /* Boss_h */
