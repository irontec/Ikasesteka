//
//  SceneManager.h
//  IkasGame
//
//  Created by Sergio Garcia on 30/01/15.
//
//

#ifndef __IkasCocosGame__SceneManager__
#define __IkasCocosGame__SceneManager__

#include "cocos2d.h"
#include "../Constants/Constants.h"

class SceneManager
{
public:
    static SceneManager* getInstance();
    ~SceneManager();
    void runSceneWithType(const SceneType sceneType);
    void returnToLastScene();
    
    void saveCurrentScene();
    void loadSavedScene();
    void removeSavedScene();
private:
    void runScene(Scene* scene, SceneType sceneType);
    
    Scene *_savedScene;
    SceneType _savedSceneType;
    
    SceneType _sceneTypeToReturn;
    SceneType _currentSceneType;
    static SceneManager * _instance;
    SceneManager();
};
#endif /* defined(__IkasCocosGame__SceneManager__) */
