//
//  Timer.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 1/8/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "Timer.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "TimerBuilder.h"
#define FORMATSTRING "{\"njli::Timer\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    Timer::Timer():
    AbstractFactoryObject(this),
    m_Clock(new btClock()),
    m_CurrentTime(0),
    m_IsPaused(false)
    {
        
    }
    
    Timer::Timer(const AbstractBuilder &builder):
    AbstractFactoryObject(this),
    m_Clock(new btClock()),
    m_CurrentTime(0),
    m_IsPaused(false)
    {
        
    }
    
    Timer::Timer(const Timer &copy):
    AbstractFactoryObject(this),
    m_Clock(new btClock()),
    m_CurrentTime(0),
    m_IsPaused(false)
    {
        
    }
    
    Timer::~Timer()
    {
        delete m_Clock;
    }
    
    Timer &Timer::operator=(const Timer &rhs)
    {
        if(this != &rhs)
        {
        }
        return *this;
    }
    
    s32	Timer::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void Timer::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *Timer::getClassName()const
    {
        return "Timer";
    }
    
    s32 Timer::getType()const
    {
        return Timer::type();
    }
    
    Timer::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    Timer **Timer::createArray(const u32 size)
    {
        return (Timer**)World::getInstance()->getWorldFactory()->createArray(Timer::type(), size);
    }
    
    void Timer::destroyArray(Timer **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    Timer *Timer::create()
    {
        return dynamic_cast<Timer*>(World::getInstance()->getWorldFactory()->create(Timer::type()));
    }
    
    Timer *Timer::create(const TimerBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<Timer*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    Timer *Timer::clone(const Timer &object)
    {
        return dynamic_cast<Timer*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    Timer *Timer::copy(const Timer &object)
    {
        return dynamic_cast<Timer*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void Timer::destroy(Timer *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void Timer::load(Timer &object, lua_State *L, int index)
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
                Timer::load(object, L, -2);
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
    
    u32 Timer::type()
    {
        return JLI_OBJECT_TYPE_Timer;
    }
    
    void Timer::tick()
    {
        unsigned long int current = m_Clock->getTimeMilliseconds();
        m_Clock->reset();
        
        if(!m_IsPaused)
            m_CurrentTime -= current;
    }
    
    void Timer::start(unsigned long int total)
    {
        m_CurrentTime = total;
        enablePause(false);
    }
    
    void Timer::enablePause(bool enable)
    {
        if (!isPaused() && enable)
            tick();
        
        m_Clock->reset();
        
        m_IsPaused = enable;
    }
    
    bool Timer::isPaused()const
    {
        return m_IsPaused;
    }
    
    bool Timer::isFinished()const
    {
        return m_CurrentTime <= 0;
    }
    
    unsigned long int Timer::getTimeMillisecondsLeft()const
    {
        return m_CurrentTime;
    }
}
