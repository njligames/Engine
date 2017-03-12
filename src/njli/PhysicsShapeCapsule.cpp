//
//  PhysicsShapeCapsule.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 6/22/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "PhysicsShapeCapsule.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsShapeCapsuleBuilder.h"
#define TAG "PhysicsShapeCapsule.cpp"
#define FORMATSTRING "{\"njli::PhysicsShapeCapsule\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "btCapsuleShape.h"

namespace njli
{
    PhysicsShapeCapsule::PhysicsShapeCapsule():
    PhysicsShape(),
    m_btCapsuleShape(new btCapsuleShape(1, 1))
    {
        m_btCapsuleShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeCapsule::PhysicsShapeCapsule(const AbstractBuilder &builder):
    PhysicsShape(builder),
    m_btCapsuleShape(new btCapsuleShape(1, 1))
    {
        m_btCapsuleShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeCapsule::PhysicsShapeCapsule(const PhysicsShapeCapsule &copy):
    PhysicsShape(copy),
    m_btCapsuleShape(new btCapsuleShape(1, 1))
    {
        m_btCapsuleShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeCapsule::~PhysicsShapeCapsule()
    {
        m_btCapsuleShape->setUserPointer(NULL);
        delete m_btCapsuleShape;m_btCapsuleShape=NULL;
    }
    
    PhysicsShapeCapsule &PhysicsShapeCapsule::operator=(const PhysicsShapeCapsule &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	PhysicsShapeCapsule::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsShapeCapsule::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsShapeCapsule::getClassName()const
    {
        return "PhysicsShapeCapsule";
    }
    
    s32 PhysicsShapeCapsule::getType()const
    {
        return PhysicsShapeCapsule::type();
    }
    
    PhysicsShapeCapsule::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsShapeCapsule **PhysicsShapeCapsule::createArray(const u32 size)
    {
        return (PhysicsShapeCapsule**)World::getInstance()->getWorldFactory()->createArray(PhysicsShapeCapsule::type(), size);
    }
    
    void PhysicsShapeCapsule::destroyArray(PhysicsShapeCapsule **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsShapeCapsule *PhysicsShapeCapsule::create()
    {
        return dynamic_cast<PhysicsShapeCapsule*>(World::getInstance()->getWorldFactory()->create(PhysicsShapeCapsule::type()));
    }
    
    PhysicsShapeCapsule *PhysicsShapeCapsule::create(const PhysicsShapeCapsuleBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsShapeCapsule*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsShapeCapsule *PhysicsShapeCapsule::clone(const PhysicsShapeCapsule &object)
    {
        return dynamic_cast<PhysicsShapeCapsule*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsShapeCapsule *PhysicsShapeCapsule::copy(const PhysicsShapeCapsule &object)
    {
        return dynamic_cast<PhysicsShapeCapsule*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsShapeCapsule::destroy(PhysicsShapeCapsule *object)
    {
        if(object)
        {
            PhysicsShape::destroy(object);
        }
    }
    
    void PhysicsShapeCapsule::load(PhysicsShapeCapsule &object, lua_State *L, int index)
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
                PhysicsShapeCapsule::load(object, L, -2);
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
    
    u32 PhysicsShapeCapsule::type()
    {
        return JLI_OBJECT_TYPE_PhysicsShapeCapsule;
    }
    
    
    int	PhysicsShapeCapsule::getNumVertices() const
    {
        return 0;
    }
    
    int PhysicsShapeCapsule::getNumEdges() const
    {
        return 0;
    }
    
    void PhysicsShapeCapsule::getEdge(int i,btVector3& pa,btVector3& pb) const
    {
        
    }
    
    void PhysicsShapeCapsule::getVertex(int i,btVector3& vtx) const
    {
        
    }
    
    int	PhysicsShapeCapsule::getNumPlanes() const
    {
        return 0;
    }
    
    void PhysicsShapeCapsule::getPlane(btVector3& planeNormal,btVector3& planeSupport,int i ) const
    {
        
    }
    
    bool PhysicsShapeCapsule::isInside(const btVector3& pt, f32 tolerance) const
    {
        return false;
    }
    
    
    void PhysicsShapeCapsule::setRadiusX(f32 radius)
    {
        *m_btCapsuleShape = btCapsuleShapeX(radius, getHalfHeight() * 2.0f);
    }
    
    void PhysicsShapeCapsule::setHeightX(f32 height)
    {
        *m_btCapsuleShape = btCapsuleShapeX(getRadius(), height);
    }
    
    void PhysicsShapeCapsule::setRadiusY(f32 radius)
    {
        *m_btCapsuleShape = btCapsuleShape(radius, getHalfHeight() * 2.0f);
    }
    
    void PhysicsShapeCapsule::setHeightY(f32 height)
    {
        *m_btCapsuleShape = btCapsuleShape(getRadius(), height);
    }
    
    void PhysicsShapeCapsule::setRadiusZ(f32 radius)
    {
        *m_btCapsuleShape = btCapsuleShapeZ(radius, getHalfHeight() * 2.0f);
    }
    
    void PhysicsShapeCapsule::setHeightZ(f32 height)
    {
        *m_btCapsuleShape = btCapsuleShapeZ(getRadius(), height);
    }
    
    
    void PhysicsShapeCapsule::calculateLocalInertia(f32 mass,btVector3& inertia) const
    {
        const btCapsuleShape *capsule = dynamic_cast<const btCapsuleShape*>(getCollisionShape());
        capsule->calculateLocalInertia(mass, inertia);
    }
    
    void PhysicsShapeCapsule::setMargin(f32 collisionMargin)
    {
        btCapsuleShape *capsule = dynamic_cast<btCapsuleShape*>(getCollisionShape());
        capsule->setMargin(collisionMargin);
    }
    
    int	PhysicsShapeCapsule::getUpAxis() const
    {
        const btCapsuleShape *capsule = dynamic_cast<const btCapsuleShape*>(getCollisionShape());
        return capsule->getUpAxis();
    }
    
    f32	PhysicsShapeCapsule::getRadius() const
    {
        const btCapsuleShape *capsule = dynamic_cast<const btCapsuleShape*>(getCollisionShape());
        return capsule->getRadius();
    }
    
    f32	PhysicsShapeCapsule::getHalfHeight() const
    {
        const btCapsuleShape *capsule = dynamic_cast<const btCapsuleShape*>(getCollisionShape());
        return capsule->getHalfHeight();
    }
    
    void PhysicsShapeCapsule::setLocalScaling(const btVector3& scaling)
    {
        getCollisionShape()->setLocalScaling(scaling);
    }
    
    btVector3 PhysicsShapeCapsule::getAnisotropicRollingFrictionDirection() const
    {
        const btCapsuleShape *capsule = dynamic_cast<const btCapsuleShape*>(getCollisionShape());
        return capsule->getAnisotropicRollingFrictionDirection();
    }
    
    
    
    void PhysicsShapeCapsule::getAabb(const btTransform& t,btVector3& aabbMin,btVector3& aabbMax) const
    {
        getCollisionShape()->getAabb(t, aabbMin, aabbMax);
    }
    
    const btCollisionShape*	PhysicsShapeCapsule::getCollisionShape() const
    {
        return m_btCapsuleShape;
    }
    
    btCollisionShape* PhysicsShapeCapsule::getCollisionShape()
    {
        return m_btCapsuleShape;
    }
    
    void PhysicsShapeCapsule::setCollisionShape(const btCollisionShape &shape)
    {
        DEBUG_ASSERT(shape.getShapeType() == m_btCapsuleShape->getShapeType());
        const btCapsuleShape *capsule = dynamic_cast<const btCapsuleShape*>(&shape);
        setRadiusY(capsule->getRadius());
        setHeightY(capsule->getHalfHeight()*2);
    }
}
