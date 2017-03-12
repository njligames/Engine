//
//  Clock.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "Clock.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "ClockBuilder.h"

#define FORMATSTRING "{\"njli::Clock\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    Clock::Clock():
    AbstractFactoryObject(this),
    AbstractClock(),
    m_btClock(new btClock())
    {
        m_btClock->reset();
    }
    
    Clock::Clock(const AbstractBuilder &builder):
    AbstractFactoryObject(this),
    AbstractClock(),
    m_btClock(new btClock())
    {
        m_btClock->reset();
    }
    
    Clock::Clock(const Clock &copy):
    AbstractFactoryObject(this),
    AbstractClock(copy),
    m_btClock(new btClock())
    {
        m_btClock->reset();
    }
    
    Clock::~Clock()
    {
        delete m_btClock;
        m_btClock = NULL;
    }
    
    Clock &Clock::operator=(const Clock &rhs)
    {
        if(this != &rhs)
        {
            AbstractClock::operator=(rhs);
            
            delete m_btClock;
            
            m_btClock = new btClock;
        }
        return *this;
    }
    
    s32	Clock::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void Clock::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *Clock::getClassName()const
    {
        return "Clock";
    }
    
    s32 Clock::getType()const
    {
        return Clock::type();
    }
    
    Clock::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    Clock **Clock::createArray(const u32 size)
    {
        return (Clock**)World::getInstance()->getWorldFactory()->createArray(Clock::type(), size);
    }
    
    void Clock::destroyArray(Clock **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    Clock *Clock::create()
    {
        return dynamic_cast<Clock*>(World::getInstance()->getWorldFactory()->create(Clock::type()));
    }
    
    Clock *Clock::create(const ClockBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<Clock*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    Clock *Clock::clone(const Clock &object)
    {
        return dynamic_cast<Clock*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    Clock *Clock::copy(const Clock &object)
    {
        return dynamic_cast<Clock*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void Clock::destroy(Clock *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void Clock::load(Clock &object, lua_State *L, int index)
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
                Clock::load(object, L, -2);
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
    
    u32 Clock::type()
    {
        return JLI_OBJECT_TYPE_Clock;
    }
    void Clock::update(f64 milliseconds)
    {
        BT_PROFILE("Clock::update");
    }
    
    void Clock::reset()
    {
        m_btClock->reset();
    }
    
    unsigned long int Clock::getTimeMilliseconds()
    {
        return m_btClock->getTimeMilliseconds();
    }
    
    unsigned long int Clock::getTimeMicroseconds()
    {
        return m_btClock->getTimeMicroseconds();
    }
}
