//
//  PhysicsShapeHeightfieldTerrain.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 6/22/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "PhysicsShapeHeightfieldTerrain.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsShapeHeightfieldTerrainBuilder.h"
#define TAG "PhysicsShapeHeightfieldTerrain.cpp"
#define FORMATSTRING "{\"njli::PhysicsShapeHeightfieldTerrain\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "btHeightfieldTerrainShape.h"

namespace njli
{
    PhysicsShapeHeightfieldTerrain::PhysicsShapeHeightfieldTerrain():
    PhysicsShape(),
    m_btHeightfieldTerrainShape(new btHeightfieldTerrainShape(0,0,NULL, 0,0,true,false))
    {
        m_btHeightfieldTerrainShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeHeightfieldTerrain::PhysicsShapeHeightfieldTerrain(const AbstractBuilder &builder):
    PhysicsShape(builder),
    m_btHeightfieldTerrainShape(new btHeightfieldTerrainShape(0,0,NULL, 0,0,true,false))
    {
        m_btHeightfieldTerrainShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeHeightfieldTerrain::PhysicsShapeHeightfieldTerrain(const PhysicsShapeHeightfieldTerrain &copy):
    PhysicsShape(copy),
    m_btHeightfieldTerrainShape(new btHeightfieldTerrainShape(0,0,NULL, 0,0,true,false))
    {
        m_btHeightfieldTerrainShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeHeightfieldTerrain::~PhysicsShapeHeightfieldTerrain()
    {
        m_btHeightfieldTerrainShape->setUserPointer(NULL);
        delete m_btHeightfieldTerrainShape;m_btHeightfieldTerrainShape=NULL;
    }
    
    PhysicsShapeHeightfieldTerrain &PhysicsShapeHeightfieldTerrain::operator=(const PhysicsShapeHeightfieldTerrain &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	PhysicsShapeHeightfieldTerrain::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsShapeHeightfieldTerrain::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsShapeHeightfieldTerrain::getClassName()const
    {
        return "PhysicsShapeHeightfieldTerrain";
    }
    
    s32 PhysicsShapeHeightfieldTerrain::getType()const
    {
        return PhysicsShapeHeightfieldTerrain::type();
    }
    
    PhysicsShapeHeightfieldTerrain::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsShapeHeightfieldTerrain **PhysicsShapeHeightfieldTerrain::createArray(const u32 size)
    {
        return (PhysicsShapeHeightfieldTerrain**)World::getInstance()->getWorldFactory()->createArray(PhysicsShapeHeightfieldTerrain::type(), size);
    }
    
    void PhysicsShapeHeightfieldTerrain::destroyArray(PhysicsShapeHeightfieldTerrain **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsShapeHeightfieldTerrain *PhysicsShapeHeightfieldTerrain::create()
    {
        return dynamic_cast<PhysicsShapeHeightfieldTerrain*>(World::getInstance()->getWorldFactory()->create(PhysicsShapeHeightfieldTerrain::type()));
    }
    
    PhysicsShapeHeightfieldTerrain *PhysicsShapeHeightfieldTerrain::create(const PhysicsShapeHeightfieldTerrainBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsShapeHeightfieldTerrain*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsShapeHeightfieldTerrain *PhysicsShapeHeightfieldTerrain::clone(const PhysicsShapeHeightfieldTerrain &object)
    {
        return dynamic_cast<PhysicsShapeHeightfieldTerrain*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsShapeHeightfieldTerrain *PhysicsShapeHeightfieldTerrain::copy(const PhysicsShapeHeightfieldTerrain &object)
    {
        return dynamic_cast<PhysicsShapeHeightfieldTerrain*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsShapeHeightfieldTerrain::destroy(PhysicsShapeHeightfieldTerrain *object)
    {
        if(object)
        {
            PhysicsShape::destroy(object);
        }
    }
    
    void PhysicsShapeHeightfieldTerrain::load(PhysicsShapeHeightfieldTerrain &object, lua_State *L, int index)
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
                PhysicsShapeHeightfieldTerrain::load(object, L, -2);
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
    
    u32 PhysicsShapeHeightfieldTerrain::type()
    {
        return JLI_OBJECT_TYPE_PhysicsShapeHeightfieldTerrain;
    }
    
    
    int	PhysicsShapeHeightfieldTerrain::getNumVertices() const
    {
        return 0;
    }
    
    int PhysicsShapeHeightfieldTerrain::getNumEdges() const
    {
        return 0;
    }
    
    void PhysicsShapeHeightfieldTerrain::getEdge(int i,btVector3& pa,btVector3& pb) const
    {
        
    }
    
    void PhysicsShapeHeightfieldTerrain::getVertex(int i,btVector3& vtx) const
    {
        
    }
    
    int	PhysicsShapeHeightfieldTerrain::getNumPlanes() const
    {
        return 0;
    }
    
    void PhysicsShapeHeightfieldTerrain::getPlane(btVector3& planeNormal,btVector3& planeSupport,int i ) const
    {
        
    }
    
    bool PhysicsShapeHeightfieldTerrain::isInside(const btVector3& pt, f32 tolerance) const
    {
        return false;
    }
    
//    void PhysicsShapeHeightfieldTerrain::getAabb(const btTransform& t,btVector3& aabbMin,btVector3& aabbMax) const
//    {
//        
//    }
    
    const btCollisionShape*	PhysicsShapeHeightfieldTerrain::getCollisionShape() const
    {
        return m_btHeightfieldTerrainShape;
    }
    
    btCollisionShape* PhysicsShapeHeightfieldTerrain::getCollisionShape()
    {
        return m_btHeightfieldTerrainShape;
    }
    
    void PhysicsShapeHeightfieldTerrain::setCollisionShape(const btCollisionShape &shape)
    {
        
    }
}
