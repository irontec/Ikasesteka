//
//  AppleHelper.h
//  IkasGame
//
//  Created by Sergio Garcia on 24/2/15.
//
//

#ifndef __IkasGame__AppleHelper__
#define __IkasGame__AppleHelper__

#include "cocos2d.h"
#include <string>

using namespace cocos2d;

class AppleHelper
{
public:
    static void ignorePathFromiCloud(std::string path , bool isDir, bool ignore);
};

#endif /* defined(__IkasGame__AppleHelper__) */
