//
//  MainCategory.h
//  ikaszopa
//
//  Created by Axier Fernandez on 24/2/15.
//
//

#ifndef ikaszopa_MainCategory_h
#define ikaszopa_MainCategory_h

#include "cocos2d.h"
#include "SubCategory.h"
#include "../Constants/Constants.h"

using namespace cocos2d;
using namespace std;

class MainCategory : public Object
{
public:
    
    MainCategory(){};
    ~MainCategory(){};
    
    vector<SubCategory*> getFilteredSubCategoriesByLevel(Difficulty difficulty);
    vector<SubCategory*> getFilteredSubCategoriesByLevel(int minLevel);
    
    CC_SYNTHESIZE(string, m_Name, Name);
    CC_SYNTHESIZE(string, m_FileName, FileName);
    CC_SYNTHESIZE(vector<SubCategory*>, m_SubCategories, SubCategories);
};

#endif
