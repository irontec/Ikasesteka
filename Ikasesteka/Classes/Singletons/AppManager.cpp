//
//  AppManager.cpp
//  IkasGame
//
//  Created by Mikel Eizagirre on 2014-12-24.
//
//

#include "AppManager.h"
#include "SceneManager.h"

// Singleton
AppManager * AppManager::_instance = NULL;

AppManager* AppManager::getInstance()
{
    if(!_instance) _instance = new AppManager();
    return _instance;
}

AppManager::AppManager()
{
    _delegate = NULL;
}

AppManager::~AppManager()
{
    
}

void AppManager::exitToMain()
{
    SceneManager::getInstance()->runSceneWithType(SceneType::MAIN);
}
