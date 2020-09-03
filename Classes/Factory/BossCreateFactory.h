//
//  BossCreateFactory.h
//  Structural_Design_Temp
//
//  Created by CD-parkdaedong on 2020/09/03.
//

#ifndef BossCreateFactory_h
#define BossCreateFactory_h

#include "BossFactory.h"

class BossCreateFactory : public BossFactory
{
    
public:
    virtual Boss* CreateBoss(BossType bossType) override;
};


#endif /* BossCreateFactory_h */
