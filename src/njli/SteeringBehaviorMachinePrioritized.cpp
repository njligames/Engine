//
//  SteeringBehaviorMachinePrioritized.cpp
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 5/6/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#pragma mark Implementation

#include "SteeringBehaviorMachinePrioritized.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "SteeringBehaviorMachinePrioritizedBuilder.h"
#define TAG "SteeringBehaviorMachinePrioritized.cpp"

#define FORMATSTRING "{\"jli::SteeringBehaviorMachinePrioritized\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "SteeringBehavior.h"
#include "btVector3.h"

namespace njli
{
    SteeringBehaviorMachinePrioritized::SteeringBehaviorMachinePrioritized():
    SteeringBehaviorMachine()
    {
        
    }
    
    SteeringBehaviorMachinePrioritized::SteeringBehaviorMachinePrioritized(const AbstractBuilder &builder):
    SteeringBehaviorMachine(builder)
    {
        
    }
    
    SteeringBehaviorMachinePrioritized::SteeringBehaviorMachinePrioritized(const SteeringBehaviorMachinePrioritized &copy):
    SteeringBehaviorMachine(copy)
    {
        
    }
    
    SteeringBehaviorMachinePrioritized::~SteeringBehaviorMachinePrioritized()
    {
        
    }
    
    SteeringBehaviorMachinePrioritized &SteeringBehaviorMachinePrioritized::operator=(const SteeringBehaviorMachinePrioritized &rhs)
    {
        if(this != &rhs)
        {
        }
        
        return *this;
    }
    
    s32	SteeringBehaviorMachinePrioritized::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void SteeringBehaviorMachinePrioritized::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *SteeringBehaviorMachinePrioritized::getClassName()const
    {
        return "SteeringBehaviorMachinePrioritized";
    }
    
    s32 SteeringBehaviorMachinePrioritized::getType()const
    {
        return SteeringBehaviorMachinePrioritized::type();
    }
    
    SteeringBehaviorMachinePrioritized::operator std::string() const
    {
        //TODO: implement to string...
        
        std::string s = string_format("%s", FORMATSTRING);
        
        JsonJLI *json = JsonJLI::create();
        s = json->parse(s.c_str());
        JsonJLI::destroy(json);
        
        return s;
    }
    
    SteeringBehaviorMachinePrioritized **SteeringBehaviorMachinePrioritized::createArray(const u32 size)
    {
        return (SteeringBehaviorMachinePrioritized**)World::getInstance()->getWorldFactory()->createArray(SteeringBehaviorMachinePrioritized::type(), size);
    }
    
    void SteeringBehaviorMachinePrioritized::destroyArray(SteeringBehaviorMachinePrioritized **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    SteeringBehaviorMachinePrioritized *SteeringBehaviorMachinePrioritized::create()
    {
        return dynamic_cast<SteeringBehaviorMachinePrioritized*>(World::getInstance()->getWorldFactory()->create(SteeringBehaviorMachinePrioritized::type()));
    }
    
    SteeringBehaviorMachinePrioritized *SteeringBehaviorMachinePrioritized::create(const SteeringBehaviorMachinePrioritizedBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<SteeringBehaviorMachinePrioritized*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    SteeringBehaviorMachinePrioritized *SteeringBehaviorMachinePrioritized::clone(const SteeringBehaviorMachinePrioritized &object)
    {
        return dynamic_cast<SteeringBehaviorMachinePrioritized*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    SteeringBehaviorMachinePrioritized *SteeringBehaviorMachinePrioritized::copy(const SteeringBehaviorMachinePrioritized &object)
    {
        return dynamic_cast<SteeringBehaviorMachinePrioritized*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void SteeringBehaviorMachinePrioritized::destroy(SteeringBehaviorMachinePrioritized *object)
    {
        World::getInstance()->getWorldFactory()->destroy(object);
    }
    
    void SteeringBehaviorMachinePrioritized::load(SteeringBehaviorMachinePrioritized &object, lua_State *L, int index)
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
                SteeringBehaviorMachinePrioritized::load(object, L, -2);
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
    
    u32 SteeringBehaviorMachinePrioritized::type()
    {
        return JLI_OBJECT_TYPE_SteeringBehaviorMachinePrioritized;
    }
    
    const btVector3 &SteeringBehaviorMachinePrioritized::calculateSteeringForce()
    {
        btVector3 force(0,0,0);
        
        this->setCalculatedForce(force);
        return getCalculatedForce();
    }
}
