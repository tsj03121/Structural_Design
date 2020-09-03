//
//  Boss.h
//  Structural_Design_Temp
//
//  Created by CD-parkdaedong on 2020/09/02.
//

#ifndef SpiderBoss_h
#define SpiderBoss_h
#include "Boss.h"

class SpiderBoss : public Boss
{
public:
    virtual void bossInit() override;
    
public:
    SpiderBoss();
};

#endif /* Boss_h */
