//
//  ScreenHelper.h
//  Ikasesteka
//
//  Created by Sergio Garcia on 26/11/14.
//
//

#ifndef __Ikasesteka__ScreenHelper__
#define __Ikasesteka__ScreenHelper__

#include "cocos2d.h"

using namespace cocos2d;

class ScreenSizeManager
{
private:
    static void lazyInit();
    static Rect visibleScreen;
public:
    static Rect getVisibleRect();
    
    static Vec2 getScreenPositionFromPercentage(int percentageX, int percentageY);
    
    static float getWidthFromPercentage(int widthPercentage);
    static float getHeightFromPercentage(int heightPercentage);
};
#endif /* defined(__Ikasesteka__ScreenHelper__) */
