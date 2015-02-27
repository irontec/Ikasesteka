//
//  DataFileManager.cpp
//  ikaszopa
//
//  Created by Axier Fernandez on 24/2/15.
//
//

#include "DataFileManager.h"
#include "../Singletons/ZipManager.h"

using namespace cocos2d;

DataFileManager * DataFileManager::_instance = NULL;

DataFileManager* DataFileManager::getInstance()
{
    if(!_instance) _instance = new DataFileManager();
    return _instance;
}

DataFileManager::DataFileManager()
{
}

DataFileManager::~DataFileManager()
{
}

void DataFileManager::parseDataFile()
{
    _categories.clear();
    
    string fullPath = ZipManager::getInstance()->getDataFolderFullPath("data.json");
    if (fullPath.empty()) {
        return;
    }
    unsigned char* fileContent = NULL;
    ssize_t bufferSize = 0;
    fileContent = CCFileUtils::getInstance()->getFileData(fullPath.c_str(), "r", &bufferSize);
    if (fileContent == NULL) {
        return;
    }
    cocos2d::CCString *ccStr = cocos2d::CCString::createWithData(fileContent, bufferSize);
    free(fileContent);
    
    cJSON *pRoot = cJSON_Parse(ccStr->getCString());
    int numItems = cJSON_GetArraySize(pRoot);
    
    for (int i = 0; i < numItems; i++)
    {
        MainCategory *pCat = new MainCategory();
        
        cJSON * item = cJSON_GetArrayItem(pRoot, i);
        pCat->setName(cJSON_GetObjectItem(item, "name")->valuestring);
        pCat->setFileName(cJSON_GetObjectItem(item, "fileName")->valuestring);
        
        cJSON *pSubCategories = cJSON_GetObjectItem(item, "element");
        
        vector<SubCategory*> subCategories;
        
        int numSubCategories = cJSON_GetArraySize(pSubCategories);
        for (int j = 0; j < numSubCategories; j++)
        {
            cJSON *jsonSubCategories = cJSON_GetArrayItem(pSubCategories, j);
            SubCategory *pSub = new SubCategory();
            pSub->setName(cJSON_GetObjectItem(jsonSubCategories, "name")->valuestring);
            pSub->setFileName(cJSON_GetObjectItem(jsonSubCategories, "fileName")->valuestring);
            pSub->setMinLevel(cJSON_GetObjectItem(jsonSubCategories, "minLevel")->valueint);
            pSub->setMainColor(cJSON_GetObjectItem(jsonSubCategories, "mainColor")->valuestring);
            
            cJSON *pOptions = cJSON_GetObjectItem(jsonSubCategories, "options");
            
            vector<Option*> options;
            
            int numOptions = cJSON_GetArraySize(pOptions);
            for (int k = 0; k < numOptions; k++)
            {
                cJSON *jsonOption = cJSON_GetArrayItem(pOptions, k);
                Option *pOpt = new Option();
                pOpt->setName(cJSON_GetObjectItem(jsonOption, "name")->valuestring);
                pOpt->setFileName(cJSON_GetObjectItem(jsonOption, "fileName")->valuestring);
                options.push_back(pOpt);
            }
            
            pSub->setOptions(options);
            
            subCategories.push_back(pSub);
        }
        
        pCat->setSubCategories(subCategories);
        _categories.push_back(pCat);
    }
    
    cJSON_Delete(pRoot);
}

