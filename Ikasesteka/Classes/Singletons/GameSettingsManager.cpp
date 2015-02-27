//
//  GameSettingsManager.cpp
//  IkasGame
//
//  Created by Sergio Garcia on 30/01/15.
//
//

#include "GameSettingsManager.h"

// Singleton
GameSettingsManager * GameSettingsManager::_instance = NULL;

GameSettingsManager* GameSettingsManager::getInstance()
{
    if(!_instance) _instance = new GameSettingsManager();
    return _instance;
}

GameSettingsManager::GameSettingsManager()
{
    this->loadSettings();
}

GameSettingsManager::~GameSettingsManager()
{

}

/**
 * Load ALL settings variables from UserDefault
 */
void GameSettingsManager::loadSettings()
{
    UserDefault *userDefault = UserDefault::getInstance();
    
    // set device language
    if (userDefault->getIntegerForKey("currentLanguage", -1) == -1)
    {
        userDefault->setIntegerForKey("currentLanguage", static_cast<int>(Application::getInstance()->getCurrentLanguage()));
        userDefault->flush();
    }
    
    _currentLanguage = static_cast<CustomLanguage>(userDefault->getIntegerForKey("currentLanguage", 0));
    _firstLaunch = userDefault->getBoolForKey("firstLaunch", true);
    _dataAvalaible = userDefault->getBoolForKey("newDataAvalaible", false);
    _music = userDefault->getBoolForKey("music", true);
    _sfx = userDefault->getBoolForKey("sfx", true);
    _zipName = userDefault->getStringForKey("zipName", "");
    _zipUrl = userDefault->getStringForKey("zipUrl", "");
}

/**
 * Set Application language
 */
void GameSettingsManager::setLanguage(CustomLanguage language)
{
    _currentLanguage = language;

    UserDefault *userDefault = UserDefault::getInstance();
    userDefault->setIntegerForKey("currentLanguage", static_cast<int>(language));
    userDefault->flush();
}

void GameSettingsManager::setFirstLaunch(bool firstLaunch)
{
    _firstLaunch = firstLaunch;
    
    UserDefault *userDefault = UserDefault::getInstance();
    userDefault->setBoolForKey("firstLaunch", static_cast<bool>(firstLaunch));
    userDefault->flush();

}

void GameSettingsManager::setDataAvalaible(bool dataAvalaible)
{
    _dataAvalaible = dataAvalaible;
    
    UserDefault *userDefault = UserDefault::getInstance();
    userDefault->setBoolForKey("newDataAvalaible", static_cast<bool>(dataAvalaible));
    userDefault->flush();
}

/**
 * If background music is playing, stop it it. Else, play it
 */
void GameSettingsManager::switchMusic()
{
    _music = !_music;
    
    if (_music) {
        SoundManager::getInstance()->musicPlay("background");
    }
    else {
        SoundManager::getInstance()->musicStop();
    }
    
    UserDefault *userDefault = UserDefault::getInstance();
    userDefault->setBoolForKey("music", _music);
    userDefault->flush();
}

/**
 * If sound effects are enabled, disable them. Else, enable them
 */
void GameSettingsManager::switchSFX()
{
    _sfx = !_sfx;
    
    UserDefault *userDefault = UserDefault::getInstance();
    userDefault->setBoolForKey("sfx", _sfx);
    userDefault->flush();
}

void GameSettingsManager::setZipName(std::string zipName)
{
    _zipName = zipName;
    UserDefault *userDefault = UserDefault::getInstance();
    userDefault->setStringForKey("zipName", _zipName);
    userDefault->flush();
}

void GameSettingsManager::setZipUrl(std::string zipUrl)
{
    _zipUrl = zipUrl;
    UserDefault *userDefault = UserDefault::getInstance();
    userDefault->setStringForKey("zipUrl", _zipUrl);
    userDefault->flush();
}
