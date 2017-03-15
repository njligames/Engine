//
//  PhysicsShapeBox.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 1/1/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "PhysicsShapeBox.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsShapeBoxBuilder.h"
#include "btCollisionShape.h"
#include "btBoxShape.h"
#include "PhysicsBody.h"
#define FORMATSTRING "{\"njli::PhysicsShapeBox\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

namespace njli
{   
    PhysicsShapeBox::PhysicsShapeBox():
    PhysicsShape(),
    m_btBoxShape(new btBoxShape(btVector3(1,1,1)))
    {
        m_btBoxShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeBox::PhysicsShapeBox(const AbstractBuilder &builder):
    PhysicsShape(builder),
    m_btBoxShape(new btBoxShape(btVector3(1,1,1)))
    {
        m_btBoxShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeBox::PhysicsShapeBox(const PhysicsShapeBox &copy):
    PhysicsShape(copy),
    m_btBoxShape(new btBoxShape(btVector3(1,1,1)))
    {
        //TODO: implement
        
        m_btBoxShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeBox::~PhysicsShapeBox()
    {
        m_btBoxShape->setUserPointer(NULL);
        delete m_btBoxShape;m_btBoxShape=NULL;
    }
    
    PhysicsShapeBox &PhysicsShapeBox::operator=(const PhysicsShapeBox &rhs)
    {
        if(this != &rhs)
        {
            //TODO: implement
        }
        return *this;
    }
    
    s32	PhysicsShapeBox::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsShapeBox::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsShapeBox::getClassName()const
    {
        return "PhysicsShapeBox";
    }
    
    s32 PhysicsShapeBox::getType()const
    {
        return PhysicsShapeBox::type();
    }
    
    PhysicsShapeBox::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsShapeBox **PhysicsShapeBox::createArray(const u32 size)
    {
        return (PhysicsShapeBox**)World::getInstance()->getWorldFactory()->createArray(PhysicsShapeBox::type(), size);
    }
    
    void PhysicsShapeBox::destroyArray(PhysicsShapeBox **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsShapeBox *PhysicsShapeBox::create()
    {
        return dynamic_cast<PhysicsShapeBox*>(World::getInstance()->getWorldFactory()->create(PhysicsShapeBox::type()));
    }
    
    PhysicsShapeBox *PhysicsShapeBox::create(const PhysicsShapeBoxBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsShapeBox*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsShapeBox *PhysicsShapeBox::clone(const PhysicsShapeBox &object)
    {
        return dynamic_cast<PhysicsShapeBox*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsShapeBox *PhysicsShapeBox::copy(const PhysicsShapeBox &object)
    {
        return dynamic_cast<PhysicsShapeBox*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsShapeBox::destroy(PhysicsShapeBox *object)
    {
        if(object)
        {
            PhysicsShape::destroy(object);
        }
    }
    
    void PhysicsShapeBox::load(PhysicsShapeBox &object, lua_State *L, int index)
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
                PhysicsShapeBox::load(object, L, -2);
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
    
    u32 PhysicsShapeBox::type()
    {
        return JLI_OBJECT_TYPE_PhysicsShapeBox;
    }
    
    void PhysicsShapeBox::setHalfExtends(const btVector3 &extends)
    {
        *m_btBoxShape = btBoxShape(extends);
        
//        enablePropertyChange();
//        PhysicsShape::getParent()->setPhysicsBody();
    }

    btVector3 PhysicsShapeBox::getHalfExtentsWithMargin() const
    {
        return getShape()->getHalfExtentsWithMargin();
    }

    const btVector3& PhysicsShapeBox::getHalfExtentsWithoutMargin() const
    {
        return getShape()->getHalfExtentsWithoutMargin();
    }

    btVector3 PhysicsShapeBox::localGetSupportingVertex(const btVector3& vec) const
    {
        return getShape()->localGetSupportingVertex(vec);
    }

    btVector3 PhysicsShapeBox::localGetSupportingVertexWithoutMargin(const btVector3& vec)const
    {
        return getShape()->localGetSupportingVertexWithoutMargin(vec);
    }

    void PhysicsShapeBox::batchedUnitVectorGetSupportingVertexWithoutMargin(const btVector3* vectors,btVector3* supportVerticesOut,int numVectors) const
    {
        getShape()->batchedUnitVectorGetSupportingVertexWithoutMargin(vectors, supportVerticesOut, numVectors);
    }

    void PhysicsShapeBox::setMargin(btScalar collisionMargin)
    {
        getShape()->setMargin(collisionMargin);
        
//        enablePropertyChange();
//        PhysicsShape::getParent()->setPhysicsBody();
    }

//    void PhysicsShapeBox::setLocalScaling(const btVector3& scaling)
//    {
//        getShape()->setLocalScaling(scaling);
//        
////        enablePropertyChange();
////        PhysicsShape::getParent()->setPhysicsBody();
//    }

//    void PhysicsShapeBox::getAabb(const btTransform& t,btVector3& aabbMin,btVector3& aabbMax) const
//    {
//        getShape()->getAabb(t, aabbMin, aabbMax);
//    }

    void PhysicsShapeBox::calculateLocalInertia(btScalar mass,btVector3& inertia) const
    {
        getShape()->calculateLocalInertia(mass, inertia);
    }

    void PhysicsShapeBox::getPlane(btVector3& planeNormal,btVector3& planeSupport,int i ) const
    {
        getShape()->getPlane(planeNormal, planeSupport, i);
    }
    
    btVector3 PhysicsShapeBox::getPlane(int i)const
    {
        btVector3 v,dummy;
        getPlane(v, dummy, i);
        return v;
    }

    int PhysicsShapeBox::getNumPlanes() const
    {
        return getShape()->getNumPlanes();
    }

    int PhysicsShapeBox::getNumVertices() const
    {
        return getShape()->getNumVertices();
    }

    int PhysicsShapeBox::getNumEdges() const
    {
        return getShape()->getNumEdges();
    }

    void PhysicsShapeBox::getVertex(int i,btVector3& vtx) const
    {
        getShape()->getVertex(i, vtx);
    }

    void PhysicsShapeBox::getPlaneEquation(btVector4& plane,int i) const
    {
        getShape()->getPlaneEquation(plane, i);
    }

    void PhysicsShapeBox::getEdge(int i,btVector3& pa,btVector3& pb) const
    {
        getShape()->getEdge(i, pa, pb);
    }
    
    bool PhysicsShapeBox::isInside(const btVector3& pt,btScalar tolerance) const
    {
        return getShape()->isInside(pt, tolerance);
    }
    
    const btCollisionShape* PhysicsShapeBox::getCollisionShape() const
    {
        return m_btBoxShape;
    }
    
    btCollisionShape* PhysicsShapeBox::getCollisionShape()
    {
        return m_btBoxShape;
    }
    
    void PhysicsShapeBox::setCollisionShape(const btCollisionShape &shape)
    {
        DEBUG_ASSERT(shape.getShapeType() == m_btBoxShape->getShapeType());
        
        const btBoxShape *_btBoxShape = dynamic_cast<const btBoxShape*>(&shape);
        
        setHalfExtends(_btBoxShape->getHalfExtentsWithoutMargin() / _btBoxShape->getLocalScaling());
        
//        enablePropertyChange();
//        PhysicsShape::getParent()->setPhysicsBody();
    }
    
    const btBoxShape* PhysicsShapeBox::getShape() const
    {
        return dynamic_cast<const btBoxShape*>(m_btBoxShape);
    }
    
    btBoxShape* PhysicsShapeBox::getShape()
    {
        return dynamic_cast<btBoxShape*>(m_btBoxShape);
    }
}
