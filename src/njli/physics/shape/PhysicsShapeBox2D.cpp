//
//  PhysicsShapeBox2D.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 3/14/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "PhysicsShapeBox2D.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsShapeBox2DBuilder.h"
#include "Log.h"
#define TAG "PhysicsShapeBox2D.cpp"
#include "btBox2dShape.h"
#include "PhysicsBody.h"
#define FORMATSTRING "{\"njli::PhysicsShapeBox2D\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{
    PhysicsShapeBox2D::PhysicsShapeBox2D():
    PhysicsShape(),
    m_btBox2dShape(new btBox2dShape(btVector3(1,1,0)))
    {
        m_btBox2dShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeBox2D::PhysicsShapeBox2D(const AbstractBuilder &builder):
    PhysicsShape(),
    m_btBox2dShape(new btBox2dShape(btVector3(1,1,0)))
    {
        m_btBox2dShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeBox2D::PhysicsShapeBox2D(const PhysicsShapeBox2D &copy):
    PhysicsShape(),
    m_btBox2dShape(new btBox2dShape(btVector3(1,1,0)))
    {
        m_btBox2dShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeBox2D::~PhysicsShapeBox2D()
    {
        m_btBox2dShape->setUserPointer(NULL);
        delete m_btBox2dShape;m_btBox2dShape=NULL;
    }
    
    PhysicsShapeBox2D &PhysicsShapeBox2D::operator=(const PhysicsShapeBox2D &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	PhysicsShapeBox2D::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsShapeBox2D::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsShapeBox2D::getClassName()const
    {
        return "PhysicsShapeBox2D";
    }
    
    s32 PhysicsShapeBox2D::getType()const
    {
        return JLI_OBJECT_TYPE_PhysicsShapeBox2D;
    }
    
    PhysicsShapeBox2D::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsShapeBox2D **PhysicsShapeBox2D::createArray(const u32 size)
    {
        return (PhysicsShapeBox2D**)World::getInstance()->getWorldFactory()->createArray(PhysicsShapeBox2D::type(), size);
    }
    
    void PhysicsShapeBox2D::destroyArray(PhysicsShapeBox2D **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsShapeBox2D *PhysicsShapeBox2D::create()
    {
        return dynamic_cast<PhysicsShapeBox2D*>(World::getInstance()->getWorldFactory()->create(PhysicsShapeBox2D::type()));
    }
    
    PhysicsShapeBox2D *PhysicsShapeBox2D::create(const PhysicsShapeBox2DBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsShapeBox2D*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsShapeBox2D *PhysicsShapeBox2D::clone(const PhysicsShapeBox2D &object)
    {
        return dynamic_cast<PhysicsShapeBox2D*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsShapeBox2D *PhysicsShapeBox2D::copy(const PhysicsShapeBox2D &object)
    {
        return dynamic_cast<PhysicsShapeBox2D*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsShapeBox2D::destroy(PhysicsShapeBox2D *object)
    {
        if(object)
        {
            PhysicsShape::destroy(object);
        }
    }
    
    void PhysicsShapeBox2D::load(PhysicsShapeBox2D &object, lua_State *L, int index)
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
                PhysicsShapeBox2D::load(object, L, -2);
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
    
    u32 PhysicsShapeBox2D::type()
    {
        return JLI_OBJECT_TYPE_PhysicsShapeBox2D;
    }
    
    void PhysicsShapeBox2D::setHalfExtends(const btVector2 &extends)
    {
        btVector3 _extends(extends.x(), extends.y(), 0.0f);
        *m_btBox2dShape = btBox2dShape(_extends);
        
//        enablePropertyChange();
//        PhysicsShape::getParent()->setPhysicsBody();
    }
    
    void PhysicsShapeBox2D::setMargin(btScalar collisionMargin)
    {
        getShape()->setMargin(collisionMargin);
    }
//    void PhysicsShapeBox2D::setLocalScaling(const btVector3& scaling)
//    {
//        getShape()->setLocalScaling(scaling);
//    }
//    void PhysicsShapeBox2D::getAabb(const btTransform& t,btVector3& aabbMin,btVector3& aabbMax) const
//    {
//        getShape()->getAabb(t, aabbMin, aabbMax);
//    }
    void PhysicsShapeBox2D::calculateLocalInertia(btScalar mass,btVector3& inertia) const
    {
        getShape()->calculateLocalInertia(mass, inertia);
    }
    int	PhysicsShapeBox2D::getVertexCount() const
    {
        return getShape()->getVertexCount();
    }
    int PhysicsShapeBox2D::getNumVertices()const
    {
        return getShape()->getNumVertices();
    }
    void PhysicsShapeBox2D::getPlane(btVector3& planeNormal,btVector3& planeSupport,int i ) const
    {
        getShape()->getPlane(planeNormal, planeSupport, i);
    }
    const btVector3& PhysicsShapeBox2D::getCentroid() const
    {
        return getShape()->getCentroid();
    }
    int PhysicsShapeBox2D::getNumPlanes() const
    {
        return getShape()->getNumPlanes();
    }
    int PhysicsShapeBox2D::getNumEdges() const
    {
        return getShape()->getNumEdges();
    }
    void PhysicsShapeBox2D::getVertex(int i,btVector3& vtx) const
    {
        getShape()->getVertex(i, vtx);
    }
    void PhysicsShapeBox2D::getPlaneEquation(btVector4& plane,int i) const
    {
        getShape()->getPlaneEquation(plane, i);
    }
    void PhysicsShapeBox2D::getEdge(int i,btVector3& pa,btVector3& pb) const
    {
        getShape()->getEdge(i, pa, pb);
    }
    bool PhysicsShapeBox2D::isInside(const btVector3& pt,btScalar tolerance) const
    {
        return getShape()->isInside(pt, tolerance);
    }
    int PhysicsShapeBox2D::getNumPreferredPenetrationDirections() const
    {
        return getShape()->getNumPreferredPenetrationDirections();
    }
    void PhysicsShapeBox2D::getPreferredPenetrationDirection(int index, btVector3& penetrationVector) const
    {
        getShape()->getPreferredPenetrationDirection(index, penetrationVector);
    }
    
    const btCollisionShape* PhysicsShapeBox2D::getCollisionShape() const
    {
        return m_btBox2dShape;
    }
    
    btCollisionShape* PhysicsShapeBox2D::getCollisionShape()
    {
        return m_btBox2dShape;
    }
    
    void PhysicsShapeBox2D::setCollisionShape(const btCollisionShape &shape)
    {
        DEBUG_ASSERT(shape.getShapeType() == m_btBox2dShape->getShapeType());
        
        const btBox2dShape *_btBoxShape = dynamic_cast<const btBox2dShape*>(&shape);
        
        setHalfExtends(_btBoxShape->getHalfExtentsWithoutMargin() / _btBoxShape->getLocalScaling());
        
//        enablePropertyChange();
//        PhysicsShape::getParent()->setPhysicsBody();
    }
    
    const btBox2dShape* PhysicsShapeBox2D::getShape() const
    {
        return dynamic_cast<const btBox2dShape*>(m_btBox2dShape);
    }
    
    btBox2dShape* PhysicsShapeBox2D::getShape()
    {
        return dynamic_cast<btBox2dShape*>(m_btBox2dShape);
    }
}
