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
    setHp(2);
    setBossType(0);
    setScaleSize(Size(4, 4));
    setbossImgName("spiderBoss.png");

    Scene* scene = (Scene*) _director->getRunningScene();
    if(scene->getName() != "Editor")
    {
        schedule(schedule_selector(SpiderBoss::BossAttack), 0.1);
    }
    
}
