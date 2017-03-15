//
//  PhysicsShapeCone.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 6/22/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "PhysicsShapeCone.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsShapeConeBuilder.h"
#define TAG "PhysicsShapeCone.cpp"
#define FORMATSTRING "{\"njli::PhysicsShapeCone\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "btConeShape.h"

namespace njli
{
    PhysicsShapeCone::PhysicsShapeCone():
    PhysicsShape(),
    m_btConeShape(new btConeShape(1,1))
    {
        m_btConeShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeCone::PhysicsShapeCone(const AbstractBuilder &builder):
    PhysicsShape(builder),
    m_btConeShape(new btConeShape(1,1))
    {
        m_btConeShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeCone::PhysicsShapeCone(const PhysicsShapeCone &copy):
    PhysicsShape(copy),
    m_btConeShape(new btConeShape(1,1))
    {
        m_btConeShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeCone::~PhysicsShapeCone()
    {
        m_btConeShape->setUserPointer(NULL);
        delete m_btConeShape;m_btConeShape=NULL;
    }
    
    PhysicsShapeCone &PhysicsShapeCone::operator=(const PhysicsShapeCone &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	PhysicsShapeCone::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsShapeCone::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsShapeCone::getClassName()const
    {
        return "PhysicsShapeCone";
    }
    
    s32 PhysicsShapeCone::getType()const
    {
        return PhysicsShapeCone::type();
    }
    
    PhysicsShapeCone::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsShapeCone **PhysicsShapeCone::createArray(const u32 size)
    {
        return (PhysicsShapeCone**)World::getInstance()->getWorldFactory()->createArray(PhysicsShapeCone::type(), size);
    }
    
    void PhysicsShapeCone::destroyArray(PhysicsShapeCone **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsShapeCone *PhysicsShapeCone::create()
    {
        return dynamic_cast<PhysicsShapeCone*>(World::getInstance()->getWorldFactory()->create(PhysicsShapeCone::type()));
    }
    
    PhysicsShapeCone *PhysicsShapeCone::create(const PhysicsShapeConeBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsShapeCone*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsShapeCone *PhysicsShapeCone::clone(const PhysicsShapeCone &object)
    {
        return dynamic_cast<PhysicsShapeCone*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsShapeCone *PhysicsShapeCone::copy(const PhysicsShapeCone &object)
    {
        return dynamic_cast<PhysicsShapeCone*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsShapeCone::destroy(PhysicsShapeCone *object)
    {
        if(object)
        {
            PhysicsShape::destroy(object);
        }
    }
    
    void PhysicsShapeCone::load(PhysicsShapeCone &object, lua_State *L, int index)
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
                PhysicsShapeCone::load(object, L, -2);
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
    
    u32 PhysicsShapeCone::type()
    {
        return JLI_OBJECT_TYPE_PhysicsShapeCone;
    }
    
    
    int	PhysicsShapeCone::getNumVertices() const
    {
        return 0;
    }
    
    int PhysicsShapeCone::getNumEdges() const
    {
        return 0;
    }
    
    void PhysicsShapeCone::getEdge(int i,btVector3& pa,btVector3& pb) const
    {
        
    }
    
    void PhysicsShapeCone::getVertex(int i,btVector3& vtx) const
    {
        
    }
    
    int	PhysicsShapeCone::getNumPlanes() const
    {
        return 0;
    }
    
    void PhysicsShapeCone::getPlane(btVector3& planeNormal,btVector3& planeSupport,int i ) const
    {
        
    }
    
    bool PhysicsShapeCone::isInside(const btVector3& pt, f32 tolerance) const
    {
        return false;
    }

    void PhysicsShapeCone::setRadiusX(f32 radius)
    {
        *m_btConeShape = btConeShapeX(radius, getHeight());
    }
    
    void PhysicsShapeCone::setHeightX(f32 height)
    {
        *m_btConeShape = btConeShapeX(getRadius(), height);
    }
    
    void PhysicsShapeCone::setRadiusY(f32 radius)
    {
        *m_btConeShape = btConeShape(radius, getHeight());
    }
    
    void PhysicsShapeCone::setHeightY(f32 height)
    {
        *m_btConeShape = btConeShape(getRadius(), height);
    }
    
    void PhysicsShapeCone::setRadiusZ(f32 radius)
    {
        *m_btConeShape = btConeShapeZ(radius, getHeight());
    }
    
    void PhysicsShapeCone::setHeightZ(f32 height)
    {
        *m_btConeShape = btConeShapeZ(getRadius(), height);
    }
    
    f32 PhysicsShapeCone::getRadius() const
    {
        const btConeShape *cylinder = dynamic_cast<const btConeShape*>(getCollisionShape());
        return cylinder->getRadius();
    }
    
    f32 PhysicsShapeCone::getHeight() const
    {
        const btConeShape *cylinder = dynamic_cast<const btConeShape*>(getCollisionShape());
        return cylinder->getHeight();
    }
    
    void PhysicsShapeCone::calculateLocalInertia(f32 mass,btVector3& inertia) const
    {
        const btConeShape *cylinder = dynamic_cast<const btConeShape*>(getCollisionShape());
        cylinder->calculateLocalInertia(mass, inertia);
    }
    
    void PhysicsShapeCone::setConeUpIndex(int upIndex)
    {
        btConeShape *cylinder = dynamic_cast<btConeShape*>(getCollisionShape());
        cylinder->setConeUpIndex(upIndex);
    }
    
    int	PhysicsShapeCone::getConeUpIndex() const
    {
        const btConeShape *cylinder = dynamic_cast<const btConeShape*>(getCollisionShape());
        return cylinder->getConeUpIndex();
    }
    
    btVector3 PhysicsShapeCone::getAnisotropicRollingFrictionDirection() const
    {
        const btConeShape *cylinder = dynamic_cast<const btConeShape*>(getCollisionShape());
        return cylinder->getAnisotropicRollingFrictionDirection();
    }
    
    
//    void PhysicsShapeCone::getAabb(const btTransform& t,btVector3& aabbMin,btVector3& aabbMax) const
//    {
//        
//    }
    
    const btCollisionShape*	PhysicsShapeCone::getCollisionShape() const
    {
        return m_btConeShape;
    }
    
    btCollisionShape* PhysicsShapeCone::getCollisionShape()
    {
        return m_btConeShape;
    }
    
    void PhysicsShapeCone::setCollisionShape(const btCollisionShape &shape)
    {
        DEBUG_ASSERT(shape.getShapeType() == m_btConeShape->getShapeType());
        const btConeShape *cone = dynamic_cast<const btConeShape*>(&shape);
        setRadiusY(cone->getRadius());
        setHeightY(cone->getHeight());
    }
}
