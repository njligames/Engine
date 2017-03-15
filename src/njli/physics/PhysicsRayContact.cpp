//
//  PhysicsRayContact.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 1/8/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "PhysicsRayContact.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsRayContactBuilder.h"

#include "btVector2.h"
#include "btVector3.h"
#include "Node.h"
#define FORMATSTRING "{\"njli::PhysicsRayContact\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    PhysicsRayContact::PhysicsRayContact():
    AbstractFactoryObject(this),
    m_closestHitFraction(0),
    m_hitNormalWorld(new btVector3()),
    m_hitPointWorld(new btVector3()),
    m_node(NULL),
    m_touchPosition(new btVector2())
    {
        
    }
    
    PhysicsRayContact::PhysicsRayContact(const AbstractBuilder &builder):
    AbstractFactoryObject(this),
    m_closestHitFraction(0),
    m_hitNormalWorld(new btVector3()),
    m_hitPointWorld(new btVector3()),
    m_node(NULL),
    m_touchPosition(new btVector2())
    {
        
    }
    
    PhysicsRayContact::PhysicsRayContact(const PhysicsRayContact &copy):
    AbstractFactoryObject(this),
    m_closestHitFraction(copy.m_closestHitFraction),
    m_hitNormalWorld(new btVector3(*(copy.m_hitNormalWorld))),
    m_hitPointWorld(new btVector3(*(copy.m_hitPointWorld))),
    m_node(NULL),
    m_touchPosition(new btVector2())
    {
        
    }
    
    PhysicsRayContact::~PhysicsRayContact()
    {
        delete m_touchPosition;m_touchPosition=NULL;
        delete m_hitPointWorld;m_hitPointWorld=NULL;
        delete m_hitNormalWorld;m_hitNormalWorld=NULL;
    }
    
    PhysicsRayContact &PhysicsRayContact::operator=(const PhysicsRayContact &rhs)
    {
        if(this != &rhs)
        {
            m_closestHitFraction = rhs.m_closestHitFraction;
            *m_hitNormalWorld = *(rhs.m_hitNormalWorld);
            *m_hitPointWorld = *(rhs.m_hitPointWorld);
            m_node = rhs.m_node;
        }
        return *this;
    }
    
    s32	PhysicsRayContact::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsRayContact::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsRayContact::getClassName()const
    {
        return "PhysicsRayContact";
    }
    
    s32 PhysicsRayContact::getType()const
    {
        return PhysicsRayContact::type();
    }
    
    PhysicsRayContact::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsRayContact **PhysicsRayContact::createArray(const u32 size)
    {
        return (PhysicsRayContact**)World::getInstance()->getWorldFactory()->createArray(PhysicsRayContact::type(), size);
    }
    
    void PhysicsRayContact::destroyArray(PhysicsRayContact **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsRayContact *PhysicsRayContact::create()
    {
        return dynamic_cast<PhysicsRayContact*>(World::getInstance()->getWorldFactory()->create(PhysicsRayContact::type()));
    }
    
    PhysicsRayContact *PhysicsRayContact::create(const PhysicsRayContactBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsRayContact*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsRayContact *PhysicsRayContact::clone(const PhysicsRayContact &object)
    {
        return dynamic_cast<PhysicsRayContact*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsRayContact *PhysicsRayContact::copy(const PhysicsRayContact &object)
    {
        return dynamic_cast<PhysicsRayContact*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsRayContact::destroy(PhysicsRayContact *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void PhysicsRayContact::load(PhysicsRayContact &object, lua_State *L, int index)
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
                PhysicsRayContact::load(object, L, -2);
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
    
    u32 PhysicsRayContact::type()
    {
        return JLI_OBJECT_TYPE_PhysicsRayContact;
    }
    
    f32 PhysicsRayContact::getClosestHitFraction()const
    {
        return m_closestHitFraction;
    }
    
    const btVector3 &PhysicsRayContact::getHitNormalWorld()const
    {
        return *m_hitNormalWorld;
    }
    
    const btVector3 &PhysicsRayContact::getHitPointWorld()const
    {
        return *m_hitPointWorld;
    }
    
    Node *PhysicsRayContact::getHitNode()const
    {
        return m_node;
    }
    
    const btVector2 &PhysicsRayContact::getTouchPosition()const
    {
        return *m_touchPosition;
    }
    
    void PhysicsRayContact::screenPosition(const btVector2 &pos)
    {
        *m_touchPosition = pos;
    }
    
    void PhysicsRayContact::set(f32 closestHitFraction,
                                const btVector3 &hitNormalWorld,
                                const btVector3 &hitPointWorld,
                                Node *node)
    {
        m_closestHitFraction = closestHitFraction;
        *m_hitNormalWorld = hitNormalWorld;
        *m_hitPointWorld = hitPointWorld;
        m_node = node;
        m_node->enableTouched();
    }
}
