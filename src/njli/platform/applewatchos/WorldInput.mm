//
//  WorldInput.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 1/30/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "WorldInput.h"
#include "JLIFactoryTypes.h"
#include "DeviceTouch.h"
#include "World.h"
#import <UIKit/UIKit.h>
//#import "GameViewController.h"

#define FORMATSTRING "{\"njli::WorldInput\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    WorldInput::WorldInput():
    m_AllTouches(new njli::DeviceTouch*[njli::DeviceTouch::MAX_TOUCHES]),
    m_CurrentTouches(new njli::DeviceTouch*[njli::DeviceTouch::MAX_TOUCHES]),
    m_NumTouches(0),
    m_Orientation(0)
    {
        for (u32 i = 0; i < njli::DeviceTouch::MAX_TOUCHES; ++i)
        {
            m_AllTouches[i] = new njli::DeviceTouch();
        }
        clearTouches();
    }
    
    WorldInput::~WorldInput()
    {
        for (u32 i = 0; i < njli::DeviceTouch::MAX_TOUCHES; ++i)
        {
            delete m_AllTouches[i];
        }
        delete [] m_AllTouches;
        delete [] m_CurrentTouches;
    }
    
    const char *WorldInput::getClassName()const
    {
        return "WorldInput";
    }
    
    s32 WorldInput::getType()const
    {
        return JLI_OBJECT_TYPE_WorldInput;
    }
    
    WorldInput::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    DeviceTouch * WorldInput::getTouch(const s32 index)
    {
        if (index >= 0 && index < DeviceTouch::MAX_TOUCHES)
        {
            return m_CurrentTouches[index];
        }
        return NULL;
    }
    
    const DeviceTouch * WorldInput::getTouch(const s32 index)const
    {
        if (index >= 0 && index < DeviceTouch::MAX_TOUCHES)
        {
            return m_CurrentTouches[index];
        }
        return NULL;
    }
    
    s32 WorldInput::numberOfTouches()const
    {
        return m_NumTouches;
    }
    
//    void WorldInput::resetTouches()
//    {
//        m_NumTouches = 0;
//    }
    
    void WorldInput::setTouch(const void *touch, const int index, const int num_touches)
    {
        m_CurrentTouches[index] = m_AllTouches[index];
        m_CurrentTouches[index]->set(touch, index, num_touches);
        m_NumTouches = num_touches;
    }
    void WorldInput::setTouch(const int x, const int y, const int index, const int num_touches, float scaleFactor)
    {
        m_CurrentTouches[index] = m_AllTouches[index];
        m_CurrentTouches[index]->set(x, y, index, num_touches, scaleFactor);
        m_NumTouches = num_touches;
    }
    
    void WorldInput::clearNodeTouches()
    {
        clearTouches();
        if(njli::World::getInstance()->getScene())
            njli::World::getInstance()->getScene()->clearNodeTouches();
    }
    
    void WorldInput::touchDown()
    {
        njli::World::getInstance()->touchDown(m_CurrentTouches);
//        clearTouches();
    }
    void WorldInput::touchUp()
    {
        njli::World::getInstance()->touchUp(m_CurrentTouches);
//        clearTouches();
    }
    void WorldInput::touchMove()
    {
        njli::World::getInstance()->touchMove(m_CurrentTouches);
//        clearTouches();
    }
    void WorldInput::touchCancelled()
    {
        njli::World::getInstance()->touchCancelled(m_CurrentTouches);
//        clearTouches();
    }
    
    
    
    void WorldInput::keyboardShow()
    {
        njli::World::getInstance()->keyboardShow();
    }
    
    void WorldInput::keyboardCancel()
    {
        njli::World::getInstance()->keyboardCancel();
    }
    
    void WorldInput::keyboardReturn(const char* text)
    {
        njli::World::getInstance()->keyboardReturn(text);
    }
    
    void WorldInput::setOrientation(const s32 orientation)
    {
        m_Orientation = orientation;
    }
    
    bool WorldInput::isPortraitOrientation()const
    {
        return (((UIInterfaceOrientation)m_Orientation == UIInterfaceOrientationPortrait) || ((UIInterfaceOrientation)m_Orientation == UIInterfaceOrientationPortraitUpsideDown));
    }
    
    bool WorldInput::isLandscapeOrientation()const
    {
        return (((UIInterfaceOrientation)m_Orientation == UIInterfaceOrientationLandscapeLeft) || ((UIInterfaceOrientation)m_Orientation == UIInterfaceOrientationLandscapeRight));
    }
    
    s32 WorldInput::getOrientation()const
    {
        return m_Orientation;
    }
    
    void WorldInput::showKeyboard(const char *currentText)
    {
//        id<UIApplicationDelegate> appDelegate = [[UIApplication sharedApplication] delegate];
//        GameViewController *viewController = (GameViewController*)appDelegate.window.rootViewController;
//        [viewController showKeyboard:[NSString stringWithCString:currentText encoding:NSUTF8StringEncoding]];
    }
    
    void WorldInput::clearTouches()
    {
        for (u32 i = 0; i < njli::DeviceTouch::MAX_TOUCHES; ++i)
        {
            m_CurrentTouches[i] = NULL;
        }
    }
}
