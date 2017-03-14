//
//  WorldStateMachine.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 12/6/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "WorldStateMachine.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "WorldStateMachineBuilder.h"
#define FORMATSTRING "{\"njli::WorldStateMachine\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    WorldStateMachine::WorldStateMachine():
    AbstractStateMachine<void>()
    {
        
    }
    
    WorldStateMachine::WorldStateMachine(const AbstractBuilder &builder):
    AbstractStateMachine<void>(builder)
    {
        
    }
    
    WorldStateMachine::WorldStateMachine(const WorldStateMachine &copy):
    AbstractStateMachine<void>(copy)
    {
        
    }
    
    WorldStateMachine::~WorldStateMachine()
    {
        
    }
    
    WorldStateMachine &WorldStateMachine::operator=(const WorldStateMachine &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	WorldStateMachine::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void WorldStateMachine::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *WorldStateMachine::getClassName()const
    {
        return "WorldStateMachine";
    }
    
    s32 WorldStateMachine::getType()const
    {
        return WorldStateMachine::type();
    }
    
    WorldStateMachine::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    WorldStateMachine **WorldStateMachine::createArray(const u32 size)
    {
        return (WorldStateMachine**)World::getInstance()->getWorldFactory()->createArray(WorldStateMachine::type(), size);
    }
    
    void WorldStateMachine::destroyArray(WorldStateMachine **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    WorldStateMachine *WorldStateMachine::create()
    {
        return dynamic_cast<WorldStateMachine*>(World::getInstance()->getWorldFactory()->create(WorldStateMachine::type()));
    }
    
    WorldStateMachine *WorldStateMachine::create(const WorldStateMachineBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<WorldStateMachine*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    WorldStateMachine *WorldStateMachine::clone(const WorldStateMachine &object)
    {
        return dynamic_cast<WorldStateMachine*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    WorldStateMachine *WorldStateMachine::copy(const WorldStateMachine &object)
    {
        return dynamic_cast<WorldStateMachine*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void WorldStateMachine::destroy(WorldStateMachine *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void WorldStateMachine::load(WorldStateMachine &object, lua_State *L, int index)
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
                WorldStateMachine::load(object, L, -2);
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
    
    u32 WorldStateMachine::type()
    {
        return JLI_OBJECT_TYPE_WorldStateMachine;
    }
}