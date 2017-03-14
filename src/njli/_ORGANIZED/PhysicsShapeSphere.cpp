//
//  PhysicsShapeSphere.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 6/22/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "PhysicsShapeSphere.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsShapeSphereBuilder.h"
#define TAG "PhysicsShapeSphere.cpp"
#define FORMATSTRING "{\"njli::PhysicsShapeSphere\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "btSphereShape.h"

namespace njli
{
    PhysicsShapeSphere::PhysicsShapeSphere():
    PhysicsShape(),
    m_btSphereShape(new btSphereShape(1.0f))
    {
        m_btSphereShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeSphere::PhysicsShapeSphere(const AbstractBuilder &builder):
    PhysicsShape(builder),
    m_btSphereShape(new btSphereShape(1.0f))
    {
        m_btSphereShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeSphere::PhysicsShapeSphere(const PhysicsShapeSphere &copy):
    PhysicsShape(copy),
    m_btSphereShape(new btSphereShape(1.0f))
    {
        m_btSphereShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeSphere::~PhysicsShapeSphere()
    {
        m_btSphereShape->setUserPointer(NULL);
        delete m_btSphereShape;m_btSphereShape=NULL;
    }
    
    PhysicsShapeSphere &PhysicsShapeSphere::operator=(const PhysicsShapeSphere &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	PhysicsShapeSphere::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsShapeSphere::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsShapeSphere::getClassName()const
    {
        return "PhysicsShapeSphere";
    }
    
    s32 PhysicsShapeSphere::getType()const
    {
        return PhysicsShapeSphere::type();
    }
    
    PhysicsShapeSphere::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsShapeSphere **PhysicsShapeSphere::createArray(const u32 size)
    {
        return (PhysicsShapeSphere**)World::getInstance()->getWorldFactory()->createArray(PhysicsShapeSphere::type(), size);
    }
    
    void PhysicsShapeSphere::destroyArray(PhysicsShapeSphere **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsShapeSphere *PhysicsShapeSphere::create()
    {
        return dynamic_cast<PhysicsShapeSphere*>(World::getInstance()->getWorldFactory()->create(PhysicsShapeSphere::type()));
    }
    
    PhysicsShapeSphere *PhysicsShapeSphere::create(const PhysicsShapeSphereBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsShapeSphere*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsShapeSphere *PhysicsShapeSphere::clone(const PhysicsShapeSphere &object)
    {
        return dynamic_cast<PhysicsShapeSphere*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsShapeSphere *PhysicsShapeSphere::copy(const PhysicsShapeSphere &object)
    {
        return dynamic_cast<PhysicsShapeSphere*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsShapeSphere::destroy(PhysicsShapeSphere *object)
    {
        if(object)
        {
            PhysicsShape::destroy(object);
        }
        
    }
    
    void PhysicsShapeSphere::load(PhysicsShapeSphere &object, lua_State *L, int index)
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
                PhysicsShapeSphere::load(object, L, -2);
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
    
    u32 PhysicsShapeSphere::type()
    {
        return JLI_OBJECT_TYPE_PhysicsShapeSphere;
    }
    
    
    int	PhysicsShapeSphere::getNumVertices() const
    {
        return 0;
    }
    
    int PhysicsShapeSphere::getNumEdges() const
    {
        return 0;
    }
    
    void PhysicsShapeSphere::getEdge(int i,btVector3& pa,btVector3& pb) const
    {
        
    }
    
    void PhysicsShapeSphere::getVertex(int i,btVector3& vtx) const
    {
        
    }
    
    int	PhysicsShapeSphere::getNumPlanes() const
    {
        return 0;
    }
    
    void PhysicsShapeSphere::getPlane(btVector3& planeNormal,btVector3& planeSupport,int i ) const
    {
        
    }
    
    bool PhysicsShapeSphere::isInside(const btVector3& pt,f32 tolerance) const
    {
        return false;
    }
    
    
    void PhysicsShapeSphere::setRadius(f32 radius)
    {
        *m_btSphereShape = btSphereShape(radius);
    }
    
//    btVector3 PhysicsShapeSphere::localGetSupportingVertex(const btVector3& vec)const
//    {
//        const btSphereShape *sphere = dynamic_cast<const btSphereShape*>(getCollisionShape());
//        return sphere->localGetSupportingVertex(vec);
//    }
//    
//    btVector3 PhysicsShapeSphere::localGetSupportingVertexWithoutMargin(const btVector3& vec)const
//    {
//        const btSphereShape *sphere = dynamic_cast<const btSphereShape*>(getCollisionShape());
//        return sphere->localGetSupportingVertexWithoutMargin(vec);
//    }
    
    /*void PhysicsShapeSphere::batchedUnitVectorGetSupportingVertexWithoutMargin(const btVector3* vectors,btVector3* supportVerticesOut,int numVectors) const
    {
        const btSphereShape *sphere = dynamic_cast<const btSphereShape*>(getCollisionShape());
        sphere->btConvexShape::batchedUnitVectorGetSupportingVertexWithoutMargin(vectors, supportVerticesOut, numVectors);
    }*/
    
    void PhysicsShapeSphere::calculateLocalInertia(f32 mass,btVector3& inertia) const
    {
        const btSphereShape *sphere = dynamic_cast<const btSphereShape*>(getCollisionShape());
        sphere->calculateLocalInertia(mass, inertia);
    }
    
    f32 PhysicsShapeSphere::getRadius() const
    {
        const btSphereShape *sphere = dynamic_cast<const btSphereShape*>(getCollisionShape());
        return sphere->getRadius();
    }
    
    void PhysicsShapeSphere::setUnscaledRadius(f32	radius)
    {
        btSphereShape *sphere = dynamic_cast<btSphereShape*>(getCollisionShape());
        sphere->setUnscaledRadius(radius);
    }
    
    void PhysicsShapeSphere::setMargin(f32 margin)
    {
        btSphereShape *sphere = dynamic_cast<btSphereShape*>(getCollisionShape());
        sphere->setMargin(margin);
    }
    
    f32 PhysicsShapeSphere::getMargin() const
    {
        const btSphereShape *sphere = dynamic_cast<const btSphereShape*>(getCollisionShape());
        
        return sphere->getMargin();
    }
    
//    void PhysicsShapeSphere::getAabb(const btTransform& t,btVector3& aabbMin,btVector3& aabbMax) const
//    {
//        getCollisionShape()->getAabb(t, aabbMin, aabbMax);
//    }
    
    const btCollisionShape*	PhysicsShapeSphere::getCollisionShape() const
    {
        return m_btSphereShape;
    }
    
    btCollisionShape* PhysicsShapeSphere::getCollisionShape()
    {
        return m_btSphereShape;
    }
    
    void PhysicsShapeSphere::setCollisionShape(const btCollisionShape &shape)
    {
        DEBUG_ASSERT(shape.getShapeType() == m_btSphereShape->getShapeType());
        const btSphereShape *_btSphereShape = dynamic_cast<const btSphereShape*>(&shape);
        setRadius(_btSphereShape->getRadius());
    }
}
