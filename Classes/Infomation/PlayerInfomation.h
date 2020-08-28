//
//  Player.h
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/28.
//

#ifndef Player_h
#define Player_h

class PlayerInfo
{
public:
    int clearTime_ = 0;
    int shortClearTime_ = NULL;
    int coinScore_ = 10;
    int coinMoney_ = 100;
    
private:
    unsigned int highScore_ = 0;
    unsigned int totalScore_ = 0;
    unsigned int nowScore_ = 0;
    unsigned int money_ = 0;
    unsigned int ticket_ = 5;

public:
    static PlayerInfo* pPlayerInfo_;

public:
    static PlayerInfo& getInstance();
    
public:
    int getMoney(){ return money_; };
    int getTicket(){ return ticket_; };
    int getHighScore(){ return highScore_; };
    int getNowScore(){ return nowScore_; };
    int getTotalScore(){ return totalScore_; };
    
public:
    void setShortClearTime(int t);
    void setHighScore(int num);
    void setTicket(int num){ ticket_ = num; };
    void setNowScore(int num){ nowScore_ = num; };
    
public:
    void addNowScore(int num){ nowScore_ += num; };
    void addMoney(int num){ money_ += num; };
    void addTotalScore(int num){ totalScore_ += num; };
    
    
public:
    std::string TimerPrint(int t);
};

#endif /* Player_h */
