//
//  PhysicsShapeConvexTriangleMesh.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 6/22/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "PhysicsShapeConvexTriangleMesh.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsShapeConvexTriangleMeshBuilder.h"
#define TAG "PhysicsShapeConvexTriangleMesh.cpp"
#define FORMATSTRING "{\"njli::PhysicsShapeConvexTriangleMesh\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "btConvexTriangleMeshShape.h"

namespace njli
{
    PhysicsShapeConvexTriangleMesh::PhysicsShapeConvexTriangleMesh():
    PhysicsShape(),
    m_btConvexTriangleMeshShape(new btConvexTriangleMeshShape(NULL))
    {
        m_btConvexTriangleMeshShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeConvexTriangleMesh::PhysicsShapeConvexTriangleMesh(const AbstractBuilder &builder):
    PhysicsShape(builder),
    m_btConvexTriangleMeshShape(new btConvexTriangleMeshShape(NULL))
    {
        m_btConvexTriangleMeshShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeConvexTriangleMesh::PhysicsShapeConvexTriangleMesh(const PhysicsShapeConvexTriangleMesh &copy):
    PhysicsShape(copy),
    m_btConvexTriangleMeshShape(new btConvexTriangleMeshShape(NULL))
    {
        m_btConvexTriangleMeshShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeConvexTriangleMesh::~PhysicsShapeConvexTriangleMesh()
    {
        m_btConvexTriangleMeshShape->setUserPointer(NULL);
        delete m_btConvexTriangleMeshShape;m_btConvexTriangleMeshShape=NULL;
    }
    
    PhysicsShapeConvexTriangleMesh &PhysicsShapeConvexTriangleMesh::operator=(const PhysicsShapeConvexTriangleMesh &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	PhysicsShapeConvexTriangleMesh::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsShapeConvexTriangleMesh::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsShapeConvexTriangleMesh::getClassName()const
    {
        return "PhysicsShapeConvexTriangleMesh";
    }
    
    s32 PhysicsShapeConvexTriangleMesh::getType()const
    {
        return PhysicsShapeConvexTriangleMesh::type();
    }
    
    PhysicsShapeConvexTriangleMesh::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsShapeConvexTriangleMesh **PhysicsShapeConvexTriangleMesh::createArray(const u32 size)
    {
        return (PhysicsShapeConvexTriangleMesh**)World::getInstance()->getWorldFactory()->createArray(PhysicsShapeConvexTriangleMesh::type(), size);
    }
    
    void PhysicsShapeConvexTriangleMesh::destroyArray(PhysicsShapeConvexTriangleMesh **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsShapeConvexTriangleMesh *PhysicsShapeConvexTriangleMesh::create()
    {
        return dynamic_cast<PhysicsShapeConvexTriangleMesh*>(World::getInstance()->getWorldFactory()->create(PhysicsShapeConvexTriangleMesh::type()));
    }
    
    PhysicsShapeConvexTriangleMesh *PhysicsShapeConvexTriangleMesh::create(const PhysicsShapeConvexTriangleMeshBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsShapeConvexTriangleMesh*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsShapeConvexTriangleMesh *PhysicsShapeConvexTriangleMesh::clone(const PhysicsShapeConvexTriangleMesh &object)
    {
        return dynamic_cast<PhysicsShapeConvexTriangleMesh*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsShapeConvexTriangleMesh *PhysicsShapeConvexTriangleMesh::copy(const PhysicsShapeConvexTriangleMesh &object)
    {
        return dynamic_cast<PhysicsShapeConvexTriangleMesh*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsShapeConvexTriangleMesh::destroy(PhysicsShapeConvexTriangleMesh *object)
    {
        if(object)
        {
            PhysicsShape::destroy(object);
        }
    }
    
    void PhysicsShapeConvexTriangleMesh::load(PhysicsShapeConvexTriangleMesh &object, lua_State *L, int index)
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
                PhysicsShapeConvexTriangleMesh::load(object, L, -2);
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
    
    u32 PhysicsShapeConvexTriangleMesh::type()
    {
        return JLI_OBJECT_TYPE_PhysicsShapeConvexTriangleMesh;
    }
    
    
    int	PhysicsShapeConvexTriangleMesh::getNumVertices() const
    {
        return 0;
    }
    
    int PhysicsShapeConvexTriangleMesh::getNumEdges() const
    {
        return 0;
    }
    
    void PhysicsShapeConvexTriangleMesh::getEdge(int i,btVector3& pa,btVector3& pb) const
    {
        
    }
    
    void PhysicsShapeConvexTriangleMesh::getVertex(int i,btVector3& vtx) const
    {
        
    }
    
    int	PhysicsShapeConvexTriangleMesh::getNumPlanes() const
    {
        return 0;
    }
    
    void PhysicsShapeConvexTriangleMesh::getPlane(btVector3& planeNormal,btVector3& planeSupport,int i ) const
    {
        
    }
    
    bool PhysicsShapeConvexTriangleMesh::isInside(const btVector3& pt, f32 tolerance) const
    {
        return false;
    }
    
//    void PhysicsShapeConvexTriangleMesh::getAabb(const btTransform& t,btVector3& aabbMin,btVector3& aabbMax) const
//    {
//        
//    }
    
    const btCollisionShape*	PhysicsShapeConvexTriangleMesh::getCollisionShape() const
    {
        return m_btConvexTriangleMeshShape;
    }
    
    btCollisionShape* PhysicsShapeConvexTriangleMesh::getCollisionShape()
    {
        return m_btConvexTriangleMeshShape;
    }
    
    void PhysicsShapeConvexTriangleMesh::setCollisionShape(const btCollisionShape &shape)
    {
        
    }
}
