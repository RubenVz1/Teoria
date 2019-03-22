#include "AppDelegate.h"
//#include "IntroScene.h"
#include "GraphScene.h"

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
	#if USE_AUDIO_ENGINE
		AudioEngine::end();
	#elif USE_SIMPLE_AUDIO_ENGINE
		SimpleAudioEngine::end();
	#endif
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};
    GLView::setGLContextAttrs(glContextAttrs);
}

static int register_all_packages()
{
    return 0;
}

bool AppDelegate::applicationDidFinishLaunching()
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview)
	{
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
				glview = GLViewImpl::createWithRect("Teoria_de_Graficas", cocos2d::Rect(0, 0, mediumResolutionSize.width, mediumResolutionSize.height));
		#else
				glview = GLViewImpl::create("Teoria_de_Graficas");
		#endif
				director->setOpenGLView(glview);
    }

    director->setDisplayStats(true);

    director->setAnimationInterval(1.0f / 60);

    glview->setDesignResolutionSize(mediumResolutionSize.width, mediumResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();

    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/ mediumResolutionSize.height, largeResolutionSize.width/ mediumResolutionSize.width));
    }
  
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/ mediumResolutionSize.height, mediumResolutionSize.width/ mediumResolutionSize.width));
    }

    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/ mediumResolutionSize.height, smallResolutionSize.width/ mediumResolutionSize.width));
    }

	director->setClearColor(Color4F::WHITE);

    register_all_packages();

    //auto scene = Intro::createScene();

	auto scene = Graph::createScene();

    director->runWithScene(scene);

    return true;
}


void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

	#if USE_AUDIO_ENGINE
		AudioEngine::pauseAll();
	#elif USE_SIMPLE_AUDIO_ENGINE
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		SimpleAudioEngine::getInstance()->pauseAllEffects();
	#endif
}


void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

	#if USE_AUDIO_ENGINE
		AudioEngine::resumeAll();
	#elif USE_SIMPLE_AUDIO_ENGINE
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		SimpleAudioEngine::getInstance()->resumeAllEffects();
	#endif
}
