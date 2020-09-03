//
//  Boss.cpp
//  Structural_Design_Temp
//
//  Created by CD-parkdaedong on 2020/09/02.
//

#include <stdio.h>
#include "SpiderBoss.h"

USING_NS_CC;

SpiderBoss::SpiderBoss()
{
    bossInit();
}

void SpiderBoss::bossInit()
{
    setHp(3);
    setBossType(0);
    setbossImgName("spiderBoss.png");
}
