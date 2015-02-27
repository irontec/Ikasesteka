//
//  Win.h
//  IkasGame
//
//  Created by Sergio Garcia on 11/2/15.
//
//

#ifndef __IkasGame__Win__
#define __IkasGame__Win__

#include "../Constants/Constants.h"

#include "cocos2d.h"
using namespace cocos2d;

class Win : public Layer
{
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(Win);
    
protected:
    void loadNextGamePlay(Ref* sender);
    void switchSoundSettings(Ref* sender);
    void returnHome(Ref* sender);
};
#endif /* defined(__IkasGame__Win__) */
