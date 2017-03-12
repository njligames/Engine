//
//  PhysicsShapeConvexHull.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 6/22/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "PhysicsShapeConvexHull.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsShapeConvexHullBuilder.h"
#define TAG "PhysicsShapeConvexHull.cpp"
#define FORMATSTRING "{\"njli::PhysicsShapeConvexHull\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "btConvexHullShape.h"

namespace njli
{
    PhysicsShapeConvexHull::PhysicsShapeConvexHull():
    PhysicsShape(),
    m_btConvexHullShape(new btConvexHullShape())
    {
        m_btConvexHullShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeConvexHull::PhysicsShapeConvexHull(const AbstractBuilder &builder):
    PhysicsShape(builder),
    m_btConvexHullShape(new btConvexHullShape())
    {
        m_btConvexHullShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeConvexHull::PhysicsShapeConvexHull(const PhysicsShapeConvexHull &copy):
    PhysicsShape(copy),
    m_btConvexHullShape(new btConvexHullShape())
    {
        m_btConvexHullShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeConvexHull::~PhysicsShapeConvexHull()
    {
        m_btConvexHullShape->setUserPointer(NULL);
        delete m_btConvexHullShape;m_btConvexHullShape=NULL;
    }
    
    PhysicsShapeConvexHull &PhysicsShapeConvexHull::operator=(const PhysicsShapeConvexHull &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	PhysicsShapeConvexHull::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsShapeConvexHull::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsShapeConvexHull::getClassName()const
    {
        return "PhysicsShapeConvexHull";
    }
    
    s32 PhysicsShapeConvexHull::getType()const
    {
        return PhysicsShapeConvexHull::type();
    }
    
    PhysicsShapeConvexHull::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsShapeConvexHull **PhysicsShapeConvexHull::createArray(const u32 size)
    {
        return (PhysicsShapeConvexHull**)World::getInstance()->getWorldFactory()->createArray(PhysicsShapeConvexHull::type(), size);
    }
    
    void PhysicsShapeConvexHull::destroyArray(PhysicsShapeConvexHull **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsShapeConvexHull *PhysicsShapeConvexHull::create()
    {
        return dynamic_cast<PhysicsShapeConvexHull*>(World::getInstance()->getWorldFactory()->create(PhysicsShapeConvexHull::type()));
    }
    
    PhysicsShapeConvexHull *PhysicsShapeConvexHull::create(const PhysicsShapeConvexHullBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsShapeConvexHull*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsShapeConvexHull *PhysicsShapeConvexHull::clone(const PhysicsShapeConvexHull &object)
    {
        return dynamic_cast<PhysicsShapeConvexHull*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsShapeConvexHull *PhysicsShapeConvexHull::copy(const PhysicsShapeConvexHull &object)
    {
        return dynamic_cast<PhysicsShapeConvexHull*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsShapeConvexHull::destroy(PhysicsShapeConvexHull *object)
    {
        if(object)
        {
            PhysicsShape::destroy(object);
        }
    }
    
    void PhysicsShapeConvexHull::load(PhysicsShapeConvexHull &object, lua_State *L, int index)
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
                PhysicsShapeConvexHull::load(object, L, -2);
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
    
    u32 PhysicsShapeConvexHull::type()
    {
        return JLI_OBJECT_TYPE_PhysicsShapeConvexHull;
    }
    
    
    int	PhysicsShapeConvexHull::getNumVertices() const
    {
        const btConvexHullShape *convexhull = dynamic_cast<const btConvexHullShape*>(getCollisionShape());
        return convexhull->getNumVertices();
    }
    
    int PhysicsShapeConvexHull::getNumEdges() const
    {
        const btConvexHullShape *convexhull = dynamic_cast<const btConvexHullShape*>(getCollisionShape());
        return convexhull->getNumEdges();
    }
    
    void PhysicsShapeConvexHull::getEdge(int i,btVector3& pa,btVector3& pb) const
    {
        const btConvexHullShape *convexhull = dynamic_cast<const btConvexHullShape*>(getCollisionShape());
        convexhull->getEdge(i, pa, pb);
    }
    
    void PhysicsShapeConvexHull::getVertex(int i,btVector3& vtx) const
    {
        const btConvexHullShape *convexhull = dynamic_cast<const btConvexHullShape*>(getCollisionShape());
        convexhull->getVertex(i, vtx);
    }
    
    int	PhysicsShapeConvexHull::getNumPlanes() const
    {
        const btConvexHullShape *convexhull = dynamic_cast<const btConvexHullShape*>(getCollisionShape());
        return convexhull->getNumPlanes();
    }
    
    void PhysicsShapeConvexHull::getPlane(btVector3& planeNormal,btVector3& planeSupport,int i ) const
    {
        const btConvexHullShape *convexhull = dynamic_cast<const btConvexHullShape*>(getCollisionShape());
        convexhull->getPlane(planeNormal, planeSupport, i);
    }
    
    bool PhysicsShapeConvexHull::isInside(const btVector3& pt, f32 tolerance) const
    {
        const btConvexHullShape *convexhull = dynamic_cast<const btConvexHullShape*>(getCollisionShape());
        return convexhull->isInside(pt, tolerance);
    }
    
    
    void PhysicsShapeConvexHull::addPoint(const btVector3& point, bool recalculateLocalAabb)
    {
        btConvexHullShape *convexhull = dynamic_cast<btConvexHullShape*>(getCollisionShape());
        convexhull->addPoint(point, recalculateLocalAabb);
    }
    
    void PhysicsShapeConvexHull::getUnscaledPoints(std::vector<btVector3> &points)const
    {
        const btConvexHullShape *convexhull = dynamic_cast<const btConvexHullShape*>(getCollisionShape());
        for (s32 i = 0; i < getNumPoints(); ++i)
        {
            points.push_back(convexhull->getUnscaledPoints()[i]);
        }
    }
    
    btVector3 PhysicsShapeConvexHull::getScaledPoint(int i) const
    {
        const btConvexHullShape *convexhull = dynamic_cast<const btConvexHullShape*>(getCollisionShape());
        return convexhull->getScaledPoint(i);
    }
    
    int PhysicsShapeConvexHull::getNumPoints() const
    {
        const btConvexHullShape *convexhull = dynamic_cast<const btConvexHullShape*>(getCollisionShape());
        return convexhull->getNumPoints();
    }
    
    void PhysicsShapeConvexHull::project(const btTransform& trans, const btVector3& dir, btScalar& minProj, btScalar& maxProj, btVector3& witnesPtMin,btVector3& witnesPtMax) const
    {
        const btConvexHullShape *convexhull = dynamic_cast<const btConvexHullShape*>(getCollisionShape());
        convexhull->project(trans, dir, minProj, maxProj, witnesPtMin, witnesPtMax);
    }
    
//    void PhysicsShapeConvexHull::getAabb(const btTransform& t,btVector3& aabbMin,btVector3& aabbMax) const
//    {
//        
//    }
    
    const btCollisionShape*	PhysicsShapeConvexHull::getCollisionShape() const
    {
        return m_btConvexHullShape;
    }
    
    btCollisionShape* PhysicsShapeConvexHull::getCollisionShape()
    {
        return m_btConvexHullShape;
    }
    
    void PhysicsShapeConvexHull::setCollisionShape(const btCollisionShape &shape)
    {
        DEBUG_ASSERT(shape.getShapeType() == m_btConvexHullShape->getShapeType());
        const btConvexHullShape *convexhull = dynamic_cast<const btConvexHullShape*>(&shape);
        btAlignedObjectArray<btScalar> points;
        
        for (s32 i = 0; i < convexhull->getNumPoints(); ++i)
        {
            btVector3 v = convexhull->getPoints()[i];
            points.push_back(v.x());
            points.push_back(v.y());
            points.push_back(v.z());
        }
        *m_btConvexHullShape = btConvexHullShape(&points[0], convexhull->getNumPoints());
    }
}
