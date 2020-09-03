//
//  DataIO.cpp
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/28.
//

#include <stdio.h>
#include "DataIO.h"
#include "PlayerInfomation.h"
#include "json.h"
#include "SpiderBoss.h"
#include "BossCreateFactory.h"

USING_NS_CC;

DataIO* DataIO::pDataIO = nullptr;

DataIO* DataIO::getInstance()
{
    if(pDataIO == nullptr)
    {
        pDataIO = new DataIO();
    }
    
    return pDataIO;
}

void DataIO::readJSON()
{
    std::string fileName = FileUtils::getInstance()->getWritablePath();
    fileName.append("test_data.json");
    
    if(fileName == "")
        return;
    
    unsigned long bufferSize = 0;
    unsigned char* json = FileUtils::sharedFileUtils()->getFileData(fileName.c_str(), "rb", (ssize_t *) &bufferSize);
    std::string clearData((const char*)json, bufferSize);
    
    readUserData(clearData);
}

void DataIO::readUserData(std::string pData)
{
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(pData, root);
    if (! parsingSuccessful)
    {
        log("parser failed : \n %s", pData.c_str());
        return ;
    }
    
    int highScore = root.get("HighScore", "defaultvalue").asInt();
    int score = root.get("Score", "defaultvalue").asInt();
    int time = root.get("Time", "defaultvalue").asInt();
    int money = root.get("Money", "defaultvalue").asInt();
    int ticket = root.get("Ticket", "defaultvalue").asInt();
    
    PlayerInfo pPlayerInfo = PlayerInfo::getInstance();
    pPlayerInfo.pPlayerInfo_->setHighScore(highScore);
    pPlayerInfo.pPlayerInfo_->addTotalScore(score);
    pPlayerInfo.pPlayerInfo_->setShortClearTime(time);
    pPlayerInfo.pPlayerInfo_->addMoney(money);
    pPlayerInfo.pPlayerInfo_->setTicket(ticket);
}

void DataIO::writeJSON()
{
    PlayerInfo pPlayerInfo = PlayerInfo::getInstance();

    Json::Value root;
    root["HighScore"] = pPlayerInfo.pPlayerInfo_->getHighScore();
    root["Score"] = pPlayerInfo.pPlayerInfo_->getTotalScore();
    root["Time"] = pPlayerInfo.pPlayerInfo_->shortClearTime_;
    root["Money"] = pPlayerInfo.pPlayerInfo_->getMoney();
    root["Ticket"] = pPlayerInfo.pPlayerInfo_->getTicket();

    Json::StyledWriter writer;
    std::string strJSON = writer.write(root);
    std::string filePath = FileUtils::getInstance()->getWritablePath();
    filePath.append("test_data.json");
    
    log("JSON WriteTest : %s" , strJSON.c_str());
    writeUserData( filePath, strJSON.c_str());
}

void DataIO::writeUserData(std::string pszFileName, const char* pData)
{
    FILE *fp = fopen(pszFileName.c_str(), "wb");
    if (! fp)
    {
        log("can not create file %s", pszFileName.c_str());
        return;
    }
    else
    {
        log("write file success: %s",pszFileName.c_str());
    }
    fputs(pData, fp); //pdata->fp에 복사
    fclose(fp);
}


void DataIO::readMapJSON(Layer* layer, std::string fileName)
{
    std::string filePath = FileUtils::getInstance()->getWritablePath();
    filePath.append(fileName);
    
    if(filePath == "")
        return;
    
    unsigned long bufferSize = 0;
    unsigned char* json = FileUtils::sharedFileUtils()->getFileData(filePath.c_str(), "rb", (ssize_t *) &bufferSize);
    std::string clearData((const char*)json, bufferSize);
    
    readMapData(clearData, layer);
}

void DataIO::readMapData(std::string pData, Layer* layer)
{
    int spriteSize = 30;
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(pData, root);
    if (! parsingSuccessful)
    {
        log("parser failed : \n %s", pData.c_str());
        return ;
    }
    
    Sprite* player = Sprite::create("red.png", Rect(0, 0, spriteSize, spriteSize));
    double playerX = root.get("PlayerX", "defaultvalue").asDouble();
    double playerY = root.get("PlayerY", "defaultvalue").asDouble();
    player->setPosition(playerX, playerY);
    layer->addChild(player, 2, "Player");
    
    if(root.get("BossType", -1).asInt() != -1)
    {
        BossCreateFactory* bossFactory = new BossCreateFactory();
        Boss* boss = bossFactory->CreateBoss((BossType) root.get("BossType", -1).asInt());
        Sprite* bossSprite = Sprite::create(boss->getbossImgName());
        bossSprite->addChild(boss, -1, "BossInfo");
        bossSprite->setScale(boss->getScaleSize().height, boss->getScaleSize().width);
        
        double bossX = root.get("BossX", "defaultvalue").asDouble();
        double bossY = root.get("BossY", "defaultvalue").asDouble();
        bossSprite->setPosition(bossX, bossY);
        layer->addChild(bossSprite, 1, "Boss");
    }
    
    const Json::Value coinArrayX = root["CoinX"];
    const Json::Value coinArrayY = root["CoinY"];
    for (int posX = 0; posX < coinArrayX.size(); ++posX)
    {
        Sprite* coin = Sprite::create("coin.png");
        coin->setScale(0.05, 0.05);
        coin->setPosition(coinArrayX[posX].asDouble(), coinArrayY[posX].asDouble());
        layer->addChild(coin, 1, "Coin");
    }
    
    const Json::Value trapArrayX = root["TrapX"];
    const Json::Value trapArrayY = root["TrapY"];
    for (int posX = 0; posX < trapArrayX.size(); ++posX)
    {
        Sprite* trap = Sprite::create("trap.png");
        trap->setPosition(trapArrayX[posX].asDouble(), trapArrayY[posX].asDouble());
        layer->addChild(trap, 1, "Trap");
    }
}

void DataIO::writeMapJSON(Layer* layer)
{
    Json::Value root;
    Sprite* player = (Sprite*) layer->getChildByName("Player");
    root["PlayerX"] = player->getPosition().x;
    root["PlayerY"] = player->getPosition().y;
    
    Sprite* boss = (Sprite*) layer->getChildByName("Boss");
    if(boss != nullptr)
    {
        Boss* bossinfo = (Boss*) boss->getChildByName("BossInfo");
        root["BossType"] = bossinfo->getBossType();
        root["BossX"] = boss->getPosition().x;
        root["BossY"] = boss->getPosition().y;
    }
    
    Json::Value coinX;
    Json::Value coinY;
    Json::Value trapX;
    Json::Value trapY;
    Vector<Node*> node = layer->getChildren();
    for(Node* sprites : node)
    {
        Sprite* sprite = (Sprite*) sprites;
        if(sprite->getName() == "Coin")
        {
            coinX.append(sprite->getPosition().x);
            coinY.append(sprite->getPosition().y);
        }
        else if(sprite->getName() == "Trap")
        {
            trapX.append(sprite->getPosition().x);
            trapY.append(sprite->getPosition().y);
        }
    }
    root["CoinX"] = coinX;
    root["CoinY"] = coinY;
    root["TrapX"] = trapX;
    root["TrapY"] = trapY;
    
    Json::StyledWriter writer;
    std::string strJSON = writer.write(root);
    std::string filePath = FileUtils::getInstance()->getWritablePath();
    if(openFileName == "")
    {
        filePath.append("Save1.json");
        
        bool isFileCheck = FileUtils::getInstance()->isFileExist(filePath);
        int count = 2;
        
        while(isFileCheck)
        {
            filePath = FileUtils::getInstance()->getWritablePath();
            filePath.append("Save");
            filePath.append(std::to_string(count));
            filePath.append(".json");
            isFileCheck = FileUtils::getInstance()->isFileExist(filePath);
            count += 1;
        }
    }
    else
    {
        filePath.append(openFileName);
    }

    log("JSON WriteMapJson : %s" , strJSON.c_str());
    writeMapData(filePath, strJSON.c_str());
}

void DataIO::writeMapData(std::string pszFileName, const char* pData)
{
    FILE *fp = fopen(pszFileName.c_str(), "wb");
    if (! fp)
    {
        log("can not create file %s", pszFileName.c_str());
        return;
    }
    else
    {
        log("write file success: %s",pszFileName.c_str());
    }
    fputs(pData, fp); //pdata->fp에 복사
    fclose(fp);
}

std::list<std::string> DataIO::FileExist()
{
    std::list<std::string> fileNames;
    std::string filePath = FileUtils::getInstance()->getWritablePath();
    std::string fileName = "Save1.json";
    filePath.append(fileName);
    bool isFileCheck = FileUtils::getInstance()->isFileExist(filePath);
    int count = 1;
    while(isFileCheck)
    {
        fileNames.push_back(fileName);
        count += 1;
        filePath = FileUtils::getInstance()->getWritablePath();
        fileName = "Save";
        fileName.append(std::to_string(count));
        fileName.append(".json");
        filePath.append(fileName);
        isFileCheck = FileUtils::getInstance()->isFileExist(filePath);
    }
    
    return fileNames;
}



