//
//  PhysicsShapeCylinder.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 6/22/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "PhysicsShapeCylinder.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsShapeCylinderBuilder.h"
#define TAG "PhysicsShapeCylinder.cpp"
#define FORMATSTRING "{\"njli::PhysicsShapeCylinder\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "btCylinderShape.h"

namespace njli
{
    PhysicsShapeCylinder::PhysicsShapeCylinder():
    PhysicsShape(),
    m_btCylinderShape(new btCylinderShape(btVector3(1,1,1)))
    {
        m_btCylinderShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeCylinder::PhysicsShapeCylinder(const AbstractBuilder &builder):
    PhysicsShape(builder),
    m_btCylinderShape(new btCylinderShape(btVector3(1,1,1)))
    {
        m_btCylinderShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeCylinder::PhysicsShapeCylinder(const PhysicsShapeCylinder &copy):
    PhysicsShape(copy),
    m_btCylinderShape(new btCylinderShape(btVector3(1,1,1)))
    {
        m_btCylinderShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeCylinder::~PhysicsShapeCylinder()
    {
        m_btCylinderShape->setUserPointer(NULL);
        delete m_btCylinderShape;m_btCylinderShape=NULL;
    }
    
    PhysicsShapeCylinder &PhysicsShapeCylinder::operator=(const PhysicsShapeCylinder &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	PhysicsShapeCylinder::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsShapeCylinder::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsShapeCylinder::getClassName()const
    {
        return "PhysicsShapeCylinder";
    }
    
    s32 PhysicsShapeCylinder::getType()const
    {
        return PhysicsShapeCylinder::type();
    }
    
    PhysicsShapeCylinder::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsShapeCylinder **PhysicsShapeCylinder::createArray(const u32 size)
    {
        return (PhysicsShapeCylinder**)World::getInstance()->getWorldFactory()->createArray(PhysicsShapeCylinder::type(), size);
    }
    
    void PhysicsShapeCylinder::destroyArray(PhysicsShapeCylinder **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsShapeCylinder *PhysicsShapeCylinder::create()
    {
        return dynamic_cast<PhysicsShapeCylinder*>(World::getInstance()->getWorldFactory()->create(PhysicsShapeCylinder::type()));
    }
    
    PhysicsShapeCylinder *PhysicsShapeCylinder::create(const PhysicsShapeCylinderBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsShapeCylinder*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsShapeCylinder *PhysicsShapeCylinder::clone(const PhysicsShapeCylinder &object)
    {
        return dynamic_cast<PhysicsShapeCylinder*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsShapeCylinder *PhysicsShapeCylinder::copy(const PhysicsShapeCylinder &object)
    {
        return dynamic_cast<PhysicsShapeCylinder*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsShapeCylinder::destroy(PhysicsShapeCylinder *object)
    {
        if(object)
        {
            PhysicsShape::destroy(object);
        }
    }
    
    void PhysicsShapeCylinder::load(PhysicsShapeCylinder &object, lua_State *L, int index)
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
                PhysicsShapeCylinder::load(object, L, -2);
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
    
    u32 PhysicsShapeCylinder::type()
    {
        return JLI_OBJECT_TYPE_PhysicsShapeCylinder;
    }
    
    
    int	PhysicsShapeCylinder::getNumVertices() const
    {
        return 0;
    }
    
    int PhysicsShapeCylinder::getNumEdges() const
    {
        return 0;
    }
    
    void PhysicsShapeCylinder::getEdge(int i,btVector3& pa,btVector3& pb) const
    {
        
    }
    
    void PhysicsShapeCylinder::getVertex(int i,btVector3& vtx) const
    {
        
    }
    
    int	PhysicsShapeCylinder::getNumPlanes() const
    {
        return 0;
    }
    
    void PhysicsShapeCylinder::getPlane(btVector3& planeNormal,btVector3& planeSupport,int i ) const
    {
        
    }
    
    bool PhysicsShapeCylinder::isInside(const btVector3& pt, f32 tolerance) const
    {
        return false;
    }
    
    
    btVector3 PhysicsShapeCylinder::getHalfExtentsWithMargin() const
    {
        const btCylinderShape *cylinder = dynamic_cast<const btCylinderShape*>(getCollisionShape());
        return cylinder->getHalfExtentsWithMargin();
    }
    
    const btVector3& PhysicsShapeCylinder::getHalfExtentsWithoutMargin() const
    {
        const btCylinderShape *cylinder = dynamic_cast<const btCylinderShape*>(getCollisionShape());
        return cylinder->getHalfExtentsWithoutMargin();
    }
    
    void PhysicsShapeCylinder::setHalfExtentsX (const btVector3& halfExtents)
    {
        *m_btCylinderShape = btCylinderShapeX(halfExtents);
    }
    
    void PhysicsShapeCylinder::setHalfExtentsY (const btVector3& halfExtents)
    {
        *m_btCylinderShape = btCylinderShape(halfExtents);
    }
    
    void PhysicsShapeCylinder::setHalfExtentsZ (const btVector3& halfExtents)
    {
        *m_btCylinderShape = btCylinderShapeZ(halfExtents);
    }
    
    void PhysicsShapeCylinder::calculateLocalInertia(f32 mass,btVector3& inertia) const
    {
        const btCylinderShape *cylinder = dynamic_cast<const btCylinderShape*>(getCollisionShape());
        cylinder->calculateLocalInertia(mass, inertia);
    }
    
    void PhysicsShapeCylinder::setMargin(f32 collisionMargin)
    {
        btCylinderShape *cylinder = dynamic_cast<btCylinderShape*>(getCollisionShape());
        cylinder->setMargin(collisionMargin);
    }
    
    int	PhysicsShapeCylinder::getUpAxis() const
    {
        const btCylinderShape *cylinder = dynamic_cast<const btCylinderShape*>(getCollisionShape());
        return cylinder->getUpAxis();
    }
    
    btVector3 PhysicsShapeCylinder::getAnisotropicRollingFrictionDirection() const
    {
        const btCylinderShape *cylinder = dynamic_cast<const btCylinderShape*>(getCollisionShape());
        return cylinder->getAnisotropicRollingFrictionDirection();
    }
    
    f32 PhysicsShapeCylinder::getRadius() const
    {
        const btCylinderShape *cylinder = dynamic_cast<const btCylinderShape*>(getCollisionShape());
        return cylinder->getRadius();
    }
    
    
    const btCollisionShape*	PhysicsShapeCylinder::getCollisionShape() const
    {
        return m_btCylinderShape;
    }
    
    btCollisionShape* PhysicsShapeCylinder::getCollisionShape()
    {
        return m_btCylinderShape;
    }
    
    void PhysicsShapeCylinder::setCollisionShape(const btCollisionShape &shape)
    {
        DEBUG_ASSERT(shape.getShapeType() == m_btCylinderShape->getShapeType());
        const btCylinderShape *cylinder = dynamic_cast<const btCylinderShape*>(&shape);
        setHalfExtentsY(cylinder->getHalfExtentsWithoutMargin());
    }
}
