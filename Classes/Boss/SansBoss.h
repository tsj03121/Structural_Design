//
//  SansBoss.h
//  Structural_Design_Temp
//
//  Created by CD-parkdaedong on 2020/09/03.
//

#ifndef SansBoss_h
#define SansBoss_h
#include "Boss.h"

class SansBoss : public Boss
{
public:
    virtual void bossInit() override;
    
public:
    SansBoss();
};

#endif /* SansBoss_h */
