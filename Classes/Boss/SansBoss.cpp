//
//  SansBoss.cpp
//  Structural_Design_Temp
//
//  Created by CD-parkdaedong on 2020/09/03.
//

#include <stdio.h>
#include "SansBoss.h"

USING_NS_CC;

SansBoss::SansBoss()
{
    bossInit();
}

void SansBoss::bossInit()
{
    setHp(5);
    setBossType(1);
    setScaleSize(Size(0.5, 0.5));
    setbossImgName("sansBoss.png");
    
    Scene* scene = (Scene*) _director->getRunningScene();
    if(scene->getName() != "Editor")
    {
        schedule(schedule_selector(SansBoss::BossAttack), 0.1);
    }
}
