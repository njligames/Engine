
#include "Log.h"
#define TAG "Game.cpp"
#include "AbstractRender.h"
#include "GLPlatform.h"
#include "Game.h"
#include "World.h"

#ifdef __ANDROID__
#else
#include <sys/sysctl.h>
#include <sys/types.h>
#endif

namespace njli {

bool NJLIGameEngine::isIOS() { return platformID() == PlatformID_iOS; }

bool NJLIGameEngine::isANDROID() { return platformID() == PlatformID_Android; }

bool NJLIGameEngine::isEMSCRIPTEN()
{
    return platformID() == PlatformID_Emscripten;
}

bool NJLIGameEngine::isMACOSX() { return platformID() == PlatformID_MacOSx; }

bool NJLIGameEngine::isTVOS(){ return platformID() == PlatformID_tvOS;}
    
bool NJLIGameEngine::create(const char* deviceName, bool initLua)
{
    njli::World::createInstance();
    if(initLua)
        njli::World::getInstance()->getWorldLuaVirtualMachine()->init();

    if (LOGGING_ON) {
        const char* platform = (isIOS()
                ? "iOS"
                : (isANDROID()
                          ? "Android"
                          : (isEMSCRIPTEN()
                                    ? "Emscripten"
                                    : ((isMACOSX() ? "MacOSx" : "UNKNOWN_PLATFORM")))));
        DEBUG_LOG_V(TAG, "Platform Name = `%s`\n", platform);
        DEBUG_LOG_V(TAG, "Device Name = `%s`\n", deviceName);

        //        printGLInfo();
        printGLInfo();
    }

    initGL();
    
    njli::World::getInstance()->setDeviceName(deviceName);
    
    return true;
}

void NJLIGameEngine::resize(int x, int y, int width, int height,
    int orientation)
{
    njli::World::getInstance()->resize(width, height, orientation);
}

    void NJLIGameEngine::start()
    {
        njli::World::getInstance()->getWorldClock()->reset();
        
        std::string source = std::string("\
                                         function __NJLIWorldEnterState() end\n\
                                         function __NJLIWorldUpdateState(timeStep) end\n\
                                         function __NJLIWorldExitState() end\n\
                                         function __NJLIWorldOnMessage(message) end\n\
                                         function __NJLIWorldKeyboardShow() end\n\
                                         function __NJLIWorldKeyboardCancel() end\n\
                                         function __NJLIWorldKeyboardReturn(text) end\n\
                                         function __NJLIWorldReceivedMemoryWarning() end\n\
                                         function __NJLIWorldGamePause() end\n\
                                         function __NJLIWorldGameUnPause() end\n\
                                         function __NJLIWorldRenderHUD() end\n\
                                         function __NJLIWorldTouchDown(touches) end\n\
                                         function __NJLIWorldTouchUp(touches) end\n\
                                         function __NJLIWorldTouchMove(touches) end\n\
                                         function __NJLIWorldTouchCancelled(touches) end\n\
                                         function __NJLISceneEnterState(scene) end\n\
                                         function __NJLISceneUpdateState(scene, timeStep) end\n\
                                         function __NJLISceneExitState(scene) end\n\
                                         function __NJLISceneOnMessage(scene, message) end\n\
                                         function __NJLISceneKeyboardShow(scene) end\n\
                                         function __NJLISceneKeyboardCancel(scene) end\n\
                                         function __NJLISceneKeyboardReturn(scene, text) end\n\
                                         function __NJLISceneRenderHUD(scene) end\n\
                                         function __NJLISceneGamePause(scene) end\n\
                                         function __NJLISceneGameUnPause(scene) end\n\
                                         function __NJLISceneTouchDown(scene, touches) end\n\
                                         function __NJLISceneTouchUp(scene, touches) end\n\
                                         function __NJLISceneTouchMove(scene, touches) end\n\
                                         function __NJLISceneTouchCancelled(scene, touches) end\n\
                                         function __NJLINodeEnterState(node) end\n\
                                         function __NJLINodeUpdateState(node, timeStep) end\n\
                                         function __NJLINodeExitState(node) end\n\
                                         function __NJLINodeOnMessage(node, message) end\n\
                                         function __NJLINodeCollide(node, otherNode, collisionPoint) end\n\
                                         function __NJLINodeNear(node, otherNode) end\n\
                                         function __NJLINodeActionUpdate(action, timeStep) end\n\
                                         function __NJLINodeActionComplete(action) end\n\
                                         function __NJLINodeRayTouchDown(rayContact) end\n\
                                         function __NJLINodeRayTouchUp(rayContact) end\n\
                                         function __NJLINodeRayTouchMove(rayContact) end\n\
                                         function __NJLINodeRayTouchCancelled(rayContact) end\n\
                                         function __NJLIGameWillResignActive() end\n\
                                         function __NJLIGameDidBecomeActive() end\n\
                                         function __NJLIGameDidEnterBackground() end\n\
                                         function __NJLIGameWillEnterForeground() end\n\
                                         function __NJLIGameWillTerminate() end\n\
                                         function __NJLIGameInterrupt() end\n\
                                         function __NJLIGameResumeInterrupt() end\n\
                                         ");
        
        
        World::getInstance()->getWorldLuaVirtualMachine()->loadString(source.c_str());
        njli::World::getInstance()->getWorldLuaVirtualMachine()->compile();
        
        njli::World::getInstance()->getWorldLuaVirtualMachine()->loadFile("scripts/main.lua");
        //    njli::World::getInstance()->getWorldLuaVirtualMachine()->loadFile("scripts/TestMain.lua");
        njli::World::getInstance()->getWorldLuaVirtualMachine()->compile();
    }
void NJLIGameEngine::update(float step)
{
    BT_PROFILE("Game update");
    njli::World::getInstance()->update(step, 3);
}

void NJLIGameEngine::render() { njli::World::getInstance()->render(); }

void NJLIGameEngine::destroy() { njli::World::destroyInstance(); }

void NJLIGameEngine::setTouch(const void* touch, const int index,
    const unsigned long num_touches)
{
    //    DEBUG_LOG_V("Game.cpp", "set_touch(%s)\n", "?");
    njli::World::getInstance()->getWorldInput()->setTouch(touch,
                                                          index,
                                                          num_touches);
}
//void NJLIGameEngine::setTouch(const int x, const int y, const int index,
//    const unsigned long num_touches, float scaleFactor)
//{
//    //    DEBUG_LOG_V("Game.cpp", "set_touch(%d, %d, %d, %d, %f)\n", x, y, index,
//    //    num_touches, scaleFactor);
//    int xx = (x < 0)
//        ? 0
//        : ((x > njli::World::getInstance()->getViewportDimensions().x())
//                  ? njli::World::getInstance()->getViewportDimensions().x()
//                  : x);
//    int yy = (y < 0)
//        ? 0
//        : ((y > njli::World::getInstance()->getViewportDimensions().y())
//                  ? njli::World::getInstance()->getViewportDimensions().y()
//                  : y);
//
//    njli::World::getInstance()->getWorldInput()->setTouch(
//        xx, yy, index, num_touches, scaleFactor);
//}

void NJLIGameEngine::clearNodeTouches()
{
    njli::World::getInstance()->getWorldInput()->clearNodeTouches();
}

void NJLIGameEngine::touchDown()
{
    //    DEBUG_LOG_V("Game.cpp", "touch_down(%s)\n", "");
    njli::World::getInstance()->getWorldInput()->touchDown();
}
void NJLIGameEngine::touchUp()
{
    //    DEBUG_LOG_V("Game.cpp", "touch_up(%s)\n", "");
    njli::World::getInstance()->getWorldInput()->touchUp();
}
void NJLIGameEngine::touchMove()
{
    //    DEBUG_LOG_V("Game.cpp", "touch_move(%s)\n", "");
    njli::World::getInstance()->getWorldInput()->touchMove();
}
void NJLIGameEngine::touchCancelled()
{
    njli::World::getInstance()->getWorldInput()->touchCancelled();
}

    void NJLIGameEngine::willResignActive()
    {
        char buffer[256];
        sprintf(buffer, "%s", "__NJLIWorldWillResignActive");
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);
        
        if(njli::World::getInstance()->getScene())
            njli::World::getInstance()->getScene()->willResignActive();
        
        
    }
    void NJLIGameEngine::didBecomeActive()
    {
        char buffer[256];
        sprintf(buffer, "%s", "__NJLIWorldDidBecomeActive");
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);
        
        if(njli::World::getInstance()->getScene())
            njli::World::getInstance()->getScene()->didBecomeActive();
    }
    
    void NJLIGameEngine::didEnterBackground()
    {
        char buffer[256];
        sprintf(buffer, "%s", "__NJLIWorldDidEnterBackground");
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);
        
        if(njli::World::getInstance()->getScene())
            njli::World::getInstance()->getScene()->didEnterBackground();
    }
    
    void NJLIGameEngine::willEnterForeground()
    {
        char buffer[256];
        sprintf(buffer, "%s", "__NJLIWorldWillEnterForeground");
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);
        
        if(njli::World::getInstance()->getScene())
            njli::World::getInstance()->getScene()->willEnterForeground();
    }
    
    void NJLIGameEngine::willTerminate()
    {
        char buffer[256];
        sprintf(buffer, "%s", "__NJLIWorldWillTerminate");
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);
        
        if(njli::World::getInstance()->getScene())
            njli::World::getInstance()->getScene()->willTerminate();
    }
    
    void NJLIGameEngine::interrupt()
    {
        njli::World::getInstance()->getWorldSound()->enablePause();
        
        char buffer[256];
        sprintf(buffer, "%s", "__NJLIWorldInterrupt");
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);
        
        if(njli::World::getInstance()->getScene())
            njli::World::getInstance()->getScene()->interrupt();
    }
    
    void NJLIGameEngine::resumeInterrupt()
    {
        njli::World::getInstance()->getWorldSound()->enablePause(false);
        
        char buffer[256];
        sprintf(buffer, "%s", "__NJLIWorldResumeInterrupt");
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);
        
        if(njli::World::getInstance()->getScene())
            njli::World::getInstance()->getScene()->resumeInterrupt();
    }
    
//void NJLIGameEngine::pauseGame()
//{
//    njli::World::getInstance()->enablePauseGame();
//}
//
//void NJLIGameEngine::unpauseGame()
//{
//    njli::World::getInstance()->enablePauseGame(false);
//}

//void NJLIGameEngine::pauseSound()
//{
//    njli::World::getInstance()->getWorldSound()->enablePause();
//}
//
//void NJLIGameEngine::unpauseSound()
//{
//    njli::World::getInstance()->getWorldSound()->enablePause(false);
//}

void NJLIGameEngine::keyboardShow()
{
    njli::World::getInstance()->getWorldInput()->keyboardShow();
//    char buffer[256];
//    sprintf(buffer, "%s", "__NJLIWorldKeyboardShow");
//    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);
}

void NJLIGameEngine::keyboardCancel()
{
    njli::World::getInstance()->getWorldInput()->keyboardCancel();
//    char buffer[256];
//    sprintf(buffer, "%s", "__NJLIWorldKeyboardCancel");
//    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);
}

void NJLIGameEngine::keyboardReturn(const char* text)
{
    njli::World::getInstance()->getWorldInput()->keyboardReturn(text);
//    char buffer[256];
//    sprintf(buffer, "%s", "__NJLIWorldKeyboardReturn");
//
//    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer, text);
}
    
void NJLIGameEngine::receivedMemoryWarning()
{
//    njli::World::getInstance()->getWorldResourceLoader()->unLoadAll();
//    njli::World::getInstance()->getWorldFactory()->collectGarbage();
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute("__NJLIWorldReceivedMemoryWarning");
    
    if(njli::World::getInstance()->getScene())
        njli::World::getInstance()->getScene()->receivedMemoryWarning();
}
}
