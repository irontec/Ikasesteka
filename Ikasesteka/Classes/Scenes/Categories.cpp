//
//  Categories.cpp
//  IkasGame
//
//  Created by Sergio Garcia on 2/2/15.
//
//

#include "./Categories.h"
#include "../Singletons/GameSettingsManager.h"
#include "../Singletons/GamePlayPointsManager.h"
#include "../Singletons/SceneManager.h"
#include "../Singletons/SoundManager.h"
#include "../Helpers/LanguageManager.h"
#include "../Helpers/ScreenSizeManager.h"
#include "../Helpers/ImageManager.h"
#include "../Helpers/DataFileManager.h"

#define TitleSeparatorHeight 10

#define TableViewWidthPercentage 70
#define TableViewHeightPercentage 40
#define TableViewItemsPerPage 3

#define TableViewXPositionPercentage 50
#define TableViewYPositionPercentage 50

#define TableViewItemImageHeightPercentage 80
#define TableViewItemImageTitleSeparationPercentage 5

enum class TablewViewPageDirection
{
    PREVIOUS,
    NEXT
};

Scene* Categories::createScene()
{
    auto *scene = Scene::create();
    
    auto *layer = Categories::create();
    layer->setTag(2334);
    
    scene->addChild(layer);
    
    return scene;
}

bool Categories::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    DataFileManager *dataManager = DataFileManager::getInstance();
    dataManager->parseDataFile();
    _categories = dataManager->getMainCategories();
    
    Rect visibleRect = ScreenSizeManager::getVisibleRect();
    
    auto background = Sprite::create(ImageManager::getImage("background"), visibleRect);
    background->setPosition(ScreenSizeManager::getScreenPositionFromPercentage(50, 50));
    background->setAnchorPoint(Point::ANCHOR_MIDDLE);
    this->addChild(background);
    
    buttonsLayer = Layer::create();
    buttonsLayer->setContentSize(visibleRect.size);
    buttonsLayer->setPosition(0, 0);

    auto buttonBack = SpriteButton::create(ImageManager::getImage("back"), 0.30f, CC_CALLBACK_1(Categories::changeScene, this));
    buttonBack->setTag(static_cast<int>(SceneType::MAIN));
    buttonBack->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 positionButtonBack = ScreenSizeManager::getScreenPositionFromPercentage(5, 5);
    positionButtonBack.x += buttonBack->getBoundingBox().size.width / 2;
    positionButtonBack.y += buttonBack->getBoundingBox().size.height / 2;
    buttonBack->setPosition(positionButtonBack);
    buttonsLayer->addChild(buttonBack);
    
    auto buttonAbout = SpriteButton::create(ImageManager::getImage("info"), 0.30f, CC_CALLBACK_1(Categories::openInfo, this));
    buttonAbout->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 positionButtonAbout = ScreenSizeManager::getScreenPositionFromPercentage(95, 5);
    positionButtonAbout.x -= buttonAbout->getBoundingBox().size.width / 2;
    positionButtonAbout.y += buttonAbout->getBoundingBox().size.height / 2;
    buttonAbout->setPosition(positionButtonAbout);
    buttonsLayer->addChild(buttonAbout);
    
    auto buttonSFXSettings = SpriteButton::create(ImageManager::getImage(GameSettingsManager::getInstance()->getIsSFXOn() ? SoundEnableImage : SoundDisableImage), 0.30f, CC_CALLBACK_1(Categories::switchSoundSettings, this));
    buttonSFXSettings->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 positionButtonSFXSettings = buttonAbout->getPosition();
    positionButtonSFXSettings.x -= ScreenSizeManager::getWidthFromPercentage(5);
    positionButtonSFXSettings.x -= buttonSFXSettings->getBoundingBox().size.width;
    buttonSFXSettings->setPosition(positionButtonSFXSettings);
    buttonsLayer->addChild(buttonSFXSettings);

    this->addChild(buttonsLayer);
    
    /* PagingTablewView */
    
    layerCategories = Layer::create();
    layerCategories->setContentSize(visibleRect.size);
    layerCategories->setPosition(0, 0);
    
    tableViewCategories = PagingTableView::create(this, Size(ScreenSizeManager::getWidthFromPercentage(TableViewWidthPercentage), ScreenSizeManager::getHeightFromPercentage(TableViewHeightPercentage)));
    tableViewCategories->setDirection(PagingScrollView::Direction::HORIZONTAL);
    tableViewCategories->setDelegate(this);
    tableViewCategories->setEnablePaging(true);
    tableViewCategories->setPageSize(tableViewCategories->getBoundingBox().size/TableViewItemsPerPage);
    
    Vec2 positionTablewView = ScreenSizeManager::getScreenPositionFromPercentage(TableViewXPositionPercentage, TableViewYPositionPercentage);
    positionTablewView.x -= tableViewCategories->getBoundingBox().size.width/2;
    positionTablewView.y -= tableViewCategories->getBoundingBox().size.height/2;
    tableViewCategories->setPosition(positionTablewView);
    tableViewCategories->setTag(static_cast<int>(false));
    layerCategories->addChild(tableViewCategories);
    
    auto labelCategoriesTitle = Label::createWithTTF(LanguageManager::getLocalizedText("Categories", "title"), MainRegularFont, 70);
    labelCategoriesTitle->setAlignment(TextHAlignment::CENTER);
    labelCategoriesTitle->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    labelCategoriesTitle->setTextColor(IkasGrayDark);
    Vec2 positionLabelTableView = tableViewCategories->getPosition();
    positionLabelTableView.x += tableViewCategories->getBoundingBox().size.width/2;
    positionLabelTableView.y += tableViewCategories->getBoundingBox().size.height;
    positionLabelTableView.y += ScreenSizeManager::getHeightFromPercentage(TitleSeparatorHeight);
    
    labelCategoriesTitle->setPosition(positionLabelTableView);
    layerCategories->addChild(labelCategoriesTitle);
    
    buttonPreviousPage = SpriteButton::create(ImageManager::getImage("left"), 0.70f, 10.0f, CC_CALLBACK_1(Categories::updateTableViewPage, this));
    buttonPreviousPage->setTag(static_cast<int>(TablewViewPageDirection::PREVIOUS));
    buttonPreviousPage->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 positionButtonPreviousPage = positionTablewView;
    positionButtonPreviousPage.y += tableViewCategories->getBoundingBox().size.height / 2;
    positionButtonPreviousPage.x -= buttonPreviousPage->getBoundingBox().size.width / 2;
    buttonPreviousPage->setPosition(positionButtonPreviousPage);
    layerCategories->addChild(buttonPreviousPage);
    
    buttonNextPage = SpriteButton::create(ImageManager::getImage("right"), 0.70f, 10.0f, CC_CALLBACK_1(Categories::updateTableViewPage, this));
    buttonNextPage->setTag(static_cast<int>(TablewViewPageDirection::NEXT));
    buttonNextPage->setAnchorPoint(Point::ANCHOR_MIDDLE);
    Vec2 positionButtonNextPage = positionTablewView;
    positionButtonNextPage.y += tableViewCategories->getBoundingBox().size.height / 2;
    positionButtonNextPage.x += tableViewCategories->getBoundingBox().size.width;
    positionButtonNextPage.x += buttonNextPage->getBoundingBox().size.width / 2;
    buttonNextPage->setPosition(positionButtonNextPage);
    layerCategories->addChild(buttonNextPage);

    this->addChild(layerCategories);
    tableViewCategories->reloadData();
    
    return true;
}

ssize_t Categories::numberOfCellsInTableView(PagingTableView *table)
{
    return _categories.size();
}

Size Categories::tableCellSizeForIndex(PagingTableView *table, ssize_t idx)
{
    return this->getScrollItemSize();
}

PagingTableViewCell* Categories::tableCellAtIndex(PagingTableView *table, ssize_t idx)
{
    MainCategory mainCategory = *_categories.at(idx);
    auto string = String::createWithFormat(mainCategory.getName().c_str(), (int)idx);
    
    PagingTableViewCell *cell = table->dequeueCell();
    
    Size itemSize = this->getScrollItemSize();

    if (!cell) {
        cell = new PagingTableViewCell();
        cell->autorelease();
    }
    
    cell->removeAllChildren();
    
    Size spriteSize = itemSize;
    spriteSize.height = spriteSize.height * TableViewItemImageHeightPercentage/100;
    
    float maxSize = 0;
    float scale = 1.0f;
    
    // Create circle
    auto circle = SpriteButton::create(ImageManager::getImage("category-circle"), scale, NULL);
    
    if (spriteSize.width < spriteSize.height) {
        maxSize = spriteSize.width;
        scale = spriteSize.width / circle->getBoundingBox().size.width;
    } else {
        maxSize = spriteSize.height;
        scale = spriteSize.height / circle->getBoundingBox().size.height;
    }
    // Append min margin
    scale -= 0.15f;
    circle->setScale(scale);
    circle->setAnchorPoint(Point::ANCHOR_MIDDLE);
    circle->setPosition(Vec2(itemSize.width/2, itemSize.height - spriteSize.height/2));
    cell->addChild(circle);
    
    // Add category image
    // Reset values
    maxSize = 0;
    scale = 1.0f;
    spriteSize = circle->getBoundingBox().size;
    auto categoryImage = SpriteButton::create(ZipManager::getInstance()->getDataFolderFullPath("hd/topics/" + mainCategory.getFileName()), scale, NULL);
    float maxSizePercentage = 0.80;
    if (spriteSize.width < spriteSize.height) {
        maxSize = spriteSize.width;
        scale = spriteSize.width * maxSizePercentage / categoryImage->getBoundingBox().size.width;
    } else {
        maxSize = spriteSize.height;
        scale = spriteSize.height * maxSizePercentage / categoryImage->getBoundingBox().size.height;
    }
    categoryImage->setScale(scale);
    categoryImage->setAnchorPoint(Point::ANCHOR_MIDDLE);
    categoryImage->setPosition(circle->getPosition());
    cell->addChild(categoryImage);
    
    
    Size labelSize = itemSize;
    labelSize.height = labelSize.height * (1 - TableViewItemImageHeightPercentage/100 - TableViewItemImageTitleSeparationPercentage/100);
    auto label = Label::createWithTTF(string->getCString(), MainRegularFont, 70.0);
    label->setContentSize(labelSize);
    label->setPosition(Vec2(itemSize.width/2, 0));
    label->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    label->setAlignment(TextHAlignment::CENTER);
    label->setTag(123);
    label->setTextColor(IkasRed);
    cell->addChild(label);

    return cell;
}

void Categories::tableCellTouched(PagingTableView* table, PagingTableViewCell* cell)
{
    SoundManager::getInstance()->sfxPlay("button");
    if (_categories.at((int)cell->getIdx())->getSubCategories().empty()) {
        log("subcategorias en blanco!");
        return;
    }
    GamePlayPointsManager::getInstance()->setCurrentCategory((int)cell->getIdx());
    SceneManager::getInstance()->runSceneWithType(SceneType::LEVEL);
}

Size Categories::getScrollSize()
{
    if (scrollSize.width == 0 && scrollSize.height == 0) {
        scrollSize = Size(ScreenSizeManager::getWidthFromPercentage(TableViewWidthPercentage), ScreenSizeManager::getHeightFromPercentage(TableViewHeightPercentage));
    }
    return scrollSize;
}

Size Categories::getScrollItemSize()
{
    if (scrollItemSize.width == 0 && scrollItemSize.height == 0) {
        Size mScrollSize = this->getScrollSize();
        float itemWidth = mScrollSize.width/TableViewItemsPerPage;
        float itemHeight =  mScrollSize.height;
        
        scrollItemSize = Size(itemWidth, itemHeight);
    }
    return scrollItemSize;
}

void Categories::switchSoundSettings(Ref* sender)
{
    SoundManager::getInstance()->sfxPlay("button");
    GameSettingsManager::getInstance()->switchSFX();
    GameSettingsManager::getInstance()->switchMusic();
    SpriteButton *item = static_cast<SpriteButton*>(sender);
    item->setTexture(ImageManager::getImage(GameSettingsManager::getInstance()->getIsSFXOn() ? SoundEnableImage : SoundDisableImage));
}

void Categories::changeScene(Ref* sender)
{
    SoundManager::getInstance()->sfxPlay("button");
    
    SpriteButton *item = static_cast<SpriteButton*>(sender);
    SceneManager::getInstance()->runSceneWithType(static_cast<SceneType>(item->getTag()));
}

void Categories::openInfo(Ref* sender)
{
    SoundManager::getInstance()->sfxPlay("button");
    Application::getInstance()->openURL(InfoURL);
}

void Categories::updateTableViewPage(Ref* sender)
{
    if (static_cast<bool>(tableViewCategories->getTag()) == false) {
        tableViewContentOffset = tableViewCategories->getContentOffset();
        tableViewCategories->setTag(static_cast<int>(true));
    }
    
    SoundManager::getInstance()->sfxPlay("button");
    
    SpriteButton *item = static_cast<SpriteButton*>(sender);
    TablewViewPageDirection direction = static_cast<TablewViewPageDirection>(item->getTag());

    if (TablewViewPageDirection::PREVIOUS == direction) {
        if (-tableViewContentOffset.x > 0) {
            tableViewContentOffset.x += this->getPaginationOffset();
        }
    } else {
        if (-tableViewContentOffset.x < tableViewCategories->getContentSize().width - tableViewCategories->getBoundingBox().size.width) {
            tableViewContentOffset.x -= this->getPaginationOffset();
        }
    }

    tableViewCategories->setContentOffsetInDuration(tableViewContentOffset, 0.25f);
}

float Categories::getPaginationOffset()
{
    return tableViewCategories->getBoundingBox().size.width/TableViewItemsPerPage;
}

void Categories::scrollViewDidScroll(PagingScrollView* view)
{
    float value = -view->getContentOffset().x;
    float nearItemPosition = value / this->getPaginationOffset();
    float decimal = nearItemPosition - (int)nearItemPosition;
    if (decimal >= 0.5f) {
        nearItemPosition = nearItemPosition + 1;
    }
    nearItemPosition = (int)nearItemPosition;
    float nearItemOffset = nearItemPosition * this->getPaginationOffset();
    
    tableViewContentOffset.x = -nearItemOffset;
}
