//
//  SkinnerBuilder.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 1/8/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "SkinnerBuilder.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#define FORMATSTRING "{\"njli::SkinnerBuilder\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    SkinnerBuilder::SkinnerBuilder()
    {
    }
    
    SkinnerBuilder::SkinnerBuilder(const SkinnerBuilder &copy)
    {
        
    }
    
    SkinnerBuilder::~SkinnerBuilder()
    {
    }
    
    SkinnerBuilder &SkinnerBuilder::operator=(const SkinnerBuilder &rhs)
    {
        if (this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	SkinnerBuilder::calculateSerializeBufferSize() const
    {
        return 0;
    }
    
    void SkinnerBuilder::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        
    }
    
    u32 SkinnerBuilder::getObjectType()const
    {
        return JLI_OBJECT_TYPE_Skinner;
    }
    
    const char *SkinnerBuilder::getClassName()const
    {
        return "SkinnerBuilder";
    }
    
    s32 SkinnerBuilder::getType()const
    {
        return SkinnerBuilder::type();
    }
    
    SkinnerBuilder::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    SkinnerBuilder **SkinnerBuilder::createArray(const u32 size)
    {
        return (SkinnerBuilder**)World::getInstance()->getWorldFactory()->createArray(SkinnerBuilder::type(), size);
    }
    
    void SkinnerBuilder::destroyArray(SkinnerBuilder **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    SkinnerBuilder *SkinnerBuilder::create()
    {
        return dynamic_cast<SkinnerBuilder*>(World::getInstance()->getWorldFactory()->create(SkinnerBuilder::type()));
    }
    
    SkinnerBuilder *SkinnerBuilder::clone(const SkinnerBuilder &object)
    {
        return dynamic_cast<SkinnerBuilder*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    void SkinnerBuilder::destroy(SkinnerBuilder *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void SkinnerBuilder::load(SkinnerBuilder &object, lua_State *L, int index)
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
                SkinnerBuilder::load(object, L, -2);
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
    
    u32 SkinnerBuilder::type()
    {
        return JLI_OBJECT_TYPE_SkinnerBuilder;
    }
}
