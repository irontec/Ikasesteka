//
//  Splash.cpp
//  IkasGame
//
//  Created by Sergio Garcia on 29/1/15.
//
//

#include "Splash.h"
#include "../Singletons/SceneManager.h"
#include "../Helpers/ImageManager.h"
#include "../Helpers/ScreenSizeManager.h"
#include "../Constants/Constants.h"

const Value SplashTime = Value(1.5);//In seconds

Scene* Splash::createScene()
{
    auto *scene = Scene::create();
    
    auto *layer = Splash::create();
    layer->setTag(2334);
    
    scene->addChild(layer);
    
    return scene;
}

bool Splash::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Rect visibleRect = ScreenSizeManager::getVisibleRect();
    
    auto background = Sprite::create(ImageManager::getImage("splash"), visibleRect);
    background->setPosition(ScreenSizeManager::getScreenPositionFromPercentage(50, 50));
    background->setAnchorPoint(Point::ANCHOR_MIDDLE);
    this->addChild(background);
    
    DelayTime *delayAction = DelayTime::create(SplashTime.asFloat());
    CallFunc *mySelector = CallFunc::create(CC_CALLBACK_0(Splash::launchMainScene, this));
    this->runAction(Sequence::create(delayAction, mySelector, nullptr));
    
    return true;
}

void Splash::launchMainScene()
{
    SceneManager::getInstance()->runSceneWithType(SceneType::MAIN);
}