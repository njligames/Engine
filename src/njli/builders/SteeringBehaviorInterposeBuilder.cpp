//
//  SteeringBehaviorInterposeBuilder.cpp
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 5/5/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#pragma mark Implementation

#include "SteeringBehaviorInterposeBuilder.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#define TAG "SteeringBehaviorInterposeBuilder.cpp"
#define FORMATSTRING "{\"jli::SteeringBehaviorInterposeBuilder\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    SteeringBehaviorInterposeBuilder::SteeringBehaviorInterposeBuilder()
    {
    }
    
    SteeringBehaviorInterposeBuilder::SteeringBehaviorInterposeBuilder(const SteeringBehaviorInterposeBuilder &copy)
    {
        
    }
    
    SteeringBehaviorInterposeBuilder::~SteeringBehaviorInterposeBuilder()
    {
    }
    
    SteeringBehaviorInterposeBuilder &SteeringBehaviorInterposeBuilder::operator=(const SteeringBehaviorInterposeBuilder &rhs)
    {
        if (this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	SteeringBehaviorInterposeBuilder::calculateSerializeBufferSize() const
    {
        return 0;
    }
    
    void SteeringBehaviorInterposeBuilder::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        
    }
    
    u32 SteeringBehaviorInterposeBuilder::getObjectType()const
    {
        return JLI_OBJECT_TYPE_SteeringBehaviorInterposeBuilder;
    }
    
    const char *SteeringBehaviorInterposeBuilder::getClassName()const
    {
        return "SteeringBehaviorInterposeBuilder";
    }
    
    s32 SteeringBehaviorInterposeBuilder::getType()const
    {
        return SteeringBehaviorInterposeBuilder::type();
    }
    
    SteeringBehaviorInterposeBuilder::operator std::string() const
    {
        //TODO: implement to string...
        
        std::string s = string_format("%s", FORMATSTRING);
        
        JsonJLI *json = JsonJLI::create();
        s = json->parse(s.c_str());
        JsonJLI::destroy(json);
        
        return s;
    }
    
    SteeringBehaviorInterposeBuilder **SteeringBehaviorInterposeBuilder::createArray(const u32 size)
    {
        return (SteeringBehaviorInterposeBuilder**)World::getInstance()->getWorldFactory()->createArray(SteeringBehaviorInterposeBuilder::type(), size);
    }
    
    void SteeringBehaviorInterposeBuilder::destroyArray(SteeringBehaviorInterposeBuilder **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    SteeringBehaviorInterposeBuilder *SteeringBehaviorInterposeBuilder::create()
    {
        return dynamic_cast<SteeringBehaviorInterposeBuilder*>(World::getInstance()->getWorldFactory()->create(SteeringBehaviorInterposeBuilder::type()));
    }
    
    SteeringBehaviorInterposeBuilder *SteeringBehaviorInterposeBuilder::clone(const SteeringBehaviorInterposeBuilder &object)
    {
        return dynamic_cast<SteeringBehaviorInterposeBuilder*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    void SteeringBehaviorInterposeBuilder::destroy(SteeringBehaviorInterposeBuilder *object)
    {
        World::getInstance()->getWorldFactory()->destroy(object);
    }
    
    void SteeringBehaviorInterposeBuilder::load(SteeringBehaviorInterposeBuilder &object, lua_State *L, int index)
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
                SteeringBehaviorInterposeBuilder::load(object, L, -2);
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
                    //                    jli::AbstractFactoryObject *object = static_cast<jli::AbstractFactoryObject*>(usr->ptr);
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
    
    u32 SteeringBehaviorInterposeBuilder::type()
    {
        return JLI_OBJECT_TYPE_SteeringBehaviorInterposeBuilder;
    }
}
