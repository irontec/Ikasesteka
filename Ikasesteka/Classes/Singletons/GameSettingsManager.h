//
//  GameSettingsManager.h
//  IkasGame
//
//  Created by Sergio Garcia on 30/01/15.
//
//

#ifndef __IkasCocosGame__GameSettingsManager__
#define __IkasCocosGame__GameSettingsManager__

#include "cocos2d.h"
#include "SoundManager.h"
#include "../Constants/Constants.h"

using namespace cocos2d;

class GameSettingsManager
{
public:
    static GameSettingsManager* getInstance();
    ~GameSettingsManager();
    
    void loadSettings();
    void setLanguage(CustomLanguage language);
    void setFirstLaunch(bool firstLaunch);
    void setDataAvalaible(bool dataAvalaible);
    
    void switchMusic();
    void switchSFX();
    
    void setZipName(std::string zipName);
    void setZipUrl(std::string zipUrl);
    
    CC_SYNTHESIZE_READONLY(CustomLanguage, _currentLanguage, CurrentLanguage);
    CC_SYNTHESIZE_READONLY(bool, _firstLaunch, IsFirstLaunch);
    CC_SYNTHESIZE_READONLY(bool, _dataAvalaible, IsNewDataAvalaible);
    CC_SYNTHESIZE_READONLY(bool, _music, IsMusicOn);
    CC_SYNTHESIZE_READONLY(bool, _sfx, IsSFXOn);
    
    CC_SYNTHESIZE_READONLY(std::string, _zipName, ZipName);
    CC_SYNTHESIZE_READONLY(std::string, _zipUrl, ZipUrl);
protected:
    GameSettingsManager();
    static GameSettingsManager * _instance;
};
#endif /* defined(__IkasCocosGame__GameSettingsManager__) */
