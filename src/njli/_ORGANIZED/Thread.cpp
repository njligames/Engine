//
//  Thread.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 10/1/15.
//  Copyright © 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "Thread.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "ThreadBuilder.h"
#define TAG "Thread.cpp"

#define FORMATSTRING "{\"njli::Thread\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    Thread::Thread():
    AbstractFactoryObject(this),
    m_state(SIO2_PAUSE)
    {
        
    }
    
    Thread::Thread(const AbstractBuilder &builder):
    AbstractFactoryObject(this),
    m_state(SIO2_PAUSE)
    {
        
    }
    
    Thread::Thread(const Thread &copy):
    AbstractFactoryObject(this),
    m_JLIthreadcallback(copy.m_JLIthreadcallback),
    m_priority(copy.m_priority),
    m_userdata(copy.m_userdata),
    m_state(SIO2_PAUSE)
    {
        
    }
    
    Thread::~Thread()
    {
        stop();
        
        while( m_state != SIO2_STOP )
        { njliSleep( 1 ); }
        
        pthread_join( m_thread, NULL );
    }
    
    Thread &Thread::operator=(const Thread &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	Thread::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void Thread::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *Thread::getClassName()const
    {
        return "Thread";
    }
    
    s32 Thread::getType()const
    {
        return Thread::type();
    }
    
    Thread::operator std::string() const
    {
        //TODO: implement to string...
        
        std::string s = string_format("%s", FORMATSTRING);
        
        njli::JsonJLI *json = njli::JsonJLI::create();
        s = json->parse(s.c_str());
        njli::JsonJLI::destroy(json);
        
        return s;
    }
    
    Thread **Thread::createArray(const u32 size)
    {
        return (Thread**)World::getInstance()->getWorldFactory()->createArray(Thread::type(), size);
    }
    
    void Thread::destroyArray(Thread **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    Thread *Thread::create()
    {
        return dynamic_cast<Thread*>(World::getInstance()->getWorldFactory()->create(Thread::type()));
    }
    
    Thread *Thread::create(const ThreadBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<Thread*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    Thread *Thread::clone(const Thread &object)
    {
        return dynamic_cast<Thread*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    Thread *Thread::copy(const Thread &object)
    {
        return dynamic_cast<Thread*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void Thread::destroy(Thread *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void Thread::load(Thread &object, lua_State *L, int index)
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
                Thread::load(object, L, -2);
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
    
    u32 Thread::type()
    {
        return JLI_OBJECT_TYPE_Thread;
    }
    
    void Thread::setup(const std::string &luaFunctionName, int _priority)
    {
        
    }
    
    void Thread::enablePause(bool enable)
    {
        m_state = (enable)?SIO2_PLAY:SIO2_PAUSE;
    }
    
    bool Thread::isPaused()const
    {
        return m_state == SIO2_PAUSE;
    }
    
    void Thread::stop()
    {
        m_state = SIO2_STOP;
    }
    
    void Thread::run()
    {
        struct sched_param param;
        
        param.sched_priority = m_priority;
        pthread_setschedparam( m_thread, SCHED_RR, &param );
        
        enablePause();
        
        while( m_state )
        {
            if( m_state == SIO2_PLAY )
            {
                m_JLIthreadcallback( m_userdata );
            }
            
            njliSleep( 1 );
        }
    }
    
    extern "C" void* call_func( void *f )
    {
        std::auto_ptr< wrap > w( static_cast< wrap* >( f ) );
        w->ins.run();
        
        return 0;
    }
    
    void Thread::setup(JLIthreadcallback *_JLIthreadcallback, void *_userdata,int _priority)
    {
        m_JLIthreadcallback = _JLIthreadcallback;
        m_priority			 = _priority;
        m_userdata			 = _userdata;
        
        wrap* w = new wrap( Thread(*this) );
        
        
        w->ins.m_thread_hdl = pthread_create( &w->ins.m_thread, NULL, call_func, w );
        
        while( w->ins.m_state != SIO2_PAUSE )
        { njliSleep( 1 ); }
    }
}
