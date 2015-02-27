//
//  SceneManager.cpp
//  IkasGame
//
//  Created by Sergio Garcia on 30/01/15.
//
//

#include "SceneManager.h"
#include "AppManager.h"
#include "../Scenes/Splash.h"
#include "../Scenes/Main.h"
#include "../Scenes/Categories.h"
#include "../Scenes/Level.h"
#include "../Scenes/GamePlay.h"
#include "../Scenes/Pause.h"
#include "../Scenes/Win.h"
#include "../Scenes/Lose.h"

using namespace cocos2d;

// Singleton
SceneManager * SceneManager::_instance = NULL;

/**
 * Give me a pointer to Singleton!
 */
SceneManager* SceneManager::getInstance()
{
    if(!_instance) _instance = new SceneManager();
    return _instance;
}

SceneManager::SceneManager():
_sceneTypeToReturn(SceneType::MAIN),
_currentSceneType(SceneType::MAIN)
{
    
}

SceneManager::~SceneManager()
{
    
}

void SceneManager::runSceneWithType(const SceneType sceneType)
{
    Scene *sceneToRun = nullptr;
    switch (sceneType) {
        case SceneType::SPLASH:
            sceneToRun = Splash::createScene();
            break;
        case SceneType::MAIN:
            sceneToRun = Main::createScene();
            break;
        case SceneType::CATEGORIES:
            sceneToRun = Categories::createScene();
            break;
        case SceneType::LEVEL:
            sceneToRun = Level::createScene();
            break;
        case SceneType::GAMEPLAY:
            sceneToRun = GamePlay::createScene();
            break;
        case SceneType::PAUSE:
            sceneToRun = Pause::createScene();
            break;
        case SceneType::WIN:
            sceneToRun = Win::createScene();
            break;
        case SceneType::LOSE:
            sceneToRun = Lose::createScene();
            break;
        default:
            log("WARNING! Default value when trying to run scene with id %d", static_cast<int>(sceneType));
            return;
            break;
    }
    
    this->runScene(sceneToRun, sceneType);
}

void SceneManager::runScene(Scene* sceneToRun, SceneType sceneType)
{
    SceneType oldScene = _currentSceneType;
    _currentSceneType = sceneType;
    
    sceneToRun->setTag(static_cast<int>(sceneType));
    
    if (sceneToRun == nullptr) {
        _currentSceneType = oldScene;
        return;
    }
    
    _sceneTypeToReturn = oldScene;
    
    if (Director::getInstance()->getRunningScene() == nullptr) {
        Director::getInstance()->runWithScene(sceneToRun);
    }
    else {
        Director::getInstance()->replaceScene(sceneToRun);
    }
}

void SceneManager::returnToLastScene()
{
    this->runSceneWithType(_sceneTypeToReturn);
}

void SceneManager::saveCurrentScene()
{
    _savedScene = Director::getInstance()->getRunningScene();
    CC_SAFE_RETAIN(_savedScene);
    _savedSceneType = _currentSceneType;
}

void SceneManager::loadSavedScene()
{
    CC_ASSERT(_savedScene != nullptr);
    this->runScene(_savedScene, _savedSceneType);
    this->removeSavedScene();
}

void SceneManager::removeSavedScene()
{
    CC_SAFE_RELEASE(_savedScene);
}

