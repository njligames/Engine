#ifndef __NJLIGameEngine__
#define __NJLIGameEngine__

namespace njli {
class NJLIGameEngine {
public:
    static bool isIOS();
    static bool isANDROID();
    static bool isEMSCRIPTEN();
    static bool isMACOSX();
    static bool isTVOS();

    static bool create(const char* deviceName, bool initLua = true);
//    static bool create(int x, int y, int width, int height, int orientation, const char* deviceName, bool initLua = true);
    static void resize(int x, int y, int width, int height, int orientation);
    
    static void start();
    static void update(float step);
    static void render();
    static void destroy();

    static void setTouch(const void* touch, const int index, const unsigned long num_touches);
//    static void setTouch(const int x, const int y, const int index, const unsigned long num_touches, float scaleFactor);

    static void clearNodeTouches();

    static void touchDown();
    static void touchUp();
    static void touchMove();
    static void touchCancelled();

    static void willResignActive();
    static void didBecomeActive();
    static void didEnterBackground();
    static void willEnterForeground();
    static void willTerminate();
    static void interrupt();
    static void resumeInterrupt();
    
//    static void pauseGame();
//    static void unpauseGame();
//
//    static void pauseSound();
//    static void unpauseSound();

    static void keyboardShow();
    static void keyboardCancel();
    static void keyboardReturn(const char* text);
    
    static void receivedMemoryWarning();

    enum PlatformID {
        PlatformID_iOS = 0,
        PlatformID_Android,
        PlatformID_Emscripten,
        PlatformID_MacOSx,
        PlatformID_tvOS
    };

    static PlatformID platformID();

protected:
private:
};
}

#endif
