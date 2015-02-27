//
//  GamePlayPointsManager.h
//  IkasGame
//
//  Created by Sergio Garcia on 16/2/15.
//
//

#ifndef __IkasGame__GamePlayPointsManager__
#define __IkasGame__GamePlayPointsManager__

#include "cocos2d.h"
#include "../Constants/Constants.h"

using namespace cocos2d;

class GamePlayPointsManager
{
public:
    static GamePlayPointsManager* getInstance();
    ~GamePlayPointsManager();
    void loadSettings();
    void saveSettings();
    
    void setCurrentCategory(int category);
    void setCurrentDifficulty(Difficulty difficulty);
    
    void addSuccessPoints();
    void resetCurrentPoints();
    void resetCurrentGamePlaySettings();
    
    CC_SYNTHESIZE_READONLY(int, _currentCategory, CurrentCategory);
    CC_SYNTHESIZE_READONLY(Difficulty, _currentDifficulty, CurrentDifficulty);
    CC_SYNTHESIZE_READONLY(int, _currentPoints, CurrentPoints);
protected:
    GamePlayPointsManager();
    static GamePlayPointsManager * _instance;
    void setCurrentPoints(int points);
};
#endif /* defined(__IkasGame__GamePlayPointsManager__) */
