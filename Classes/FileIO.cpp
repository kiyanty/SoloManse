#include "cocos2d.h"
// #include "CCFileUtils.h"
#include "FileIO.h"
#include "FileEncryptor.h"
#include "FileDecryptor.h"
#include <fstream>
#include "GameData.h"
#include <sstream>

using std::string;
using cocos2d::CCFileUtils;

FileIO* FileIO::instance;

void FileIO::readFile()
{
    string path = getFilePath();
    
    char buffer[256]={0};
    
    std::ifstream ifs(path.c_str(), std::ios::binary);
    
    if(!ifs.is_open())
    {
        saveFile();
        ifs.open(path.c_str(), std::ios::binary);
    }
    
    ifs.read(buffer, 2);
    FileDecryptor fd(buffer[0], buffer[1]);

    ifs.read(buffer, 256);
    fd.Decrypt(buffer, 256);
 
//    CCLOG("read %s", buffer);
    
    int sum = 0;
    for(int i=0; i<sizeof(buffer); i++)
    {
        sum += buffer[i];
    }
    if(sum % 7 != 0)
    {
//        CCLOG("%d", sum % 7);
        saveFile();
        ifs.open(path.c_str(), std::ios::binary);
        
        for(int i=0; i<sizeof(buffer); i++)
        {
            buffer[i] = 0;
        }

        ifs.read(buffer, 2);
        FileDecryptor fd(buffer[0], buffer[1]);
        
        ifs.read(buffer, 256);
        fd.Decrypt(buffer, 256);
    }
    
    string temp = "";
    int dataNumber = 0;
    for(int i=2; i<sizeof(buffer); i++)
    {
        if(buffer[i] == ',')
        {
            variableSetting(temp, dataNumber);
            dataNumber++;
            temp = "";
            continue;
        }
        else if(buffer[i] == 0)
        {
            break;
        }
        else
        {
            temp += buffer[i];
        }
    }
    
    ifs.close();
    
//    if(GameData::saveVersion != GameData::SCORE_VERSION)
//    {
//        GameData::highestHardcoreScore = 0;
//        GameData::highestNormalScore = 0;
//        GameData::saveVersion = GameData::SCORE_VERSION;
//        saveFile();
//    }
}

void FileIO::saveFile()
{
    FileEncryptor fe;
    
    string path = getFilePath();
    char buffer[256];
    
    std::ofstream ofs(path.c_str(), std::ios::binary);
    
    fe.GetKey(buffer);
    ofs.write(buffer, 2);

    char temp[256] = {0};
    
    sprintf(temp, "%c,%d,%d,%d,", 0,
            GameData::isMusicSound, GameData::highScore, GameData::guestId);
//
    int sum = 0;
    for(int i=0; i<sizeof(temp); i++)
    {
        sum += temp[i];
    }
    
    temp[0] = 7 - sum % 7;
    
    for(int i=0; i<sizeof(buffer); i++)
    {
        buffer[i] = temp[i];
    }
  
//    CCLOG("write %s", buffer);
    fe.Encrypt(buffer, 256);
    ofs.write(buffer, 256);
    
    ofs.close();
}

string FileIO::getFilePath()
{
    string path = (CCFileUtils::sharedFileUtils()) -> getWriteablePath();
    path.append("data");
//    CCLOG("getFilePath() : %s", path.c_str());
    return path;
}

void FileIO::variableSetting(string temp, int dataNumber)
{
    std::stringstream ss(temp);
    int data;
    ss >> data;
    
    switch (dataNumber)
    {
        case 0:
            GameData::isMusicSound = data;
            break;
        case 1:
            GameData::highScore = data;
            break;
        case 2:
            GameData::guestId = data;
            break;
    }
    CCLOG("%d, %d, %d", GameData::isMusicSound, GameData::highScore, GameData::guestId);
//    CCLOG("%d,%d,%d,%d,%d", GameData::isBackSound, GameData::isEffectSound, GameData::isVibrate, GameData::money, GameData::highestScore);
}

FileIO* FileIO::sharedInstance()
{
    if(instance == NULL)
    {
        instance = new FileIO();
    }
    return instance;
}

void FileIO::removeInstance()
{
    delete this;
}