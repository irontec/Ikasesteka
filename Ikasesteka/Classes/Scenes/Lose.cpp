//
//  Lose.cpp
//  IkasGame
//
//  Created by Sergio Garcia on 11/2/15.
//
//

#include "Lose.h"
#include "../Singletons/GameSettingsManager.h"
#include "../Singletons/GamePlayPointsManager.h"
#include "../Singletons/SceneManager.h"
#include "../Singletons/SoundManager.h"
#include "../Singletons/AppManager.h"
#include "../Helpers/LanguageManager.h"
#include "../Helpers/ScreenSizeManager.h"
#include "../Helpers/ImageManager.h"
#include "../CustomGUI/SpriteButton.h"

Scene* Lose::createScene()
{
    SceneManager::getInstance()->saveCurrentScene();
    
    auto *scene = Scene::create();
    auto *layer = Lose::create();
    layer->setTag(2339);
    
    scene->addChild(layer);
    
    return scene;
}

bool Lose::init()
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
    
    auto buttonNextGamePlay = SpriteButton::create(ImageManager::getImage("restart"), 1.0f, CC_CALLBACK_1(Lose::resetGame, this));
    buttonNextGamePlay->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 positionButtonNextGamePlay = ScreenSizeManager::getScreenPositionFromPercentage(50, 50);
    buttonNextGamePlay->setPosition(positionButtonNextGamePlay);
    this->addChild(buttonNextGamePlay);
    
    auto labelResume = Label::createWithTTF(LanguageManager::getLocalizedText("Lose", "reset"), MainRegularFont, 70);
    labelResume->setAlignment(TextHAlignment::CENTER);
    labelResume->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    labelResume->setTextColor(IkasGrayDark);
    Vec2 positionLabelResume = buttonNextGamePlay->getPosition();
    positionLabelResume.y -= buttonNextGamePlay->getBoundingBox().size.height / 2;
    positionLabelResume.y -= ScreenSizeManager::getHeightFromPercentage(1);
    labelResume->setPosition(positionLabelResume);
    this->addChild(labelResume);
    
    std::ostringstream totalPoints;
    totalPoints << GamePlayPointsManager::getInstance()->getCurrentPoints() << " " << LanguageManager::getLocalizedText("Lose", "points-value");

    auto labelPointsValue = Label::createWithTTF(totalPoints.str(), MainRegularFont, 75);
    labelPointsValue->setAlignment(TextHAlignment::CENTER);
    labelPointsValue->setAnchorPoint(Point::ANCHOR_MIDDLE);
    labelPointsValue->setTextColor(IkasGrayDark);
    Vec2 positionLabelPointsValue = buttonNextGamePlay->getPosition();
    positionLabelPointsValue.y += buttonNextGamePlay->getBoundingBox().size.height / 2;
    positionLabelPointsValue.y += labelPointsValue->getBoundingBox().size.height / 2;
    positionLabelPointsValue.y += ScreenSizeManager::getHeightFromPercentage(1);
    labelPointsValue->setPosition(positionLabelPointsValue);
    this->addChild(labelPointsValue);
    
    auto labelPointsTitle = Label::createWithTTF(LanguageManager::getLocalizedText("Lose", "points-title"), MainRegularFont, 75);
    labelPointsTitle->setAlignment(TextHAlignment::CENTER);
    labelPointsTitle->setAnchorPoint(Point::ANCHOR_MIDDLE);
    labelPointsTitle->setTextColor(IkasGrayDark);
    Vec2 positionLabelPointsTitle = labelPointsValue->getPosition();
    positionLabelPointsTitle.y += labelPointsValue->getBoundingBox().size.height / 2;
    positionLabelPointsTitle.y += labelPointsTitle->getBoundingBox().size.height / 2;
    positionLabelPointsTitle.y += ScreenSizeManager::getHeightFromPercentage(1);
    labelPointsTitle->setPosition(positionLabelPointsTitle);
    this->addChild(labelPointsTitle);

    auto labelTitle = Label::createWithTTF(LanguageManager::getLocalizedText("Lose", "title"), MainRegularFont, 90);
    labelTitle->setAlignment(TextHAlignment::CENTER);
    labelTitle->setAnchorPoint(Point::ANCHOR_MIDDLE);
    labelTitle->setTextColor(IkasPink);
    Vec2 positionLabelTitle = labelPointsTitle->getPosition();
    positionLabelTitle.y += labelPointsTitle->getBoundingBox().size.height / 2;
    positionLabelTitle.y += labelTitle->getBoundingBox().size.height / 2;
    positionLabelTitle.y += ScreenSizeManager::getHeightFromPercentage(1);
    labelTitle->setPosition(positionLabelTitle);
    this->addChild(labelTitle);
    
    auto buttonSoundSettings = SpriteButton::create(ImageManager::getImage(GameSettingsManager::getInstance()->getIsSFXOn() ? SoundEnableImage : SoundDisableImage), 0.30f, CC_CALLBACK_1(Lose::switchSoundSettings, this));
    buttonSoundSettings->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 positionButtonSoundSettings = ScreenSizeManager::getScreenPositionFromPercentage(80, 15);
    buttonSoundSettings->setPosition(positionButtonSoundSettings);
    this->addChild(buttonSoundSettings);
    
    auto buttonHome = SpriteButton::create(ImageManager::getImage("home"), 0.30f, CC_CALLBACK_1(Lose::returnHome, this));
    buttonHome->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 positionButtonHome = ScreenSizeManager::getScreenPositionFromPercentage(22, 15);
    buttonHome->setPosition(positionButtonHome);
    this->addChild(buttonHome);
    
    return true;
}

void Lose::resetGame(Ref* sender)
{
    SoundManager::getInstance()->sfxPlay("button");
    GamePlayPointsManager::getInstance()->resetCurrentPoints();
    SceneManager::getInstance()->loadSavedScene();
    AppManager::getInstance()->restartGame();
}

void Lose::switchSoundSettings(Ref* sender)
{
    SoundManager::getInstance()->sfxPlay("button");
    GameSettingsManager::getInstance()->switchSFX();
    GameSettingsManager::getInstance()->switchMusic();
    SpriteButton *item = static_cast<SpriteButton*>(sender);
    item->setTexture(ImageManager::getImage(GameSettingsManager::getInstance()->getIsSFXOn() ? SoundEnableImage : SoundDisableImage));
}

void Lose::returnHome(Ref* sender)
{
    SoundManager::getInstance()->sfxPlay("button");
    AppManager::getInstance()->setGamePlayDelegate(NULL);
    SceneManager::getInstance()->runSceneWithType(SceneType::MAIN);
    SceneManager::getInstance()->removeSavedScene();
}
