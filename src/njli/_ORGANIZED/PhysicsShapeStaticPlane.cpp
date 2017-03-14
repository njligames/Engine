//
//  PhysicsShapeStaticPlane.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 6/22/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "PhysicsShapeStaticPlane.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsShapeStaticPlaneBuilder.h"
#define TAG "PhysicsShapeStaticPlane.cpp"
#define FORMATSTRING "{\"njli::PhysicsShapeStaticPlane\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "btStaticPlaneShape.h"

namespace njli
{
    PhysicsShapeStaticPlane::PhysicsShapeStaticPlane():
    PhysicsShape(),
    m_btStaticPlaneShape(new btStaticPlaneShape(btVector3(0,1,0),0))
    {
        m_btStaticPlaneShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeStaticPlane::PhysicsShapeStaticPlane(const AbstractBuilder &builder):
    PhysicsShape(builder),
    m_btStaticPlaneShape(new btStaticPlaneShape(btVector3(0,1,0),0))
    {
        m_btStaticPlaneShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeStaticPlane::PhysicsShapeStaticPlane(const PhysicsShapeStaticPlane &copy):
    PhysicsShape(copy),
    m_btStaticPlaneShape(new btStaticPlaneShape(btVector3(0,1,0),0))
    {
        m_btStaticPlaneShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeStaticPlane::~PhysicsShapeStaticPlane()
    {
        m_btStaticPlaneShape->setUserPointer(NULL);
        delete m_btStaticPlaneShape;m_btStaticPlaneShape=NULL;
    }
    
    PhysicsShapeStaticPlane &PhysicsShapeStaticPlane::operator=(const PhysicsShapeStaticPlane &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	PhysicsShapeStaticPlane::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsShapeStaticPlane::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsShapeStaticPlane::getClassName()const
    {
        return "PhysicsShapeStaticPlane";
    }
    
    s32 PhysicsShapeStaticPlane::getType()const
    {
        return PhysicsShapeStaticPlane::type();
    }
    
    PhysicsShapeStaticPlane::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsShapeStaticPlane **PhysicsShapeStaticPlane::createArray(const u32 size)
    {
        return (PhysicsShapeStaticPlane**)World::getInstance()->getWorldFactory()->createArray(PhysicsShapeStaticPlane::type(), size);
    }
    
    void PhysicsShapeStaticPlane::destroyArray(PhysicsShapeStaticPlane **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsShapeStaticPlane *PhysicsShapeStaticPlane::create()
    {
        return dynamic_cast<PhysicsShapeStaticPlane*>(World::getInstance()->getWorldFactory()->create(PhysicsShapeStaticPlane::type()));
    }
    
    PhysicsShapeStaticPlane *PhysicsShapeStaticPlane::create(const PhysicsShapeStaticPlaneBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsShapeStaticPlane*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsShapeStaticPlane *PhysicsShapeStaticPlane::clone(const PhysicsShapeStaticPlane &object)
    {
        return dynamic_cast<PhysicsShapeStaticPlane*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsShapeStaticPlane *PhysicsShapeStaticPlane::copy(const PhysicsShapeStaticPlane &object)
    {
        return dynamic_cast<PhysicsShapeStaticPlane*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsShapeStaticPlane::destroy(PhysicsShapeStaticPlane *object)
    {
        if(object)
        {
            PhysicsShape::destroy(object);
        }
    }
    
    void PhysicsShapeStaticPlane::load(PhysicsShapeStaticPlane &object, lua_State *L, int index)
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
                PhysicsShapeStaticPlane::load(object, L, -2);
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
    
    u32 PhysicsShapeStaticPlane::type()
    {
        return JLI_OBJECT_TYPE_PhysicsShapeStaticPlane;
    }
    
    
    int	PhysicsShapeStaticPlane::getNumVertices() const
    {
        return 0;
    }
    
    int PhysicsShapeStaticPlane::getNumEdges() const
    {
        return 0;
    }
    
    void PhysicsShapeStaticPlane::getEdge(int i,btVector3& pa,btVector3& pb) const
    {
        
    }
    
    void PhysicsShapeStaticPlane::getVertex(int i,btVector3& vtx) const
    {
        
    }
    
    int	PhysicsShapeStaticPlane::getNumPlanes() const
    {
        return 0;
    }
    
    void PhysicsShapeStaticPlane::getPlane(btVector3& planeNormal,btVector3& planeSupport,int i ) const
    {
        
    }
    
    bool PhysicsShapeStaticPlane::isInside(const btVector3& pt, f32 tolerance) const
    {
        return false;
    }
    
    void PhysicsShapeStaticPlane::setPlaneNormal(const btVector3 &normal)
    {
        *m_btStaticPlaneShape = btStaticPlaneShape(normal, getPlaneConstant());
    }
    
    void PhysicsShapeStaticPlane::setPlaneConstant(f32 planeConstant)
    {
        *m_btStaticPlaneShape = btStaticPlaneShape(getPlaneNormal(), planeConstant);
    }
    
    void PhysicsShapeStaticPlane::calculateLocalInertia(btScalar mass,btVector3& inertia) const
    {
        const btStaticPlaneShape *staticplane = dynamic_cast<const btStaticPlaneShape*>(getCollisionShape());
        staticplane->calculateLocalInertia(mass, inertia);
    }
    
    void PhysicsShapeStaticPlane::setLocalScaling(const btVector3& scaling)
    {
        btStaticPlaneShape *staticplane = dynamic_cast<btStaticPlaneShape*>(getCollisionShape());
        staticplane->setLocalScaling(scaling);
    }
    
    const btVector3& PhysicsShapeStaticPlane::getPlaneNormal() const
    {
        const btStaticPlaneShape *staticplane = dynamic_cast<const btStaticPlaneShape*>(getCollisionShape());
        return staticplane->getPlaneNormal();
    }
    
    const btScalar&	PhysicsShapeStaticPlane::getPlaneConstant() const
    {
        const btStaticPlaneShape *staticplane = dynamic_cast<const btStaticPlaneShape*>(getCollisionShape());
        return staticplane->getPlaneConstant();
    }
    
//    void PhysicsShapeStaticPlane::getAabb(const btTransform& t,btVector3& aabbMin,btVector3& aabbMax) const
//    {
//        
//    }
    
    const btCollisionShape*	PhysicsShapeStaticPlane::getCollisionShape() const
    {
        return m_btStaticPlaneShape;
    }
    
    btCollisionShape* PhysicsShapeStaticPlane::getCollisionShape()
    {
        return m_btStaticPlaneShape;
    }
    
    void PhysicsShapeStaticPlane::setCollisionShape(const btCollisionShape &shape)
    {
        DEBUG_ASSERT(shape.getShapeType() == m_btStaticPlaneShape->getShapeType());
        const btStaticPlaneShape *staticplane = dynamic_cast<const btStaticPlaneShape*>(&shape);
        *m_btStaticPlaneShape = btStaticPlaneShape(staticplane->getPlaneNormal(), staticplane->getPlaneConstant());
    }
}
