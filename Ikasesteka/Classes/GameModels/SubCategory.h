//
//  SubCategory.h
//  ikaszopa
//
//  Created by Axier Fernandez on 24/2/15.
//
//

#ifndef ikaszopa_SubCategory_h
#define ikaszopa_SubCategory_h

#include "cocos2d.h"
#include "Option.h"

using namespace cocos2d;
using namespace std;

class SubCategory : public Object
{
public:
    
    SubCategory(){};
    ~SubCategory(){};
    
    CC_SYNTHESIZE(string, m_Name, Name);
    CC_SYNTHESIZE(string, m_FileName, FileName);
    CC_SYNTHESIZE(int, m_MinLevel, MinLevel);
    CC_SYNTHESIZE(string, m_MainColor, MainColor);
    CC_SYNTHESIZE(vector<Option*>, m_Options, Options);
};

#endif
