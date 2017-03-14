//
//  PhysicsShapeBvhTriangleMesh.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 6/22/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "PhysicsShapeBvhTriangleMesh.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsShapeBvhTriangleMeshBuilder.h"
#define TAG "PhysicsShapeBvhTriangleMesh.cpp"
#define FORMATSTRING "{\"njli::PhysicsShapeBvhTriangleMesh\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "btBvhTriangleMeshShape.h"

namespace njli
{
    PhysicsShapeBvhTriangleMesh::PhysicsShapeBvhTriangleMesh():
    PhysicsShape(),
    m_btBvhTriangleMeshShape(new btBvhTriangleMeshShape(NULL, false))
    {
        m_btBvhTriangleMeshShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeBvhTriangleMesh::PhysicsShapeBvhTriangleMesh(const AbstractBuilder &builder):
    PhysicsShape(builder),
    m_btBvhTriangleMeshShape(new btBvhTriangleMeshShape(NULL, false))
    {
        m_btBvhTriangleMeshShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeBvhTriangleMesh::PhysicsShapeBvhTriangleMesh(const PhysicsShapeBvhTriangleMesh &copy):
    PhysicsShape(copy),
    m_btBvhTriangleMeshShape(new btBvhTriangleMeshShape(NULL, false))
    {
        m_btBvhTriangleMeshShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeBvhTriangleMesh::~PhysicsShapeBvhTriangleMesh()
    {
        m_btBvhTriangleMeshShape->setUserPointer(NULL);
        delete m_btBvhTriangleMeshShape;m_btBvhTriangleMeshShape=NULL;
    }
    
    PhysicsShapeBvhTriangleMesh &PhysicsShapeBvhTriangleMesh::operator=(const PhysicsShapeBvhTriangleMesh &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	PhysicsShapeBvhTriangleMesh::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsShapeBvhTriangleMesh::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsShapeBvhTriangleMesh::getClassName()const
    {
        return "PhysicsShapeBvhTriangleMesh";
    }
    
    s32 PhysicsShapeBvhTriangleMesh::getType()const
    {
        return PhysicsShapeBvhTriangleMesh::type();
    }
    
    PhysicsShapeBvhTriangleMesh::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsShapeBvhTriangleMesh **PhysicsShapeBvhTriangleMesh::createArray(const u32 size)
    {
        return (PhysicsShapeBvhTriangleMesh**)World::getInstance()->getWorldFactory()->createArray(PhysicsShapeBvhTriangleMesh::type(), size);
    }
    
    void PhysicsShapeBvhTriangleMesh::destroyArray(PhysicsShapeBvhTriangleMesh **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsShapeBvhTriangleMesh *PhysicsShapeBvhTriangleMesh::create()
    {
        return dynamic_cast<PhysicsShapeBvhTriangleMesh*>(World::getInstance()->getWorldFactory()->create(PhysicsShapeBvhTriangleMesh::type()));
    }
    
    PhysicsShapeBvhTriangleMesh *PhysicsShapeBvhTriangleMesh::create(const PhysicsShapeBvhTriangleMeshBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsShapeBvhTriangleMesh*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsShapeBvhTriangleMesh *PhysicsShapeBvhTriangleMesh::clone(const PhysicsShapeBvhTriangleMesh &object)
    {
        return dynamic_cast<PhysicsShapeBvhTriangleMesh*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsShapeBvhTriangleMesh *PhysicsShapeBvhTriangleMesh::copy(const PhysicsShapeBvhTriangleMesh &object)
    {
        return dynamic_cast<PhysicsShapeBvhTriangleMesh*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsShapeBvhTriangleMesh::destroy(PhysicsShapeBvhTriangleMesh *object)
    {
        if(object)
        {
            PhysicsShape::destroy(object);
        }
    }
    
    void PhysicsShapeBvhTriangleMesh::load(PhysicsShapeBvhTriangleMesh &object, lua_State *L, int index)
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
                PhysicsShapeBvhTriangleMesh::load(object, L, -2);
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
    
    u32 PhysicsShapeBvhTriangleMesh::type()
    {
        return JLI_OBJECT_TYPE_PhysicsShapeBvhTriangleMesh;
    }
    
    
    int	PhysicsShapeBvhTriangleMesh::getNumVertices() const
    {
        return 0;
    }
    
    int PhysicsShapeBvhTriangleMesh::getNumEdges() const
    {
        return 0;
    }
    
    void PhysicsShapeBvhTriangleMesh::getEdge(int i,btVector3& pa,btVector3& pb) const
    {
        
    }
    
    void PhysicsShapeBvhTriangleMesh::getVertex(int i,btVector3& vtx) const
    {
        
    }
    
    int	PhysicsShapeBvhTriangleMesh::getNumPlanes() const
    {
        return 0;
    }
    
    void PhysicsShapeBvhTriangleMesh::getPlane(btVector3& planeNormal,btVector3& planeSupport,int i ) const
    {
        
    }
    
    bool PhysicsShapeBvhTriangleMesh::isInside(const btVector3& pt, f32 tolerance) const
    {
        return false;
    }
    
//    void PhysicsShapeBvhTriangleMesh::getAabb(const btTransform& t,btVector3& aabbMin,btVector3& aabbMax) const
//    {
//        
//    }
    
    const btCollisionShape*	PhysicsShapeBvhTriangleMesh::getCollisionShape() const
    {
        return m_btBvhTriangleMeshShape;
    }
    
    btCollisionShape* PhysicsShapeBvhTriangleMesh::getCollisionShape()
    {
        return m_btBvhTriangleMeshShape;
    }
    
    void PhysicsShapeBvhTriangleMesh::setCollisionShape(const btCollisionShape &shape)
    {
        
    }
}
