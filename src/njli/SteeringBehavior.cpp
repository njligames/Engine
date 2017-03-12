//
//  SteeringBehavior.cpp
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 5/5/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#pragma mark Implementation

#include "SteeringBehavior.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "SteeringBehaviorBuilder.h"

#define TAG "SteeringBehavior.cpp"

#include "SteeringBehaviorMachine.h"

#define FORMATSTRING "{\"jli::SteeringBehavior\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    SteeringBehavior::SteeringBehavior():
    AbstractFactoryObject(this),
    m_CurrentForce(new btVector3(0,0,0))
    {
        
    }
    
    SteeringBehavior::SteeringBehavior(const AbstractBuilder &builder):
    AbstractFactoryObject(this),
    m_CurrentForce(new btVector3(0,0,0))
    {
        
    }
    
    SteeringBehavior::SteeringBehavior(const SteeringBehavior &copy):
    AbstractFactoryObject(this),
    m_CurrentForce(new btVector3(*copy.m_CurrentForce))
    {
        
    }
    
    SteeringBehavior::~SteeringBehavior()
    {
        delete m_CurrentForce;
    }
    
    SteeringBehavior &SteeringBehavior::operator=(const SteeringBehavior &rhs)
    {
        if(this != &rhs)
        {
            *m_CurrentForce = *(rhs.m_CurrentForce);
        }
        return *this;
    }
    
    s32	SteeringBehavior::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void SteeringBehavior::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *SteeringBehavior::getClassName()const
    {
        return "SteeringBehavior";
    }
    
    s32 SteeringBehavior::getType()const
    {
        return SteeringBehavior::type();
    }
    
    SteeringBehavior::operator std::string() const
    {
        //TODO: implement to string...
        
        std::string s = string_format("%s", FORMATSTRING);
        
        JsonJLI *json = JsonJLI::create();
        s = json->parse(s.c_str());
        JsonJLI::destroy(json);
        
        return s;
    }
    
    SteeringBehavior **SteeringBehavior::createArray(const u32 size)
    {
        return (SteeringBehavior**)World::getInstance()->getWorldFactory()->createArray(SteeringBehavior::type(), size);
    }
    
    void SteeringBehavior::destroyArray(SteeringBehavior **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    SteeringBehavior *SteeringBehavior::create()
    {
        return dynamic_cast<SteeringBehavior*>(World::getInstance()->getWorldFactory()->create(SteeringBehavior::type()));
    }
    
    SteeringBehavior *SteeringBehavior::create(const SteeringBehaviorBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<SteeringBehavior*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    SteeringBehavior *SteeringBehavior::clone(const SteeringBehavior &object)
    {
        return dynamic_cast<SteeringBehavior*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    SteeringBehavior *SteeringBehavior::copy(const SteeringBehavior &object)
    {
        return dynamic_cast<SteeringBehavior*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void SteeringBehavior::destroy(SteeringBehavior *object)
    {
        World::getInstance()->getWorldFactory()->destroy(object);
    }
    
    void SteeringBehavior::load(SteeringBehavior &object, lua_State *L, int index)
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
                SteeringBehavior::load(object, L, -2);
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
    
    u32 SteeringBehavior::type()
    {
        return JLI_OBJECT_TYPE_SteeringBehavior;
    }
    
    const btVector3 &SteeringBehavior::getCurrentForce()const
    {
        return *m_CurrentForce;
    }
    
    s32 SteeringBehavior::addTarget(Node *target)
    {
        DEBUG_ASSERT(NULL != target);
        
        
        TargetVector::const_iterator iter = std::find(m_TargetList.begin(), m_TargetList.end(), target);
        
        if(iter == m_TargetList.end())
        {
            TargetVector::iterator iter = std::find(m_TargetList.begin(), m_TargetList.end(), target);
            
            if(iter != m_TargetList.end())
                removeTarget(target);
            
            m_TargetList.push_back(target);
            
            addChild(target);
        }
        
        return getTargetIndex(target);
    }
    
    bool SteeringBehavior::removeTarget(Node * target)
    {
        DEBUG_ASSERT(NULL != target);
        
        TargetVector::iterator iter = std::find(m_TargetList.begin(), m_TargetList.end(), target);
        
        if(iter != m_TargetList.end())
        {
            removeChild(*iter);
            m_TargetList.erase(iter);
            return true;
        }
        return false;
    }
    
    void SteeringBehavior::removeAllTargets()
    {
        for(TargetVector::iterator iter = m_TargetList.begin();
            iter != m_TargetList.end();
            ++iter)
        {
            removeChild(*iter);
        }
        m_TargetList.clear();
    }
    
    s32 SteeringBehavior::numberOfTargets() const
    {
        return m_TargetList.size();
    }
    
    
    void SteeringBehavior::getTargets(std::vector<Node*> & targets) const
    {
        for(TargetVector::const_iterator iter = m_TargetList.begin();
            iter != m_TargetList.end();
            ++iter)
        {
            if(getChildIndex(*iter) != -1)
                targets.push_back(*iter);
        }
    }
    
    s32 SteeringBehavior::getTargetIndex(Node * target) const
    {
        TargetVector::const_iterator iter = std::find(m_TargetList.begin(), m_TargetList.end(), target);
        
        if (iter != m_TargetList.end())
        {
            return std::distance(m_TargetList.begin(), iter);
        }
        return -1;
    }
    
    Node* SteeringBehavior::getTarget(const u32 index)
    {
        if (index < m_TargetList.size())
        {
            s32 idx = getChildIndex(m_TargetList.at(index));
            if(idx != -1)
                return dynamic_cast<Node*>(getChild(idx));
        }
        return NULL;
    }
    
    const Node* SteeringBehavior::getTarget(const u32 index) const
    {
        if (index < m_TargetList.size())
        {
            s32 idx = getChildIndex(m_TargetList.at(index));
            if(idx != -1)
                return dynamic_cast<const Node*>(getChild(idx));
        }
        return NULL;
    }
    
    void SteeringBehavior::setCurrentForce(const btVector3 &force)
    {
        *m_CurrentForce = force;
    }
    
    bool SteeringBehavior::hasOwner()const
    {
        return (getParent() &&
                getParent()->getParent());
    }
    
    btVector3 SteeringBehavior::getOwnerPosition()const
    {
        btVector3 pos(0,0,0);
        if(hasOwner())
            pos = getParent()->getParent()->getOrigin();
        return pos;
    }
    
    btVector3 SteeringBehavior::getAverageTargetPosition()const
    {
        if(numberOfTargets() > 0)
        {
            btVector3 target(0,0,0);
            
            for(TargetVector::const_iterator i = m_TargetList.begin();
                i != m_TargetList.end();
                i++)
            {
                target += (*i)->getOrigin();
            }
            
            return (target / numberOfTargets());
        }
        
        return btVector3(0,0,0);
    }
    
    SteeringBehaviorMachine* SteeringBehavior::getParent()
    {
        return dynamic_cast<SteeringBehaviorMachine*>(AbstractDecorator::getParent());
    }
    const SteeringBehaviorMachine* SteeringBehavior::getParent() const
    {
        return dynamic_cast<const SteeringBehaviorMachine*>(AbstractDecorator::getParent());
    }
}
