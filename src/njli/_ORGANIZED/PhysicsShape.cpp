//
//  PhysicsShape.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "PhysicsShape.h"
#include "JLIFactoryTypes.h"
#include "World.h"
//#include "PhysicsShapeBuilder.h"
#include "btRigidBody.h"
#include "btMotionState.h"
#include "btCollisionShape.h"
#include "PhysicsBody.h"
#define FORMATSTRING "{\"njli::PhysicsShape\":[]}";

namespace njli
{
    PhysicsShape::PhysicsShape():
    AbstractFactoryObject(this)
    {
        
    }
    
    PhysicsShape::PhysicsShape(const AbstractBuilder &builder):
    AbstractFactoryObject(this)
    {
        //TODO: Implement...
        
    }
    
    PhysicsShape::PhysicsShape(const PhysicsShape &copy):
    AbstractFactoryObject(this)
    {
        //TODO: Implement...
        
    }
    
    PhysicsShape::~PhysicsShape()
    {
        
    }
    
    PhysicsShape &PhysicsShape::operator=(const PhysicsShape &rhs)
    {
        if(this != &rhs)
        {
            setCollisionShape(*(rhs.getCollisionShape()));
//            m_PropertyChanged = true;
        }
        return *this;
    }
    
    PhysicsShape *PhysicsShape::create(u32 type)
    {
//        DEBUG_ASSERT(type == JLI_OBJECT_TYPE_PhysicsShapeBox);
        
        return dynamic_cast<PhysicsShape*>(World::getInstance()->getWorldFactory()->create(type));
    }
    
    void PhysicsShape::destroy(PhysicsShape *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void PhysicsShape::load(PhysicsShape &object, lua_State *L, int index)
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
                PhysicsShape::load(object, L, -2);
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
    
    u32 PhysicsShape::type()
    {
        return JLI_OBJECT_TYPE_PhysicsShape;
    }
    
    btRigidBody *PhysicsShape::createRigidBodyWithShape(f32 mass, btMotionState* motionState, const btVector3& localInertia)
    {
        btRigidBody *rb = new btRigidBody(mass, motionState, getCollisionShape(), localInertia);
        return rb;
    }
    
    btVector3 PhysicsShape::calculateLocalInertia(btScalar mass)const
    {
        btVector3 localInertia(0,0,0);
        if(mass > 0.0f)
        {
            getCollisionShape()->calculateLocalInertia(mass, localInertia);
        }
        return localInertia;
    }
    
//    void PhysicsShape::enablePropertyChange(bool enable)
//    {
//        m_PropertyChanged = enable;
//    }
//    bool PhysicsShape::isPropertyChanged()const
//    {
//        return m_PropertyChanged;
//    }
    
    void PhysicsShape::setLocalScaling(const btVector3& scaling)
    {
        getCollisionShape()->setLocalScaling(scaling);
    }
    
    void PhysicsShape::getAabb(const btTransform& t,btVector3& aabbMin,btVector3& aabbMax) const
    {
        getCollisionShape()->getAabb(t, aabbMin, aabbMax);
    }
    
//    void PhysicsShape::applyPhysicsShape()
//    {
//        PhysicsBody *body = getParent();
//        if(body)
//        {
//            Node *node = body->getParent();
//            if(node)
//            {
//                node->applyPhysicsShape();
//            }
//        }
//    }
    
    PhysicsBody *PhysicsShape::getParent()
    {
        return dynamic_cast<PhysicsBody*>(getParent());
    }
    const PhysicsBody *PhysicsShape::getParent()const
    {
        return dynamic_cast<const PhysicsBody*>(getParent());
    }
}