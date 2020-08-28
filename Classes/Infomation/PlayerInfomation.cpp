//
//  PlayerInfomation.cpp
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/28.
//

#include <stdio.h>
#include "PlayerInfomation.h"

PlayerInfo* PlayerInfo::pPlayerInfo_ = nullptr;

PlayerInfo& PlayerInfo::getInstance()
{
    if(pPlayerInfo_ == nullptr)
    {
        pPlayerInfo_ = new PlayerInfo();
    }
    return *pPlayerInfo_;
}

void PlayerInfo::setHighScore(int num)
{
    if(highScore_ < num)
    {
        highScore_ = num;
    }
}

void PlayerInfo::setShortClearTime(int t)
{
    if(shortClearTime_ == 0)
    {
        shortClearTime_ = t;
        return;
    }
    
    if(shortClearTime_ > t)
    {
        shortClearTime_ = t;
    }
}

std::string PlayerInfo::TimerPrint(int t)
{
    std::string timerText = "";
    int h = t / 3600;
    int m = (t - (h * 3600)) / 60;
    int s = t - (h * 3600) - (m * 60);
    if(h == 0)
    {
        timerText.append("00 : ");
    }
    else if(h < 10)
    {
        timerText.append("0");
        timerText.append(std::to_string(h));
        timerText.append(" : ");
    }
    else if(h >= 10)
    {
        timerText.append(std::to_string(h));
        timerText.append(" : ");
    }
    
    if(m == 0)
    {
        timerText.append("00 : ");
    }
    else if(m < 10)
    {
        timerText.append("0");
        timerText.append(std::to_string(m));
        timerText.append(" : ");
    }
    else if(m >= 10)
    {
        timerText.append(std::to_string(m));
        timerText.append(" : ");
    }
    
    if(s == 0)
    {
        timerText.append("00");
    }
    else if(s < 10)
    {
        timerText.append("0");
        timerText.append(std::to_string(s));
    }
    else if(s >= 10)
    {
        timerText.append(std::to_string(s));
    }
    
    return timerText;
}
