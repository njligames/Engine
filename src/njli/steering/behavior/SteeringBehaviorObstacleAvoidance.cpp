//
//  SteeringBehaviorObstacleAvoidance.cpp
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 5/5/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#pragma mark Implementation

#include "SteeringBehaviorObstacleAvoidance.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "SteeringBehaviorObstacleAvoidanceBuilder.h"

#define TAG "SteeringBehaviorObstacleAvoidance.cpp"

#define FORMATSTRING "{\"jli::SteeringBehaviorObstacleAvoidance\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    SteeringBehaviorObstacleAvoidance::SteeringBehaviorObstacleAvoidance():
    SteeringBehavior()
    {
        
    }
    
    SteeringBehaviorObstacleAvoidance::SteeringBehaviorObstacleAvoidance(const AbstractBuilder &builder):
    SteeringBehavior(builder)
    {
        
    }
    
    SteeringBehaviorObstacleAvoidance::SteeringBehaviorObstacleAvoidance(const SteeringBehaviorObstacleAvoidance &copy):
    SteeringBehavior(copy)
    {
        
    }
    
    SteeringBehaviorObstacleAvoidance::~SteeringBehaviorObstacleAvoidance()
    {
        
    }
    
    SteeringBehaviorObstacleAvoidance &SteeringBehaviorObstacleAvoidance::operator=(const SteeringBehaviorObstacleAvoidance &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	SteeringBehaviorObstacleAvoidance::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void SteeringBehaviorObstacleAvoidance::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *SteeringBehaviorObstacleAvoidance::getClassName()const
    {
        return "SteeringBehaviorObstacleAvoidance";
    }
    
    s32 SteeringBehaviorObstacleAvoidance::getType()const
    {
        return SteeringBehaviorObstacleAvoidance::type();
    }
    
    SteeringBehaviorObstacleAvoidance::operator std::string() const
    {
        //TODO: implement to string...
        
        std::string s = string_format("%s", FORMATSTRING);
        
        JsonJLI *json = JsonJLI::create();
        s = json->parse(s.c_str());
        JsonJLI::destroy(json);
        
        return s;
    }
    
    SteeringBehaviorObstacleAvoidance **SteeringBehaviorObstacleAvoidance::createArray(const u32 size)
    {
        return (SteeringBehaviorObstacleAvoidance**)World::getInstance()->getWorldFactory()->createArray(SteeringBehaviorObstacleAvoidance::type(), size);
    }
    
    void SteeringBehaviorObstacleAvoidance::destroyArray(SteeringBehaviorObstacleAvoidance **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    SteeringBehaviorObstacleAvoidance *SteeringBehaviorObstacleAvoidance::create()
    {
        return dynamic_cast<SteeringBehaviorObstacleAvoidance*>(World::getInstance()->getWorldFactory()->create(SteeringBehaviorObstacleAvoidance::type()));
    }
    
    SteeringBehaviorObstacleAvoidance *SteeringBehaviorObstacleAvoidance::create(const SteeringBehaviorObstacleAvoidanceBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<SteeringBehaviorObstacleAvoidance*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    SteeringBehaviorObstacleAvoidance *SteeringBehaviorObstacleAvoidance::clone(const SteeringBehaviorObstacleAvoidance &object)
    {
        return dynamic_cast<SteeringBehaviorObstacleAvoidance*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    SteeringBehaviorObstacleAvoidance *SteeringBehaviorObstacleAvoidance::copy(const SteeringBehaviorObstacleAvoidance &object)
    {
        return dynamic_cast<SteeringBehaviorObstacleAvoidance*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void SteeringBehaviorObstacleAvoidance::destroy(SteeringBehaviorObstacleAvoidance *object)
    {
        World::getInstance()->getWorldFactory()->destroy(object);
    }
    
    void SteeringBehaviorObstacleAvoidance::load(SteeringBehaviorObstacleAvoidance &object, lua_State *L, int index)
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
                SteeringBehaviorObstacleAvoidance::load(object, L, -2);
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
    
    u32 SteeringBehaviorObstacleAvoidance::type()
    {
        return JLI_OBJECT_TYPE_SteeringBehaviorObstacleAvoidance;
    }
    
    const btVector3 &SteeringBehaviorObstacleAvoidance::calculateForce()
    {
        DEBUG_ASSERT_WRITE(false, "TODO");
        return *m_CurrentForce;
    }
}
