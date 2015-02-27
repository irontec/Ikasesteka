//
//  LanguageManager.cpp
//  IkasGame
//
//  Edited by Sergio Garcia on 30/01/15.
//
//

#include "LanguageManager.h"
#include "../Singletons/GameSettingsManager.h"

std::string LanguageManager::getLocalizedText(const char *miniDic, const char *key)
{
    const char *dictionary;
    
    switch (GameSettingsManager::getInstance()->getCurrentLanguage())
    {
        case CustomLanguage::SPANISH:
            dictionary = "languages/languages_Spanish.plist";
            break;
        default:
            dictionary = "languages/languages_Euskara.plist";
            break;
    }
    
    // Create Path and temp Dictionary
    std::string plistPath = FileUtils::getInstance()->fullPathForFilename(dictionary);
    auto languageDictionary = FileUtils::getInstance()->getValueMapFromFile(plistPath);
    
	// Check if exist Dictionary in path
	if (languageDictionary.empty())
	{
		return "";
	}
    
	// Check if exist Dictionary
    auto miniDictionary = languageDictionary.at(miniDic).asValueMap();

	if (miniDictionary.empty())
	{
		return "";
	}
    
	return miniDictionary.at(key).asString();
}

std::string LanguageManager::getCurrentLanguageName()
{
    std::string toReturn;
    switch (GameSettingsManager::getInstance()->getCurrentLanguage())
    {
        case CustomLanguage::SPANISH:
            toReturn = "Español";
            break;
        default:
            toReturn = "Euskara";
            break;
    }
    return toReturn;
}
