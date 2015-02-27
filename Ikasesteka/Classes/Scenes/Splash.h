//
//  Splash.h
//  IkasGame
//
//  Created by Sergio Garcia on 29/1/15.
//
//

#ifndef __IkasCocosGame__Splash__
#define __IkasCocosGame__Splash__

#include "cocos2d.h"

using namespace cocos2d;

class Splash : public Layer
{
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(Splash);
    
private:
    void launchMainScene();
};
#endif /* defined(__IkasCocosGame__Splash__) */
