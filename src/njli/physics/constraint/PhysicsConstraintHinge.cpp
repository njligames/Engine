//
//  PhysicsConstraintHinge.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 6/18/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "PhysicsConstraintHinge.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsConstraintHingeBuilder.h"
#define TAG "PhysicsConstraintHinge.cpp"

#include "btHingeConstraint.h"
#include "PhysicsWorld.h"
#include "PhysicsBody.h"

#define FORMATSTRING "{\"njli::PhysicsConstraintHinge\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    PhysicsConstraintHinge::PhysicsConstraintHinge():
    PhysicsConstraint(),
    m_btHingeConstraint(NULL)
    {
        
    }
    
    PhysicsConstraintHinge::PhysicsConstraintHinge(const AbstractBuilder &builder):
    PhysicsConstraint(builder),
    m_btHingeConstraint(NULL)
    {
        
    }
    
    PhysicsConstraintHinge::PhysicsConstraintHinge(const PhysicsConstraintHinge &copy):
    PhysicsConstraint(copy),
    m_btHingeConstraint(NULL)
    {
        
    }
    
    PhysicsConstraintHinge::~PhysicsConstraintHinge()
    {
        removeConstraint();
    }
    
    PhysicsConstraintHinge &PhysicsConstraintHinge::operator=(const PhysicsConstraintHinge &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	PhysicsConstraintHinge::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsConstraintHinge::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsConstraintHinge::getClassName()const
    {
        return "PhysicsConstraintHinge";
    }
    
    s32 PhysicsConstraintHinge::getType()const
    {
        return PhysicsConstraintHinge::type();
    }
    
    PhysicsConstraintHinge::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsConstraintHinge **PhysicsConstraintHinge::createArray(const u32 size)
    {
        return (PhysicsConstraintHinge**)World::getInstance()->getWorldFactory()->createArray(PhysicsConstraintHinge::type(), size);
    }
    
    void PhysicsConstraintHinge::destroyArray(PhysicsConstraintHinge **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsConstraintHinge *PhysicsConstraintHinge::create()
    {
        return dynamic_cast<PhysicsConstraintHinge*>(World::getInstance()->getWorldFactory()->create(PhysicsConstraintHinge::type()));
    }
    
    PhysicsConstraintHinge *PhysicsConstraintHinge::create(const PhysicsConstraintHingeBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsConstraintHinge*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsConstraintHinge *PhysicsConstraintHinge::clone(const PhysicsConstraintHinge &object)
    {
        return dynamic_cast<PhysicsConstraintHinge*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsConstraintHinge *PhysicsConstraintHinge::copy(const PhysicsConstraintHinge &object)
    {
        return dynamic_cast<PhysicsConstraintHinge*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsConstraintHinge::destroy(PhysicsConstraintHinge *object)
    {
        if(object)
        {
            PhysicsConstraint::destroy(object);
        }
    }
    
    void PhysicsConstraintHinge::load(PhysicsConstraintHinge &object, lua_State *L, int index)
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
                PhysicsConstraintHinge::load(object, L, -2);
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
    
    u32 PhysicsConstraintHinge::type()
    {
        return JLI_OBJECT_TYPE_PhysicsConstraintHinge;
    }
    
    
    
    
    
    
    
    
    
    
    
    
    void PhysicsConstraintHinge::setNodes(Node *nodeA, Node *nodeB, const btVector3& pivotInA,const btVector3& pivotInB, const btVector3& axisInA,const btVector3& axisInB, bool useReferenceFrameA)
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
            m_btHingeConstraint = new btHingeConstraint(*rigidBodyA, pivotInA, axisInA, useReferenceFrameA);
        }
        else if (rigidBodyA && rigidBodyB)
        {
            m_btHingeConstraint = new btHingeConstraint(*rigidBodyA, *rigidBodyB, pivotInA, pivotInB, axisInA, axisInB, useReferenceFrameA);
        }
        
        if(rigidBodyA)
            getNodeA()->getPhysicsBody()->setPhysicsConstraint(this);
        if(rigidBodyB)
            getNodeB()->getPhysicsBody()->setPhysicsConstraint(this);
        
//        Scene *scene = njli::World::getInstance()->getScene();
        Scene *scene = getParent()->getParent()->getCurrentScene();
        scene->getPhysicsWorld()->addConstraint(this);
        
    }
    
    void PhysicsConstraintHinge::setNodes(Node *nodeA, const btVector3& pivotInA, const btVector3& axisInA, bool useReferenceFrameA)
    {
        setNodes(nodeA, NULL, pivotInA, pivotInA, axisInA, axisInA, useReferenceFrameA);
    }
    
    void PhysicsConstraintHinge::setNodes(Node *nodeA, Node *nodeB, const btTransform& rbAFrame, const btTransform& rbBFrame, bool useReferenceFrameA)
    {
        DEBUG_ASSERT(nodeA || nodeB);
        
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
            m_btHingeConstraint = new btHingeConstraint(*rigidBodyA, rbAFrame, useReferenceFrameA);
        }
        else if (rigidBodyA && rigidBodyB)
        {
            m_btHingeConstraint = new btHingeConstraint(*rigidBodyA, *rigidBodyB, rbAFrame, rbBFrame, useReferenceFrameA);
        }
        
        if(rigidBodyA)
            getNodeA()->getPhysicsBody()->setPhysicsConstraint(this);
        if(rigidBodyB)
            getNodeB()->getPhysicsBody()->setPhysicsConstraint(this);
        
//        Scene *scene = njli::World::getInstance()->getScene();
        Scene *scene = getParent()->getParent()->getCurrentScene();
        scene->getPhysicsWorld()->addConstraint(this);
    }
    
    void PhysicsConstraintHinge::setNodes(Node *nodeA, const btTransform& rbAFrame, bool useReferenceFrameA)
    {
        setNodes(nodeA, NULL, rbAFrame, rbAFrame, useReferenceFrameA);
    }
    
    btTransform& PhysicsConstraintHinge::getFrameOffsetA()
    {
        btHingeConstraint *constraint = dynamic_cast<btHingeConstraint*>(getConstraint());
        return constraint->getFrameOffsetA();
    }
    
    btTransform& PhysicsConstraintHinge::getFrameOffsetB()
    {
        btHingeConstraint *constraint = dynamic_cast<btHingeConstraint*>(getConstraint());
        return constraint->getFrameOffsetB();
    }
    
    void PhysicsConstraintHinge::setFrames(const btTransform& frameA, const btTransform& frameB)
    {
        btHingeConstraint *constraint = dynamic_cast<btHingeConstraint*>(getConstraint());
        constraint->setFrames(frameA, frameB);
    }
    
    void PhysicsConstraintHinge::setAngularOnly(bool angularOnly)
    {
        btHingeConstraint *constraint = dynamic_cast<btHingeConstraint*>(getConstraint());
        constraint->setAngularOnly(angularOnly);
    }
    
    void PhysicsConstraintHinge::enableAngularMotor(bool enableMotor, f32 targetVelocity, f32 maxMotorImpulse)
    {
        btHingeConstraint *constraint = dynamic_cast<btHingeConstraint*>(getConstraint());
        constraint->enableAngularMotor(enableMotor, targetVelocity, maxMotorImpulse);
    }
    
    void PhysicsConstraintHinge::enableMotor(bool enableMotor)
    {
        btHingeConstraint *constraint = dynamic_cast<btHingeConstraint*>(getConstraint());
        constraint->enableMotor(enableMotor);
    }
    
    void PhysicsConstraintHinge::setMaxMotorImpulse(f32 maxMotorImpulse)
    {
        btHingeConstraint *constraint = dynamic_cast<btHingeConstraint*>(getConstraint());
        constraint->setMaxMotorImpulse(maxMotorImpulse);
    }
    
    void PhysicsConstraintHinge::setMotorTarget(const btQuaternion& qAinB, f32 dt)
    {
        btHingeConstraint *constraint = dynamic_cast<btHingeConstraint*>(getConstraint());
        constraint->setMotorTarget(qAinB, dt);
    }
    
    void PhysicsConstraintHinge::setMotorTarget(f32 targetAngle, f32 dt)
    {
        btHingeConstraint *constraint = dynamic_cast<btHingeConstraint*>(getConstraint());
        constraint->setMotorTarget(targetAngle, dt);
    }
    
    void PhysicsConstraintHinge::setLimit(f32 low, f32 high, f32 _softness, f32 _biasFactor, f32 _relaxationFactor)
    {
        btHingeConstraint *constraint = dynamic_cast<btHingeConstraint*>(getConstraint());
        constraint->setLimit(low, high, _softness, _biasFactor, _relaxationFactor);
    }
    
    void PhysicsConstraintHinge::setAxis(btVector3& axisInA)
    {
        btHingeConstraint *constraint = dynamic_cast<btHingeConstraint*>(getConstraint());
        constraint->setAxis(axisInA);
    }
    
    f32	PhysicsConstraintHinge::getLowerLimit() const
    {
        const btHingeConstraint *constraint = dynamic_cast<const btHingeConstraint*>(getConstraint());
        return constraint->getLowerLimit();
    }
    
    f32	PhysicsConstraintHinge::getUpperLimit() const
    {
        const btHingeConstraint *constraint = dynamic_cast<const btHingeConstraint*>(getConstraint());
        return constraint->getUpperLimit();
    }
    
    f32 PhysicsConstraintHinge::getHingeAngle()
    {
        btHingeConstraint *constraint = dynamic_cast<btHingeConstraint*>(getConstraint());
        return getHingeAngle();
    }
    
    f32 PhysicsConstraintHinge::getHingeAngle(const btTransform& transA,const btTransform& transB)
    {
        btHingeConstraint *constraint = dynamic_cast<btHingeConstraint*>(getConstraint());
        return constraint->getHingeAngle(transA, transB);
    }
    
    void PhysicsConstraintHinge::testLimit(const btTransform& transA,const btTransform& transB)
    {
        btHingeConstraint *constraint = dynamic_cast<btHingeConstraint*>(getConstraint());
        constraint->testLimit(transA, transB);
    }
    
    const btTransform& PhysicsConstraintHinge::getAFrame() const
    {
        const btHingeConstraint *constraint = dynamic_cast<const btHingeConstraint*>(getConstraint());
        return constraint->getAFrame();
    }
    
    const btTransform& PhysicsConstraintHinge::getBFrame() const
    {
        const btHingeConstraint *constraint = dynamic_cast<const btHingeConstraint*>(getConstraint());
        return constraint->getBFrame();
    }
    
    btTransform& PhysicsConstraintHinge::getAFrame()
    {
        btHingeConstraint *constraint = dynamic_cast<btHingeConstraint*>(getConstraint());
        return constraint->getAFrame();
    }
    
    btTransform& PhysicsConstraintHinge::getBFrame()
    {
        btHingeConstraint *constraint = dynamic_cast<btHingeConstraint*>(getConstraint());
        return constraint->getBFrame();
    }
    
    int PhysicsConstraintHinge::getSolveLimit()
    {
        btHingeConstraint *constraint = dynamic_cast<btHingeConstraint*>(getConstraint());
        return constraint->getSolveLimit();
    }
    
    f32 PhysicsConstraintHinge::getLimitSign()
    {
        btHingeConstraint *constraint = dynamic_cast<btHingeConstraint*>(getConstraint());
        return constraint->getLimitSign();
    }
    
    bool PhysicsConstraintHinge::getAngularOnly()
    {
        btHingeConstraint *constraint = dynamic_cast<btHingeConstraint*>(getConstraint());
        return constraint->getAngularOnly();
    }
    
    bool PhysicsConstraintHinge::getEnableAngularMotor()
    {
        btHingeConstraint *constraint = dynamic_cast<btHingeConstraint*>(getConstraint());
        return constraint->getEnableAngularMotor();
    }
    
    f32 PhysicsConstraintHinge::getMotorTargetVelocity()
    {
        btHingeConstraint *constraint = dynamic_cast<btHingeConstraint*>(getConstraint());
        return constraint->getMotorTargetVelosity();
    }
    
    f32 PhysicsConstraintHinge::getMaxMotorImpulse()
    {
        btHingeConstraint *constraint = dynamic_cast<btHingeConstraint*>(getConstraint());
        return constraint->getMaxMotorImpulse();
    }
    
    btTypedConstraint *PhysicsConstraintHinge::getConstraint()
    {
        DEBUG_ASSERT(m_btHingeConstraint);
        return m_btHingeConstraint;
    }
    
    const btTypedConstraint *PhysicsConstraintHinge::getConstraint()const
    {
        DEBUG_ASSERT(m_btHingeConstraint);
        return m_btHingeConstraint;
    }
    
    void PhysicsConstraintHinge::removeConstraint()
    {
        PhysicsConstraint::removeConstraint();
        
        if(m_btHingeConstraint)
            delete m_btHingeConstraint;
        m_btHingeConstraint = NULL;
    }
    
}
