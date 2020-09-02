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
    

//    배열 읽을 때
//    const Json::Value array = root["a"];
//    for (unsigned int i = 0; i < array.size(); ++i)
//    {
//        int item = array[i].asInt();
//        log("%d, ", item);
//    }
    
}

void DataIO::writeJSON()
{
    PlayerInfo pPlayerInfo = PlayerInfo::getInstance();
    
    //배열 쓰기 사용방법
    //Json::Value friends;
    //    friends.append("Im Kkeokjung");
    //    friends.append("Elisabeth");
    //    root["Friend"] = friends;

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
    player->setPosition(root.get("PlayerX", "defaultvalue").asDouble(), root.get("PlayerY", "defaultvalue").asDouble());
    layer->addChild(player, 2, "Player");
    
    const Json::Value arrayX = root["CoinX"];
    const Json::Value arrayY = root["CoinY"];
    for (int posX = 0; posX < arrayX.size(); ++posX)
    {
        Sprite* coin = Sprite::create("coin.png");
        coin->setScale(0.05, 0.05);
        coin->setPosition(arrayX[posX].asDouble(), arrayY[posX].asDouble());
        layer->addChild(coin, 1, "Coin");
    }
}

void DataIO::writeMapJSON(Layer* layer)
{
    Json::Value root;
    Sprite* player = (Sprite*) layer->getChildByName("Player");
    root["PlayerX"] = player->getPosition().x;
    root["PlayerY"] = player->getPosition().y;
    
    Json::Value coinX;
    Json::Value coinY;
    Vector<Node*> node = layer->getChildren();
    for(Node* sprites : node)
    {
        Sprite* sprite = (Sprite*) sprites;
        if(sprite->getName() == "Coin")
        {
            coinX.append(sprite->getPosition().x);
            coinY.append(sprite->getPosition().y);
        }
    }
    root["CoinX"] = coinX;
    root["CoinY"] = coinY;
    
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
        //filePath.append("\\");
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



