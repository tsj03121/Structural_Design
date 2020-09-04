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
    static PlayerInfo* pPlayerInfo_;
    static PlayerInfo* getInstance();
    
public:
    int clearTime_ = 0;
    int shortClearTime_ = NULL;
    int coinScore_ = 10;
    int coinMoney_ = 100;
    int playMapNumber_ = -1;
    int maxTicket_ = 5;
    int maxHp_ = 3;
    
private:
    unsigned int playerHp_ = 3;
    unsigned int highScore_ = 0;
    unsigned int totalScore_ = 0;
    unsigned int nowScore_ = 0;
    unsigned int totalMoney_ = 0;
    unsigned int nowMoney_ = 0;
    unsigned int ticket_ = 5;
    
public:
    int getNowMoney(){ return nowMoney_; };
    int getTotalMoney(){ return totalMoney_; };
    int getTicket(){ return ticket_; };
    int getHighScore(){ return highScore_; };
    int getNowScore(){ return nowScore_; };
    int getTotalScore(){ return totalScore_; };
    int getPlayerHp(){ return playerHp_; };
    
public:
    void setShortClearTime(int t);
    void setHighScore(int num);
    void setTicket(int num){ ticket_ = num; };
    void setNowScore(int num){ nowScore_ = num; };
    void setNowMoney(int num){ nowMoney_ = num; };
    void setPlayerHp(int num){ playerHp_ = num; };
    
public:
    void addNowScore(int num){ nowScore_ += num; };
    void addNowMoney(int num){ nowMoney_ += num; };
    void addTotalScore(int num){ totalScore_ += num; };
    void addTotalMoney(int num){ totalMoney_ += num; };
    
public:
    void PlayGameUpdate(int coinScore, int coinMoney);
    void TotalUpdate();
    std::string TimerPrint(int t);
};

#endif /* Player_h */
