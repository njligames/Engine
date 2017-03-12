//
//  StopWatch.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 1/8/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "StopWatch.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "StopWatchBuilder.h"
#define FORMATSTRING "{\"njli::StopWatch\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    StopWatch::StopWatch():
    AbstractFactoryObject(this),
    AbstractClock(),
    m_CurrentClock(new btClock()),
    m_IsStopped(false),
    m_StoppedMilliseconds(-1)
    {
        
    }
    
    StopWatch::StopWatch(const AbstractBuilder &builder):
    AbstractFactoryObject(this),
    AbstractClock(),
    m_CurrentClock(new btClock()),
    m_IsStopped(false),
    m_StoppedMilliseconds(-1)
    {
        
    }
    
    StopWatch::StopWatch(const StopWatch &copy):
    AbstractFactoryObject(this),
    AbstractClock(copy),
    m_CurrentClock(new btClock()),
    m_IsStopped(false),
    m_StoppedMilliseconds(-1)
    {
        
    }
    
    StopWatch::~StopWatch()
    {
        delete m_CurrentClock;
        m_CurrentClock = NULL;
    }
    
    StopWatch &StopWatch::operator=(const StopWatch &rhs)
    {
        if(this != &rhs)
        {
            AbstractClock::operator=(rhs);
        }
        return *this;
    }
    
    s32	StopWatch::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void StopWatch::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *StopWatch::getClassName()const
    {
        return "StopWatch";
    }
    
    s32 StopWatch::getType()const
    {
        return StopWatch::type();
    }
    
    StopWatch::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    StopWatch **StopWatch::createArray(const u32 size)
    {
        return (StopWatch**)World::getInstance()->getWorldFactory()->createArray(StopWatch::type(), size);
    }
    
    void StopWatch::destroyArray(StopWatch **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    StopWatch *StopWatch::create()
    {
        return dynamic_cast<StopWatch*>(World::getInstance()->getWorldFactory()->create(StopWatch::type()));
    }
    
    StopWatch *StopWatch::create(const StopWatchBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<StopWatch*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    StopWatch *StopWatch::clone(const StopWatch &object)
    {
        return dynamic_cast<StopWatch*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    StopWatch *StopWatch::copy(const StopWatch &object)
    {
        return dynamic_cast<StopWatch*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void StopWatch::destroy(StopWatch *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void StopWatch::load(StopWatch &object, lua_State *L, int index)
    {
        // Push another reference to the table on top of the stack (so we know
        // where it is, and this function can work for negative, positive and
        // pseudo indices
        lua_pushvalue(L, index);
        // stack now contains: -1 => table
        lua_pushnil(L);
        // stack now contains: -1 => nil; -2 => table
        while (lua_next(L, -2))
        {
            // stack now contains: -1 => value; -2 => key; -3 => table
            // copy the key so that lua_tostring does not modify the original
            lua_pushvalue(L, -2);
            // stack now contains: -1 => key; -2 => value; -3 => key; -4 => table
            const char *key = lua_tostring(L, -1);
            const char *value = lua_tostring(L, -2);
            if(lua_istable(L, -2))
            {
                StopWatch::load(object, L, -2);
            }
            else
            {
                if(lua_isnumber(L, index))
                {
                    double number = lua_tonumber(L, index);
                    printf("%s => %f\n", key, number);
                }
                else if(lua_isstring(L, index))
                {
                    const char *v = lua_tostring(L, index);
                    printf("%s => %s\n", key, v);
                }
                else if(lua_isboolean(L, index))
                {
                    bool v = lua_toboolean(L, index);
                    printf("%s => %d\n", key, v);
                }
                else if(lua_isuserdata(L, index))
                {
//                    swig_lua_userdata *usr;
//                    swig_type_info *type;
//                    assert(lua_isuserdata(L,index));
//                    usr=(swig_lua_userdata*)lua_touserdata(L,index);  /* get data */
//                    type = usr->type;
//                    njli::AbstractFactoryObject *object = static_cast<njli::AbstractFactoryObject*>(usr->ptr);
//                    printf("%s => %d:%s\n", key, object->getType(), object->getClassName());
                    
                }
            }
            // pop value + copy of key, leaving original key
            lua_pop(L, 2);
            // stack now contains: -1 => key; -2 => table
        }
        // stack now contains: -1 => table (when lua_next returns 0 it pops the key
        // but does not push anything.)
        // Pop table
        lua_pop(L, 1);
        // Stack is now the same as it was on entry to this function
    }
    
    u32 StopWatch::type()
    {
        return JLI_OBJECT_TYPE_StopWatch;
    }
    
    void StopWatch::update(f64 milliseconds)
    {
    }
    
    //TODO: fill in specific methods for StopWatch
    
    //Start or continue the current lap.
    void StopWatch::start()
    {
        m_IsStopped = false;
        m_CurrentClock->reset();
    }
    
    unsigned long int StopWatch::getMilliseconds(s32 index)
    {
        if (index < 0)
        {
            if (isStopped())
                return m_StoppedMilliseconds;
            return m_CurrentClock->getTimeMilliseconds();
        }
        else if (index < m_Laps.size())
        {
            return m_Laps.at(index);
        }
        return -1;
        
    }
    
    //stop the current lap
    //if already stopped, reset.
    void StopWatch::stop()
    {
        if (!isStopped())
        {
            m_IsStopped = true;
            m_StoppedMilliseconds = getMilliseconds();
        }
    }
    
    bool StopWatch::isStopped()const
    {
        return m_IsStopped;
    }
    
    //stop the current lap and start a new lap.
    bool StopWatch::lap()
    {
        if (!isStopped())
        {
            m_Laps.push_back(getMilliseconds());
            m_CurrentClock->reset();
            return true;
        }
        return false;
    }
    
    void StopWatch::clearLaps()
    {
        m_Laps.clear();
    }
    
    //return the current number of laps.
    u64 StopWatch::numberOfLaps()
    {
        return m_Laps.size();
    }
}