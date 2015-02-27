//
//  Pause.cpp
//  IkasGame
//
//  Created by Sergio Garcia on 11/2/15.
//
//

#include "Pause.h"
#include "../Singletons/GameSettingsManager.h"
#include "../Singletons/SceneManager.h"
#include "../Singletons/SoundManager.h"
#include "../Singletons/AppManager.h"
#include "../Helpers/LanguageManager.h"
#include "../Helpers/ScreenSizeManager.h"
#include "../Helpers/ImageManager.h"
#include "../CustomGUI/SpriteButton.h"

Scene* Pause::createScene()
{
    SceneManager::getInstance()->saveCurrentScene();
    
    auto *scene = Scene::create();
    auto *layer = Pause::create();
    layer->setTag(2339);
    
    scene->addChild(layer);
    
    return scene;
}

bool Pause::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Rect visibleRect = ScreenSizeManager::getVisibleRect();
    
    auto background = Sprite::create(ImageManager::getImage("background"), visibleRect);
    background->setPosition(ScreenSizeManager::getScreenPositionFromPercentage(50, 50));
    background->setAnchorPoint(Point::ANCHOR_MIDDLE);
    this->addChild(background);
    
    auto buttonResume = SpriteButton::create(ImageManager::getImage("play"), 1.2f, CC_CALLBACK_1(Pause::resumeGamePlay, this));
    buttonResume->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 positionButtonResume = ScreenSizeManager::getScreenPositionFromPercentage(50, 70);
    buttonResume->setPosition(positionButtonResume);
    this->addChild(buttonResume);
    
    auto labelResume = Label::createWithTTF(LanguageManager::getLocalizedText("Pause", "resume"), MainRegularFont, 130);
    labelResume->setAlignment(TextHAlignment::CENTER);
    labelResume->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    labelResume->setTextColor(IkasGrayDark);
    Vec2 positionLabelResume = buttonResume->getPosition();
    positionLabelResume.y -= buttonResume->getBoundingBox().size.height/2;
    positionLabelResume.y -= ScreenSizeManager::getHeightFromPercentage(10);
    labelResume->setPosition(positionLabelResume);
    this->addChild(labelResume);
    
    auto buttonSoundSettings = SpriteButton::create(ImageManager::getImage(GameSettingsManager::getInstance()->getIsSFXOn() ? SoundEnableImage : SoundDisableImage), 0.30f, CC_CALLBACK_1(Pause::switchSoundSettings, this));
    buttonSoundSettings->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 positionButtonSoundSettings = ScreenSizeManager::getScreenPositionFromPercentage(80, 15);
    buttonSoundSettings->setPosition(positionButtonSoundSettings);
    this->addChild(buttonSoundSettings);
    
    auto buttonHome = SpriteButton::create(ImageManager::getImage("home"), 0.30f, CC_CALLBACK_1(Pause::returnHome, this));
    buttonHome->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 positionButtonHome = ScreenSizeManager::getScreenPositionFromPercentage(22, 15);
    buttonHome->setPosition(positionButtonHome);
    this->addChild(buttonHome);
    
    return true;
}

void Pause::resumeGamePlay(Ref* sender)
{
    SoundManager::getInstance()->sfxPlay("button");
    SceneManager::getInstance()->loadSavedScene();
    AppManager::getInstance()->resumeGamePlay();
}

void Pause::switchSoundSettings(Ref* sender)
{
    SoundManager::getInstance()->sfxPlay("button");
    GameSettingsManager::getInstance()->switchSFX();
    GameSettingsManager::getInstance()->switchMusic();
    SpriteButton *item = static_cast<SpriteButton*>(sender);
    item->setTexture(ImageManager::getImage(GameSettingsManager::getInstance()->getIsSFXOn() ? SoundEnableImage : SoundDisableImage));
}

void Pause::returnHome(Ref* sender)
{
    SoundManager::getInstance()->sfxPlay("button");
    AppManager::getInstance()->setGamePlayDelegate(NULL);
    SceneManager::getInstance()->runSceneWithType(SceneType::MAIN);
    SceneManager::getInstance()->removeSavedScene();
}