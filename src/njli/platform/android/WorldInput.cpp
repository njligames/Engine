//
//  WorldInput.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 1/30/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "DeviceTouch.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "WorldInput.h"

namespace njli {
WorldInput::WorldInput()
    : m_AllTouches(new njli::DeviceTouch*[njli::DeviceTouch::MAX_TOUCHES])
    , m_CurrentTouches(new njli::DeviceTouch*[njli::DeviceTouch::MAX_TOUCHES])
    , m_NumTouches(0)
    , m_Orientation(0)
{
    for (u32 i = 0; i < njli::DeviceTouch::MAX_TOUCHES; ++i) {
        m_AllTouches[i] = new njli::DeviceTouch();
    }
    clearTouches();
}

WorldInput::~WorldInput()
{
    for (u32 i = 0; i < njli::DeviceTouch::MAX_TOUCHES; ++i) {
        delete m_AllTouches[i];
    }
    delete[] m_AllTouches;
    delete[] m_CurrentTouches;
}

const char* WorldInput::getClassName() const
{
    return "WorldInput";
}

s32 WorldInput::getType() const
{
    return JLI_OBJECT_TYPE_WorldInput;
}

WorldInput::operator std::string() const
{
    return "TODO";
}

DeviceTouch* WorldInput::getTouch(const s32 index)
{
    if (index >= 0 && index < DeviceTouch::MAX_TOUCHES) {
        return m_CurrentTouches[index];
    }
    return NULL;
}

const DeviceTouch* WorldInput::getTouch(const s32 index) const
{
    if (index >= 0 && index < DeviceTouch::MAX_TOUCHES) {
        return m_CurrentTouches[index];
    }
    return NULL;
}

s32 WorldInput::numberOfTouches() const
{
    return m_NumTouches;
}

//    void WorldInput::resetTouches()
//    {
//        m_NumTouches = 0;
//    }

void WorldInput::setTouch(const void* touch, const int index, const int num_touches)
{
    DEBUG_LOG_V("TAG", "setTouch(%d, %d)", 0, 0);
    m_CurrentTouches[index] = m_AllTouches[index];
    m_CurrentTouches[index]->set(touch, index, num_touches);
    m_NumTouches = num_touches;
}
void WorldInput::setTouch(const int x, const int y, const int index, const int num_touches, float scaleFactor)
{
    DEBUG_LOG_V("TAG", "setTouch(%d, %d)", x, y);
    m_CurrentTouches[index] = m_AllTouches[index];
    m_CurrentTouches[index]->set(x, y, index, num_touches, scaleFactor);
    m_NumTouches = num_touches;
}

void WorldInput::clearNodeTouches()
{
    clearTouches();
    if (njli::World::getInstance()->getScene())
        njli::World::getInstance()->getScene()->clearNodeTouches();
}

void WorldInput::touchDown()
{
    DEBUG_LOG_V("TAG", "WorldInput::touchDown(%s)", "jim");
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

void WorldInput::setOrientation(const s32 orientation)
{
    m_Orientation = orientation;
}

bool WorldInput::isPortraitOrientation() const
{
    // return (((UIInterfaceOrientation)m_Orientation == UIInterfaceOrientationPortrait) || ((UIInterfaceOrientation)m_Orientation == UIInterfaceOrientationPortraitUpsideDown));
    return false;
}

bool WorldInput::isLandscapeOrientation() const
{
    // return (((UIInterfaceOrientation)m_Orientation == UIInterfaceOrientationLandscapeLeft) || ((UIInterfaceOrientation)m_Orientation == UIInterfaceOrientationLandscapeRight));
    return true;
}

s32 WorldInput::getOrientation() const
{
    return m_Orientation;
}

void WorldInput::showKeyboard(const char* currentText)
{
    DEBUG_LOG_WRITE_V("TAG", "cannot show keyboard yet on android\n");
}

void WorldInput::clearTouches()
{
    for (u32 i = 0; i < njli::DeviceTouch::MAX_TOUCHES; ++i) {
        m_CurrentTouches[i] = NULL;
    }
}
}