//
//  DataIO.h
//  Structural_Design
//
//  Created by CD-parkdaedong on 2020/08/28.
//

#ifndef DataIO_h
#define DataIO_h

class DataIO
{
public:
    static DataIO* pDataIO;
    //int dataCount = 5;
    std::string openFileName = "";
    
public:
    static DataIO* getInstance();
    
public:
    void setData(int data[5]);
    void getData();
    void readJSON();
    void readUserData(std::string pData);
    void writeJSON();
    void writeUserData(std::string pszFileName, const char* pData);
    
    void readMapJSON(cocos2d::Layer* layer, std::string fileName);
    void readMapData(std::string pData, cocos2d::Layer* layer);
    void writeMapJSON(cocos2d::Layer* layer);
    void writeMapData(std::string pszFileName, const char* pData);
    
    std::list<std::string> FileExist();
};

#endif /* DataIO_h */
