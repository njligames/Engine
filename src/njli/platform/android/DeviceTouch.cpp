//
//  DeviceTouch.mm
//  JLIGameEngineTest
//
//  Created by James Folk on 12/8/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "DeviceTouch.h"
// #include <UIKit/UIKit.h>
#include "JLIFactoryTypes.h"
#include "World.h"
#include <jni.h>

namespace njli {
const u8 DeviceTouch::MAX_TOUCHES = 5;

void DeviceTouch::convert(DeviceTouch& t, const void* _touch)
{
    if (_touch) {
        // UITouch *touch = (__bridge UITouch*)_touch;
        // CGFloat scaleFactor = touch.view.contentScaleFactor;
        // t.setTimeStampFrame(touch.timestamp);
        // CGPoint p = [touch locationInView:touch.view];
        // m_xpos = (p.x * scaleFactor);
        // m_ypos = njli::World::getInstance()->getViewportDimensions().y() - (p.y * scaleFactor);
        // p = [touch previousLocationInView:touch.view];
        // m_prev_xpos = (p.x * scaleFactor);
        // m_prev_ypos = njli::World::getInstance()->getViewportDimensions().y() - (p.y * scaleFactor);
        // t.m_address = [touch hash];
        // t.m_tapCount = [touch tapCount];
    }
}
}
