//
//  SteeringBehaviorMachineWeighted.cpp
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 5/6/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#pragma mark Implementation

#include "SteeringBehaviorMachineWeighted.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "SteeringBehaviorMachineWeightedBuilder.h"
#define TAG "SteeringBehaviorMachineWeighted.cpp"

#define FORMATSTRING "{\"jli::SteeringBehaviorMachineWeighted\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "SteeringBehavior.h"
#include "btVector3.h"

namespace njli
{
    SteeringBehaviorMachineWeighted::SteeringBehaviorMachineWeighted():
    SteeringBehaviorMachine()
    {
        
    }
    
    SteeringBehaviorMachineWeighted::SteeringBehaviorMachineWeighted(const AbstractBuilder &builder):
    SteeringBehaviorMachine(builder)
    {
        
    }
    
    SteeringBehaviorMachineWeighted::SteeringBehaviorMachineWeighted(const SteeringBehaviorMachineWeighted &copy):
    SteeringBehaviorMachine(copy)
    {
        
    }
    
    SteeringBehaviorMachineWeighted::~SteeringBehaviorMachineWeighted()
    {
        
    }
    
    SteeringBehaviorMachineWeighted &SteeringBehaviorMachineWeighted::operator=(const SteeringBehaviorMachineWeighted &rhs)
    {
        if(this != &rhs)
        {
            
        }
        
        return *this;
    }
    
    s32	SteeringBehaviorMachineWeighted::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void SteeringBehaviorMachineWeighted::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *SteeringBehaviorMachineWeighted::getClassName()const
    {
        return "SteeringBehaviorMachineWeighted";
    }
    
    s32 SteeringBehaviorMachineWeighted::getType()const
    {
        return SteeringBehaviorMachineWeighted::type();
    }
    
    SteeringBehaviorMachineWeighted::operator std::string() const
    {
        //TODO: implement to string...
        
        std::string s = string_format("%s", FORMATSTRING);
        
        JsonJLI *json = JsonJLI::create();
        s = json->parse(s.c_str());
        JsonJLI::destroy(json);
        
        return s;
    }
    
    SteeringBehaviorMachineWeighted **SteeringBehaviorMachineWeighted::createArray(const u32 size)
    {
        return (SteeringBehaviorMachineWeighted**)World::getInstance()->getWorldFactory()->createArray(SteeringBehaviorMachineWeighted::type(), size);
    }
    
    void SteeringBehaviorMachineWeighted::destroyArray(SteeringBehaviorMachineWeighted **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    SteeringBehaviorMachineWeighted *SteeringBehaviorMachineWeighted::create()
    {
        return dynamic_cast<SteeringBehaviorMachineWeighted*>(World::getInstance()->getWorldFactory()->create(SteeringBehaviorMachineWeighted::type()));
    }
    
    SteeringBehaviorMachineWeighted *SteeringBehaviorMachineWeighted::create(const SteeringBehaviorMachineWeightedBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<SteeringBehaviorMachineWeighted*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    SteeringBehaviorMachineWeighted *SteeringBehaviorMachineWeighted::clone(const SteeringBehaviorMachineWeighted &object)
    {
        return dynamic_cast<SteeringBehaviorMachineWeighted*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    SteeringBehaviorMachineWeighted *SteeringBehaviorMachineWeighted::copy(const SteeringBehaviorMachineWeighted &object)
    {
        return dynamic_cast<SteeringBehaviorMachineWeighted*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void SteeringBehaviorMachineWeighted::destroy(SteeringBehaviorMachineWeighted *object)
    {
        World::getInstance()->getWorldFactory()->destroy(object);
    }
    
    void SteeringBehaviorMachineWeighted::load(SteeringBehaviorMachineWeighted &object, lua_State *L, int index)
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
                SteeringBehaviorMachineWeighted::load(object, L, -2);
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
    
    u32 SteeringBehaviorMachineWeighted::type()
    {
        return JLI_OBJECT_TYPE_SteeringBehaviorMachineWeighted;
    }
    
    const btVector3 &SteeringBehaviorMachineWeighted::calculateSteeringForce()
    {
        btVector3 force(0,0,0);
        
        for(SteeringMap::iterator iter = m_SteeringBehaviorMap.begin();
            iter != m_SteeringBehaviorMap.end();
            ++iter)
        {
            force += (iter->first->calculateForce() * iter->second);
        }
        
        if(force.length2() > getMaxForce2())
            this->setCalculatedForce(force.normalized() * getMaxForce());
        else
            this->setCalculatedForce(force);
        
        return getCalculatedForce();
    }
    
}
