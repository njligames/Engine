//
//  PhysicsConstraintGeneric6DofSpring.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 6/19/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "PhysicsConstraintGeneric6DofSpring.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsConstraintGeneric6DofSpringBuilder.h"
#define TAG "PhysicsConstraintGeneric6DofSpring.cpp"

#include "btGeneric6DofSpringConstraint.h"
#include "PhysicsWorld.h"
#include "PhysicsBody.h"

#define FORMATSTRING "{\"njli::PhysicsConstraintGeneric6DofSpring\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    PhysicsConstraintGeneric6DofSpring::PhysicsConstraintGeneric6DofSpring():
    PhysicsConstraintGeneric6Dof(),
    m_btGeneric6DofSpringConstraint(NULL)
    {
        
    }
    
    PhysicsConstraintGeneric6DofSpring::PhysicsConstraintGeneric6DofSpring(const AbstractBuilder &builder):
    PhysicsConstraintGeneric6Dof(builder),
    m_btGeneric6DofSpringConstraint(NULL)
    {
        
    }
    
    PhysicsConstraintGeneric6DofSpring::PhysicsConstraintGeneric6DofSpring(const PhysicsConstraintGeneric6DofSpring &copy):
    PhysicsConstraintGeneric6Dof(copy),
    m_btGeneric6DofSpringConstraint(NULL)
    {
        
    }
    
    PhysicsConstraintGeneric6DofSpring::~PhysicsConstraintGeneric6DofSpring()
    {
        removeConstraint();
    }
    
    PhysicsConstraintGeneric6DofSpring &PhysicsConstraintGeneric6DofSpring::operator=(const PhysicsConstraintGeneric6DofSpring &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	PhysicsConstraintGeneric6DofSpring::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsConstraintGeneric6DofSpring::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsConstraintGeneric6DofSpring::getClassName()const
    {
        return "PhysicsConstraintGeneric6DofSpring";
    }
    
    s32 PhysicsConstraintGeneric6DofSpring::getType()const
    {
        return PhysicsConstraintGeneric6DofSpring::type();
    }
    
    PhysicsConstraintGeneric6DofSpring::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsConstraintGeneric6DofSpring **PhysicsConstraintGeneric6DofSpring::createArray(const u32 size)
    {
        return (PhysicsConstraintGeneric6DofSpring**)World::getInstance()->getWorldFactory()->createArray(PhysicsConstraintGeneric6DofSpring::type(), size);
    }
    
    void PhysicsConstraintGeneric6DofSpring::destroyArray(PhysicsConstraintGeneric6DofSpring **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsConstraintGeneric6DofSpring *PhysicsConstraintGeneric6DofSpring::create()
    {
        return dynamic_cast<PhysicsConstraintGeneric6DofSpring*>(World::getInstance()->getWorldFactory()->create(PhysicsConstraintGeneric6DofSpring::type()));
    }
    
    PhysicsConstraintGeneric6DofSpring *PhysicsConstraintGeneric6DofSpring::create(const PhysicsConstraintGeneric6DofSpringBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsConstraintGeneric6DofSpring*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsConstraintGeneric6DofSpring *PhysicsConstraintGeneric6DofSpring::clone(const PhysicsConstraintGeneric6DofSpring &object)
    {
        return dynamic_cast<PhysicsConstraintGeneric6DofSpring*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsConstraintGeneric6DofSpring *PhysicsConstraintGeneric6DofSpring::copy(const PhysicsConstraintGeneric6DofSpring &object)
    {
        return dynamic_cast<PhysicsConstraintGeneric6DofSpring*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsConstraintGeneric6DofSpring::destroy(PhysicsConstraintGeneric6DofSpring *object)
    {
        if(object)
        {
            PhysicsConstraint::destroy(object);
        }
    }
    
    void PhysicsConstraintGeneric6DofSpring::load(PhysicsConstraintGeneric6DofSpring &object, lua_State *L, int index)
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
                PhysicsConstraintGeneric6DofSpring::load(object, L, -2);
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
    
    u32 PhysicsConstraintGeneric6DofSpring::type()
    {
        return JLI_OBJECT_TYPE_PhysicsConstraintGeneric6DofSpring;
    }
    
    void PhysicsConstraintGeneric6DofSpring::setNodes(Node *nodeA, Node *nodeB, const btTransform& frameInA, const btTransform& frameInB , bool useLinearReferenceFrameA)
    {
        DEBUG_ASSERT(nodeA || nodeB);
        
        if(nodeA && !nodeA->getPhysicsBody()->isDynamicPhysics())
            DEBUG_LOG_W(TAG, "%s", nodeA->getName());
        
        if(nodeB && !nodeB->getPhysicsBody()->isDynamicPhysics())
            DEBUG_LOG_W(TAG, "%s", nodeB->getName());
        
        if(nodeA)
            DEBUG_ASSERT(nodeA->getPhysicsBody());
        
        if(nodeB)
            DEBUG_ASSERT(nodeB->getPhysicsBody());
        
        btRigidBody *rigidBodyA = NULL;
        btRigidBody *rigidBodyB = NULL;
        
        if(nodeA)
            rigidBodyA = dynamic_cast<btRigidBody*>(nodeA->getPhysicsBody()->getCollisionObject());
        
        if(nodeB)
            rigidBodyB = dynamic_cast<btRigidBody*>(nodeB->getPhysicsBody()->getCollisionObject());
        
        removeConstraint();
        
        if (rigidBodyA && !rigidBodyB)
        {
            m_btGeneric6DofSpringConstraint = new btGeneric6DofSpringConstraint(*rigidBodyB, frameInB, useLinearReferenceFrameA);
        }
        else if (rigidBodyA && rigidBodyB)
        {
            m_btGeneric6DofSpringConstraint = new btGeneric6DofSpringConstraint(*rigidBodyA, *rigidBodyB, frameInA, frameInB, useLinearReferenceFrameA);
        }
        
        if(rigidBodyA)
            getNodeA()->getPhysicsBody()->setPhysicsConstraint(this);
        if(rigidBodyB)
            getNodeB()->getPhysicsBody()->setPhysicsConstraint(this);
        
//        Scene *scene = njli::World::getInstance()->getScene();
        Scene *scene = getParent()->getParent()->getCurrentScene();
        scene->getPhysicsWorld()->addConstraint(this);
        
    }
    
    void PhysicsConstraintGeneric6DofSpring::setNodes(Node *nodeB, const btTransform& frameInB, bool useLinearReferenceFrameB)
    {
        setNodes(NULL, nodeB, frameInB, frameInB, useLinearReferenceFrameB);
    }
    
    void PhysicsConstraintGeneric6DofSpring::enableSpring(int index, bool onOff)
    {
        btGeneric6DofSpringConstraint *constraint = dynamic_cast<btGeneric6DofSpringConstraint*>(getConstraint());
        constraint->enableSpring(index, onOff);
    }
    
    void PhysicsConstraintGeneric6DofSpring::setStiffness(int index, f32 stiffness)
    {
        btGeneric6DofSpringConstraint *constraint = dynamic_cast<btGeneric6DofSpringConstraint*>(getConstraint());
        constraint->setStiffness(index, stiffness);
    }
    
    void PhysicsConstraintGeneric6DofSpring::setDamping(int index, f32 damping)
    {
        btGeneric6DofSpringConstraint *constraint = dynamic_cast<btGeneric6DofSpringConstraint*>(getConstraint());
        constraint->setDamping(index, damping);
    }
    
    void PhysicsConstraintGeneric6DofSpring::setEquilibriumPoint()
    {
        btGeneric6DofSpringConstraint *constraint = dynamic_cast<btGeneric6DofSpringConstraint*>(getConstraint());
        constraint->setEquilibriumPoint();
    }
    
    void PhysicsConstraintGeneric6DofSpring::setEquilibriumPoint(int index)
    {
        btGeneric6DofSpringConstraint *constraint = dynamic_cast<btGeneric6DofSpringConstraint*>(getConstraint());
        constraint->setEquilibriumPoint(index);
    }
    
    void PhysicsConstraintGeneric6DofSpring::setEquilibriumPoint(int index, f32 val)
    {
        btGeneric6DofSpringConstraint *constraint = dynamic_cast<btGeneric6DofSpringConstraint*>(getConstraint());
        constraint->setEquilibriumPoint(index, val);
    }
    
    void PhysicsConstraintGeneric6DofSpring::setAxis( const btVector3& axis1, const btVector3& axis2)
    {
        btGeneric6DofSpringConstraint *constraint = dynamic_cast<btGeneric6DofSpringConstraint*>(getConstraint());
        constraint->setAxis(axis1, axis1);
    }
    
    btTypedConstraint *PhysicsConstraintGeneric6DofSpring::getConstraint()
    {
        DEBUG_ASSERT(m_btGeneric6DofSpringConstraint);
        return m_btGeneric6DofSpringConstraint;
    }
    
    const btTypedConstraint *PhysicsConstraintGeneric6DofSpring::getConstraint()const
    {
        DEBUG_ASSERT(m_btGeneric6DofSpringConstraint);
        return m_btGeneric6DofSpringConstraint;
    }
    
    void PhysicsConstraintGeneric6DofSpring::removeConstraint()
    {
        PhysicsConstraint::removeConstraint();
        
        if(m_btGeneric6DofSpringConstraint)
            delete m_btGeneric6DofSpringConstraint;
        m_btGeneric6DofSpringConstraint = NULL;
    }
}
