//
//  PhysicsBodyRigid.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "PhysicsBodyRigid.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsBodyRigidBuilder.h"
#include "btRigidBody.h"
#include "PhysicsWorld.h"
#include "btVector3.h"
#include "btDefaultMotionState.h"
#include "PhysicsShape.h"
#include "btCollisionShape.h"
#include "PhysicsShapeBox.h"
#include "Geometry.h"
#include "Log.h"
#define TAG "PhysicsBodyRigid.cpp"
#define FORMATSTRING "{\"njli::PhysicsBodyRigid\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    PhysicsBodyRigid::PhysicsBodyRigid():
    PhysicsBody(),
    m_Mass(1.0f),
    m_btDefaultMotionState(new btDefaultMotionState()),
    m_btRigidBody(NULL),
    m_LinearForceAndPositionArrayIndex(0),
    m_AngularForceAndPositionArrayIndex(0),
//    m_btTransform(new btTransform(btTransform::getIdentity())),
    m_Charge(0)
    {
//        for(s32 i = 0; i < 20; ++i)
//        {
//            m_LinearForceAndPositionArray.push_back(new ForceAndPosition());
//            m_AngularForceAndPositionArray.push_back(new ForceAndPosition());
//        }
//        enableHandleCollideCallback();
//        setDynamicPhysics();
    }
    
    PhysicsBodyRigid::PhysicsBodyRigid(const AbstractBuilder &builder):
    PhysicsBody(builder),
    m_Mass(1.0f),
    m_btDefaultMotionState(new btDefaultMotionState()),
    m_btRigidBody(NULL),
    m_LinearForceAndPositionArrayIndex(0),
    m_AngularForceAndPositionArrayIndex(0),
//    m_btTransform(new btTransform(btTransform::getIdentity())),
    m_Charge(0)
    {
//        for(s32 i = 0; i < 20; ++i)
//        {
//            m_LinearForceAndPositionArray.push_back(new ForceAndPosition());
//            m_AngularForceAndPositionArray.push_back(new ForceAndPosition());
//        }
//        enableHandleCollideCallback();
//        setDynamicPhysics();
    }
    
    PhysicsBodyRigid::PhysicsBodyRigid(const PhysicsBodyRigid &copy):
    PhysicsBody(copy),
    m_Mass(1.0f),
    m_btDefaultMotionState(new btDefaultMotionState()),
    m_btRigidBody(NULL),
    m_LinearForceAndPositionArrayIndex(0),
    m_AngularForceAndPositionArrayIndex(0),
//    m_btTransform(new btTransform(btTransform::getIdentity())),
    m_Charge(0)
    {
//        for(s32 i = 0; i < 20; ++i)
//        {
//            m_LinearForceAndPositionArray.push_back(new ForceAndPosition());
//            m_AngularForceAndPositionArray.push_back(new ForceAndPosition());
//        }
    }
    
    PhysicsBodyRigid::~PhysicsBodyRigid()
    {
        removePhysicsBody();
        
//        ForceAndPosition *p = NULL;
        
//        for (s32 i = 0; i < 20; ++i)
//        {
//            p = m_LinearForceAndPositionArray.at(i);
//            delete p;
//            
//            p = m_AngularForceAndPositionArray.at(i);
//            delete p;
//        }
        
//        delete m_btTransform;
//        m_btTransform=NULL;
        
        if(m_btRigidBody)
            delete m_btRigidBody;
        m_btRigidBody = NULL;
        
        delete m_btDefaultMotionState;
        m_btDefaultMotionState = NULL;
    }
    
    PhysicsBodyRigid &PhysicsBodyRigid::operator=(const PhysicsBodyRigid &rhs)
    {
        if(this != &rhs)
        {
            //TODO: implement
        }
        return *this;
    }
    
    s32	PhysicsBodyRigid::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsBodyRigid::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsBodyRigid::getClassName()const
    {
        return "PhysicsBodyRigid";
    }
    
    s32 PhysicsBodyRigid::getType()const
    {
        return PhysicsBodyRigid::type();
    }
    
    PhysicsBodyRigid::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsBodyRigid **PhysicsBodyRigid::createArray(const u32 size)
    {
        return (PhysicsBodyRigid**)World::getInstance()->getWorldFactory()->createArray(PhysicsBodyRigid::type(), size);
    }
    
    void PhysicsBodyRigid::destroyArray(PhysicsBodyRigid **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsBodyRigid *PhysicsBodyRigid::create()
    {
        return dynamic_cast<PhysicsBodyRigid*>(World::getInstance()->getWorldFactory()->create(PhysicsBodyRigid::type()));
    }
    
    PhysicsBodyRigid *PhysicsBodyRigid::create(const PhysicsBodyRigidBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsBodyRigid*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsBodyRigid *PhysicsBodyRigid::clone(const PhysicsBodyRigid &object)
    {
        return dynamic_cast<PhysicsBodyRigid*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsBodyRigid *PhysicsBodyRigid::copy(const PhysicsBodyRigid &object)
    {
        return dynamic_cast<PhysicsBodyRigid*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsBodyRigid::destroy(PhysicsBodyRigid *object)
    {
        if(object)
        {
            PhysicsBody::destroy(object);
        }
    }
    
    void PhysicsBodyRigid::load(PhysicsBodyRigid &object, lua_State *L, int index)
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
                PhysicsBodyRigid::load(object, L, -2);
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

    u32 PhysicsBodyRigid::type()
    {
        return JLI_OBJECT_TYPE_PhysicsBodyRigid;
    }
    
    void PhysicsBodyRigid::setWorldTransform(const btTransform &transform)
    {
//        getBody()->getMotionState()->setWorldTransform(transform);
        
        m_btDefaultMotionState->setWorldTransform(transform);
        if(getBody())
            getBody()->setMotionState(m_btDefaultMotionState);
    }
    
    btTransform PhysicsBodyRigid::getWorldTransform()const
    {
        btTransform t(btTransform::getIdentity());
        if(getBody() && getBody()->getMotionState())
        {
            getBody()->getMotionState()->getWorldTransform(t);
        }
//        DEBUG_ASSERT(getBody());
//        DEBUG_ASSERT(getBody()->getMotionState());
//        
//        getBody()->getMotionState()->getWorldTransform(t);
//        m_btDefaultMotionState->getWorldTransform(t);
        return t;
    }
    
//    const btTransform& PhysicsBodyRigid::getWorldTransform() const
//    {
////        m_btDefaultMotionState->getWorldTransform(*m_btTransform);
//        getBody()->getMotionState()->getWorldTransform(*m_btTransform);
//        return *m_btTransform;
//    }
    
    void PhysicsBodyRigid::setLinearFactor(const btVector3 &factor)
    {
        getBody()->setLinearFactor(factor);
    }
    
    const btVector3 &PhysicsBodyRigid::getLinearFactor()const
    {
        return getBody()->getLinearFactor();
    }
    
    void PhysicsBodyRigid::setAngularFactor(const btVector3 &factor)
    {
        getBody()->setAngularFactor(factor);
    }
    
    void PhysicsBodyRigid::setAngularFactor(f32 factor)
    {
        getBody()->setAngularFactor(factor);
    }
    
    const btVector3 &PhysicsBodyRigid::getAngularFactor()const
    {
        return getBody()->getAngularFactor();
    }
    
    void PhysicsBodyRigid::setMass(f32 mass)
    {
        m_Mass = mass;
        
        if(PhysicsBody::getParent() && getPhysicsShape())
        {
            btTransform t = getWorldTransform();
            setTransform(t);
        }
    }
    
    f32 PhysicsBodyRigid::getMass()const
    {
        return m_Mass;
    }
    
    void PhysicsBodyRigid::setCharge(f32 charge)
    {
        m_Charge = charge;
    }
    
    f32 PhysicsBodyRigid::getCharge()const
    {
        return m_Charge;
    }
    
    void PhysicsBodyRigid::setDamping(f32 damping)
    {
        getBody()->setDamping(damping, getAngularDamping());
    }
    
    f32 PhysicsBodyRigid::getDamping()const
    {
        return getBody()->getLinearDamping();
    }
    
    void PhysicsBodyRigid::setAngularDamping(f32 damping)
    {
        getBody()->setDamping(getDamping(), damping);
    }
    
    f32 PhysicsBodyRigid::getAngularDamping()const
    {
        return getBody()->getAngularDamping();
    }
    
    void PhysicsBodyRigid::applyForce(const btVector3 &direction, bool impulse)
    {
        if(impulse)
        {
            getBody()->applyCentralImpulse(direction);
        }
        else
        {
            DEBUG_ASSERT(m_LinearForceAndPositionArrayIndex < (20 - 1));
            
            ForceAndPosition *fp = m_LinearForceAndPositionArray.at(m_LinearForceAndPositionArrayIndex);
            fp->set(direction, getParent()->getOrigin());
            ++m_LinearForceAndPositionArrayIndex;
        }
    }
    
    void PhysicsBodyRigid::applyForce(const btVector3 &direction, const btVector3 &position, bool impulse)
    {
        if(impulse)
        {
            getBody()->applyImpulse(direction, position);
        }
        else
        {
            DEBUG_ASSERT(m_LinearForceAndPositionArrayIndex < (20 - 1));
            
            ForceAndPosition *fp = m_LinearForceAndPositionArray.at(m_LinearForceAndPositionArrayIndex);
            fp->set(direction, position);
            ++m_LinearForceAndPositionArrayIndex;
        }
    }
    
    void PhysicsBodyRigid::applyAngularForce(const btVector3 &direction, bool impulse)
    {
        if(impulse)
        {
            getBody()->applyTorqueImpulse(direction);
        }
        else
        {
            DEBUG_ASSERT(m_AngularForceAndPositionArrayIndex < (20 - 1));
            
            ForceAndPosition *fp = m_AngularForceAndPositionArray.at(m_AngularForceAndPositionArrayIndex);
            fp->set(direction, getParent()->getOrigin());
            ++m_AngularForceAndPositionArrayIndex;
        }
    }
    
    void PhysicsBodyRigid::clearAllForces()
    {
        getBody()->clearForces();
        m_LinearForceAndPositionArrayIndex = 0;
        m_AngularForceAndPositionArrayIndex = 0;
    }
    
    
    
    void PhysicsBodyRigid::setVelocity(const btVector3 &velocity)
    {
        getBody()->setLinearVelocity(velocity);
    }
    
    const btVector3 &PhysicsBodyRigid::getVelocity()const
    {
        return getBody()->getLinearVelocity();
    }
    
    void PhysicsBodyRigid::setAngularVelocity(const btVector3 &velocity)
    {
        getBody()->setAngularVelocity(velocity);
    }
    
    const btVector3 &PhysicsBodyRigid::getAngularVelocity()const
    {
        return getBody()->getAngularVelocity();
    }
    
    const btCollisionObject* PhysicsBodyRigid::getCollisionObject() const
    {
        return m_btRigidBody;
    }
    
    btCollisionObject* PhysicsBodyRigid::getCollisionObject()
    {
        return m_btRigidBody;
    }
    
    void PhysicsBodyRigid::setCollisionObject(const btCollisionObject &obj, PhysicsShape *shape)
    {
        DEBUG_ASSERT(shape);
        DEBUG_ASSERT(obj.getInternalType()&btCollisionObject::CO_RIGID_BODY);
        
        const btCollisionObject *_collisionObject = dynamic_cast<const btRigidBody *>(&obj);
        
        //TODO: Implement....
    }
    
    const btRigidBody* PhysicsBodyRigid::getBody() const
    {
        return dynamic_cast<const btRigidBody*>(m_btRigidBody);
    }
    
    btRigidBody* PhysicsBodyRigid::getBody()
    {
        return dynamic_cast<btRigidBody*>(m_btRigidBody);
    }
    
    void PhysicsBodyRigid::applyFinalForce()
    {
        for(s32 i = 0; i < m_LinearForceAndPositionArrayIndex; ++i)
        {
            getBody()->applyForce(m_LinearForceAndPositionArray[i]->getForce(), m_LinearForceAndPositionArray[i]->getPosition());
        }
        m_LinearForceAndPositionArrayIndex = 0;
        
    }
    
    void PhysicsBodyRigid::applyFinalAngularForce()
    {
        for(s32 i = 0; i < m_AngularForceAndPositionArrayIndex; ++i)
        {
            getBody()->applyTorque(m_AngularForceAndPositionArray[i]->getForce());
        }
        m_AngularForceAndPositionArrayIndex = 0;
    }
    
    /*
     call...
     
     when the scene of the Parent (Node) is changed
     When the PhysicsWorld is changed on the Scene
     When the PhysicsShape is changed on the rigid body
     When the mass is changed on the rigid body
     
     */
    bool PhysicsBodyRigid::setTransform(const btTransform &transform)
    {
        if (m_btRigidBody && m_btRigidBody->getNumConstraintRefs() != 0)
        {
//            DEBUG_LOG_WRITE_W(TAG, "The PhysicsBodyRigid has constraints so it cannot be added.");
            return false;
        }
        
        Scene *scene = getParent()->getCurrentScene();
        if(!scene)
        {
            DEBUG_LOG_WRITE_W(TAG, "Unable to set the Transform, the scene is NULL\n");
            return false;
        }
        
        PhysicsWorld *physicsWorld = scene->getPhysicsWorld();
        if(NULL != physicsWorld)
        {
            removePhysicsBody();
            
            Node *parent = PhysicsBody::getParent();
            
            if(!parent)
                DEBUG_LOG_WRITE_W(TAG, "The PhysicsBodyRigid is not attached to a Node.\n");
            
            PhysicsShape *physicsShape = getPhysicsShape();
            
            if(!physicsShape)
                DEBUG_LOG_WRITE_W(TAG, "The PhysicsBodyRigid does not have a shape.\n");
            
            if(physicsShape && parent)
            {
//                m_btDefaultMotionState->setWorldTransform(transform);
                setWorldTransform(transform);
                
                f32 mass = 0;
                if(isDynamicPhysics())
                {
                    mass = getMass();
                }
                
                /*
                 m_linearVelocity.setValue(btScalar(0.0), btScalar(0.0), btScalar(0.0));
                 m_angularVelocity.setValue(btScalar(0.),btScalar(0.),btScalar(0.));
                 m_angularFactor.setValue(1,1,1);
                 m_linearFactor.setValue(1,1,1);
                 */
                
                btVector3 localInertia(physicsShape->calculateLocalInertia(mass));
                
                btRigidBody::btRigidBodyConstructionInfo cinfo(getMass(), m_btDefaultMotionState, physicsShape->getCollisionShape(), localInertia);
                
                if (m_btRigidBody)
                {
                    btVector3 linearVelocity(getVelocity());
                    btVector3 angularVelocity(getAngularVelocity());
                    btVector3 angularFactor(getAngularFactor());
                    btVector3 linearFactor(getLinearFactor());

                    
                    *m_btRigidBody = btRigidBody(cinfo);
                    
                    m_btRigidBody->setLinearFactor(linearFactor);
                    m_btRigidBody->setAngularVelocity(angularVelocity);
                    m_btRigidBody->setAngularFactor(angularFactor);
                    m_btRigidBody->setLinearVelocity(linearVelocity);
                }
                else
                {
                    m_btRigidBody = new btRigidBody(cinfo);
                }
                
                m_btRigidBody->setCollisionFlags(getCollisionFlags());
                m_btRigidBody->setActivationState(getActivationState());
                
                
                
                return physicsWorld->addRigidBody(this);
            }
        }
        else
        {
            DEBUG_LOG_WRITE_W(TAG, "The physics world is NULL\n");
        }
        return false;
    }
    
    bool PhysicsBodyRigid::removePhysicsBody()
    {
        Scene *scene = getParent()->getCurrentScene();
        if(!scene)
        {
            DEBUG_LOG_WRITE_W(TAG, "The scene is NULL\n");
            return false;
        }
        
        PhysicsWorld *physicsWorld = scene->getPhysicsWorld();
        if(physicsWorld)
            return physicsWorld->removeRigidBody(this);
        return false;
    }
    
    bool PhysicsBodyRigid::isInWorld()const
    {
        if(m_btRigidBody)
            return m_btRigidBody->isInWorld();
        return false;
    }
    
    PhysicsBodyRigid::ForceAndPosition::ForceAndPosition() :
    m_Force(new btVector3(0,0,0)),
    m_Position(new btVector3(0,0,0))
    {
    }

    PhysicsBodyRigid::ForceAndPosition::ForceAndPosition(const PhysicsBodyRigid::ForceAndPosition &copy) :
    m_Force(new btVector3(*(copy.m_Force))),
    m_Position(new btVector3(*(copy.m_Position)))
    {
    }

    PhysicsBodyRigid::ForceAndPosition &PhysicsBodyRigid::ForceAndPosition::operator=(const PhysicsBodyRigid::ForceAndPosition &rhs)
    {
        if(this != &rhs)
        {
            *m_Force = *(rhs.m_Force);
            *m_Position = *(rhs.m_Position);
        }
        return *this;
    }

    void PhysicsBodyRigid::ForceAndPosition::set(const btVector3 &force, const btVector3 &position)
    {
        *m_Force = force;
        *m_Position = position;
    }

    const btVector3 &PhysicsBodyRigid::ForceAndPosition::getForce()const
    {
        return *m_Force;
    }

    const btVector3 &PhysicsBodyRigid::ForceAndPosition::getPosition()const
    {
        return *m_Position;
    }
    
    void PhysicsBodyRigid::ForceAndPosition::clear()
    {
        *m_Position = btVector3(0,0,0);
        *m_Force = btVector3(0,0,0);
    }

}
