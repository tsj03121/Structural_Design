//
//  BossFactory.h
//  Structural_Design_Temp
//
//  Created by CD-parkdaedong on 2020/09/03.
//

#ifndef BossFactory_h
#define BossFactory_h
#include "Boss.h"

enum BossType
{
    TypeSpiderBoss,
    TypeSansBoss
};

class BossFactory
{
public:
    virtual Boss* CreateBoss(BossType bossType){};
};


#endif /* BossFactory_h */
