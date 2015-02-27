//
//  SoundManager.cpp
//  IkasGame
//
//  Created by Mikel Eizagirre on 2014-01-09.
//
//

#include "SoundManager.h"
#include "GameSettingsManager.h"

SoundManager * SoundManager::_instance = NULL;

static std::string audioExtension = ".wav";

SoundManager* SoundManager::getInstance()
{
    if(!_instance) _instance = new SoundManager();
    return _instance;
}

SoundManager::SoundManager():
_backgroundMusicId(-1)
{

}

SoundManager::~SoundManager()
{

}

void SoundManager::pauseAll()
{
    AudioEngine::pauseAll();
}

void SoundManager::resumeAll()
{
    AudioEngine::resumeAll();
}

void SoundManager::musicPlay(std::string file, bool loop)
{
    if (!GameSettingsManager::getInstance()->getIsMusicOn()) {
        return;
    }
    std::string path;
    path = "audio/" + file + audioExtension;
    if (_backgroundMusicId > -1) {
        this->musicStop();
    }
    _backgroundMusicId = AudioEngine::play2d(path, loop);
}

void SoundManager::musicStop()
{
    AudioEngine::stop(_backgroundMusicId);
    _backgroundMusicId = -1;
}

void SoundManager::musicPause()
{
    AudioEngine::pause(_backgroundMusicId);
}

void SoundManager::sfxPlay(std::string file)
{
    if (!GameSettingsManager::getInstance()->getIsSFXOn()) {
        return;
    }
    std::string path;
    path = "audio/" + file + audioExtension;
    AudioEngine::play2d(path);
}

void SoundManager::successPlay()
{
    if (!GameSettingsManager::getInstance()->getIsSFXOn()) {
        return;
    }
    std::string path;
    path = "audio/success" + audioExtension;
    AudioEngine::play2d(path);
}

void SoundManager::failurePlay()
{
    if (!GameSettingsManager::getInstance()->getIsSFXOn()) {
        return;
    }
    std::string path;
    path = "audio/failure" + audioExtension;
    AudioEngine::play2d(path);
}