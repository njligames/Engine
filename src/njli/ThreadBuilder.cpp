//
//  ThreadBuilder.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 10/1/15.
//  Copyright © 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "ThreadBuilder.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#define TAG "ThreadBuilder.cpp"
#define FORMATSTRING "{\"njli::ThreadBuilder\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    ThreadBuilder::ThreadBuilder()
    {
    }
    
    ThreadBuilder::ThreadBuilder(const ThreadBuilder &copy)
    {
        
    }
    
    ThreadBuilder::~ThreadBuilder()
    {
    }
    
    ThreadBuilder &ThreadBuilder::operator=(const ThreadBuilder &rhs)
    {
        if (this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	ThreadBuilder::calculateSerializeBufferSize() const
    {
        return 0;
    }
    
    void ThreadBuilder::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        
    }
    
    u32 ThreadBuilder::getObjectType()const
    {
        return JLI_OBJECT_TYPE_ThreadBuilder;
    }
    
    const char *ThreadBuilder::getClassName()const
    {
        return "ThreadBuilder";
    }
    
    s32 ThreadBuilder::getType()const
    {
        return ThreadBuilder::type();
    }
    
    ThreadBuilder::operator std::string() const
    {
        //TODO: implement to string...
        
        std::string s = string_format("%s", FORMATSTRING);
        
        njli::JsonJLI *json = njli::JsonJLI::create();
        s = json->parse(s.c_str());
        njli::JsonJLI::destroy(json);
        
        return s;
    }
    
    ThreadBuilder **ThreadBuilder::createArray(const u32 size)
    {
        return (ThreadBuilder**)World::getInstance()->getWorldFactory()->createArray(ThreadBuilder::type(), size);
    }
    
    void ThreadBuilder::destroyArray(ThreadBuilder **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    ThreadBuilder *ThreadBuilder::create()
    {
        return dynamic_cast<ThreadBuilder*>(World::getInstance()->getWorldFactory()->create(ThreadBuilder::type()));
    }
    
    ThreadBuilder *ThreadBuilder::clone(const ThreadBuilder &object)
    {
        return dynamic_cast<ThreadBuilder*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    void ThreadBuilder::destroy(ThreadBuilder *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void ThreadBuilder::load(ThreadBuilder &object, lua_State *L, int index)
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
                ThreadBuilder::load(object, L, -2);
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
    
    u32 ThreadBuilder::type()
    {
        return JLI_OBJECT_TYPE_ThreadBuilder;
    }
}
