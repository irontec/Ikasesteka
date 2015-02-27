//
//  Level.h
//  IkasGame
//
//  Created by Sergio Garcia on 2/2/15.
//
//

#ifndef __IkasCocosGame__Level__
#define __IkasCocosGame__Level__

#include "cocos2d.h"
using namespace cocos2d;

#include "../CustomGUI/SpriteButton.h"

class Level : public Layer
{
    Layer *buttonsLayer;
    
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(Level);
    
protected:
    void switchSoundSettings(Ref* sender);
    void changeScene(Ref* sender);
    void openInfo(Ref* sender);
    void selectLevel(Ref* sender);
};
#endif /* defined(__IkasCocosGame__Level__) */
