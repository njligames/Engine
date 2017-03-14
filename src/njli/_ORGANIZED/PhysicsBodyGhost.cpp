//
//  PhysicsBodyGhost.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "PhysicsBodyGhost.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "btGhostObject.h"
#include "PhysicsWorld.h"
#define FORMATSTRING "{\"njli::PhysicsBodyGhost\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    PhysicsBodyGhost::PhysicsBodyGhost()
    {
        
    }
    
    PhysicsBodyGhost::PhysicsBodyGhost(const AbstractBuilder &builder)
    {
        
    }
    
    PhysicsBodyGhost::PhysicsBodyGhost(const PhysicsBodyGhost &copy)
    {
        
    }
    
    PhysicsBodyGhost::~PhysicsBodyGhost()
    {
        
    }
    
    PhysicsBodyGhost &PhysicsBodyGhost::operator=(const PhysicsBodyGhost &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	PhysicsBodyGhost::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsBodyGhost::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsBodyGhost::getClassName()const
    {
        return "PhysicsBodyGhost";
    }
    
    s32 PhysicsBodyGhost::getType()const
    {
        return PhysicsBodyGhost::type();
    }
    
    PhysicsBodyGhost::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsBodyGhost **PhysicsBodyGhost::createArray(const u32 size)
    {
        return (PhysicsBodyGhost**)World::getInstance()->getWorldFactory()->createArray(PhysicsBodyGhost::type(), size);
    }
    
    void PhysicsBodyGhost::destroyArray(PhysicsBodyGhost **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsBodyGhost *PhysicsBodyGhost::create()
    {
        return dynamic_cast<PhysicsBodyGhost*>(World::getInstance()->getWorldFactory()->create(PhysicsBodyGhost::type()));
    }
    
    PhysicsBodyGhost *PhysicsBodyGhost::create(const PhysicsBodyGhostBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsBodyGhost*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsBodyGhost *PhysicsBodyGhost::clone(const PhysicsBodyGhost &object)
    {
        return dynamic_cast<PhysicsBodyGhost*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsBodyGhost *PhysicsBodyGhost::copy(const PhysicsBodyGhost &object)
    {
        return dynamic_cast<PhysicsBodyGhost*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsBodyGhost::destroy(PhysicsBodyGhost *object)
    {
        if(object)
        {
            PhysicsBody::destroy(object);
        }
    }
    
    void PhysicsBodyGhost::load(PhysicsBodyGhost &object, lua_State *L, int index)
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
                PhysicsBodyGhost::load(object, L, -2);
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
    
    u32 PhysicsBodyGhost::type()
    {
        return JLI_OBJECT_TYPE_PhysicsBodyGhost;
    }
    
    void PhysicsBodyGhost::setWorldTransform(const btTransform &transform)
    {
    }
    
    bool PhysicsBodyGhost::isInWorld()const
    {
        return false;
    }
    
    void PhysicsBodyGhost::setMass(f32 mass)
    {
        
    }
    
    f32 PhysicsBodyGhost::getMass()const
    {
        return 0;
    }
    
    const btVector3 &PhysicsBodyGhost::getVelocity()const
    {
        return btVector3(0,0,0);
    }
    const btVector3 &PhysicsBodyGhost::getAngularVelocity()const
    {
        return btVector3(0,0,0);
    }
    
//    void PhysicsBodyGhost::setVelocity(const btVector3 &velocity)
//    {
//        enablePropertyChange();
//    }
//    
//    const btVector3 &PhysicsBodyGhost::getVelocity()const
//    {
//        btVector3 t;
//        return t;
//    }
//    
//    void PhysicsBodyGhost::setAngularVelocity(const btVector3 &velocity)
//    {
//        enablePropertyChange();
//    }
//    
//    const btVector3 &PhysicsBodyGhost::getAngularVelocity()const
//    {
//        btVector3 t;
//        return t;
//    }
    
    const btCollisionObject* PhysicsBodyGhost::getCollisionObject() const
    {
        return m_btPairCachingGhostObject;
    }
    
    btCollisionObject* PhysicsBodyGhost::getCollisionObject()
    {
        return m_btPairCachingGhostObject;
    }
    
    void PhysicsBodyGhost::setCollisionObject(const btCollisionObject &obj, PhysicsShape *shape)
    {
        DEBUG_ASSERT(shape);
        DEBUG_ASSERT(obj.getInternalType()&btCollisionObject::CO_GHOST_OBJECT);
        
        const btCollisionObject *_collisionObject = dynamic_cast<const btPairCachingGhostObject *>(&obj);
        
        //TODO: Implement....
    }
    
    bool PhysicsBodyGhost::setTransform(const btTransform &transform)
    {
        //TODO: Implement....
        return false;
    }
    
    bool PhysicsBodyGhost::removePhysicsBody()
    {
        //TODO: Implement....
        return false;
    }
    
    const btPairCachingGhostObject* PhysicsBodyGhost::getBody() const
    {
        return dynamic_cast<const btPairCachingGhostObject*>(m_btPairCachingGhostObject);
    }
    
    btPairCachingGhostObject* PhysicsBodyGhost::getBody()
    {
        return dynamic_cast<btPairCachingGhostObject*>(m_btPairCachingGhostObject);
    }
}
