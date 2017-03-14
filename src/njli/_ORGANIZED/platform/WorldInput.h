//
//  WorldInput.h
//  JLIGameEngineTest
//
//  Created by James Folk on 1/30/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__WorldInput__
#define __JLIGameEngineTest__WorldInput__

#include "AbstractObject.h"
#include <string>

namespace njli {
class DeviceTouch;

class WorldInput : public AbstractObject {
public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;

    WorldInput();
    virtual ~WorldInput();

    virtual const char* getClassName() const;
    virtual s32 getType() const;
    operator std::string() const;

public:
    //TODO: fill in specific methods for WorldInput

    DeviceTouch* getTouch(const s32 index);
    const DeviceTouch* getTouch(const s32 index) const;
    s32 numberOfTouches() const;
    //        void resetTouches();

    void setTouch(const void* touch, const int index, const int num_touches);
    void setTouch(const int x, const int y, const int index, const int num_touches, float scaleFactor);

    void clearNodeTouches();

    //TODO import bullet library and pass btVector2
    void touchDown();
    void touchUp();
    void touchMove();
    void touchCancelled();
    
    void keyboardShow();
    void keyboardCancel();
    void keyboardReturn(const char* text);
    
    void setOrientation(const s32 orientation);
    bool isPortraitOrientation() const;
    bool isLandscapeOrientation() const;
    s32 getOrientation() const;

    void showKeyboard(const char* currentText);

protected:
    void clearTouches();

private:
    WorldInput(const WorldInput&);
    WorldInput& operator=(const WorldInput&);

    DeviceTouch** m_AllTouches;
    DeviceTouch** m_CurrentTouches;
    s32 m_NumTouches;
    s32 m_Orientation;
};
}

#endif /* defined(__JLIGameEngineTest__WorldInput__) */
