//
//  PhysicsConstraint.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 6/15/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "PhysicsConstraint.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsConstraintBuilder.h"
#include "Node.h"
#include "btRigidBody.h"

#define TAG "PhysicsConstraint.cpp"
#define FORMATSTRING "{\"njli::PhysicsConstraint\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "PhysicsBody.h"
#include "PhysicsWorld.h"

namespace njli
{
    PhysicsConstraint::PhysicsConstraint():
    AbstractFactoryObject(this)
    {
        
    }
    
    PhysicsConstraint::PhysicsConstraint(const AbstractBuilder &builder):
    AbstractFactoryObject(this)
    {
        
    }
    
    PhysicsConstraint::PhysicsConstraint(const PhysicsConstraint &copy):
    AbstractFactoryObject(this)
    {
        
    }
    
    PhysicsConstraint::~PhysicsConstraint()
    {
        
    }
    
    PhysicsConstraint &PhysicsConstraint::operator=(const PhysicsConstraint &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	PhysicsConstraint::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsConstraint::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsConstraint::getClassName()const
    {
        return "PhysicsConstraint";
    }
    
    s32 PhysicsConstraint::getType()const
    {
        return JLI_OBJECT_TYPE_PhysicsConstraint;
    }
    
    PhysicsConstraint::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsConstraint **PhysicsConstraint::createArray(const u32 size)
    {
        return (PhysicsConstraint**)World::getInstance()->getWorldFactory()->createArray(PhysicsConstraint::type(), size);
    }
    
    void PhysicsConstraint::destroyArray(PhysicsConstraint **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsConstraint *PhysicsConstraint::create()
    {
        return dynamic_cast<PhysicsConstraint*>(World::getInstance()->getWorldFactory()->create(PhysicsConstraint::type()));
    }
    
    PhysicsConstraint *PhysicsConstraint::create(const PhysicsConstraintBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsConstraint*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsConstraint *PhysicsConstraint::clone(const PhysicsConstraint &object)
    {
        return dynamic_cast<PhysicsConstraint*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsConstraint *PhysicsConstraint::copy(const PhysicsConstraint &object)
    {
        return dynamic_cast<PhysicsConstraint*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsConstraint::destroy(PhysicsConstraint *object)
    {
        if(object)
        {
            object->removeConstraint();
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void PhysicsConstraint::load(PhysicsConstraint &object, lua_State *L, int index)
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
                PhysicsConstraint::load(object, L, -2);
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
    
    u32 PhysicsConstraint::type()
    {
        return JLI_OBJECT_TYPE_PhysicsConstraint;
    }
    
    Node *PhysicsConstraint::getNodeA()
    {
        btTypedConstraint *constraint = getConstraint();
        if(constraint)
        {
            btRigidBody *rigidBody = &constraint->getRigidBodyA();
            if(rigidBody)
            {
                return static_cast<Node*>(rigidBody->getUserPointer());
            }
        }
        return NULL;
    }
    
    const Node *PhysicsConstraint::getNodeA()const
    {
        const btTypedConstraint *constraint = getConstraint();
        if(constraint)
        {
            const btRigidBody *rigidBody = &constraint->getRigidBodyA();
            if(rigidBody)
            {
                return static_cast<const Node*>(rigidBody->getUserPointer());
            }
        }
        return NULL;
    }
    
    Node *PhysicsConstraint::getNodeB()
    {
        btTypedConstraint *constraint = getConstraint();
        
        if(constraint)
        {
            btRigidBody *rigidBody = &constraint->getRigidBodyB();
            if(rigidBody)
            {
                return static_cast<Node*>(rigidBody->getUserPointer());
            }
        }
        return NULL;
    }
    
    const Node *PhysicsConstraint::getNodeB()const
    {
        const btTypedConstraint *constraint = getConstraint();
        if(constraint)
        {
            const btRigidBody *rigidBody = &constraint->getRigidBodyB();
            if(rigidBody)
            {
                return static_cast<const Node*>(rigidBody->getUserPointer());
            }
        }
        
        return NULL;
    }
    
    f32 PhysicsConstraint::getBreakingImpulseThreshold()const
    {
        return getConstraint()->getBreakingImpulseThreshold();
    }
    
    void PhysicsConstraint::setBreakingImpulseThreshold(f32 impulse)
    {
        getConstraint()->setBreakingImpulseThreshold(impulse);
    }
    
    bool PhysicsConstraint::isConstraintEnabled()const
    {
        return getConstraint()->isEnabled();
    }
    
    void PhysicsConstraint::enableConstraint(bool enable)
    {
        getConstraint()->setEnabled(enable);
    }
    
    btVector3 PhysicsConstraint::getJointAppliedForceA()const
    {
        return getConstraint()->getJointFeedback()->m_appliedForceBodyA;
    }
    
    btVector3 PhysicsConstraint::getJointAppliedTorqueA()const
    {
        return getConstraint()->getJointFeedback()->m_appliedTorqueBodyA;
    }
    
    btVector3 PhysicsConstraint::getJointAppliedForceB()const
    {
        return getConstraint()->getJointFeedback()->m_appliedForceBodyB;
    }
    
    btVector3 PhysicsConstraint::getJointAppliedTorqueB()const
    {
        return getConstraint()->getJointFeedback()->m_appliedTorqueBodyB;
    }
    
    PhysicsBody *PhysicsConstraint::getParent()
    {
        return dynamic_cast<PhysicsBody*>(AbstractDecorator::getParent());
    }
    
    const PhysicsBody *PhysicsConstraint::getParent()const
    {
        return dynamic_cast<const PhysicsBody*>(AbstractDecorator::getParent());
    }
    
    void PhysicsConstraint::removeConstraint()
    {
        Node *_nodeA = getNodeA();
        if(_nodeA)
        {
            PhysicsBody *body = _nodeA->getPhysicsBody();
            if (body)
            {
                body->removePhysicsConstraint(this);
            }
        }
        
        Node *_nodeB = getNodeB();
        if(_nodeB)
        {
            PhysicsBody *body = _nodeB->getPhysicsBody();
            if (body)
            {
                body->removePhysicsConstraint(this);
            }
        }
        
        Scene *scene = getParent()->getParent()->getCurrentScene();
        scene->getPhysicsWorld()->removeConstraint(this);
    }
    
//    void PhysicsConstraint::setNodes(Node *nodeA, Node *nodeB)
//    {
//        if(nodeA && !nodeA->getPhysicsBody()->isDynamicPhysics())
//            DEBUG_LOG_W(TAG, "%s", nodeA->getName());
//        
//        if(nodeB && !nodeB->getPhysicsBody()->isDynamicPhysics())
//            DEBUG_LOG_W(TAG, "%s", nodeB->getName());
//    }
}
