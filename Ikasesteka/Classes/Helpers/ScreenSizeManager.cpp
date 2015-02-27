//
//  ScreenHelper.cpp
//  Ikasesteka
//
//  Created by Sergio Garcia on 26/11/14.
//
//

#include "ScreenSizeManager.h"

Rect ScreenSizeManager::visibleScreen;

void ScreenSizeManager::lazyInit()
{
    if (visibleScreen.size.width == 0.0f && visibleScreen.size.height == 0.0f)
    {
        visibleScreen.size = Director::getInstance()->getVisibleSize();
        visibleScreen.origin = Director::getInstance()->getVisibleOrigin();
    }
}

Rect ScreenSizeManager::getVisibleRect()
{
    lazyInit();
    return Rect(visibleScreen.origin.x, visibleScreen.origin.y, visibleScreen.size.width, visibleScreen.size.height);
}

Vec2 ScreenSizeManager::getScreenPositionFromPercentage(int percentageX, int percentageY)
{
    lazyInit();
    float realX = visibleScreen.origin.x + (percentageX * visibleScreen.size.width / 100);
    float realY = visibleScreen.origin.y + (percentageY * visibleScreen.size.height / 100);
    return Vec2(realX, realY);
}

float ScreenSizeManager::getWidthFromPercentage(int widthPercentage)
{
    lazyInit();
    return widthPercentage * visibleScreen.size.width / 100;
}

float ScreenSizeManager::getHeightFromPercentage(int heightPercentage)
{
    lazyInit();
    return heightPercentage * visibleScreen.size.height / 100;
}



