//
//  CommonProtocols.h
//  IkasGame
//
//  Created by Mikel Eizagirre on 2014-12-24.
//
//

#ifndef __IkasCocosGame__CommonProtocols
#define __IkasCocosGame__CommonProtocols

class GameHUDDelegate
{
public:
    virtual void showMenu() = 0;
    virtual void hideMenu() = 0;
};

class GamePlayDelegate
{
public:
    virtual void loadNextGamePlay() = 0;
    virtual void resumeGamePlay() = 0;
    virtual void restartGame() = 0;
    virtual void updateScreenGameStats() = 0;
};

#endif
