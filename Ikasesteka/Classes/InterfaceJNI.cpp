#include "InterfaceJNI.h"
#include "platform/android/jni/JniHelper.h"

using namespace cocos2d;

void InterfaceJNI::sendMail(const char *to, const char *subject, const char *message)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxHelper", "sendEMail", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring jto = t.env->NewStringUTF(to);
        jstring jsubject = t.env->NewStringUTF(subject);
        jstring jmessage = t.env->NewStringUTF(message);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jto, jsubject, jmessage);
        t.env->DeleteLocalRef(t.classID);
    }
}

void InterfaceJNI::openWeb(const char *direction)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxHelper", "openWeb", "(Ljava/lang/String;)V")) {
    	jstring StringArg1 = t.env->NewStringUTF(direction);
        t.env->CallStaticVoidMethod(t.classID, t.methodID,StringArg1);
        t.env->DeleteLocalRef(t.classID);
    }
}

void InterfaceJNI::openMarketApp(const char *idAndroid)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxHelper", "openMarketApp", "(Ljava/lang/String;)V")) {
        jstring StringArg1 = t.env->NewStringUTF(idAndroid);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, StringArg1);
        t.env->DeleteLocalRef(t.classID);
    }
}

void InterfaceJNI::openMarketApps(const char *idAndroid)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxHelper", "openMarketApps", "(Ljava/lang/String;)V")) {
        jstring StringArg1 = t.env->NewStringUTF(idAndroid);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, StringArg1);
        t.env->DeleteLocalRef(t.classID);
    }
}

void InterfaceJNI::openTwitterProfile(const char *username)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxHelper", "openTwitterUser", "(Ljava/lang/String;)V")) {
        jstring StringArg1 = t.env->NewStringUTF(username);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, StringArg1);
        t.env->DeleteLocalRef(t.classID);
    }
}

void InterfaceJNI::sendTweet(const char *message)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxHelper", "sendTweet", "(Ljava/lang/String;)V")) {
    	jstring jmessage = t.env->NewStringUTF(message);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jmessage);
        t.env->DeleteLocalRef(t.classID);
    }
}
