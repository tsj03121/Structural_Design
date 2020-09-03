//
//  BossCreateFactory.cpp
//  Structural_Design_Temp
//
//  Created by CD-parkdaedong on 2020/09/03.
//


#include <stdio.h>
#include "SpiderBoss.h"
#include "BossCreateFactory.h"

Boss* BossCreateFactory::CreateBoss(BossType bossType)
{
    Boss* boss = nullptr;
    switch (bossType)
    {
        case BossType::TypeSpiderBoss:
        {
            return new SpiderBoss();
        }
    }
    return boss;
}

//BossType BossCreateFactory::getBossType(int num)
//{
//    switch (num)
//    {
//        case 0:
//        {
//            return BossType::TypeSpiderBoss;
//        }
//    }
//}
