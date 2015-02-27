#include "AppDelegate.h"
#include "AppMacros.h"
#include "Scenes/Splash.h"
#include "Singletons/SoundManager.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("IkasGame");
        director->setOpenGLView(glview);
    }
    
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    
    Size frameSize = glview->getFrameSize();
    std::vector<std::string> searchPath;
    
    searchPath.push_back(resource.directory);
    director->setContentScaleFactor(MIN(resource.size.height/designResolutionSize.height, resource.size.width/designResolutionSize.width));
    
    searchPath.push_back("images");
    FileUtils::getInstance()->setSearchResolutionsOrder(searchPath);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = Splash::createScene();

    // run
    director->runWithScene(scene);

    SoundManager::getInstance()->musicPlay("background");
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SoundManager::getInstance()->pauseAll();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    //  SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SoundManager::getInstance()->resumeAll();
}
