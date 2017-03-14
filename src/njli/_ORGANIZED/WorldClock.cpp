//
//  WorldClock.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 1/8/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "WorldClock.h"
#include "JLIFactoryTypes.h"
#define FORMATSTRING "{\"njli::WorldClock\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "btQuickprof.h"

namespace njli
{
    WorldClock::WorldClock()
    {
        
    }
    
    WorldClock::~WorldClock()
    {
        
    }
    
    const char *WorldClock::getClassName()const
    {
        return "WorldClock";
    }
    
    s32 WorldClock::getType()const
    {
        return JLI_OBJECT_TYPE_WorldClock;
    }
    
    WorldClock::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    f64 WorldClock::totalMilliseconds()const
    {
        return m_TotalMilliseconds;
    }
    f32 WorldClock::timeStep()const
    {
        return m_TimeStep;
    }
    
    void WorldClock::update(f64 milliseconds)
    {
        BT_PROFILE("WorldClock::update");
        
        m_TimeStep = milliseconds;
        m_TotalMilliseconds += milliseconds;
        
//        DEBUG_LOG_V("fps", "%f",milliseconds);
    }
}