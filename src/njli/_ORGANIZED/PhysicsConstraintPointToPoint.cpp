//
//  PhysicsConstraintPointToPoint.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 6/15/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "PhysicsConstraintPointToPoint.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsConstraintPointToPointBuilder.h"

#define TAG "PhysicsConstraintPointToPoint.cpp"

#include "Node.h"
#include "PhysicsBody.h"
#include "PhysicsWorld.h"
#include "btPoint2PointConstraint.h"

#define FORMATSTRING "{\"njli::PhysicsConstraintPointToPoint\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    PhysicsConstraintPointToPoint::PhysicsConstraintPointToPoint():
    PhysicsConstraint(),
    m_btPoint2PointConstraint(NULL)
    {
        
    }
    
    PhysicsConstraintPointToPoint::PhysicsConstraintPointToPoint(const AbstractBuilder &builder):
    PhysicsConstraint(builder),
    m_btPoint2PointConstraint(NULL)
    {
        
    }
    
    PhysicsConstraintPointToPoint::PhysicsConstraintPointToPoint(const PhysicsConstraintPointToPoint &copy):
    PhysicsConstraint(copy),
    m_btPoint2PointConstraint(NULL)
    {
        
    }
    
    PhysicsConstraintPointToPoint::~PhysicsConstraintPointToPoint()
    {
//        removeConstraint();
    }
    
    PhysicsConstraintPointToPoint &PhysicsConstraintPointToPoint::operator=(const PhysicsConstraintPointToPoint &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	PhysicsConstraintPointToPoint::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsConstraintPointToPoint::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsConstraintPointToPoint::getClassName()const
    {
        return "PhysicsConstraintPointToPoint";
    }
    
    s32 PhysicsConstraintPointToPoint::getType()const
    {
        return JLI_OBJECT_TYPE_PhysicsConstraintPointToPoint;
    }
    
    PhysicsConstraintPointToPoint::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsConstraintPointToPoint **PhysicsConstraintPointToPoint::createArray(const u32 size)
    {
        return (PhysicsConstraintPointToPoint**)World::getInstance()->getWorldFactory()->createArray(PhysicsConstraintPointToPoint::type(), size);
    }
    
    void PhysicsConstraintPointToPoint::destroyArray(PhysicsConstraintPointToPoint **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsConstraintPointToPoint *PhysicsConstraintPointToPoint::create()
    {
        return dynamic_cast<PhysicsConstraintPointToPoint*>(World::getInstance()->getWorldFactory()->create(PhysicsConstraintPointToPoint::type()));
    }
    
    PhysicsConstraintPointToPoint *PhysicsConstraintPointToPoint::create(const PhysicsConstraintPointToPointBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsConstraintPointToPoint*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsConstraintPointToPoint *PhysicsConstraintPointToPoint::clone(const PhysicsConstraintPointToPoint &object)
    {
        return dynamic_cast<PhysicsConstraintPointToPoint*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsConstraintPointToPoint *PhysicsConstraintPointToPoint::copy(const PhysicsConstraintPointToPoint &object)
    {
        return dynamic_cast<PhysicsConstraintPointToPoint*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsConstraintPointToPoint::destroy(PhysicsConstraintPointToPoint *object)
    {
        if(object)
        {
            PhysicsConstraint::destroy(object);
        }
        
    }
    
    void PhysicsConstraintPointToPoint::load(PhysicsConstraintPointToPoint &object, lua_State *L, int index)
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
                PhysicsConstraintPointToPoint::load(object, L, -2);
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
    
    u32 PhysicsConstraintPointToPoint::type()
    {
        return JLI_OBJECT_TYPE_PhysicsConstraintPointToPoint;
    }
    
    void PhysicsConstraintPointToPoint::setNodes(Node *nodeA, Node *nodeB, const btVector3& pivotInA,const btVector3& pivotInB)
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
            m_btPoint2PointConstraint = new btPoint2PointConstraint(*rigidBodyA, pivotInA);
        }
        else if (rigidBodyA && rigidBodyB)
        {
            m_btPoint2PointConstraint = new btPoint2PointConstraint(*rigidBodyA, *rigidBodyB,
                                                                    pivotInA, pivotInB);
        }
        
        DEBUG_ASSERT(m_btPoint2PointConstraint);
        
        if(rigidBodyA)
            getNodeA()->getPhysicsBody()->setPhysicsConstraint(this);
        if(rigidBodyB)
            getNodeB()->getPhysicsBody()->setPhysicsConstraint(this);
        
//        Scene *scene = njli::World::getInstance()->getScene();
        Scene *scene = getParent()->getParent()->getCurrentScene();
        scene->getPhysicsWorld()->addConstraint(this);
    }
    
    void PhysicsConstraintPointToPoint::setNodes(Node *nodeA, const btVector3& pivotInA)
    {
        setNodes(nodeA, NULL, pivotInA, pivotInA);
    }
    
    void PhysicsConstraintPointToPoint::setPivotInA(const btVector3 &pivot)
    {
        dynamic_cast<btPoint2PointConstraint*>(getConstraint())->setPivotA(pivot);
    }
    
    void PhysicsConstraintPointToPoint::setPivotInB(const btVector3 &pivot)
    {
        dynamic_cast<btPoint2PointConstraint*>(getConstraint())->setPivotB(pivot);
    }
    
    const btVector3 &PhysicsConstraintPointToPoint::getPivotInA()const
    {
        return dynamic_cast<const btPoint2PointConstraint*>(getConstraint())->getPivotInA();
    }
    
    const btVector3 &PhysicsConstraintPointToPoint::getPivotInB()const
    {
        return dynamic_cast<const btPoint2PointConstraint*>(getConstraint())->getPivotInB();
    }
    
    btTypedConstraint *PhysicsConstraintPointToPoint::getConstraint()
    {
        return m_btPoint2PointConstraint;
    }
    
    const btTypedConstraint *PhysicsConstraintPointToPoint::getConstraint()const
    {
        return m_btPoint2PointConstraint;
    }
    
    void PhysicsConstraintPointToPoint::removeConstraint()
    {
        PhysicsConstraint::removeConstraint();
        
        if(m_btPoint2PointConstraint)
            delete m_btPoint2PointConstraint;
        m_btPoint2PointConstraint = NULL;
    }
}
