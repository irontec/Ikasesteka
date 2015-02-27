//
//  DataFileManager.h
//  ikaszopa
//
//  Created by Axier Fernandez on 24/2/15.
//
//

#ifndef __ikaszopa__DataFileManager__
#define __ikaszopa__DataFileManager__

#include <stdio.h>
#include "cocos2d.h"
#include "../json/cJSON.h"
#include "../GameModels/MainCategory.h"
#include "../GameModels/SubCategory.h"
#include "../GameModels/Option.h"

using namespace cocos2d;
using namespace std;

class DataFileManager
{
public:
    static DataFileManager* getInstance();
    ~DataFileManager();
    void parseDataFile();
    CC_SYNTHESIZE_READONLY(vector<MainCategory*>, _categories, MainCategories);
protected:
    DataFileManager();
    static DataFileManager * _instance;
};

#endif /* defined(__ikaszopa__DataFileManager__) */
