//
//  Win.cpp
//  IkasGame
//
//  Created by Sergio Garcia on 11/2/15.
//
//

#include "Win.h"
#include "../Singletons/GameSettingsManager.h"
#include "../Singletons/SceneManager.h"
#include "../Singletons/SoundManager.h"
#include "../Singletons/AppManager.h"
#include "../Helpers/LanguageManager.h"
#include "../Helpers/ScreenSizeManager.h"
#include "../Helpers/ImageManager.h"
#include "../CustomGUI/SpriteButton.h"


Scene* Win::createScene()
{
    SceneManager::getInstance()->saveCurrentScene();
    
    auto *scene = Scene::create();
    auto *layer = Win::create();
    layer->setTag(2339);
    
    scene->addChild(layer);
    
    return scene;
}

bool Win::init()
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
    
    auto buttonNextGamePlay = SpriteButton::create(ImageManager::getImage("play"), 1.0f, CC_CALLBACK_1(Win::loadNextGamePlay, this));
    buttonNextGamePlay->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 positionButtonNextGamePlay = ScreenSizeManager::getScreenPositionFromPercentage(50, 50);
    buttonNextGamePlay->setPosition(positionButtonNextGamePlay);
    this->addChild(buttonNextGamePlay);
    
    auto winTitle = Sprite::create(ImageManager::getImage("win-title"));
    winTitle->setScale(0.75f);
    Vec2 positionWinTitle = buttonNextGamePlay->getPosition();
    positionWinTitle.y += buttonNextGamePlay->getBoundingBox().size.height / 2;
    positionWinTitle.y += ScreenSizeManager::getHeightFromPercentage(2);
    winTitle->setPosition(positionWinTitle);
    winTitle->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    this->addChild(winTitle);
    
    auto labelResume = Label::createWithTTF(LanguageManager::getLocalizedText("Win", "resume"), MainRegularFont, 70);
    labelResume->setAlignment(TextHAlignment::CENTER);
    labelResume->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    labelResume->setTextColor(IkasGrayDark);
    Vec2 positionLabelResume = buttonNextGamePlay->getPosition();
    positionLabelResume.y -= buttonNextGamePlay->getBoundingBox().size.height / 2;
    positionLabelResume.y -= ScreenSizeManager::getHeightFromPercentage(1);
    labelResume->setPosition(positionLabelResume);
    this->addChild(labelResume);
    
    auto buttonSoundSettings = SpriteButton::create(ImageManager::getImage(GameSettingsManager::getInstance()->getIsSFXOn() ? SoundEnableImage : SoundDisableImage), 0.30f, CC_CALLBACK_1(Win::switchSoundSettings, this));
    buttonSoundSettings->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 positionButtonSoundSettings = ScreenSizeManager::getScreenPositionFromPercentage(80, 15);
    buttonSoundSettings->setPosition(positionButtonSoundSettings);
    this->addChild(buttonSoundSettings);
    
    auto buttonHome = SpriteButton::create(ImageManager::getImage("home"), 0.30f, CC_CALLBACK_1(Win::returnHome, this));
    buttonHome->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 positionButtonHome = ScreenSizeManager::getScreenPositionFromPercentage(22, 15);
    buttonHome->setPosition(positionButtonHome);
    this->addChild(buttonHome);
    
    return true;
}

void Win::loadNextGamePlay(Ref* sender)
{
    SoundManager::getInstance()->sfxPlay("button");
    SceneManager::getInstance()->loadSavedScene();
    AppManager::getInstance()->loadNextGamePlay();
}

void Win::switchSoundSettings(Ref* sender)
{
    SoundManager::getInstance()->sfxPlay("button");
    GameSettingsManager::getInstance()->switchSFX();
    GameSettingsManager::getInstance()->switchMusic();
    SpriteButton *item = static_cast<SpriteButton*>(sender);
    item->setTexture(ImageManager::getImage(GameSettingsManager::getInstance()->getIsSFXOn() ? SoundEnableImage : SoundDisableImage));
}

void Win::returnHome(Ref* sender)
{
    SoundManager::getInstance()->sfxPlay("button");
    AppManager::getInstance()->setGamePlayDelegate(NULL);
    SceneManager::getInstance()->runSceneWithType(SceneType::MAIN);
    SceneManager::getInstance()->removeSavedScene();
}