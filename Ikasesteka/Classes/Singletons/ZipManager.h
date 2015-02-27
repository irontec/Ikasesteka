//
//  ZipManager.h
//  IkasGame
//
//  Created by Sergio Garcia on 24/2/15.
//
//

#ifndef __IkasGame__ZipManager__
#define __IkasGame__ZipManager__

#include "cocos2d.h"
#include "../Constants/Constants.h"

using namespace cocos2d;

class ZipManager
{
public:
    static ZipManager* getInstance();
    ~ZipManager();
    
    bool saveZipDataToDisk(std::vector<char>* buffer);
    bool unzipZipDataAndDeletePreviousData();
    bool deleteZipData();
    std::string getDataFolderPath();
    std::string getDataFolderFullPath(std::string filePath);
protected:
    ZipManager();
    static ZipManager * _instance;
    std::string getZipFilePath();
    
};
#endif /* defined(__IkasGame__ZipManager__) */
