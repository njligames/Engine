//
//  PhysicsWorldBuilder.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "PhysicsWorldBuilder.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#define FORMATSTRING "{\"njli::PhysicsWorldBuilder\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    PhysicsWorldBuilder::PhysicsWorldBuilder()
    {
    }
    
    PhysicsWorldBuilder::PhysicsWorldBuilder(const PhysicsWorldBuilder &copy)
    {
        
    }
    
    PhysicsWorldBuilder::~PhysicsWorldBuilder()
    {
    }
    
    PhysicsWorldBuilder &PhysicsWorldBuilder::operator=(const PhysicsWorldBuilder &rhs)
    {
        if (this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	PhysicsWorldBuilder::calculateSerializeBufferSize() const
    {
        return 0;
    }
    
    void PhysicsWorldBuilder::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        
    }
    
    u32 PhysicsWorldBuilder::getObjectType()const
    {
        return JLI_OBJECT_TYPE_PhysicsWorld;
    }
    
    const char *PhysicsWorldBuilder::getClassName()const
    {
        return "PhysicsWorldBuilder";
    }
    
    s32 PhysicsWorldBuilder::getType()const
    {
        return PhysicsWorldBuilder::type();
    }
    
    PhysicsWorldBuilder::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsWorldBuilder **PhysicsWorldBuilder::createArray(const u32 size)
    {
        return (PhysicsWorldBuilder**)World::getInstance()->getWorldFactory()->createArray(PhysicsWorldBuilder::type(), size);
    }
    
    void PhysicsWorldBuilder::destroyArray(PhysicsWorldBuilder **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsWorldBuilder *PhysicsWorldBuilder::create()
    {
        return dynamic_cast<PhysicsWorldBuilder*>(World::getInstance()->getWorldFactory()->create(PhysicsWorldBuilder::type()));
    }
    
    PhysicsWorldBuilder *PhysicsWorldBuilder::clone(const PhysicsWorldBuilder &object)
    {
        return dynamic_cast<PhysicsWorldBuilder*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    void PhysicsWorldBuilder::destroy(PhysicsWorldBuilder *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void PhysicsWorldBuilder::load(PhysicsWorldBuilder &object, lua_State *L, int index)
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
                PhysicsWorldBuilder::load(object, L, -2);
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
    
    u32 PhysicsWorldBuilder::type()
    {
        return JLI_OBJECT_TYPE_PhysicsWorldBuilder;
    }
}