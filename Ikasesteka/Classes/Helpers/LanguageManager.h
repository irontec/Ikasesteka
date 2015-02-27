//
//  LanguageManager.h
//  IkasGame
//
//  Edited by Sergio Garcia on 30/01/15.
//
//

#ifndef __IkasCocosGame__LanguageManager__
#define __IkasCocosGame__LanguageManager__

#include <string>

class LanguageManager
{
public:
    static std::string getLocalizedText(const char *miniDic, const char *key);
    static std::string getCurrentLanguageName();
};
#endif /* defined(__IkasCocosGame__LanguageManager__) */
