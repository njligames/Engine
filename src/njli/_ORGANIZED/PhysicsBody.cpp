//
//  PhysicsBody.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "PhysicsBody.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "btManifoldPoint.h"
#include "btDispatcher.h"
#include "btCollisionObject.h"
#include "btVector3.h"
#include "PhysicsShape.h"
#include "btCollisionShape.h"
#include "PhysicsWorld.h"
#define FORMATSTRING "{\"njli::PhysicsBody\":[]}";

#include "PhysicsConstraint.h"

namespace njli
{
    PhysicsBody::PhysicsBody():
    AbstractFactoryObject(this),
//    m_PhysicsWorld(NULL),
    m_PhysicsShape(NULL),
//    m_VelocityFactor(new btVector3()),
//    m_AngularVelocityFactor(new btVector3()),
//    m_njliPhysicsType(JLI_PHYSICS_TYPE_Dynamic),
//    m_Mass(1.0f),
//    m_Charge(0.0f),
//    m_Friction(1.0f),
//    m_AngularFriction(1.0f),
//    m_Restitution(1.0f),
//    m_Damping(1.0f),
//    m_AngularDamping(1.0f),
    m_CategoryBitMask(JLI_BIT_CATEGORY_ALL),
    m_CollisionBitMask(JLI_BIT_CATEGORY_ALL),
//    m_TotalForce(new btVector3()),
//    m_TotalAngularForce(new btVector3()),
    m_RestingAllowed(true),
    m_IsResting(false),
    m_CollisionFlags(btCollisionObject::CF_STATIC_OBJECT),
    m_ActivationState(ACTIVE_TAG)
    {
        
    }
    
    PhysicsBody::PhysicsBody(const AbstractBuilder &builder):
    AbstractFactoryObject(this),
//    m_PhysicsWorld(NULL),
    m_PhysicsShape(NULL),
//    m_VelocityFactor(new btVector3()),
//    m_AngularVelocityFactor(new btVector3()),
//    m_njliPhysicsType(JLI_PHYSICS_TYPE_Dynamic),
//    m_Mass(1.0f),
//    m_Charge(0.0f),
//    m_Friction(1.0f),
//    m_AngularFriction(1.0f),
//    m_Restitution(1.0f),
//    m_Damping(1.0f),
//    m_AngularDamping(1.0f),
    m_CategoryBitMask(JLI_BIT_CATEGORY_ALL),
    m_CollisionBitMask(JLI_BIT_CATEGORY_ALL),
//    m_TotalForce(new btVector3()),
//    m_TotalAngularForce(new btVector3()),
    m_RestingAllowed(true),
    m_IsResting(false),
    m_CollisionFlags(btCollisionObject::CF_STATIC_OBJECT),
    m_ActivationState(ACTIVE_TAG)
    {
        
    }
    
    PhysicsBody::PhysicsBody(const PhysicsBody &copy):
    AbstractFactoryObject(this),
//    m_PhysicsWorld(NULL),
    m_PhysicsShape(NULL),
//    m_VelocityFactor(new btVector3()),
//    m_AngularVelocityFactor(new btVector3()),
//    m_njliPhysicsType(JLI_PHYSICS_TYPE_Dynamic),
//    m_Mass(1.0f),
//    m_Charge(0.0f),
//    m_Friction(1.0f),
//    m_AngularFriction(1.0f),
//    m_Restitution(1.0f),
//    m_Damping(1.0f),
//    m_AngularDamping(1.0f),
    m_CategoryBitMask(JLI_BIT_CATEGORY_ALL),
    m_CollisionBitMask(JLI_BIT_CATEGORY_ALL),
//    m_TotalForce(new btVector3()),
//    m_TotalAngularForce(new btVector3()),
    m_RestingAllowed(true),
    m_IsResting(false),
    m_CollisionFlags(btCollisionObject::CF_STATIC_OBJECT),
    m_ActivationState(ACTIVE_TAG)
    {
        
    }
    
    PhysicsBody::~PhysicsBody()
    {
        
    }
    
    PhysicsBody &PhysicsBody::operator=(const PhysicsBody &rhs)
    {
        if(this != &rhs)
        {
            //TODO:implement....
        }
        return *this;
    }
    
    PhysicsBody *PhysicsBody::create(u32 type)
    {
        DEBUG_ASSERT(type == JLI_OBJECT_TYPE_PhysicsBodyRigid ||
                  type == JLI_OBJECT_TYPE_PhysicsBodySoft ||
                  type == JLI_OBJECT_TYPE_PhysicsBodyGhost);
        
        return dynamic_cast<PhysicsBody*>(World::getInstance()->getWorldFactory()->create(type));
    }
    
    void PhysicsBody::destroy(PhysicsBody *object)
    {
        if(object)
        {
            object->removePhysicsShape();
            
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void PhysicsBody::load(PhysicsBody &object, lua_State *L, int index)
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
                PhysicsBody::load(object, L, -2);
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
    
    u32 PhysicsBody::type()
    {
        return JLI_OBJECT_TYPE_PhysicsBody;
    }
    
    void PhysicsBody::handleCollide(PhysicsBody *body, const btManifoldPoint&pt)
    {
        if (body->getPhysicsShape() && m_PhysicsShape)
        {
            char buffer[BUFFER_SIZE] = "__NJLINodeCollide";
            njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer, getParent(), body->getParent(), pt);
        }
    }
    
    void PhysicsBody::handleCollisionNear(PhysicsBody *body, const btDispatcherInfo& dispatchInfo)
    {
        if (m_PhysicsShape)
        {
            char buffer[BUFFER_SIZE] = "__NJLINodeNear";
            njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer, getParent(), body->getParent(), dispatchInfo);
        }
        
    }
//    void PhysicsBody::addPhysicsWorld(PhysicsWorld *world)
//    {
//        DEBUG_ASSERT(world != NULL);
//        
//        if(getPhysicsWorld())
//            removeChild(getPhysicsWorld());
//        
//        m_PhysicsWorld = world;
//        
//        addChild(m_PhysicsWorld);
//    }
//    
//    void PhysicsBody::removePhysicsWorld()
//    {
//        if(getPhysicsWorld())
//            removeChild(getPhysicsWorld());
//        
//        m_PhysicsWorld = NULL;
//    }
//    
//    PhysicsWorld *PhysicsBody::getPhysicsWorld()
//    {
//        s32 idx = getChildIndex(m_PhysicsWorld);
//        if(idx != -1)
//            return dynamic_cast<PhysicsWorld*>(getChild(idx));
//        return NULL;
//    }
//    
//    const PhysicsWorld *PhysicsBody::getPhysicsWorld() const
//    {
//        s32 idx = getChildIndex(m_PhysicsWorld);
//        if(idx != -1)
//            return dynamic_cast<const PhysicsWorld*>(getChild(idx));
//        return NULL;
//    }
    
    void PhysicsBody::setPhysicsShape(PhysicsShape *shape)
    {
        DEBUG_ASSERT(shape != NULL);
        
        if(getPhysicsShape())
            removeChild(getPhysicsShape());
        
        m_PhysicsShape = shape;
        
        addChild(m_PhysicsShape);
        
        
        
        
        
        
        
        
        
        
//        Node *node = getParent();
//        Geometry *geometry = node->getGeometry();
//        if(geometry)
//        {
//            geometry->setTransform(node->getGeometryIndex(), node->getWorldTransform());
//            PhysicsBody *physicsBody = node->getPhysicsBody();
//            if(physicsBody)
//                geometry->applyShape(node, physicsBody->getPhysicsShape());
//        }
    }
    
    void PhysicsBody::removePhysicsShape()
    {
        if(getPhysicsShape())
        {
            removeChild(getPhysicsShape());
        }
        
        m_PhysicsShape = NULL;
    }
    
    PhysicsShape *PhysicsBody::getPhysicsShape()
    {
        s32 idx = getChildIndex(m_PhysicsShape);
        if(idx != -1)
            return dynamic_cast<PhysicsShape*>(getChild(idx));
        return NULL;
    }
    
    const PhysicsShape *PhysicsBody::getPhysicsShape()const
    {
        s32 idx = getChildIndex(m_PhysicsShape);
        if(idx != -1)
        {
//            DEBUG_ASSERT(dynamic_cast<const PhysicsShape*>(getChild(idx)));
            return dynamic_cast<const PhysicsShape*>(getChild(idx));
        }
        return NULL;
    }
    
    btTransform PhysicsBody::getWorldTransform()const
    {
        return getCollisionObject()->getWorldTransform();
    }
    
    void PhysicsBody::setFriction(f32 friction)
    {
        getCollisionObject()->setFriction(friction);
    }
    
    f32 PhysicsBody::getFriction()const
    {
        return getCollisionObject()->getFriction();
    }
    
    void PhysicsBody::setAngularFriction(f32 friction)
    {
        getCollisionObject()->setRollingFriction(friction);
    }
    
    f32 PhysicsBody::getAngularFriction()const
    {
        return getCollisionObject()->getRollingFriction();
    }
    
    void PhysicsBody::setRestitution(f32 restitution)
    {
        getCollisionObject()->setRestitution(restitution);
    }
    
    f32 PhysicsBody::getRestitution()const
    {
        return getCollisionObject()->getRestitution();
    }
    
    void PhysicsBody::setPhysicsType(njliPhysicsType type)
    {
        DEBUG_ASSERT(type > JLI_PHYSICS_TYPE_NONE &&
                  type < JLI_PHYSICS_TYPE_MAX);
        
        switch (type)
        {
            case JLI_PHYSICS_TYPE_Dynamic:
                setDynamicPhysics();
                break;
            case JLI_PHYSICS_TYPE_Kinematic:
                setKinematicPhysics();
                break;
            case JLI_PHYSICS_TYPE_Static:
                setStaticPhysics();
                break;
            default:
                break;
        }
        
        if(PhysicsBody::getParent() && getPhysicsShape())
        {
            btTransform t = getWorldTransform();
            setTransform(t);
        }
    }
    
    njliPhysicsType PhysicsBody::getPhysicsType()const
    {
        if(isKinematicPhysics())
            return JLI_PHYSICS_TYPE_Kinematic;
        
        if(isStaticPhysics())
            return JLI_PHYSICS_TYPE_Static;
        
        if(isDynamicPhysics())
            return JLI_PHYSICS_TYPE_Dynamic;
        
        return JLI_PHYSICS_TYPE_NONE;
    }
    
    void PhysicsBody::setCollisionGroup(njliBitCategories categoryBitMask)
    {
        m_CategoryBitMask = categoryBitMask;
        if(PhysicsBody::getParent() && getPhysicsShape())
        {
            btTransform t = getWorldTransform();
            setTransform(t);
        }
    }
    
    njliBitCategories PhysicsBody::getCollisionGroup()const
    {
        return m_CategoryBitMask;
    }
    
    void PhysicsBody::setCollisionMask(njliBitCategories categoryBitMask)
    {
        m_CollisionBitMask = categoryBitMask;
        if(PhysicsBody::getParent() && getPhysicsShape())
        {
            btTransform t = getWorldTransform();
            setTransform(t);
        }
    }
    
    njliBitCategories PhysicsBody::getCollisionMask()const
    {
        return m_CollisionBitMask;
    }
    
    
    void PhysicsBody::setStaticPhysics()
    {
        m_CollisionFlags = On(m_CollisionFlags, btCollisionObject::CF_STATIC_OBJECT);
        m_CollisionFlags = Off(m_CollisionFlags, btCollisionObject::CF_KINEMATIC_OBJECT);
        m_ActivationState = ACTIVE_TAG;
        
        if(getCollisionObject())
        {
            getCollisionObject()->setCollisionFlags(m_CollisionFlags);
            getCollisionObject()->setActivationState(m_ActivationState);
        }
        
        if(PhysicsBody::getParent() && getPhysicsShape())
        {
            btTransform t = getWorldTransform();
            setTransform(t);
        }
    }
    void PhysicsBody::setKinematicPhysics()
    {
        m_CollisionFlags = On(m_CollisionFlags, btCollisionObject::CF_KINEMATIC_OBJECT);
        m_CollisionFlags = Off(m_CollisionFlags, btCollisionObject::CF_STATIC_OBJECT);
        m_ActivationState = DISABLE_DEACTIVATION;
        
        if(getCollisionObject())
        {
            getCollisionObject()->setCollisionFlags(m_CollisionFlags);
            getCollisionObject()->setActivationState(m_ActivationState);
        }
        
        if(PhysicsBody::getParent() && getPhysicsShape())
        {
            btTransform t = getWorldTransform();
            setTransform(t);
        }
    }
    void PhysicsBody::setDynamicPhysics()
    {
        m_CollisionFlags = Off(m_CollisionFlags, btCollisionObject::CF_KINEMATIC_OBJECT);
        m_CollisionFlags = Off(m_CollisionFlags, btCollisionObject::CF_STATIC_OBJECT);
        m_ActivationState = ACTIVE_TAG;
        
        if(getCollisionObject())
        {
            getCollisionObject()->setCollisionFlags(m_CollisionFlags);
            getCollisionObject()->setActivationState(m_ActivationState);
        }
        
        if(PhysicsBody::getParent() && getPhysicsShape())
        {
            btTransform t = getWorldTransform();
            setTransform(t);
        }
    }
    void PhysicsBody::enableContactResponse(bool enable)
    {
        if(enable)
        {
            m_CollisionFlags = Off(m_CollisionFlags, btCollisionObject::CF_NO_CONTACT_RESPONSE);
        }
        else
        {
            m_CollisionFlags = On(m_CollisionFlags, btCollisionObject::CF_NO_CONTACT_RESPONSE);
        }
        
        if(getCollisionObject())
        {
            getCollisionObject()->setCollisionFlags(m_CollisionFlags);
        }
    }
    void PhysicsBody::enableHandleCollideCallback(bool enable)
    {
        if(enable)
        {
            m_CollisionFlags = On(m_CollisionFlags, btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
        }
        else
        {
            m_CollisionFlags = Off(m_CollisionFlags, btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
        }
        
        if(getCollisionObject())
        {
            getCollisionObject()->setCollisionFlags(m_CollisionFlags);
        }
    }
    
    bool PhysicsBody::isStaticPhysics()const
    {
        return IsOn(m_CollisionFlags, btCollisionObject::CF_STATIC_OBJECT);
    }
    
    bool PhysicsBody::isKinematicPhysics()const
    {
        return IsOn(m_CollisionFlags, btCollisionObject::CF_KINEMATIC_OBJECT);
    }
    
    bool PhysicsBody::isDynamicPhysics()const
    {
        return (!(IsOn(m_CollisionFlags, btCollisionObject::CF_STATIC_OBJECT)) &&
                !(IsOn(m_CollisionFlags, btCollisionObject::CF_KINEMATIC_OBJECT)));
    }
    
    bool PhysicsBody::isResting()const
    {
        return m_IsResting;
    }
    
    void PhysicsBody::enableResting(bool enable)
    {
        m_RestingAllowed = enable;
    }
    
    
    
    
    s32 PhysicsBody::setPhysicsConstraint(PhysicsConstraint *constraint)
    {
        DEBUG_ASSERT(NULL != constraint);
        
        Scene *scene = getParent()->getCurrentScene();
        DEBUG_ASSERT(NULL != scene);
        
        if (getParent() && getParent()->getParentNode())
        {
            DEBUG_LOG_W("PHYSICSBODY", "%s - %s->%s", "**ADDING A CONSTRAINT TO A CHILD NODE OTHER THAN THE ROOT**", getParent()->getName(), getParent()->getParentNode()->getName());
        }
//        DEBUG_LOG_PRINT_W("PHYSICSBODY", "%s", (getParent() && getParent()->getParentNode())?"**ADDING A CONSTRAINT TO A CHILD NODE OTHER THAN THE ROOT**\n":"");
        
        std::vector<PhysicsConstraint*>::const_iterator iter = std::find(m_PhysicsConstraintList.begin(), m_PhysicsConstraintList.end(), constraint);
        
        if(iter == m_PhysicsConstraintList.end())
        {
            std::vector<PhysicsConstraint*>::iterator iter = std::find(m_PhysicsConstraintList.begin(), m_PhysicsConstraintList.end(), constraint);
            
            if(iter != m_PhysicsConstraintList.end())
                removeChild(constraint);
            
            m_PhysicsConstraintList.push_back(constraint);
            
            addChild(constraint);
            //!!!TODO:
            //!!!TODO:            scene->addActivePhysicsConstraint(constraint);
        }
        
        return getPhysicsConstraintIndex(constraint);
    }
    
    bool PhysicsBody::removePhysicsConstraint(PhysicsConstraint *constraint)
    {
        DEBUG_ASSERT(NULL != constraint);
        
        Scene *scene = getParent()->getCurrentScene();
        DEBUG_ASSERT(NULL != scene);
        
        std::vector<PhysicsConstraint*>::iterator iter = std::find(m_PhysicsConstraintList.begin(), m_PhysicsConstraintList.end(), constraint);
        
        if(iter != m_PhysicsConstraintList.end())
        {
            removeChild(*iter);
            //!!!TODO:            scene->removeActivePhysicsConstraint(*iter);
            
            m_PhysicsConstraintList.erase(iter);
            return true;
        }
        return false;
    }
    
    void PhysicsBody::removeAllPhysicsConstraints()
    {
        for(std::vector<PhysicsConstraint*>::iterator iter = m_PhysicsConstraintList.begin();
            iter != m_PhysicsConstraintList.end();
            ++iter)
        {
            removeChild(*iter);
        }
        m_PhysicsConstraintList.clear();
    }
    
    void PhysicsBody::getPhysicsConstraints(std::vector<PhysicsConstraint*> &particleEmitters)const
    {
        for(std::vector<PhysicsConstraint*>::const_iterator iter = m_PhysicsConstraintList.begin();
            iter != m_PhysicsConstraintList.end();
            ++iter)
        {
            if(getChildIndex(*iter) != -1)
                particleEmitters.push_back(*iter);
        }
    }
    
    s32 PhysicsBody::getPhysicsConstraintIndex(PhysicsConstraint *sound)const
    {
        std::vector<PhysicsConstraint*>::const_iterator iter = std::find(m_PhysicsConstraintList.begin(), m_PhysicsConstraintList.end(), sound);
        
        if (iter != m_PhysicsConstraintList.end())
        {
            return std::distance(m_PhysicsConstraintList.begin(), iter);
        }
        return -1;
    }
    
    PhysicsConstraint *PhysicsBody::getPhysicsConstraint(const u32 index)
    {
        if (index < m_PhysicsConstraintList.size())
        {
            s32 idx = getChildIndex(m_PhysicsConstraintList.at(index));
            if(idx != -1)
                return dynamic_cast<PhysicsConstraint*>(getChild(idx));
        }
        return NULL;
    }
    
    const PhysicsConstraint *PhysicsBody::getPhysicsConstraint(const u32 index)const
    {
        if (index < m_PhysicsConstraintList.size())
        {
            s32 idx = getChildIndex(m_PhysicsConstraintList.at(index));
            if(idx != -1)
                return dynamic_cast<const PhysicsConstraint*>(getChild(idx));
        }
        return NULL;
    }
    
    bool PhysicsBody::hasPhysicsConstraint()const
    {
        unsigned long constraintListSize = m_PhysicsConstraintList.size();
        const btRigidBody *rigidBody = dynamic_cast<const btRigidBody*>(getCollisionObject());
        
        DEBUG_ASSERT(rigidBody->getNumConstraintRefs() == constraintListSize);
        
//        DEBUG_LOG_PRINT_V("hasPhysicsConstraint", "hasPhysicsConstraint: %d", s);
        return constraintListSize > 0;
    }
    
    
//    void PhysicsBody::enablePropertyChange(bool enable)
//    {
//        m_PropertyChanged = enable;
//    }
//    
//    bool PhysicsBody::isPropertyChanged()const
//    {
//        if(getPhysicsShape())
//            return m_PropertyChanged || getPhysicsShape()->isPropertyChanged();
//        return m_PropertyChanged;
//    }
    
    Node *PhysicsBody::getParent()
    {
        return dynamic_cast<Node*>(AbstractDecorator::getParent());
    }
    
    const Node *PhysicsBody::getParent()const
    {
        return dynamic_cast<const Node*>(AbstractDecorator::getParent());
    }
    
    s32 PhysicsBody::getCollisionFlags()const
    {
        return m_CollisionFlags;
    }
    
    s32 PhysicsBody::getActivationState()const
    {
        return m_ActivationState;
    }
}
