//
//  PhysicsCloseContact.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 1/8/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "PhysicsCloseContact.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsCloseContactBuilder.h"
#define FORMATSTRING "{\"njli::PhysicsCloseContact\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    PhysicsCloseContact::PhysicsCloseContact():
    AbstractFactoryObject(this)
    {
        
    }
    
    PhysicsCloseContact::PhysicsCloseContact(const AbstractBuilder &builder):
    AbstractFactoryObject(this)
    {
        
    }
    
    PhysicsCloseContact::PhysicsCloseContact(const PhysicsCloseContact &copy):
    AbstractFactoryObject(this)
    {
        
    }
    
    PhysicsCloseContact::~PhysicsCloseContact()
    {
        
    }
    
    PhysicsCloseContact &PhysicsCloseContact::operator=(const PhysicsCloseContact &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	PhysicsCloseContact::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsCloseContact::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsCloseContact::getClassName()const
    {
        return "PhysicsCloseContact";
    }
    
    s32 PhysicsCloseContact::getType()const
    {
        return PhysicsCloseContact::type();
    }
    
    PhysicsCloseContact::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsCloseContact **PhysicsCloseContact::createArray(const u32 size)
    {
        return (PhysicsCloseContact**)World::getInstance()->getWorldFactory()->createArray(PhysicsCloseContact::type(), size);
    }
    
    void PhysicsCloseContact::destroyArray(PhysicsCloseContact **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsCloseContact *PhysicsCloseContact::create()
    {
        return dynamic_cast<PhysicsCloseContact*>(World::getInstance()->getWorldFactory()->create(PhysicsCloseContact::type()));
    }
    
    PhysicsCloseContact *PhysicsCloseContact::create(const PhysicsCloseContactBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsCloseContact*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsCloseContact *PhysicsCloseContact::clone(const PhysicsCloseContact &object)
    {
        return dynamic_cast<PhysicsCloseContact*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsCloseContact *PhysicsCloseContact::copy(const PhysicsCloseContact &object)
    {
        return dynamic_cast<PhysicsCloseContact*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsCloseContact::destroy(PhysicsCloseContact *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void PhysicsCloseContact::load(PhysicsCloseContact &object, lua_State *L, int index)
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
                PhysicsCloseContact::load(object, L, -2);
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
    
    u32 PhysicsCloseContact::type()
    {
        return JLI_OBJECT_TYPE_PhysicsCloseContact;
    }
}
