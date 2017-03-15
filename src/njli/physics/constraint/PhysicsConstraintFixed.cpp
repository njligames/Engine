//
//  PhysicsConstraintFixed.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 6/19/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "PhysicsConstraintFixed.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsConstraintFixedBuilder.h"
#define TAG "PhysicsConstraintFixed.cpp"

#include "btFixedConstraint.h"
#include "PhysicsWorld.h"
#include "PhysicsBody.h"

#define FORMATSTRING "{\"njli::PhysicsConstraintFixed\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    PhysicsConstraintFixed::PhysicsConstraintFixed():
    PhysicsConstraint(),
    m_btFixedConstraint(NULL)
    {
        
    }
    
    PhysicsConstraintFixed::PhysicsConstraintFixed(const AbstractBuilder &builder):
    PhysicsConstraint(builder),
    m_btFixedConstraint(NULL)
    {
        
    }
    
    PhysicsConstraintFixed::PhysicsConstraintFixed(const PhysicsConstraintFixed &copy):
    PhysicsConstraint(copy),
    m_btFixedConstraint(NULL)
    {
        
    }
    
    PhysicsConstraintFixed::~PhysicsConstraintFixed()
    {
        removeConstraint();
    }
    
    PhysicsConstraintFixed &PhysicsConstraintFixed::operator=(const PhysicsConstraintFixed &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	PhysicsConstraintFixed::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsConstraintFixed::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsConstraintFixed::getClassName()const
    {
        return "PhysicsConstraintFixed";
    }
    
    s32 PhysicsConstraintFixed::getType()const
    {
        return PhysicsConstraintFixed::type();
    }
    
    PhysicsConstraintFixed::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsConstraintFixed **PhysicsConstraintFixed::createArray(const u32 size)
    {
        return (PhysicsConstraintFixed**)World::getInstance()->getWorldFactory()->createArray(PhysicsConstraintFixed::type(), size);
    }
    
    void PhysicsConstraintFixed::destroyArray(PhysicsConstraintFixed **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsConstraintFixed *PhysicsConstraintFixed::create()
    {
        return dynamic_cast<PhysicsConstraintFixed*>(World::getInstance()->getWorldFactory()->create(PhysicsConstraintFixed::type()));
    }
    
    PhysicsConstraintFixed *PhysicsConstraintFixed::create(const PhysicsConstraintFixedBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsConstraintFixed*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsConstraintFixed *PhysicsConstraintFixed::clone(const PhysicsConstraintFixed &object)
    {
        return dynamic_cast<PhysicsConstraintFixed*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsConstraintFixed *PhysicsConstraintFixed::copy(const PhysicsConstraintFixed &object)
    {
        return dynamic_cast<PhysicsConstraintFixed*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsConstraintFixed::destroy(PhysicsConstraintFixed *object)
    {
        if(object)
        {
            PhysicsConstraint::destroy(object);
        }
    }
    
    void PhysicsConstraintFixed::load(PhysicsConstraintFixed &object, lua_State *L, int index)
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
                PhysicsConstraintFixed::load(object, L, -2);
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
    
    u32 PhysicsConstraintFixed::type()
    {
        return JLI_OBJECT_TYPE_PhysicsConstraintFixed;
    }
    
    void PhysicsConstraintFixed::setNodes(Node *nodeA, Node *nodeB, const btTransform& frameInA,const btTransform& frameInB)
    {
        DEBUG_ASSERT(nodeA && nodeB);
        
        if(nodeA && !nodeA->getPhysicsBody()->isDynamicPhysics())
            DEBUG_LOG_W(TAG, "%s", nodeA->getName());
        
        if(nodeB && !nodeB->getPhysicsBody()->isDynamicPhysics())
            DEBUG_LOG_W(TAG, "%s", nodeB->getName());
        
        DEBUG_ASSERT(nodeA->getPhysicsBody());
        DEBUG_ASSERT(nodeB->getPhysicsBody());
        
        btRigidBody *rigidBodyA = NULL;
        btRigidBody *rigidBodyB = NULL;
        
        if(nodeA)
            rigidBodyA = dynamic_cast<btRigidBody*>(nodeA->getPhysicsBody()->getCollisionObject());
        
        if(nodeB)
            rigidBodyB = dynamic_cast<btRigidBody*>(nodeB->getPhysicsBody()->getCollisionObject());
        
        removeConstraint();
        
        m_btFixedConstraint = new btFixedConstraint(*rigidBodyA, *rigidBodyB, frameInA, frameInB);
        
        if(rigidBodyA)
            getNodeA()->getPhysicsBody()->setPhysicsConstraint(this);
        if(rigidBodyB)
            getNodeB()->getPhysicsBody()->setPhysicsConstraint(this);
        
//        Scene *scene = njli::World::getInstance()->getScene();
        Scene *scene = getParent()->getParent()->getCurrentScene();
        scene->getPhysicsWorld()->addConstraint(this);
    }
    
    btTypedConstraint *PhysicsConstraintFixed::getConstraint()
    {
        return m_btFixedConstraint;
    }
    
    const btTypedConstraint *PhysicsConstraintFixed::getConstraint()const
    {
        return m_btFixedConstraint;
    }
    
    void PhysicsConstraintFixed::removeConstraint()
    {
        PhysicsConstraint::removeConstraint();
        
        if(m_btFixedConstraint)
            delete m_btFixedConstraint;
        m_btFixedConstraint = NULL;
    }
}
