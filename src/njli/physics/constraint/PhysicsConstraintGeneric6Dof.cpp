//
//  PhysicsConstraintGeneric6Dof.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 6/19/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "PhysicsConstraintGeneric6Dof.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsConstraintGeneric6DofBuilder.h"
#define TAG "PhysicsConstraintGeneric6Dof.cpp"

#include "btGeneric6DofConstraint.h"
#include "PhysicsWorld.h"
#include "PhysicsBody.h"

#define FORMATSTRING "{\"njli::PhysicsConstraintGeneric6Dof\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    PhysicsConstraintGeneric6Dof::PhysicsConstraintGeneric6Dof():
    PhysicsConstraint(),
    m_btGeneric6DofConstraint(NULL)
    {
        
    }
    
    PhysicsConstraintGeneric6Dof::PhysicsConstraintGeneric6Dof(const AbstractBuilder &builder):
    PhysicsConstraint(builder),
    m_btGeneric6DofConstraint(NULL)
    {
        
    }
    
    PhysicsConstraintGeneric6Dof::PhysicsConstraintGeneric6Dof(const PhysicsConstraintGeneric6Dof &copy):
    PhysicsConstraint(copy),
    m_btGeneric6DofConstraint(NULL)
    {
        
    }
    
    PhysicsConstraintGeneric6Dof::~PhysicsConstraintGeneric6Dof()
    {
        removeConstraint();
    }
    
    PhysicsConstraintGeneric6Dof &PhysicsConstraintGeneric6Dof::operator=(const PhysicsConstraintGeneric6Dof &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	PhysicsConstraintGeneric6Dof::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsConstraintGeneric6Dof::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsConstraintGeneric6Dof::getClassName()const
    {
        return "PhysicsConstraintGeneric6Dof";
    }
    
    s32 PhysicsConstraintGeneric6Dof::getType()const
    {
        return PhysicsConstraintGeneric6Dof::type();
    }
    
    PhysicsConstraintGeneric6Dof::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsConstraintGeneric6Dof **PhysicsConstraintGeneric6Dof::createArray(const u32 size)
    {
        return (PhysicsConstraintGeneric6Dof**)World::getInstance()->getWorldFactory()->createArray(PhysicsConstraintGeneric6Dof::type(), size);
    }
    
    void PhysicsConstraintGeneric6Dof::destroyArray(PhysicsConstraintGeneric6Dof **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsConstraintGeneric6Dof *PhysicsConstraintGeneric6Dof::create()
    {
        return dynamic_cast<PhysicsConstraintGeneric6Dof*>(World::getInstance()->getWorldFactory()->create(PhysicsConstraintGeneric6Dof::type()));
    }
    
    PhysicsConstraintGeneric6Dof *PhysicsConstraintGeneric6Dof::create(const PhysicsConstraintGeneric6DofBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsConstraintGeneric6Dof*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsConstraintGeneric6Dof *PhysicsConstraintGeneric6Dof::clone(const PhysicsConstraintGeneric6Dof &object)
    {
        return dynamic_cast<PhysicsConstraintGeneric6Dof*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsConstraintGeneric6Dof *PhysicsConstraintGeneric6Dof::copy(const PhysicsConstraintGeneric6Dof &object)
    {
        return dynamic_cast<PhysicsConstraintGeneric6Dof*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsConstraintGeneric6Dof::destroy(PhysicsConstraintGeneric6Dof *object)
    {
        if(object)
        {
            PhysicsConstraint::destroy(object);
        }
    }
    
    void PhysicsConstraintGeneric6Dof::load(PhysicsConstraintGeneric6Dof &object, lua_State *L, int index)
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
                PhysicsConstraintGeneric6Dof::load(object, L, -2);
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
    
    u32 PhysicsConstraintGeneric6Dof::type()
    {
        return JLI_OBJECT_TYPE_PhysicsConstraintGeneric6Dof;
    }
    
    
    
    
    void PhysicsConstraintGeneric6Dof::setNodes(Node *nodeA, Node *nodeB, const btTransform& frameInA, const btTransform& frameInB ,bool useLinearReferenceFrameA)
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
            m_btGeneric6DofConstraint = new btGeneric6DofConstraint(*rigidBodyA, frameInB, useLinearReferenceFrameA);
        }
        else if (rigidBodyA && rigidBodyB)
        {
            m_btGeneric6DofConstraint = new btGeneric6DofConstraint(*rigidBodyA, *rigidBodyB, frameInA, frameInB, useLinearReferenceFrameA);
        }
        
        if(rigidBodyA)
            getNodeA()->getPhysicsBody()->setPhysicsConstraint(this);
        if(rigidBodyB)
            getNodeB()->getPhysicsBody()->setPhysicsConstraint(this);
        
//        Scene *scene = njli::World::getInstance()->getScene();
        Scene *scene = getParent()->getParent()->getCurrentScene();
        scene->getPhysicsWorld()->addConstraint(this);

    }
    
    void PhysicsConstraintGeneric6Dof::setNodes(Node *nodeB, const btTransform& frameInB, bool useLinearReferenceFrameB)
    {
        setNodes(NULL, nodeB, frameInB, frameInB, useLinearReferenceFrameB);
    }
    
    void PhysicsConstraintGeneric6Dof::calculateTransforms()
    {
        btGeneric6DofConstraint *constraint = dynamic_cast<btGeneric6DofConstraint*>(getConstraint());
        constraint->calculateTransforms();
    }
    
    const btTransform & PhysicsConstraintGeneric6Dof::getCalculatedTransformA() const
    {
        const btGeneric6DofConstraint *constraint = dynamic_cast<const btGeneric6DofConstraint*>(getConstraint());
        return constraint->getCalculatedTransformA();
    }
    
    const btTransform & PhysicsConstraintGeneric6Dof::getCalculatedTransformB() const
    {
        const btGeneric6DofConstraint *constraint = dynamic_cast<const btGeneric6DofConstraint*>(getConstraint());
        return constraint->getCalculatedTransformB();
    }
    
    const btTransform & PhysicsConstraintGeneric6Dof::getFrameOffsetA() const
    {
        const btGeneric6DofConstraint *constraint = dynamic_cast<const btGeneric6DofConstraint*>(getConstraint());
        return constraint->getFrameOffsetA();
    }
    
    const btTransform & PhysicsConstraintGeneric6Dof::getFrameOffsetB() const
    {
        const btGeneric6DofConstraint *constraint = dynamic_cast<const btGeneric6DofConstraint*>(getConstraint());
        return constraint->getFrameOffsetB();
    }
    
    btTransform & PhysicsConstraintGeneric6Dof::getFrameOffsetA()
    {
        btGeneric6DofConstraint *constraint = dynamic_cast<btGeneric6DofConstraint*>(getConstraint());
        return constraint->getFrameOffsetA();
    }
    
    btTransform & PhysicsConstraintGeneric6Dof::getFrameOffsetB()
    {
        btGeneric6DofConstraint *constraint = dynamic_cast<btGeneric6DofConstraint*>(getConstraint());
        return constraint->getFrameOffsetB();
    }
    
    btVector3 PhysicsConstraintGeneric6Dof::getAxis(int axis_index) const
    {
        const btGeneric6DofConstraint *constraint = dynamic_cast<const btGeneric6DofConstraint*>(getConstraint());
        return constraint->getAxis(axis_index);
    }
    
    f32 PhysicsConstraintGeneric6Dof::getAngle(int axis_index) const
    {
        const btGeneric6DofConstraint *constraint = dynamic_cast<const btGeneric6DofConstraint*>(getConstraint());
        return constraint->getAngle(axis_index);
    }
    
    f32 PhysicsConstraintGeneric6Dof::getRelativePivotPosition(int axis_index) const
    {
        const btGeneric6DofConstraint *constraint = dynamic_cast<const btGeneric6DofConstraint*>(getConstraint());
        return constraint->getRelativePivotPosition(axis_index);
    }
    
    void PhysicsConstraintGeneric6Dof::setFrames(const btTransform & frameA, const btTransform & frameB)
    {
        btGeneric6DofConstraint *constraint = dynamic_cast<btGeneric6DofConstraint*>(getConstraint());
        constraint->setFrames(frameA, frameB);
    }
    
    bool PhysicsConstraintGeneric6Dof::testAngularLimitMotor(int axis_index)
    {
        btGeneric6DofConstraint *constraint = dynamic_cast<btGeneric6DofConstraint*>(getConstraint());
        return constraint->testAngularLimitMotor(axis_index);
    }
    
    void PhysicsConstraintGeneric6Dof::setLinearLowerLimit(const btVector3& linearLower)
    {
        btGeneric6DofConstraint *constraint = dynamic_cast<btGeneric6DofConstraint*>(getConstraint());
        constraint->setLinearLowerLimit(linearLower);
    }
    
    void PhysicsConstraintGeneric6Dof::getLinearLowerLimit(btVector3& linearLower)
    {
        btGeneric6DofConstraint *constraint = dynamic_cast<btGeneric6DofConstraint*>(getConstraint());
        constraint->getLinearLowerLimit(linearLower);
    }
    
    void PhysicsConstraintGeneric6Dof::setLinearUpperLimit(const btVector3& linearUpper)
    {
        btGeneric6DofConstraint *constraint = dynamic_cast<btGeneric6DofConstraint*>(getConstraint());
        constraint->setLinearUpperLimit(linearUpper);
    }
    
    void PhysicsConstraintGeneric6Dof::getLinearUpperLimit(btVector3& linearUpper)
    {
        btGeneric6DofConstraint *constraint = dynamic_cast<btGeneric6DofConstraint*>(getConstraint());
        constraint->getLinearUpperLimit(linearUpper);
    }
    
    void PhysicsConstraintGeneric6Dof::setAngularLowerLimit(const btVector3& angularLower)
    {
        btGeneric6DofConstraint *constraint = dynamic_cast<btGeneric6DofConstraint*>(getConstraint());
        constraint->setAngularLowerLimit(angularLower);
    }
    
    void PhysicsConstraintGeneric6Dof::getAngularLowerLimit(btVector3& angularLower)
    {
        btGeneric6DofConstraint *constraint = dynamic_cast<btGeneric6DofConstraint*>(getConstraint());
        constraint->getAngularLowerLimit(angularLower);
    }
    
    void PhysicsConstraintGeneric6Dof::setAngularUpperLimit(const btVector3& angularUpper)
    {
        btGeneric6DofConstraint *constraint = dynamic_cast<btGeneric6DofConstraint*>(getConstraint());
        constraint->setAngularUpperLimit(angularUpper);
    }
    
    void PhysicsConstraintGeneric6Dof::getAngularUpperLimit(btVector3& angularUpper)
    {
        btGeneric6DofConstraint *constraint = dynamic_cast<btGeneric6DofConstraint*>(getConstraint());
        constraint->getAngularUpperLimit(angularUpper);
    }
    
    btRotationalLimitMotor * PhysicsConstraintGeneric6Dof::getRotationalLimitMotor(int index)
    {
        btGeneric6DofConstraint *constraint = dynamic_cast<btGeneric6DofConstraint*>(getConstraint());
        return constraint->getRotationalLimitMotor(index);
    }
    
    btTranslationalLimitMotor * PhysicsConstraintGeneric6Dof::getTranslationalLimitMotor()
    {
        btGeneric6DofConstraint *constraint = dynamic_cast<btGeneric6DofConstraint*>(getConstraint());
        return constraint->getTranslationalLimitMotor();
    }
    
    void PhysicsConstraintGeneric6Dof::setLimit(int axis, f32 lo, f32 hi)
    {
        btGeneric6DofConstraint *constraint = dynamic_cast<btGeneric6DofConstraint*>(getConstraint());
        constraint->setLimit(axis, lo, hi);
    }
    
    bool PhysicsConstraintGeneric6Dof::isLimited(int limitIndex)
    {
        btGeneric6DofConstraint *constraint = dynamic_cast<btGeneric6DofConstraint*>(getConstraint());
        return constraint->isLimited(limitIndex);
    }
    
    bool PhysicsConstraintGeneric6Dof::getUseFrameOffset()
    {
        btGeneric6DofConstraint *constraint = dynamic_cast<btGeneric6DofConstraint*>(getConstraint());
        return constraint->getUseFrameOffset();
    }
    
    void PhysicsConstraintGeneric6Dof::setUseFrameOffset(bool frameOffsetOnOff)
    {
        btGeneric6DofConstraint *constraint = dynamic_cast<btGeneric6DofConstraint*>(getConstraint());
        constraint->setUseFrameOffset(frameOffsetOnOff);
    }
    
    void PhysicsConstraintGeneric6Dof::setAxis(const btVector3& axis1, const btVector3& axis2)
    {
        btGeneric6DofConstraint *constraint = dynamic_cast<btGeneric6DofConstraint*>(getConstraint());
        constraint->setAxis(axis1, axis2);
    }
    
    btTypedConstraint *PhysicsConstraintGeneric6Dof::getConstraint()
    {
        DEBUG_ASSERT(m_btGeneric6DofConstraint);
        return m_btGeneric6DofConstraint;
    }
    
    const btTypedConstraint *PhysicsConstraintGeneric6Dof::getConstraint()const
    {
        DEBUG_ASSERT(m_btGeneric6DofConstraint);
        return m_btGeneric6DofConstraint;
    }
    
    void PhysicsConstraintGeneric6Dof::removeConstraint()
    {
        PhysicsConstraint::removeConstraint();
        
        if(m_btGeneric6DofConstraint)
            delete m_btGeneric6DofConstraint;
        m_btGeneric6DofConstraint = NULL;
    }
    
}
