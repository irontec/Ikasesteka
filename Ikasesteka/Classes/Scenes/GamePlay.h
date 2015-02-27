//
//  GamePlay.h
//  IkasGame
//
//  Created by Axier Fernandez on 10/2/15.
//
//

#ifndef __IkasGame__GamePlay__
#define __IkasGame__GamePlay__

#include "cocos2d.h"
using namespace cocos2d;

#include "../Constants/CommonProtocols.h"
#include "../CustomGUI/SpriteButton.h"

#include "../GameModels/MainCategory.h"
#include "../GameModels/SubCategory.h"
#include "../GameModels/Option.h"
#include "../Singletons/ZipManager.h"

enum class TouchState
{
    START,
    MOVING,
    FINISH
};

class GamePlay : public Layer, public GamePlayDelegate
{
    Layer *layerPause, *layerWin, *layerLose;
    
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(GamePlay);
    
    EventListenerTouchOneByOne *addEvents();
    
    virtual bool touchBegan(Touch *touch, Event *pEvent);
    virtual void touchEnded(Touch *touch, Event *pEvent);
    virtual void touchMoved(Touch *touch, Event *pEvent);
    virtual void touchCancelled(Touch *pTouch, Event *pEvent);
    
    // GamePlayDelegate
    virtual void loadNextGamePlay();
    virtual void resumeGamePlay();
    virtual void restartGame();
    virtual void updateScreenGameStats();
    // Time control
    void timeElapsed();
private:
    vector<MainCategory*> _categories;
    vector<SubCategory*> _subCategories;
    vector<int> _loadedIndex;
    
    void setupLevelSettings();
    void resetTimer();
    void pauseGame(Ref* sender);

    Label *_labelCategory, *_labelPoints, *_labelLevel;
    
    Layer *_gameLayer, *_touchLayer;
    DrawNode *_drawTouch, *_drawSuccess, *_drawError;
    TouchState _touchState;
    Vec2 _initialTouch, _endTouch;
    
    vector<Sprite*> _images;
    vector<Label*> _titles;
    vector<int> _indexes;
    
    ProgressTimer* _progress;
    ProgressFromTo* _action;
    Sequence* _sequence;
    
    float _elapsedTime, _currentLevelTime, _maxTime;
    int _totalSuccessScreens;
    
    SpriteButton* _pauseButton;
    
    void checkDrawResult(int index, Vec2 imageTouchLocation, Vec2 titleTouchLocation);
    void checkGameStatus();
    void openSuccessScreen();
};
#endif /* defined(__IkasGame__GamePlay__) */
