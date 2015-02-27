//
//  GamePlayPointsManager.cpp
//  IkasGame
//
//  Created by Sergio Garcia on 16/2/15.
//
//

#include "GamePlayPointsManager.h"
#include "AppManager.h"

const int SuccessAnswerPoints = 100;

// Singleton
GamePlayPointsManager * GamePlayPointsManager::_instance = NULL;

GamePlayPointsManager* GamePlayPointsManager::getInstance()
{
    if(!_instance) _instance = new GamePlayPointsManager();
    return _instance;
}

GamePlayPointsManager::GamePlayPointsManager()
{
    this->loadSettings();
}

GamePlayPointsManager::~GamePlayPointsManager()
{
    
}

/**
 * Load ALL settings variables from UserDefault
 */
void GamePlayPointsManager::loadSettings()
{
    UserDefault *userDefault = UserDefault::getInstance();
    
    _currentCategory = userDefault->getIntegerForKey("currentCategory", -1);
    _currentDifficulty = static_cast<Difficulty>(userDefault->getIntegerForKey("currentDifficulty", static_cast<int>(Difficulty::EMPTY)));
    _currentPoints = userDefault->getIntegerForKey("currentPoints", 0);
}

/**
 * Save ALL gameplay settings
 */
void GamePlayPointsManager::saveSettings()
{
    UserDefault *userDefault = UserDefault::getInstance();
    userDefault->setIntegerForKey("currentCategory", _currentCategory);
    userDefault->setIntegerForKey("currentDifficulty", static_cast<int>(_currentDifficulty));
    userDefault->setIntegerForKey("currentPoints", _currentPoints);
    userDefault->flush();
    AppManager::getInstance()->updateScreenGameStats();
}

/**
 * Set current gameplay category
 */
void GamePlayPointsManager::setCurrentCategory(int category)
{
    _currentCategory = category;
    
    UserDefault *userDefault = UserDefault::getInstance();
    userDefault->setIntegerForKey("currentCategory", category);
    userDefault->flush();
    AppManager::getInstance()->updateScreenGameStats();
}

/**
 * Set current gameplay difficulty
 */
void GamePlayPointsManager::setCurrentDifficulty(Difficulty difficulty)
{
    _currentDifficulty = difficulty;
    
    UserDefault *userDefault = UserDefault::getInstance();
    userDefault->setIntegerForKey("currentDifficulty", static_cast<int>(difficulty));
    userDefault->flush();
    AppManager::getInstance()->updateScreenGameStats();
}

/**
 * Set current gameplay points
 */
void GamePlayPointsManager::setCurrentPoints(int points)
{
    _currentPoints = points;
    
    UserDefault *userDefault = UserDefault::getInstance();
    userDefault->setIntegerForKey("currentPoints", points);
    userDefault->flush();
    AppManager::getInstance()->updateScreenGameStats();
}

/**
 * Add success anwer points to current gameplay
 */
void GamePlayPointsManager::addSuccessPoints()
{
    float levelPoints = 0;
    switch (_currentDifficulty) {
            break;
        case Difficulty::EASY:
            levelPoints = SuccessAnswerPoints * 0.75f;
            break;
        case Difficulty::MEDIUM:
            levelPoints = SuccessAnswerPoints * 1.0f;
            break;
        case Difficulty::HARD:
            levelPoints = SuccessAnswerPoints * 1.25f;
            break;
        default:
            levelPoints = 0;
            break;
    }
    this->setCurrentPoints(_currentPoints + levelPoints);
}

/**
 * Reset current points
 */
void GamePlayPointsManager::resetCurrentPoints()
{
    this->setCurrentPoints(0);
}

/**
 * Reset ALL gameplay settings
 */
void GamePlayPointsManager::resetCurrentGamePlaySettings()
{
    _currentCategory = -1;
    _currentDifficulty = Difficulty::EMPTY;
    _currentPoints = 0;
    this->saveSettings();
}