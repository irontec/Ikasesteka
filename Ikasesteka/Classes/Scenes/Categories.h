//
//  Categories.h
//  IkasGame
//
//  Created by Sergio Garcia on 2/2/15.
//
//

#ifndef __IkasCocosGame__Categories__
#define __IkasCocosGame__Categories__

#include "cocos2d.h"
using namespace cocos2d;

#include "../CustomGUI/SpriteButton.h"
#include "../CustomGUI/PagingCCScrollView.h"
#include "../CustomGUI/PagingCCTableView.h"
#include "../CustomGUI/PagingCCTableViewCell.h"

#include "../GameModels/MainCategory.h"
#include "../GameModels/SubCategory.h"
#include "../GameModels/Option.h"
#include "../Singletons/ZipManager.h"

class Categories : public Layer, public PagingTableViewDataSource, public PagingTableViewDelegate, public PagingScrollViewDelegate
{
    Layer *buttonsLayer, *layerCategories;
    PagingTableView *tableViewCategories;
    Vec2 tableViewContentOffset;
    SpriteButton *buttonPreviousPage, *buttonNextPage;
    
    Size scrollSize, scrollItemSize;
    
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(Categories);
    
protected:
    void switchSoundSettings(Ref* sender);
    void changeScene(Ref* sender);
    void openInfo(Ref* sender);
    void updateTableViewPage(Ref* sender);
    float getPaginationOffset();
    
private:
    vector<MainCategory*> _categories;
    
    Size getScrollSize();
    Size getScrollItemSize();
    
    virtual void scrollViewDidScroll(PagingScrollView* view);
    
    virtual void tableCellTouched(PagingTableView* table, PagingTableViewCell* cell);
    virtual Size tableCellSizeForIndex(PagingTableView *table, ssize_t idx);
    virtual PagingTableViewCell* tableCellAtIndex(PagingTableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(PagingTableView *table);
};
#endif /* defined(__IkasCocosGame__Categories__) */
