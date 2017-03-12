//
//  PhysicsBodySoft.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "PhysicsBodySoft.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsBodySoftBuilder.h"
#include "btSoftBody.h"
#include "PhysicsWorld.h"
#define FORMATSTRING "{\"njli::PhysicsBodySoft\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    PhysicsBodySoft::PhysicsBodySoft():
    m_btSoftBodyWorldInfo(new btSoftBodyWorldInfo()),
    m_btSoftBody(new btSoftBody(m_btSoftBodyWorldInfo))
    {
        
    }
    
    PhysicsBodySoft::PhysicsBodySoft(const AbstractBuilder &builder):
    m_btSoftBodyWorldInfo(new btSoftBodyWorldInfo()),
    m_btSoftBody(new btSoftBody(m_btSoftBodyWorldInfo))
    {
        
    }
    
    PhysicsBodySoft::PhysicsBodySoft(const PhysicsBodySoft &copy):
    m_btSoftBodyWorldInfo(new btSoftBodyWorldInfo()),
    m_btSoftBody(new btSoftBody(m_btSoftBodyWorldInfo))
    {
        
    }
    
    PhysicsBodySoft::~PhysicsBodySoft()
    {
        delete m_btSoftBodyWorldInfo;m_btSoftBodyWorldInfo=NULL;
        delete m_btSoftBody;m_btSoftBody=NULL;
    }
    
    PhysicsBodySoft &PhysicsBodySoft::operator=(const PhysicsBodySoft &rhs)
    {
        if(this != &rhs)
        {
            //TODO: implement...
        }
        return *this;
    }
    
    s32	PhysicsBodySoft::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsBodySoft::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsBodySoft::getClassName()const
    {
        return "PhysicsBodySoft";
    }
    
    s32 PhysicsBodySoft::getType()const
    {
        return PhysicsBodySoft::type();
    }
    
    PhysicsBodySoft::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsBodySoft **PhysicsBodySoft::createArray(const u32 size)
    {
        return (PhysicsBodySoft**)World::getInstance()->getWorldFactory()->createArray(PhysicsBodySoft::type(), size);
    }
    
    void PhysicsBodySoft::destroyArray(PhysicsBodySoft **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsBodySoft *PhysicsBodySoft::create()
    {
        return dynamic_cast<PhysicsBodySoft*>(World::getInstance()->getWorldFactory()->create(PhysicsBodySoft::type()));
    }
    
    PhysicsBodySoft *PhysicsBodySoft::create(const PhysicsBodySoftBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsBodySoft*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsBodySoft *PhysicsBodySoft::clone(const PhysicsBodySoft &object)
    {
        return dynamic_cast<PhysicsBodySoft*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsBodySoft *PhysicsBodySoft::copy(const PhysicsBodySoft &object)
    {
        return dynamic_cast<PhysicsBodySoft*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsBodySoft::destroy(PhysicsBodySoft *object)
    {
        if(object)
        {
            PhysicsBody::destroy(object);
        }
        
    }
    
    void PhysicsBodySoft::load(PhysicsBodySoft &object, lua_State *L, int index)
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
                PhysicsBodySoft::load(object, L, -2);
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
    
    u32 PhysicsBodySoft::type()
    {
        return JLI_OBJECT_TYPE_PhysicsBodySoft;
    }
    
    void PhysicsBodySoft::setWorldTransform(const btTransform &transform)
    {
    }
    
    bool PhysicsBodySoft::isInWorld()const
    {
        return false;
    }
    
    void PhysicsBodySoft::setMass(f32 mass)
    {
        
    }
    
    f32 PhysicsBodySoft::getMass()const
    {
        return 0;
    }
    
    const btVector3 &PhysicsBodySoft::getVelocity()const
    {
        return btVector3(0,0,0);
    }
    
    const btVector3 &PhysicsBodySoft::getAngularVelocity()const
    {
        return btVector3(0,0,0);
    }
    
//    void PhysicsBodySoft::setVelocity(const btVector3 &velocity)
//    {
//        enablePropertyChange();
//    }
//    
//    const btVector3 &PhysicsBodySoft::getVelocity()const
//    {
//        btVector3 t;
//        return t;
//    }
//    
//    void PhysicsBodySoft::setAngularVelocity(const btVector3 &velocity)
//    {
//        enablePropertyChange();
//    }
//    
//    const btVector3 &PhysicsBodySoft::getAngularVelocity()const
//    {
//        btVector3 t;
//        return t;
//    }
    
    const btCollisionObject* PhysicsBodySoft::getCollisionObject() const
    {
        return m_btSoftBody;
    }
    
    btCollisionObject* PhysicsBodySoft::getCollisionObject()
    {
        return m_btSoftBody;
    }
    
    void PhysicsBodySoft::setCollisionObject(const btCollisionObject &obj, PhysicsShape *shape)
    {
        DEBUG_ASSERT(shape);
        DEBUG_ASSERT(obj.getInternalType()&btCollisionObject::CO_SOFT_BODY);
        
        const btCollisionObject *_collisionObject = dynamic_cast<const btSoftBody *>(&obj);
        
        //TODO: Implement....
    }
    
    bool PhysicsBodySoft::setTransform(const btTransform &transform)
    {
        //TODO: Implement....
        return false;
    }
    
    bool PhysicsBodySoft::removePhysicsBody()
    {
        //TODO: Implement....
        return false;
    }
    
    const btSoftBody* PhysicsBodySoft::getBody() const
    {
        return dynamic_cast<const btSoftBody*>(m_btSoftBody);
    }
    
    btSoftBody* PhysicsBodySoft::getBody()
    {
        return dynamic_cast<btSoftBody*>(m_btSoftBody);
    }
}
