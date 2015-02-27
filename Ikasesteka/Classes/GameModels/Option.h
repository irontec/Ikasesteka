//
//  Options.h
//  ikaszopa
//
//  Created by Axier Fernandez on 24/2/15.
//
//

#ifndef ikaszopa_Option_h
#define ikaszopa_Option_h

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class Option : public Object
{
public:
    
    Option(){};
    ~Option(){};
    
    CC_SYNTHESIZE(string, m_Name, Name);
    CC_SYNTHESIZE(string, m_FileName, FileName);
};

#endif
