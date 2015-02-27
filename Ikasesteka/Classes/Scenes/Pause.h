//
//  Pause.h
//  IkasGame
//
//  Created by Sergio Garcia on 11/2/15.
//
//

#ifndef __IkasGame__Pause__
#define __IkasGame__Pause__

#include "../Constants/Constants.h"

#include "cocos2d.h"
using namespace cocos2d;

class Pause : public Layer
{
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(Pause);
    
protected:
    void resumeGamePlay(Ref* sender);
    void switchSoundSettings(Ref* sender);
    void returnHome(Ref* sender);
};
#endif /* defined(__IkasGame__Pause__) */
