//
//  AppManager.h
//  IkasGame
//
//  Created by Mikel Eizagirre on 2014-12-24.
//
//

#ifndef __IkasCocosGame__AppManager__
#define __IkasCocosGame__AppManager__

#include "cocos2d.h"
#include "../Constants/Constants.h"
#include "../Constants/CommonProtocols.h"

using namespace cocos2d;

class AppManager
{
public:
    static AppManager* getInstance();
    ~AppManager();
    
    void loadNextGamePlay() { if(_delegate) _delegate->loadNextGamePlay();};
    void resumeGamePlay() { if(_delegate) _delegate->resumeGamePlay();};
    void restartGame() { if(_delegate) _delegate->restartGame();};
    void updateScreenGameStats() { if(_delegate) _delegate->updateScreenGameStats();};
    
    void setGamePlayDelegate(GamePlayDelegate *delegate) { _delegate = delegate;};
    void exitToMain();
protected:
    AppManager();
    static AppManager *_instance;
    GamePlayDelegate *_delegate;
};
#endif /* defined(__IkasCocosGame__AppManager__) */
