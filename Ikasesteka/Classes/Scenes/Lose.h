//
//  Lose.h
//  IkasGame
//
//  Created by Sergio Garcia on 11/2/15.
//
//

#ifndef __IkasGame__Lose__
#define __IkasGame__Lose__

#include "../Constants/Constants.h"

#include "cocos2d.h"
using namespace cocos2d;

class Lose : public Layer
{
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(Lose);
    
protected:
    void resetGame(Ref* sender);
    void switchSoundSettings(Ref* sender);
    void returnHome(Ref* sender);
};
#endif /* defined(__IkasGame__Lose__) */
