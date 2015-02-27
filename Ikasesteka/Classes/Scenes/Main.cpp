//
//  Main.cpp
//  IkasGame
//
//  Created by Sergio Garcia on 30/01/15.
//
//

#include "Main.h"
#include "../Singletons/GameSettingsManager.h"
#include "../Singletons/GamePlayPointsManager.h"
#include "../Singletons/SceneManager.h"
#include "../Singletons/SoundManager.h"
#include "../Singletons/ZipManager.h"
#include "../Helpers/LanguageManager.h"
#include "../Helpers/ScreenSizeManager.h"
#include "../Helpers/ImageManager.h"
#include "../CustomGUI/SpriteButton.h"

const Value DelayMinTime = Value(5.0f);

Scene* Main::createScene()
{
    auto *scene = Scene::create();
    
    auto *layer = Main::create();
    layer->setTag(2334);
    
    scene->addChild(layer);
    
    return scene;
}

Main::~Main()
{
    _api = NULL;
}

bool Main::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    // Reset game play settings to defaults
    GamePlayPointsManager::getInstance()->resetCurrentGamePlaySettings();
    
    Rect visibleRect = ScreenSizeManager::getVisibleRect();
    
    auto background = Sprite::create(ImageManager::getImage("background"), visibleRect);
    background->setPosition(ScreenSizeManager::getScreenPositionFromPercentage(50, 50));
    background->setAnchorPoint(Point::ANCHOR_MIDDLE);
    this->addChild(background);
    
    auto logo = Sprite::create(ImageManager::getImage("logo"));
    logo->setPosition(ScreenSizeManager::getScreenPositionFromPercentage(50, 70));
    logo->setAnchorPoint(Point::ANCHOR_MIDDLE);
    logo->setScale(0.90f);
    this->addChild(logo);

    /* Play Layer */
    playLayer = Layer::create();
    playLayer->setContentSize(visibleRect.size);
    playLayer->setPosition(0, 0);
    playLayer->setVisible(false);
    
    auto buttonPlay = SpriteButton::create(ImageManager::getImage("play"), 0.5f, CC_CALLBACK_1(Main::changeScene, this));
    buttonPlay->setTag(static_cast<int>(SceneType::CATEGORIES));
    buttonPlay->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 positionPlay = ScreenSizeManager::getScreenPositionFromPercentage(50, 50);
    positionPlay.y -= ScreenSizeManager::getHeightFromPercentage(18);
    
    // Adjust views to strech screens
    float logoBottom = logo->getPosition().y - logo->getBoundingBox().size.height/2;
    float playTop = positionPlay.y + buttonPlay->getBoundingBox().size.height/2;
    int margin = 10;
    if (logoBottom <= (playTop + margin)) {
        positionPlay.y = logoBottom - margin - buttonPlay->getBoundingBox().size.height/2;
    }
    buttonPlay->setPosition(positionPlay);
    playLayer->addChild(buttonPlay);
    
    auto labelPlay = Label::createWithTTF(LanguageManager::getLocalizedText("Main", "play"), MainRegularFont, 70);
    labelPlay->setAlignment(TextHAlignment::CENTER);
    labelPlay->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    labelPlay->setTextColor(IkasGrayDark);
    Vec2 positionLabelPlay = buttonPlay->getPosition();
    positionLabelPlay.y -= ScreenSizeManager::getHeightFromPercentage(2);
    positionLabelPlay.y -= buttonPlay->getBoundingBox().size.height / 2;
    labelPlay->setPosition(positionLabelPlay);
    playLayer->addChild(labelPlay);

    auto buttonAbout = SpriteButton::create(ImageManager::getImage("info"), 0.30f, CC_CALLBACK_1(Main::openInfo, this));
    buttonAbout->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 positionAbout = ScreenSizeManager::getScreenPositionFromPercentage(95, 5);
    positionAbout.x -= buttonAbout->getBoundingBox().size.width / 2;
    positionAbout.y += buttonAbout->getBoundingBox().size.height / 2;
    buttonAbout->setPosition(positionAbout);
    playLayer->addChild(buttonAbout);
    
    auto buttonSFXSettings = SpriteButton::create(ImageManager::getImage(GameSettingsManager::getInstance()->getIsSFXOn() ? SoundEnableImage : SoundDisableImage), 0.30f, CC_CALLBACK_1(Main::switchSoundSettings, this));
    buttonSFXSettings->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 positionSFXSettings = buttonAbout->getPosition();
    positionSFXSettings.x -= ScreenSizeManager::getWidthFromPercentage(5);
    positionSFXSettings.x -= buttonSFXSettings->getBoundingBox().size.width;
    buttonSFXSettings->setPosition(positionSFXSettings);
    playLayer->addChild(buttonSFXSettings);
    
    this->addChild(playLayer);
    
    // Loading Layer
    loadingLayer = Layer::create();
    loadingLayer->setContentSize(visibleRect.size);
    loadingLayer->setPosition(0, 0);
    loadingLayer->setVisible(false);
    
    auto loadingAnimation = Sprite::create(ImageManager::getImage("loading"));
    loadingAnimation->setScale(0.40f);
    loadingAnimation->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 positionLoadingAnimation = ScreenSizeManager::getScreenPositionFromPercentage(50, 50);
    positionLoadingAnimation.y -= ScreenSizeManager::getHeightFromPercentage(20);
    
    // Adjust views to strech screens
    margin = 45;
    float loadingTop = positionLoadingAnimation.y + loadingAnimation->getBoundingBox().size.height/2;
    if (logoBottom <= (loadingTop + margin)) {
        positionLoadingAnimation.y = logoBottom - margin - loadingAnimation->getBoundingBox().size.height/2;
    }
    
    loadingAnimation->setPosition(positionLoadingAnimation);
    loadingLayer->addChild(loadingAnimation);
    
    ActionInterval* rotate = RotateBy::create(1.0f, 360.0f);
    RepeatForever *repeat = RepeatForever::create(rotate);
    loadingAnimation->runAction(repeat);
    
    auto labelLoadingAnimation = Label::createWithTTF(LanguageManager::getLocalizedText("Main", "loading"), MainRegularFont, 60);
    labelLoadingAnimation->setAlignment(TextHAlignment::CENTER);
    labelLoadingAnimation->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    labelLoadingAnimation->setTextColor(Color4B(IkasPinkAlpha));
    Vec2 positionLabelLoadingAnimation = loadingAnimation->getPosition();
    positionLabelLoadingAnimation.y -= loadingAnimation->getBoundingBox().size.height / 2;
    positionLabelLoadingAnimation.y -= ScreenSizeManager::getHeightFromPercentage(2);
    labelLoadingAnimation->setPosition(positionLabelLoadingAnimation);
    loadingLayer->addChild(labelLoadingAnimation);
    
    this->addChild(loadingLayer);
    
    // Initializing and binding
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Main::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    
    _api = new IkasAPI();
    if(GameSettingsManager::getInstance()->getIsFirstLaunch()) {
        this->checkNewData();
    } else {
        if (GameSettingsManager::getInstance()->getIsNewDataAvalaible()) {
            this->showLoading(true);
            this->downloadLatestData(CC_CALLBACK_1(Main::successDataDownloaded, this), CC_CALLBACK_1(Main::errorDataDownloaded, this));
        } else {
            this->showLoading(false);
            this->checkNewData();
        }
    }
    
    return true;
}

void Main::switchSoundSettings(Ref* sender)
{
    SoundManager::getInstance()->sfxPlay("button");
    GameSettingsManager::getInstance()->switchSFX();
    GameSettingsManager::getInstance()->switchMusic();
    SpriteButton *item = static_cast<SpriteButton*>(sender);
    item->setTexture(ImageManager::getImage(GameSettingsManager::getInstance()->getIsSFXOn() ? SoundEnableImage : SoundDisableImage));
}

void Main::changeScene(Ref* sender)
{
    SoundManager::getInstance()->sfxPlay("button");
    SpriteButton *item = static_cast<SpriteButton*>(sender);
    SceneManager::getInstance()->runSceneWithType(static_cast<SceneType>(item->getTag()));
}

void Main::openInfo(Ref* sender)
{
    SoundManager::getInstance()->sfxPlay("button");
    Application::getInstance()->openURL(InfoURL);
}

void Main::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (static_cast<int>(keyCode) != 6) return;
    log("[Main] BACK key pressed!");
}

void Main::showLoading(bool show)
{
    loadingLayer->setVisible(show);
    playLayer->setVisible(!show);
}

void Main::checkNewData()
{
    if(!GameSettingsManager::getInstance()->getIsNewDataAvalaible() || GameSettingsManager::getInstance()->getIsFirstLaunch()) {
        if (GameSettingsManager::getInstance()->getIsFirstLaunch()) {
            this->showLoading(true);
            _api->checkForLatestZipData(CC_CALLBACK_2(Main::forceFirstData, this), CC_CALLBACK_1(Main::forceFirstDataErrorCallback, this));
        } else {
            _api->checkForLatestZipData(NULL, NULL);
        }
    }
}
    
void Main::forceFirstData(Ref* sender, bool result)
{
    if (result) {
        this->downloadLatestData(CC_CALLBACK_1(Main::successDataDownloaded, this), CC_CALLBACK_1(Main::errorDataDownloaded, this));
    } else {
        // Download again
        GameSettingsManager::getInstance()->setZipUrl("");
        GameSettingsManager::getInstance()->setZipName("");
        GameSettingsManager::getInstance()->setFirstLaunch(true);
        this->checkNewData();
    }
}

void Main::forceFirstDataErrorCallback(Ref* sender)
{
    DelayTime *delayAction = DelayTime::create(DelayMinTime.asFloat());
    CallFunc *mySelector = CallFunc::create(CC_CALLBACK_0(Main::checkNewData, this));
    this->runAction(Sequence::create(delayAction, mySelector, nullptr));
}

void Main::downloadLatestData(const IkasHandler& successCallback, const IkasHandler& errorCallback)
{
    _api->downloadLatestZip(successCallback, errorCallback);
}

void Main::successDataDownloaded(Ref* sender)
{
    GameSettingsManager::getInstance()->setFirstLaunch(false);
    GameSettingsManager::getInstance()->setDataAvalaible(false);
    bool res = ZipManager::getInstance()->unzipZipDataAndDeletePreviousData();
    if (res) {
        this->showLoading(false);
    } else {
        // Download again
        GameSettingsManager::getInstance()->setZipUrl("");
        GameSettingsManager::getInstance()->setZipName("");
        GameSettingsManager::getInstance()->setFirstLaunch(true);
        DelayTime *delayAction = DelayTime::create(DelayMinTime.asFloat());
        CallFunc *mySelector = CallFunc::create(CC_CALLBACK_0(Main::checkNewData, this));
        this->runAction(Sequence::create(delayAction, mySelector, nullptr));
    }
    
}

void Main::errorDataDownloaded(Ref* sender)
{
    // Download again
    GameSettingsManager::getInstance()->setZipUrl("");
    GameSettingsManager::getInstance()->setZipName("");
    GameSettingsManager::getInstance()->setFirstLaunch(true);
    DelayTime *delayAction = DelayTime::create(DelayMinTime.asFloat());
    CallFunc *mySelector = CallFunc::create(CC_CALLBACK_0(Main::checkNewData, this));
    this->runAction(Sequence::create(delayAction, mySelector, nullptr));
}
