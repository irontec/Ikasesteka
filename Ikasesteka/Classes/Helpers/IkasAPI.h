//
//  IkasAPI.h
//  IkasGame
//
//  Created by Sergio Garcia on 23/2/15.
//
//

#ifndef __IkasAPI__
#define __IkasAPI__

#include "../Constants/Constants.h"

#include "cocos2d.h"
using namespace cocos2d;

#include "network/HttpClient.h"
using namespace cocos2d::network;

class IkasAPI : public Ref
{
public:
    virtual bool init();
    CREATE_FUNC(IkasAPI);
    
    void checkForLatestZipData(const IkasResultHandler& callback, const IkasHandler& errorCallback);
    void downloadLatestZip(const IkasHandler& successCallback, const IkasHandler& errorCallback);
protected:
    IkasResultHandler _resultCallback;
    IkasHandler _successCallback, _errorCallback;
private:
    void checkForLatestZipDataCallback(HttpClient* client , HttpResponse* response);
    void downloadLatestZipCallback(HttpClient* client , HttpResponse* response);
};

#endif /* defined(__IkasGame__IkasAPI__) */
