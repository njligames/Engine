//
//  Light.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "Light.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "LightBuilder.h"
#define FORMATSTRING "{\"njli::Light\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    Light::Light():
    AbstractFactoryObject(this)
    {
        
    }
    
    Light::Light(const AbstractBuilder &builder):
    AbstractFactoryObject(this)
    {
        
    }
    
    Light::Light(const Light &copy):
    AbstractFactoryObject(this)
    {
        
    }
    
    Light::~Light()
    {
        
    }
    
    Light &Light::operator=(const Light &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	Light::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void Light::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *Light::getClassName()const
    {
        return "Light";
    }
    
    s32 Light::getType()const
    {
        return Light::type();
    }
    
    Light::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    Light **Light::createArray(const u32 size)
    {
        return (Light**)World::getInstance()->getWorldFactory()->createArray(Light::type(), size);
    }
    
    void Light::destroyArray(Light **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    Light *Light::create()
    {
        return dynamic_cast<Light*>(World::getInstance()->getWorldFactory()->create(Light::type()));
    }
    
    Light *Light::create(const LightBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<Light*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    Light *Light::clone(const Light &object)
    {
        return dynamic_cast<Light*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    Light *Light::copy(const Light &object)
    {
        return dynamic_cast<Light*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void Light::destroy(Light *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void Light::load(Light &object, lua_State *L, int index)
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
                Light::load(object, L, -2);
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
    
    u32 Light::type()
    {
        return JLI_OBJECT_TYPE_Light;
    }
}
