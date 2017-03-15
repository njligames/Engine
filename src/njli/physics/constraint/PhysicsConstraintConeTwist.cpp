//
//  PhysicsConstraintConeTwist.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 6/19/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "PhysicsConstraintConeTwist.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsConstraintConeTwistBuilder.h"
#define TAG "PhysicsConstraintConeTwist.cpp"

#include "btConeTwistConstraint.h"
#include "PhysicsWorld.h"
#include "PhysicsBody.h"

#define FORMATSTRING "{\"PhysicsConstraint\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    PhysicsConstraintConeTwist::PhysicsConstraintConeTwist():
    PhysicsConstraint(),
    m_btConeTwistConstraint(NULL)
    {
        
    }
    
    PhysicsConstraintConeTwist::PhysicsConstraintConeTwist(const AbstractBuilder &builder):
    PhysicsConstraint(builder),
    m_btConeTwistConstraint(NULL)
    {
        
    }
    
    PhysicsConstraintConeTwist::PhysicsConstraintConeTwist(const PhysicsConstraintConeTwist &copy):
    PhysicsConstraint(copy),
    m_btConeTwistConstraint(NULL)
    {
        
    }
    
    PhysicsConstraintConeTwist::~PhysicsConstraintConeTwist()
    {
        removeConstraint();
    }
    
    PhysicsConstraintConeTwist &PhysicsConstraintConeTwist::operator=(const PhysicsConstraintConeTwist &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	PhysicsConstraintConeTwist::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsConstraintConeTwist::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsConstraintConeTwist::getClassName()const
    {
        return "PhysicsConstraintConeTwist";
    }
    
    s32 PhysicsConstraintConeTwist::getType()const
    {
        return PhysicsConstraintConeTwist::type();
    }
    
    PhysicsConstraintConeTwist::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsConstraintConeTwist **PhysicsConstraintConeTwist::createArray(const u32 size)
    {
        return (PhysicsConstraintConeTwist**)World::getInstance()->getWorldFactory()->createArray(PhysicsConstraintConeTwist::type(), size);
    }
    
    void PhysicsConstraintConeTwist::destroyArray(PhysicsConstraintConeTwist **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsConstraintConeTwist *PhysicsConstraintConeTwist::create()
    {
        return dynamic_cast<PhysicsConstraintConeTwist*>(World::getInstance()->getWorldFactory()->create(PhysicsConstraintConeTwist::type()));
    }
    
    PhysicsConstraintConeTwist *PhysicsConstraintConeTwist::create(const PhysicsConstraintConeTwistBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsConstraintConeTwist*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsConstraintConeTwist *PhysicsConstraintConeTwist::clone(const PhysicsConstraintConeTwist &object)
    {
        return dynamic_cast<PhysicsConstraintConeTwist*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsConstraintConeTwist *PhysicsConstraintConeTwist::copy(const PhysicsConstraintConeTwist &object)
    {
        return dynamic_cast<PhysicsConstraintConeTwist*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsConstraintConeTwist::destroy(PhysicsConstraintConeTwist *object)
    {
        if(object)
        {
            PhysicsConstraint::destroy(object);
        }
        
    }
    
    void PhysicsConstraintConeTwist::load(PhysicsConstraintConeTwist &object, lua_State *L, int index)
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
                PhysicsConstraintConeTwist::load(object, L, -2);
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
    
    u32 PhysicsConstraintConeTwist::type()
    {
        return JLI_OBJECT_TYPE_PhysicsConstraintConeTwist;
    }
    
    void PhysicsConstraintConeTwist::setNodes(Node *nodeA, const btTransform& rbAFrame)
    {
        setNodes(nodeA, NULL, rbAFrame, rbAFrame);
    }
    
    void PhysicsConstraintConeTwist::setNodes(Node *nodeA, Node *nodeB, const btTransform& rbAFrame, const btTransform& rbBFrame)
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
            m_btConeTwistConstraint = new btConeTwistConstraint(*rigidBodyA, rbAFrame);
        }
        else if (rigidBodyA && rigidBodyB)
        {
            m_btConeTwistConstraint = new btConeTwistConstraint(*rigidBodyA, *rigidBodyB, rbAFrame, rbBFrame);
        }
        
        if(rigidBodyA)
            getNodeA()->getPhysicsBody()->setPhysicsConstraint(this);
        if(rigidBodyB)
            getNodeB()->getPhysicsBody()->setPhysicsConstraint(this);
        
//        Scene *scene = njli::World::getInstance()->getScene();
        Scene *scene = getParent()->getParent()->getCurrentScene();
        scene->getPhysicsWorld()->addConstraint(this);
    }
    
    
    void PhysicsConstraintConeTwist::setAngularOnly(bool angularOnly)
    {
        btConeTwistConstraint *constraint = dynamic_cast<btConeTwistConstraint*>(getConstraint());
        constraint->setAngularOnly(angularOnly);
    }
    
    void PhysicsConstraintConeTwist::setLimit(int limitIndex,f32 limitValue)
    {
        btConeTwistConstraint *constraint = dynamic_cast<btConeTwistConstraint*>(getConstraint());
        constraint->setLimit(limitIndex, limitValue);
    }
    
    void PhysicsConstraintConeTwist::setLimit(f32 _swingSpan1, f32 _swingSpan2, f32 _twistSpan, f32 _softness, f32 _biasFactor, f32 _relaxationFactor)
    {
        btConeTwistConstraint *constraint = dynamic_cast<btConeTwistConstraint*>(getConstraint());
        constraint->setLimit(_swingSpan1, _swingSpan2, _twistSpan, _softness, _biasFactor, _relaxationFactor);
    }
    
    const btTransform& PhysicsConstraintConeTwist::getAFrame()
    {
        btConeTwistConstraint *constraint = dynamic_cast<btConeTwistConstraint*>(getConstraint());
        return constraint->getAFrame();
    }
    
    const btTransform& PhysicsConstraintConeTwist::getBFrame()
    {
        btConeTwistConstraint *constraint = dynamic_cast<btConeTwistConstraint*>(getConstraint());
        return constraint->getBFrame();
    }
    
    int PhysicsConstraintConeTwist::getSolveTwistLimit()
    {
        btConeTwistConstraint *constraint = dynamic_cast<btConeTwistConstraint*>(getConstraint());
        return constraint->getSolveTwistLimit();
    }
    
    int PhysicsConstraintConeTwist::getSolveSwingLimit()
    {
        btConeTwistConstraint *constraint = dynamic_cast<btConeTwistConstraint*>(getConstraint());
        return constraint->getSolveSwingLimit();
    }
    
    f32 PhysicsConstraintConeTwist::getTwistLimitSign()
    {
        btConeTwistConstraint *constraint = dynamic_cast<btConeTwistConstraint*>(getConstraint());
        return constraint->getTwistLimitSign();
    }
    
    f32 PhysicsConstraintConeTwist::getSwingSpan1()
    {
        btConeTwistConstraint *constraint = dynamic_cast<btConeTwistConstraint*>(getConstraint());
        return constraint->getSwingSpan2();
    }
    
    f32 PhysicsConstraintConeTwist::getSwingSpan2()
    {
        btConeTwistConstraint *constraint = dynamic_cast<btConeTwistConstraint*>(getConstraint());
        return constraint->getSwingSpan2();
    }
    
    f32 PhysicsConstraintConeTwist::getTwistSpan()
    {
        btConeTwistConstraint *constraint = dynamic_cast<btConeTwistConstraint*>(getConstraint());
        return constraint->getTwistSpan();
    }
    
    f32 PhysicsConstraintConeTwist::getTwistAngle()
    {
        btConeTwistConstraint *constraint = dynamic_cast<btConeTwistConstraint*>(getConstraint());
        return constraint->getTwistAngle();
    }
    
    bool PhysicsConstraintConeTwist::isPastSwingLimit()
    {
        btConeTwistConstraint *constraint = dynamic_cast<btConeTwistConstraint*>(getConstraint());
        return constraint->isPastSwingLimit();
    }
    
    void PhysicsConstraintConeTwist::setDamping(f32 damping)
    {
        btConeTwistConstraint *constraint = dynamic_cast<btConeTwistConstraint*>(getConstraint());
        constraint->setDamping(damping);
    }
    
    void PhysicsConstraintConeTwist::enableMotor(bool b)
    {
        btConeTwistConstraint *constraint = dynamic_cast<btConeTwistConstraint*>(getConstraint());
        constraint->enableMotor(b);
    }
    
    void PhysicsConstraintConeTwist::setMaxMotorImpulse(f32 maxMotorImpulse)
    {
        btConeTwistConstraint *constraint = dynamic_cast<btConeTwistConstraint*>(getConstraint());
        constraint->setMaxMotorImpulse(maxMotorImpulse);
    }
    
    void PhysicsConstraintConeTwist::setMaxMotorImpulseNormalized(f32 maxMotorImpulse)
    {
        btConeTwistConstraint *constraint = dynamic_cast<btConeTwistConstraint*>(getConstraint());
        constraint->setMaxMotorImpulseNormalized(maxMotorImpulse);
    }
    
    f32 PhysicsConstraintConeTwist::getFixThresh()
    {
        btConeTwistConstraint *constraint = dynamic_cast<btConeTwistConstraint*>(getConstraint());
        return constraint->getFixThresh();
    }
    
    void PhysicsConstraintConeTwist::setFixThresh(f32 fixThresh)
    {
        btConeTwistConstraint *constraint = dynamic_cast<btConeTwistConstraint*>(getConstraint());
        constraint->setFixThresh(fixThresh);
    }
    
    void PhysicsConstraintConeTwist::setMotorTarget(const btQuaternion &q)
    {
        btConeTwistConstraint *constraint = dynamic_cast<btConeTwistConstraint*>(getConstraint());
        constraint->setMotorTarget(q);
    }
    
    void PhysicsConstraintConeTwist::setMotorTargetInConstraintSpace(const btQuaternion &q)
    {
        btConeTwistConstraint *constraint = dynamic_cast<btConeTwistConstraint*>(getConstraint());
        constraint->setMotorTargetInConstraintSpace(q);
    }
    
    btVector3 PhysicsConstraintConeTwist::getPointForAngle(f32 fAngleInRadians, f32 fLength) const
    {
        const btConeTwistConstraint *constraint = dynamic_cast<const btConeTwistConstraint*>(getConstraint());
        return constraint->GetPointForAngle(fAngleInRadians, fLength);
    }
    
    void PhysicsConstraintConeTwist::setFrames(const btTransform& frameA, const btTransform& frameB)
    {
        btConeTwistConstraint *constraint = dynamic_cast<btConeTwistConstraint*>(getConstraint());
        constraint->setFrames(frameA, frameB);
    }
    
    const btTransform& PhysicsConstraintConeTwist::getFrameOffsetA() const
    {
        const btConeTwistConstraint *constraint = dynamic_cast<const btConeTwistConstraint*>(getConstraint());
        return constraint->getFrameOffsetA();
    }
    
    const btTransform& PhysicsConstraintConeTwist::getFrameOffsetB() const
    {
        const btConeTwistConstraint *constraint = dynamic_cast<const btConeTwistConstraint*>(getConstraint());
        return constraint->getFrameOffsetB();
    }
    
    
    
    
    
    
    btTypedConstraint *PhysicsConstraintConeTwist::getConstraint()
    {
        return m_btConeTwistConstraint;
    }
    
    const btTypedConstraint *PhysicsConstraintConeTwist::getConstraint()const
    {
        return m_btConeTwistConstraint;
    }
    
    void PhysicsConstraintConeTwist::removeConstraint()
    {
        PhysicsConstraint::removeConstraint();
        
        if(m_btConeTwistConstraint)
            delete m_btConeTwistConstraint;
        m_btConeTwistConstraint = NULL;
    }
}
