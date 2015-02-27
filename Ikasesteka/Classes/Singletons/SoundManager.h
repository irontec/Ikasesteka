//
//  SoundManager.h
//  IkasGame
//
//  Created by Mikel Eizagirre on 2014-01-09.
//
//

#ifndef __IkasGame__SoundManager__
#define __IkasGame__SoundManager__

#include "cocos2d.h"
#include "audio/include/AudioEngine.h"

using namespace cocos2d;
using namespace cocos2d::experimental;

class SoundManager
{
public:
    void pauseAll();
    void resumeAll();
    
    void musicPlay(std::string file, bool loop = true);
    void musicStop();
    void musicPause();
    
    void sfxPlay(std::string file);
    void successPlay();
    void failurePlay();;
    static SoundManager* getInstance();
    ~SoundManager();
    
protected:
    SoundManager();
    static SoundManager * _instance;
    
    int _backgroundMusicId;
public:
    
};
#endif /* defined(__IkasGame__SoundManager__) */
