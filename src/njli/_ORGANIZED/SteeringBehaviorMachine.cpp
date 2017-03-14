//
//  SteeringBehaviorMachine.cpp
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 5/6/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#pragma mark Implementation

#include "SteeringBehaviorMachine.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "SteeringBehaviorMachineBuilder.h"
#define TAG "SteeringBehaviorMachine.cpp"

#define FORMATSTRING "{\"jli::SteeringBehaviorMachine\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "SteeringBehavior.h"
#include "btVector3.h"

namespace njli
{
    SteeringBehaviorMachine::SteeringBehaviorMachine():
    AbstractFactoryObject(this),
    m_CurrentForce(new btVector3(0,0,0)),
    m_CurrentVelocity(new btVector3(0,0,0)),
    m_HeadingVector(new btVector3(0,0,0)),
    m_MaxSpeed(std::numeric_limits<f32>::max()),
    m_MaxForce(sqrt(std::numeric_limits<f32>::max())),
    m_MaxForce2(std::numeric_limits<f32>::max())
    {
        
    }
    
    SteeringBehaviorMachine::SteeringBehaviorMachine(const AbstractBuilder &builder):
    AbstractFactoryObject(this),
    m_CurrentForce(new btVector3(0,0,0)),
    m_CurrentVelocity(new btVector3(0,0,0)),
    m_HeadingVector(new btVector3(0,0,0)),
    m_MaxSpeed(std::numeric_limits<f32>::max()),
    m_MaxForce(sqrt(std::numeric_limits<f32>::max())),
    m_MaxForce2(std::numeric_limits<f32>::max())
    {
        
    }
    
    SteeringBehaviorMachine::SteeringBehaviorMachine(const SteeringBehaviorMachine &copy):
    AbstractFactoryObject(this),
    m_CurrentForce(new btVector3(*(copy.m_CurrentForce))),
    m_CurrentVelocity(new btVector3(*(copy.m_CurrentVelocity))),
    m_HeadingVector(new btVector3(*(copy.m_HeadingVector))),
    m_MaxSpeed(copy.m_MaxSpeed),
    m_MaxForce(copy.m_MaxForce),
    m_MaxForce2(copy.m_MaxForce2)
    {
        
    }
    
    SteeringBehaviorMachine::~SteeringBehaviorMachine()
    {
        delete m_HeadingVector;
        m_HeadingVector = NULL;
        
        delete m_CurrentVelocity;
        m_CurrentVelocity = NULL;
        
        delete m_CurrentForce;
        m_CurrentForce = NULL;
    }
    
    SteeringBehaviorMachine &SteeringBehaviorMachine::operator=(const SteeringBehaviorMachine &rhs)
    {
        if(this != &rhs)
        {
            m_MaxSpeed = rhs.m_MaxSpeed;
            m_MaxForce = rhs.m_MaxForce;
            m_MaxForce2 = rhs.m_MaxForce2;
            *m_HeadingVector = *(rhs.m_HeadingVector);
            *m_CurrentVelocity = *(rhs.m_CurrentVelocity);
            *m_CurrentForce = *(rhs.m_CurrentForce);
        }
        
        return *this;
    }
    
    s32	SteeringBehaviorMachine::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void SteeringBehaviorMachine::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *SteeringBehaviorMachine::getClassName()const
    {
        return "SteeringBehaviorMachine";
    }
    
    s32 SteeringBehaviorMachine::getType()const
    {
        return SteeringBehaviorMachine::type();
    }
    
    SteeringBehaviorMachine::operator std::string() const
    {
        //TODO: implement to string...
        
        std::string s = string_format("%s", FORMATSTRING);
        
        JsonJLI *json = JsonJLI::create();
        s = json->parse(s.c_str());
        JsonJLI::destroy(json);
        
        return s;
    }
    
    SteeringBehaviorMachine **SteeringBehaviorMachine::createArray(const u32 size)
    {
        return (SteeringBehaviorMachine**)World::getInstance()->getWorldFactory()->createArray(SteeringBehaviorMachine::type(), size);
    }
    
    void SteeringBehaviorMachine::destroyArray(SteeringBehaviorMachine **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    SteeringBehaviorMachine *SteeringBehaviorMachine::create()
    {
        return dynamic_cast<SteeringBehaviorMachine*>(World::getInstance()->getWorldFactory()->create(SteeringBehaviorMachine::type()));
    }
    
    SteeringBehaviorMachine *SteeringBehaviorMachine::create(const SteeringBehaviorMachineBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<SteeringBehaviorMachine*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    SteeringBehaviorMachine *SteeringBehaviorMachine::clone(const SteeringBehaviorMachine &object)
    {
        return dynamic_cast<SteeringBehaviorMachine*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    SteeringBehaviorMachine *SteeringBehaviorMachine::copy(const SteeringBehaviorMachine &object)
    {
        return dynamic_cast<SteeringBehaviorMachine*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void SteeringBehaviorMachine::destroy(SteeringBehaviorMachine *object)
    {
        World::getInstance()->getWorldFactory()->destroy(object);
    }
    
    void SteeringBehaviorMachine::load(SteeringBehaviorMachine &object, lua_State *L, int index)
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
                SteeringBehaviorMachine::load(object, L, -2);
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
    
    u32 SteeringBehaviorMachine::type()
    {
        return JLI_OBJECT_TYPE_SteeringBehaviorMachine;
    }
    
    Node* SteeringBehaviorMachine::getParent()
    {
        return dynamic_cast<Node*>(AbstractDecorator::getParent());
    }
    const Node* SteeringBehaviorMachine::getParent() const
    {
        return dynamic_cast<const Node*>(AbstractDecorator::getParent());
    }
    
    const btVector3 &SteeringBehaviorMachine::getCalculatedForce()const
    {
        return *m_CurrentForce;
    }
    
    bool SteeringBehaviorMachine::setHeuristic(SteeringBehavior *steeringBehavior, f32 heuristic)
    {
        bool retVal = false;
        
        removeSteeringBehavior(steeringBehavior);
        retVal = addSteeringBehavior(steeringBehavior, heuristic);
        
        return retVal;
    }
    
    f32 SteeringBehaviorMachine::getHeuristic(SteeringBehavior *steeringBehavior)const
    {
        f32 heuristic = 0;
        SteeringMap::const_iterator iter = m_SteeringBehaviorMap.find(steeringBehavior);
        
        if(iter != m_SteeringBehaviorMap.end())
        {
            heuristic = iter->second;
        }
        
        return heuristic;
    }
    
    bool SteeringBehaviorMachine::addSteeringBehavior(SteeringBehavior *steeringBehavior, f32 heuristic)
    {
        DEBUG_ASSERT(NULL != steeringBehavior);
        
        SteeringMap::const_iterator iter = m_SteeringBehaviorMap.find(steeringBehavior);
        
        if(iter != m_SteeringBehaviorMap.end())
        {
            m_SteeringBehaviorMap.insert(SteeringPair(steeringBehavior, heuristic));
            addChild(steeringBehavior);
            return true;
        }
        
        return false;
    }
    
    bool SteeringBehaviorMachine::removeSteeringBehavior(SteeringBehavior * steeringBehavior)
    {
        DEBUG_ASSERT(NULL != steeringBehavior);
        
        SteeringMap::const_iterator iter = m_SteeringBehaviorMap.find(steeringBehavior);
        
        if(iter != m_SteeringBehaviorMap.end())
        {
            m_SteeringBehaviorMap.erase(iter);
            removeChild(iter->first);
            return true;
        }
        
        return false;
    }
    
    void SteeringBehaviorMachine::removeAllSteeringBehaviors()
    {
        for(SteeringMap::iterator iter = m_SteeringBehaviorMap.begin();
            iter != m_SteeringBehaviorMap.end();
            ++iter)
        {
            removeChild(iter->first);
        }
        m_SteeringBehaviorMap.clear();
    }
    
    u64 SteeringBehaviorMachine::numberOfSteeringBehaviors() const
    {
        return m_SteeringBehaviorMap.size();
    }
    
    
    void SteeringBehaviorMachine::getSteeringBehaviors(std::vector<SteeringBehavior*> & steeringBehaviors) const
    {
        for(SteeringMap::const_iterator iter = m_SteeringBehaviorMap.begin();
            iter != m_SteeringBehaviorMap.end();
            ++iter)
        {
            steeringBehaviors.push_back(iter->first);
        }
    }
    
    void SteeringBehaviorMachine::setMaxSpeed(const f32 speed)
    {
        DEBUG_WARN_WRITE(speed > 0, "Speed must be greater than 0");
        
        m_MaxSpeed = speed;
    }
    
    f32 SteeringBehaviorMachine::getMaxSpeed()const
    {
        return m_MaxSpeed;
    }
    
    void SteeringBehaviorMachine::setMaxForce(const f32 speed)
    {
        DEBUG_WARN_WRITE(speed > 0, "Speed must be greater than 0");
        
        m_MaxForce = speed;
        m_MaxForce2 = m_MaxForce * m_MaxForce;
    }
    
    f32 SteeringBehaviorMachine::getMaxForce()const
    {
        return m_MaxForce;
    }
    
    const btVector3 &SteeringBehaviorMachine::getHeadingVector()const
    {
        return *m_HeadingVector;
    }
    
    f32 SteeringBehaviorMachine::getMaxForce2()const
    {
        return m_MaxForce2;
    }
    
    void SteeringBehaviorMachine::setCalculatedForce(const btVector3 &force)
    {
        *m_CurrentForce = force;
    }
    
    const btVector3 &SteeringBehaviorMachine::calculate(f32 timestep)
    {
        *m_CurrentForce = calculateSteeringForce();
        
        Node *node = getParent();
        
        if(node)
        {
            f32 mass = 1.0f;
            if(node->getPhysicsBody() &&
               node->getPhysicsBody()->isKinematicPhysics())
            {
                mass = node->getPhysicsBody()->getMass();
            }
            else
            {
#if defined(DEBUG) || defined(_DEBUG)
                if(node->getPhysicsBody() && !node->getPhysicsBody()->isKinematicPhysics())
                    DEBUG_LOG_WRITE_W(TAG, "The PhysicsBody needs to be Kinematic for steering.");
#endif
            }
            
            btVector3 acceleration((*m_CurrentForce) / mass);
           
            *m_CurrentVelocity = (*m_CurrentVelocity) + acceleration * timestep;
            
            if(m_CurrentVelocity->length() > getMaxSpeed())
                *m_CurrentVelocity = m_CurrentVelocity->normalized() * getMaxSpeed();
            
            node->setOrigin(node->getOrigin() + (*m_CurrentVelocity) * timestep);
            
            if(m_CurrentVelocity->length() > 0.00000001)
            {
                *m_HeadingVector = m_CurrentVelocity->normalized();
            }
        }
        
        return *m_CurrentForce;
    }
}
