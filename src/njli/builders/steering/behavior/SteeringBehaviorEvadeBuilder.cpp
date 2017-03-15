//
//  SteeringBehaviorEvadeBuilder.cpp
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 5/5/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#pragma mark Implementation

#include "SteeringBehaviorEvadeBuilder.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#define TAG "SteeringBehaviorEvadeBuilder.cpp"
#define FORMATSTRING "{\"jli::SteeringBehaviorEvadeBuilder\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    SteeringBehaviorEvadeBuilder::SteeringBehaviorEvadeBuilder()
    {
    }
    
    SteeringBehaviorEvadeBuilder::SteeringBehaviorEvadeBuilder(const SteeringBehaviorEvadeBuilder &copy)
    {
        
    }
    
    SteeringBehaviorEvadeBuilder::~SteeringBehaviorEvadeBuilder()
    {
    }
    
    SteeringBehaviorEvadeBuilder &SteeringBehaviorEvadeBuilder::operator=(const SteeringBehaviorEvadeBuilder &rhs)
    {
        if (this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	SteeringBehaviorEvadeBuilder::calculateSerializeBufferSize() const
    {
        return 0;
    }
    
    void SteeringBehaviorEvadeBuilder::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        
    }
    
    u32 SteeringBehaviorEvadeBuilder::getObjectType()const
    {
        return JLI_OBJECT_TYPE_SteeringBehaviorEvadeBuilder;
    }
    
    const char *SteeringBehaviorEvadeBuilder::getClassName()const
    {
        return "SteeringBehaviorEvadeBuilder";
    }
    
    s32 SteeringBehaviorEvadeBuilder::getType()const
    {
        return SteeringBehaviorEvadeBuilder::type();
    }
    
    SteeringBehaviorEvadeBuilder::operator std::string() const
    {
        //TODO: implement to string...
        
        std::string s = string_format("%s", FORMATSTRING);
        
        JsonJLI *json = JsonJLI::create();
        s = json->parse(s.c_str());
        JsonJLI::destroy(json);
        
        return s;
    }
    
    SteeringBehaviorEvadeBuilder **SteeringBehaviorEvadeBuilder::createArray(const u32 size)
    {
        return (SteeringBehaviorEvadeBuilder**)World::getInstance()->getWorldFactory()->createArray(SteeringBehaviorEvadeBuilder::type(), size);
    }
    
    void SteeringBehaviorEvadeBuilder::destroyArray(SteeringBehaviorEvadeBuilder **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    SteeringBehaviorEvadeBuilder *SteeringBehaviorEvadeBuilder::create()
    {
        return dynamic_cast<SteeringBehaviorEvadeBuilder*>(World::getInstance()->getWorldFactory()->create(SteeringBehaviorEvadeBuilder::type()));
    }
    
    SteeringBehaviorEvadeBuilder *SteeringBehaviorEvadeBuilder::clone(const SteeringBehaviorEvadeBuilder &object)
    {
        return dynamic_cast<SteeringBehaviorEvadeBuilder*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    void SteeringBehaviorEvadeBuilder::destroy(SteeringBehaviorEvadeBuilder *object)
    {
        World::getInstance()->getWorldFactory()->destroy(object);
    }
    
    void SteeringBehaviorEvadeBuilder::load(SteeringBehaviorEvadeBuilder &object, lua_State *L, int index)
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
                SteeringBehaviorEvadeBuilder::load(object, L, -2);
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
    
    u32 SteeringBehaviorEvadeBuilder::type()
    {
        return JLI_OBJECT_TYPE_SteeringBehaviorEvadeBuilder;
    }
}
