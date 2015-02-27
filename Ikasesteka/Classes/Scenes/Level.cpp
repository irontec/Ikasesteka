//
//  Level.cpp
//  IkasGame
//
//  Created by Sergio Garcia on 9/2/15.
//
//

#include "Level.h"
#include "../Singletons/GameSettingsManager.h"
#include "../Singletons/GamePlayPointsManager.h"
#include "../Singletons/SceneManager.h"
#include "../Singletons/SoundManager.h"
#include "../Helpers/LanguageManager.h"
#include "../Helpers/ScreenSizeManager.h"
#include "../Helpers/ImageManager.h"
#include "../Scenes/GamePlay.h"
#include "../Helpers/DataFileManager.h"
#include "../GameModels/MainCategory.h"

#define TitleSeparatorHeight 10

#define LevelsViewWidthPercentage 70
#define LevelsViewHeightPercentage 40

#define LevelsViewXPositionPercentage 50
#define LevelsViewYPositionPercentage 50

#define LevelsViewItemImageHeightPercentage 80
#define LevelsViewItemImageTitleSeparationPercentage 5

Scene* Level::createScene()
{
    auto *scene = Scene::create();
    
    auto *layer = Level::create();
    layer->setTag(2334);
    
    scene->addChild(layer);
    
    return scene;
}

bool Level::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Rect visibleRect = ScreenSizeManager::getVisibleRect();
    
    auto background = Sprite::create(ImageManager::getImage("background"), visibleRect);
    background->setPosition(ScreenSizeManager::getScreenPositionFromPercentage(50, 50));
    background->setAnchorPoint(Point::ANCHOR_MIDDLE);
    this->addChild(background);
    
    buttonsLayer = Layer::create();
    buttonsLayer->setContentSize(visibleRect.size);
    buttonsLayer->setPosition(0, 0);
    
    auto buttonBack = SpriteButton::create(ImageManager::getImage("back"), 0.30f, CC_CALLBACK_1(Level::changeScene, this));
    buttonBack->setTag(static_cast<int>(SceneType::CATEGORIES));
    buttonBack->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 positionButtonBack = ScreenSizeManager::getScreenPositionFromPercentage(5, 5);
    positionButtonBack.x += buttonBack->getBoundingBox().size.width / 2;
    positionButtonBack.y += buttonBack->getBoundingBox().size.height / 2;
    buttonBack->setPosition(positionButtonBack);
    buttonsLayer->addChild(buttonBack);
    
    auto buttonHome = SpriteButton::create(ImageManager::getImage("home"), 0.30f, CC_CALLBACK_1(Level::changeScene, this));
    buttonHome->setTag(static_cast<int>(SceneType::MAIN));
    buttonHome->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 positionButtonHome = buttonBack->getPosition();
    positionButtonHome.x += buttonHome->getBoundingBox().size.width;
    positionButtonHome.x += ScreenSizeManager::getWidthFromPercentage(5);
    buttonHome->setPosition(positionButtonHome);
    buttonsLayer->addChild(buttonHome);

    auto buttonAbout = SpriteButton::create(ImageManager::getImage("info"), 0.30f, CC_CALLBACK_1(Level::openInfo, this));
    buttonAbout->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 positionButtonAbout = ScreenSizeManager::getScreenPositionFromPercentage(95, 5);
    positionButtonAbout.x -= buttonAbout->getBoundingBox().size.width / 2;
    positionButtonAbout.y += buttonAbout->getBoundingBox().size.height / 2;
    buttonAbout->setPosition(positionButtonAbout);
    buttonsLayer->addChild(buttonAbout);
    
    auto buttonSFXSettings = SpriteButton::create(ImageManager::getImage(GameSettingsManager::getInstance()->getIsSFXOn() ? SoundEnableImage : SoundDisableImage), 0.30f, CC_CALLBACK_1(Level::switchSoundSettings, this));
    buttonSFXSettings->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 positionButtonSFXSettings = buttonAbout->getPosition();
    positionButtonSFXSettings.x -= buttonSFXSettings->getBoundingBox().size.width;
    positionButtonSFXSettings.x -= ScreenSizeManager::getWidthFromPercentage(5);
    buttonSFXSettings->setPosition(positionButtonSFXSettings);
    buttonsLayer->addChild(buttonSFXSettings);
    
    this->addChild(buttonsLayer);
    
    auto layerCategories = Layer::create();
    layerCategories->setContentSize(visibleRect.size);
    layerCategories->setAnchorPoint(Point::ZERO);
    layerCategories->setPosition(0, 0);
    
    auto layerDifficultyButtons = Layer::create();
    layerDifficultyButtons->setContentSize(Size(ScreenSizeManager::getWidthFromPercentage(LevelsViewWidthPercentage), ScreenSizeManager::getHeightFromPercentage(LevelsViewHeightPercentage)));
    
    Vec2 positionLayerDifficiltyButtons = ScreenSizeManager::getScreenPositionFromPercentage(LevelsViewXPositionPercentage, LevelsViewYPositionPercentage);
    positionLayerDifficiltyButtons.y -= layerDifficultyButtons->getContentSize().height/2;
    positionLayerDifficiltyButtons.x -= layerDifficultyButtons->getContentSize().width/2;
    layerDifficultyButtons->setPosition(positionLayerDifficiltyButtons);
    
    // Size and positions
    Size sizeLevelLayer = layerDifficultyButtons->getBoundingBox().size;
    sizeLevelLayer.width = sizeLevelLayer.width/3;
    
    Size sizeButton = sizeLevelLayer;
    sizeButton.height = sizeButton.height * LevelsViewItemImageHeightPercentage/100;
    
    float buttonYCenterPosition = sizeLevelLayer.height - sizeButton.height/2;
    
    Size labelSize = sizeLevelLayer;
    float percentage = (float)(100 - LevelsViewItemImageHeightPercentage - LevelsViewItemImageTitleSeparationPercentage)/100;
    labelSize.height = labelSize.height * percentage;
    
    // Levels layers
    Vec2 positionLevelLayer = Vec2(0, 0);
    auto layerEasyLevel = Layer::create();
    layerEasyLevel->setContentSize(sizeLevelLayer);
    positionLevelLayer.x = sizeLevelLayer.width * 0;
    layerEasyLevel->setPosition(positionLevelLayer);
    layerDifficultyButtons->addChild(layerEasyLevel);
    
    auto layerMediumLevel = Layer::create();
    layerMediumLevel->setContentSize(sizeLevelLayer);
    positionLevelLayer.x = sizeLevelLayer.width * 1;
    layerMediumLevel->setPosition(positionLevelLayer);
    layerDifficultyButtons->addChild(layerMediumLevel);
    
    auto layerHardLevel = Layer::create();
    layerHardLevel->setContentSize(sizeLevelLayer);
    positionLevelLayer.x = sizeLevelLayer.width * 2;
    layerHardLevel->setPosition(positionLevelLayer);
    layerDifficultyButtons->addChild(layerHardLevel);

    float maxSize;
    float scale = 1.0f;
    
    // Easy level
    auto buttonEasyLevel = SpriteButton::create(ImageManager::getImage("level-easy-circle"), scale, CC_CALLBACK_1(Level::selectLevel, this));
    buttonEasyLevel->setTag(static_cast<int>(Difficulty::EASY));
    if (sizeButton.width < sizeButton.height) {
        scale = sizeButton.width / buttonEasyLevel->getBoundingBox().size.width;
        scale -= 0.15f;
        maxSize = sizeButton.width * scale;
    } else {
        scale = sizeButton.height / buttonEasyLevel->getBoundingBox().size.height;
        scale -= 0.15f;
        maxSize = sizeButton.height * scale;
    }
    buttonEasyLevel->setScale(scale);
    buttonEasyLevel->setAnchorPoint(Point::ANCHOR_MIDDLE);

    buttonEasyLevel->setPosition(sizeLevelLayer.width/2, buttonYCenterPosition);
    layerEasyLevel->addChild(buttonEasyLevel);
    
    auto labelEasyLevel = Label::createWithTTF(LanguageManager::getLocalizedText("Level", "easy"), MainRegularFont, 70.0);
    labelEasyLevel->setContentSize(labelSize);
    labelEasyLevel->setPosition(sizeLevelLayer.width/2, 0);
    labelEasyLevel->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    labelEasyLevel->setAlignment(TextHAlignment::CENTER);
    labelEasyLevel->setTag(123);
    labelEasyLevel->setTextColor(IkasGrayDark);
    layerEasyLevel->addChild(labelEasyLevel);
    
    // Medium level
    scale = 1.0f;
    auto buttonMediumLevel = SpriteButton::create(ImageManager::getImage("level-medium-circle"), scale, CC_CALLBACK_1(Level::selectLevel, this));
    buttonMediumLevel->setTag(static_cast<int>(Difficulty::MEDIUM));
    if (sizeButton.width < sizeButton.height) {
        scale = sizeButton.width / buttonMediumLevel->getBoundingBox().size.width;
        scale -= 0.15f;
        maxSize = sizeButton.width * scale;
    } else {
        scale = sizeButton.height / buttonMediumLevel->getBoundingBox().size.height;
        scale -= 0.15f;
        maxSize = sizeButton.height * scale;
    }
    buttonMediumLevel->setScale(scale);
    buttonMediumLevel->setAnchorPoint(Point::ANCHOR_MIDDLE);
    
    buttonMediumLevel->setPosition(sizeLevelLayer.width/2, buttonYCenterPosition);
    layerMediumLevel->addChild(buttonMediumLevel);
    
    auto labelMediumLevel = Label::createWithTTF(LanguageManager::getLocalizedText("Level", "medium"), MainRegularFont, 70.0);
    labelMediumLevel->setContentSize(labelSize);
    labelMediumLevel->setPosition(sizeLevelLayer.width/2, 0);
    labelMediumLevel->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    labelMediumLevel->setAlignment(TextHAlignment::CENTER);
    labelMediumLevel->setTag(123);
    labelMediumLevel->setTextColor(IkasGrayDark);
    layerMediumLevel->addChild(labelMediumLevel);
    
    // Hard level
    scale = 1.0f;
    auto buttonHardLevel = SpriteButton::create(ImageManager::getImage("level-hard-circle"), scale, CC_CALLBACK_1(Level::selectLevel, this));
    buttonHardLevel->setTag(static_cast<int>(Difficulty::HARD));
    if (sizeButton.width < sizeButton.height) {
        scale = sizeButton.width / buttonHardLevel->getBoundingBox().size.width;
        scale -= 0.15f;
        maxSize = sizeButton.width * scale;
    } else {
        scale = sizeButton.height / buttonHardLevel->getBoundingBox().size.height;
        scale -= 0.15f;
        maxSize = sizeButton.height * scale;
    }
    buttonHardLevel->setScale(scale);
    buttonHardLevel->setAnchorPoint(Point::ANCHOR_MIDDLE);
    
    buttonHardLevel->setPosition(sizeLevelLayer.width/2, buttonYCenterPosition);
    layerHardLevel->addChild(buttonHardLevel);
    
    auto labelHardLevel = Label::createWithTTF(LanguageManager::getLocalizedText("Level", "hard"), MainRegularFont, 70.0);
    labelHardLevel->setContentSize(labelSize);
    labelHardLevel->setPosition(sizeLevelLayer.width/2, 0);
    labelHardLevel->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    labelHardLevel->setAlignment(TextHAlignment::CENTER);
    labelHardLevel->setTag(123);
    labelHardLevel->setTextColor(IkasGrayDark);
    layerHardLevel->addChild(labelHardLevel);
    
    layerCategories->addChild(layerDifficultyButtons);

    auto labelDifficultyTitle = Label::createWithTTF(LanguageManager::getLocalizedText("Level", "title"), MainRegularFont, 70);
    labelDifficultyTitle->setAlignment(TextHAlignment::CENTER);
    labelDifficultyTitle->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    labelDifficultyTitle->setTextColor(IkasGrayDark);
    Vec2 positionLabelTitle = layerDifficultyButtons->getPosition();
    positionLabelTitle.x += layerDifficultyButtons->getBoundingBox().size.width/2;
    positionLabelTitle.y += layerDifficultyButtons->getBoundingBox().size.height;
    positionLabelTitle.y += ScreenSizeManager::getHeightFromPercentage(10);
    labelDifficultyTitle->setPosition(positionLabelTitle);
    
    layerCategories->addChild(labelDifficultyTitle);

    this->addChild(layerCategories);
    
    return true;
}

void Level::switchSoundSettings(Ref* sender)
{
    SoundManager::getInstance()->sfxPlay("button");
    GameSettingsManager::getInstance()->switchSFX();
    GameSettingsManager::getInstance()->switchMusic();
    SpriteButton *item = static_cast<SpriteButton*>(sender);
    item->setTexture(ImageManager::getImage(GameSettingsManager::getInstance()->getIsSFXOn() ? SoundEnableImage : SoundDisableImage));
}

void Level::changeScene(Ref* sender)
{
    SoundManager::getInstance()->sfxPlay("button");
    
    SpriteButton *item = static_cast<SpriteButton*>(sender);
    SceneManager::getInstance()->runSceneWithType(static_cast<SceneType>(item->getTag()));
}

void Level::openInfo(Ref* sender)
{
    SoundManager::getInstance()->sfxPlay("button");
    Application::getInstance()->openURL(InfoURL);
}

void Level::selectLevel(Ref* sender)
{
    SoundManager::getInstance()->sfxPlay("button");
    
    SpriteButton *item = static_cast<SpriteButton*>(sender);
    Difficulty difficulty = static_cast<Difficulty>(item->getTag());
    vector<MainCategory*> categories = DataFileManager::getInstance()->getMainCategories();
    vector<SubCategory*> subCategories = categories.at(GamePlayPointsManager::getInstance()->getCurrentCategory())->getFilteredSubCategoriesByLevel(difficulty);
    if (subCategories.empty()) {
        log("no hay subcategorias con ese nivel!!");
        return;
    }
    GamePlayPointsManager::getInstance()->setCurrentDifficulty(difficulty);
    SceneManager::getInstance()->runSceneWithType(SceneType::GAMEPLAY);
}
