//
//  PhysicsConstraintSlider.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 6/19/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "PhysicsConstraintSlider.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsConstraintSliderBuilder.h"
#define TAG "PhysicsConstraintSlider.cpp"

#include "btSliderConstraint.h"
#include "PhysicsWorld.h"
#include "PhysicsBody.h"

#define FORMATSTRING "{\"njli::PhysicsConstraintSlider\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    PhysicsConstraintSlider::PhysicsConstraintSlider():
    PhysicsConstraint(),
    m_btSliderConstraint(NULL)
    {
        
    }
    
    PhysicsConstraintSlider::PhysicsConstraintSlider(const AbstractBuilder &builder):
    PhysicsConstraint(builder),
    m_btSliderConstraint(NULL)
    {
        
    }
    
    PhysicsConstraintSlider::PhysicsConstraintSlider(const PhysicsConstraintSlider &copy):
    PhysicsConstraint(copy),
    m_btSliderConstraint(NULL)
    {
        
    }
    
    PhysicsConstraintSlider::~PhysicsConstraintSlider()
    {
        removeConstraint();
    }
    
    PhysicsConstraintSlider &PhysicsConstraintSlider::operator=(const PhysicsConstraintSlider &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	PhysicsConstraintSlider::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsConstraintSlider::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsConstraintSlider::getClassName()const
    {
        return "PhysicsConstraintSlider";
    }
    
    s32 PhysicsConstraintSlider::getType()const
    {
        return PhysicsConstraintSlider::type();
    }
    
    PhysicsConstraintSlider::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsConstraintSlider **PhysicsConstraintSlider::createArray(const u32 size)
    {
        return (PhysicsConstraintSlider**)World::getInstance()->getWorldFactory()->createArray(PhysicsConstraintSlider::type(), size);
    }
    
    void PhysicsConstraintSlider::destroyArray(PhysicsConstraintSlider **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsConstraintSlider *PhysicsConstraintSlider::create()
    {
        return dynamic_cast<PhysicsConstraintSlider*>(World::getInstance()->getWorldFactory()->create(PhysicsConstraintSlider::type()));
    }
    
    PhysicsConstraintSlider *PhysicsConstraintSlider::create(const PhysicsConstraintSliderBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsConstraintSlider*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsConstraintSlider *PhysicsConstraintSlider::clone(const PhysicsConstraintSlider &object)
    {
        return dynamic_cast<PhysicsConstraintSlider*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsConstraintSlider *PhysicsConstraintSlider::copy(const PhysicsConstraintSlider &object)
    {
        return dynamic_cast<PhysicsConstraintSlider*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsConstraintSlider::destroy(PhysicsConstraintSlider *object)
    {
        if(object)
        {
            PhysicsConstraint::destroy(object);
        }
    }
    
    void PhysicsConstraintSlider::load(PhysicsConstraintSlider &object, lua_State *L, int index)
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
                PhysicsConstraintSlider::load(object, L, -2);
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
    
    u32 PhysicsConstraintSlider::type()
    {
        return JLI_OBJECT_TYPE_PhysicsConstraintSlider;
    }
    
    void PhysicsConstraintSlider::setNodes(Node *nodeA, Node *nodeB, const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
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
            m_btSliderConstraint = new btSliderConstraint(*rigidBodyA, frameInB, useLinearReferenceFrameA);
        }
        else if (rigidBodyA && rigidBodyB)
        {
            m_btSliderConstraint = new btSliderConstraint(*rigidBodyA, *rigidBodyB, frameInA, frameInB, useLinearReferenceFrameA);
        }
        
        if(rigidBodyA)
            getNodeA()->getPhysicsBody()->setPhysicsConstraint(this);
        if(rigidBodyB)
            getNodeB()->getPhysicsBody()->setPhysicsConstraint(this);
        
//        Scene *scene = njli::World::getInstance()->getScene();
        Scene *scene = getParent()->getParent()->getCurrentScene();
        scene->getPhysicsWorld()->addConstraint(this);
    }
    
    void PhysicsConstraintSlider::setNodes(Node *nodeB, const btTransform& frameInB, bool useLinearReferenceFrameA)
    {
        setNodes(NULL, nodeB, frameInB, frameInB, useLinearReferenceFrameA);
    }
    
    const btTransform & PhysicsConstraintSlider::getCalculatedTransformA() const
    {
        const btSliderConstraint *constraint = dynamic_cast<const btSliderConstraint*>(getConstraint());
        return constraint->getCalculatedTransformA();
    }
    const btTransform & PhysicsConstraintSlider::getCalculatedTransformB() const
    {
        const btSliderConstraint *constraint = dynamic_cast<const btSliderConstraint*>(getConstraint());
        return constraint->getCalculatedTransformB();
    }
    
    const btTransform & PhysicsConstraintSlider::getFrameOffsetA() const
    {
        const btSliderConstraint *constraint = dynamic_cast<const btSliderConstraint*>(getConstraint());
        return constraint->getFrameOffsetA();
    }
    
    const btTransform & PhysicsConstraintSlider::getFrameOffsetB() const
    {
        const btSliderConstraint *constraint = dynamic_cast<const btSliderConstraint*>(getConstraint());
        return constraint->getFrameOffsetB();
    }
    
    btTransform & PhysicsConstraintSlider::getFrameOffsetA()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getFrameOffsetA();
    }
    
    btTransform & PhysicsConstraintSlider::getFrameOffsetB()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getFrameOffsetB();
    }
    
    f32 PhysicsConstraintSlider::getLowerLinLimit()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getLowerLinLimit();
    }
    
    void PhysicsConstraintSlider::setLowerLinLimit(f32 lowerLimit)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setLowerLinLimit(lowerLimit);
    }
    
    f32 PhysicsConstraintSlider::getUpperLinLimit()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getUpperLinLimit();
    }
    
    void PhysicsConstraintSlider::setUpperLinLimit(f32 upperLimit)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setUpperLinLimit(upperLimit);
    }
    
    f32 PhysicsConstraintSlider::getLowerAngLimit()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getLowerAngLimit();
    }
    
    void PhysicsConstraintSlider::setLowerAngLimit(f32 lowerLimit)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setLowerAngLimit(lowerLimit);
    }
    
    f32 PhysicsConstraintSlider::getUpperAngLimit()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getUpperAngLimit();
    }
    
    void PhysicsConstraintSlider::setUpperAngLimit(f32 upperLimit)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setUpperAngLimit(upperLimit);
    }
    
    bool PhysicsConstraintSlider::getUseLinearReferenceFrameA()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getUseLinearReferenceFrameA();
    }
    
    f32 PhysicsConstraintSlider::getSoftnessDirLin()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getSoftnessDirLin();
    }
    
    f32 PhysicsConstraintSlider::getRestitutionDirLin()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getRestitutionDirLin();
    }
    
    f32 PhysicsConstraintSlider::getDampingDirLin()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getDampingDirLin();
    }
    
    f32 PhysicsConstraintSlider::getSoftnessDirAng()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getSoftnessDirAng();
    }
    
    f32 PhysicsConstraintSlider::getRestitutionDirAng()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getRestitutionDirAng();
    }
    
    f32 PhysicsConstraintSlider::getDampingDirAng()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getDampingDirAng();
    }
    
    f32 PhysicsConstraintSlider::getSoftnessLimLin()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getSoftnessLimLin();
    }
    
    f32 PhysicsConstraintSlider::getRestitutionLimLin()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getRestitutionLimLin();
    }
    
    f32 PhysicsConstraintSlider::getDampingLimLin()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getDampingLimLin();
    }
    
    f32 PhysicsConstraintSlider::getSoftnessLimAng()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getSoftnessLimAng();
    }
    
    f32 PhysicsConstraintSlider::getRestitutionLimAng()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getRestitutionLimAng();
    }
    
    f32 PhysicsConstraintSlider::getDampingLimAng()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getDampingLimAng();
    }
    
    f32 PhysicsConstraintSlider::getSoftnessOrthoLin()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getSoftnessOrthoLin();
    }
    
    f32 PhysicsConstraintSlider::getRestitutionOrthoLin()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getRestitutionOrthoLin();
    }
    
    f32 PhysicsConstraintSlider::getDampingOrthoLin()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getDampingOrthoLin();
    }
    
    f32 PhysicsConstraintSlider::getSoftnessOrthoAng()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getSoftnessOrthoAng();
    }
    
    f32 PhysicsConstraintSlider::getRestitutionOrthoAng()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getRestitutionOrthoAng();
    }
    
    f32 PhysicsConstraintSlider::getDampingOrthoAng()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getDampingOrthoAng();
    }
    
    void PhysicsConstraintSlider::setSoftnessDirLin(f32 softnessDirLin)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setSoftnessDirLin(softnessDirLin);
    }
    
    void PhysicsConstraintSlider::setRestitutionDirLin(f32 restitutionDirLin)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setRestitutionDirLin(restitutionDirLin);
    }
    
    void PhysicsConstraintSlider::setDampingDirLin(f32 dampingDirLin)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setDampingDirLin(dampingDirLin);
    }
    
    void PhysicsConstraintSlider::setSoftnessDirAng(f32 softnessDirAng)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setSoftnessDirAng(softnessDirAng);
    }
    
    void PhysicsConstraintSlider::setRestitutionDirAng(f32 restitutionDirAng)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setRestitutionDirAng(restitutionDirAng);
    }
    
    void PhysicsConstraintSlider::setDampingDirAng(f32 dampingDirAng)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setDampingDirAng(dampingDirAng);
    }
    
    void PhysicsConstraintSlider::setSoftnessLimLin(f32 softnessLimLin)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setSoftnessLimLin(softnessLimLin);
    }
    
    void PhysicsConstraintSlider::setRestitutionLimLin(f32 restitutionLimLin)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setRestitutionLimLin(restitutionLimLin);
    }
    
    void PhysicsConstraintSlider::setDampingLimLin(f32 dampingLimLin)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setDampingLimLin(dampingLimLin);
    }
    
    void PhysicsConstraintSlider::setSoftnessLimAng(f32 softnessLimAng)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setSoftnessLimAng(softnessLimAng);
    }
    
    void PhysicsConstraintSlider::setRestitutionLimAng(f32 restitutionLimAng)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setRestitutionLimAng(restitutionLimAng);
    }
    
    void PhysicsConstraintSlider::setDampingLimAng(f32 dampingLimAng)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setDampingLimAng(dampingLimAng);
    }
    
    void PhysicsConstraintSlider::setSoftnessOrthoLin(f32 softnessOrthoLin)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setSoftnessOrthoLin(softnessOrthoLin);
    }
    
    void PhysicsConstraintSlider::setRestitutionOrthoLin(f32 restitutionOrthoLin)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setRestitutionOrthoAng(restitutionOrthoLin);
    }
    
    void PhysicsConstraintSlider::setDampingOrthoLin(f32 dampingOrthoLin)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setDampingOrthoLin(dampingOrthoLin);
    }
    
    void PhysicsConstraintSlider::setSoftnessOrthoAng(f32 softnessOrthoAng)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setSoftnessOrthoAng(softnessOrthoAng);
    }
    
    void PhysicsConstraintSlider::setRestitutionOrthoAng(f32 restitutionOrthoAng)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setRestitutionOrthoAng(restitutionOrthoAng);
    }
    
    void PhysicsConstraintSlider::setDampingOrthoAng(f32 dampingOrthoAng)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setDampingOrthoAng(dampingOrthoAng);
    }
    
    void PhysicsConstraintSlider::setPoweredLinMotor(bool onOff)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setPoweredLinMotor(onOff);
    }
    
    bool PhysicsConstraintSlider::getPoweredLinMotor()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getPoweredLinMotor();
    }
    
    void PhysicsConstraintSlider::setTargetLinMotorVelocity(f32 targetLinMotorVelocity)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setTargetLinMotorVelocity(targetLinMotorVelocity);
    }
    
    f32 PhysicsConstraintSlider::getTargetLinMotorVelocity()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getTargetLinMotorVelocity();
    }
    
    void PhysicsConstraintSlider::setMaxLinMotorForce(f32 maxLinMotorForce)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setMaxLinMotorForce(maxLinMotorForce);
    }
    
    f32 PhysicsConstraintSlider::getMaxLinMotorForce()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getMaxLinMotorForce();
    }
    
    void PhysicsConstraintSlider::setPoweredAngMotor(bool onOff)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setPoweredAngMotor(onOff);
    }
    
    bool PhysicsConstraintSlider::getPoweredAngMotor()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getPoweredAngMotor();
    }
    
    void PhysicsConstraintSlider::setTargetAngMotorVelocity(f32 targetAngMotorVelocity)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setTargetAngMotorVelocity(targetAngMotorVelocity);
    }
    
    f32 PhysicsConstraintSlider::getTargetAngMotorVelocity()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getTargetAngMotorVelocity();
    }
    
    void PhysicsConstraintSlider::setMaxAngMotorForce(f32 maxAngMotorForce)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setMaxAngMotorForce(maxAngMotorForce);
    }
    
    f32 PhysicsConstraintSlider::getMaxAngMotorForce()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getMaxAngMotorForce();
    }
    
    f32 PhysicsConstraintSlider::getLinearPos() const
    {
        const btSliderConstraint *constraint = dynamic_cast<const btSliderConstraint*>(getConstraint());
        return constraint->getLinearPos();
    }
    
    f32 PhysicsConstraintSlider::getAngularPos() const
    {
        const btSliderConstraint *constraint = dynamic_cast<const btSliderConstraint*>(getConstraint());
        return constraint->getAngularPos();
    }
    
    bool PhysicsConstraintSlider::getSolveLinLimit()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getSolveLinLimit();
    }
    
    f32 PhysicsConstraintSlider::getLinDepth()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getLinDepth();
    }
    
    bool PhysicsConstraintSlider::getSolveAngLimit()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getSolveAngLimit();
    }
    
    f32 PhysicsConstraintSlider::getAngDepth()
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        return constraint->getAngDepth();
    }
    
    void PhysicsConstraintSlider::setFrames(const btTransform& frameA, const btTransform& frameB)
    {
        btSliderConstraint *constraint = dynamic_cast<btSliderConstraint*>(getConstraint());
        constraint->setFrames(frameA, frameB);
    }
    
    btTypedConstraint *PhysicsConstraintSlider::getConstraint()
    {
        DEBUG_ASSERT(m_btSliderConstraint);
        return m_btSliderConstraint;
    }
    
    const btTypedConstraint *PhysicsConstraintSlider::getConstraint()const
    {
        DEBUG_ASSERT(m_btSliderConstraint);
        return m_btSliderConstraint;
    }
    
    void PhysicsConstraintSlider::removeConstraint()
    {
        PhysicsConstraint::removeConstraint();
        
        if(m_btSliderConstraint)
            delete m_btSliderConstraint;
        m_btSliderConstraint = NULL;
    }
    
}
