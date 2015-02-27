//
//  Main.h
//  IkasGame
//
//  Created by Sergio Garcia on 30/01/15.
//
//

#ifndef __IkasCocosGame__Main__
#define __IkasCocosGame__Main__

#include "cocos2d.h"
#include "../Constants/Constants.h"
#include "../Helpers/IkasAPI.h"

using namespace cocos2d;

class Main : public Layer
{
    Layer *playLayer, *loadingLayer;
public:
    virtual bool init();
    ~Main();
    static Scene* createScene();
    CREATE_FUNC(Main);
    void forceFirstData(Ref* sender, bool result);
    void forceFirstDataErrorCallback(Ref* sender);
    void successDataDownloaded(Ref* sender);
    void errorDataDownloaded(Ref* sender);
protected:
    void switchSoundSettings(Ref* sender);
    void changeScene(Ref* sender);
    void openInfo(Ref* sender);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
private:
    void showLoading(bool show);
    IkasAPI *_api;
    void checkNewData();
    
    void downloadLatestData(const IkasHandler& successCallback, const IkasHandler& errorCallback);
};
#endif /* defined(__IkasCocosGame__Main__) */
