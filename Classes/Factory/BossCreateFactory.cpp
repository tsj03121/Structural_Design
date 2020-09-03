//
//  BossCreateFactory.cpp
//  Structural_Design_Temp
//
//  Created by CD-parkdaedong on 2020/09/03.
//


#include <stdio.h>
#include "BossCreateFactory.h"
#include "SpiderBoss.h"
#include "SansBoss.h"

Boss* BossCreateFactory::CreateBoss(BossType bossType)
{
    Boss* boss = nullptr;
    switch (bossType)
    {
        case BossType::TypeSpiderBoss:
        {
            return new SpiderBoss();
        }
            
        case BossType::TypeSansBoss:
        {
            return new SansBoss();
        }
    }
    return boss;
}
