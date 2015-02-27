#ifndef __INTERFACE_JNI_H__
#define __INTERFACE_JNI_H__

#include "cocos2d.h"
#include <jni.h>
#include <android/log.h>

class InterfaceJNI
{
public:
	//////////////////
	// C++ to Java
	//////////////////
    // Email
    static void sendMail(const char *to, const char *subject, const char *message);
    // Web
    static void openWeb(const char* direction);
    // Market
    static void openMarketApp(const char* idAndroid);
    static void openMarketApps(const char* idAndroid);
    // Twitter
    static void openTwitterProfile(const char* username);
    static void sendTweet(const char *message);
protected:
};

#endif // __INTERFACE_JNI_H__
