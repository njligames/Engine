//
//  PhysicsShapeMultiSphere.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 6/22/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#pragma mark Implementation

#include "PhysicsShapeMultiSphere.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "PhysicsShapeMultiSphereBuilder.h"
#define TAG "PhysicsShapeMultiSphere.cpp"
#define FORMATSTRING "{\"njli::PhysicsShapeMultiSphere\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "btMultiSphereShape.h"

namespace njli
{
    PhysicsShapeMultiSphere::PhysicsShapeMultiSphere():
    PhysicsShape(),
    m_btMultiSphereShape(new btMultiSphereShape(&m_localPositionArray[0], &m_radiArray[0], 0))
    {
        m_btMultiSphereShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeMultiSphere::PhysicsShapeMultiSphere(const AbstractBuilder &builder):
    PhysicsShape(builder),
    m_btMultiSphereShape(new btMultiSphereShape(&m_localPositionArray[0], &m_radiArray[0], 0))
    {
        m_btMultiSphereShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeMultiSphere::PhysicsShapeMultiSphere(const PhysicsShapeMultiSphere &copy):
    PhysicsShape(copy),
    m_btMultiSphereShape(new btMultiSphereShape(&m_localPositionArray[0], &m_radiArray[0], 0))
    {
        m_btMultiSphereShape->setUserPointer(static_cast<void*>(this));
    }
    
    PhysicsShapeMultiSphere::~PhysicsShapeMultiSphere()
    {
        m_btMultiSphereShape->setUserPointer(NULL);
        delete m_btMultiSphereShape;m_btMultiSphereShape=NULL;
    }
    
    PhysicsShapeMultiSphere &PhysicsShapeMultiSphere::operator=(const PhysicsShapeMultiSphere &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	PhysicsShapeMultiSphere::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsShapeMultiSphere::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsShapeMultiSphere::getClassName()const
    {
        return "PhysicsShapeMultiSphere";
    }
    
    s32 PhysicsShapeMultiSphere::getType()const
    {
        return PhysicsShapeMultiSphere::type();
    }
    
    PhysicsShapeMultiSphere::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsShapeMultiSphere **PhysicsShapeMultiSphere::createArray(const u32 size)
    {
        return (PhysicsShapeMultiSphere**)World::getInstance()->getWorldFactory()->createArray(PhysicsShapeMultiSphere::type(), size);
    }
    
    void PhysicsShapeMultiSphere::destroyArray(PhysicsShapeMultiSphere **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsShapeMultiSphere *PhysicsShapeMultiSphere::create()
    {
        return dynamic_cast<PhysicsShapeMultiSphere*>(World::getInstance()->getWorldFactory()->create(PhysicsShapeMultiSphere::type()));
    }
    
    PhysicsShapeMultiSphere *PhysicsShapeMultiSphere::create(const PhysicsShapeMultiSphereBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsShapeMultiSphere*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsShapeMultiSphere *PhysicsShapeMultiSphere::clone(const PhysicsShapeMultiSphere &object)
    {
        return dynamic_cast<PhysicsShapeMultiSphere*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    PhysicsShapeMultiSphere *PhysicsShapeMultiSphere::copy(const PhysicsShapeMultiSphere &object)
    {
        return dynamic_cast<PhysicsShapeMultiSphere*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsShapeMultiSphere::destroy(PhysicsShapeMultiSphere *object)
    {
        if(object)
        {
            PhysicsShape::destroy(object);
        }
    }
    
    void PhysicsShapeMultiSphere::load(PhysicsShapeMultiSphere &object, lua_State *L, int index)
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
                PhysicsShapeMultiSphere::load(object, L, -2);
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
    
    u32 PhysicsShapeMultiSphere::type()
    {
        return JLI_OBJECT_TYPE_PhysicsShapeMultiSphere;
    }
    
    
    int	PhysicsShapeMultiSphere::getNumVertices() const
    {
        return 0;
    }
    
    int PhysicsShapeMultiSphere::getNumEdges() const
    {
        return 0;
    }
    
    void PhysicsShapeMultiSphere::getEdge(int i,btVector3& pa,btVector3& pb) const
    {
        
    }
    
    void PhysicsShapeMultiSphere::getVertex(int i,btVector3& vtx) const
    {
        
    }
    
    int	PhysicsShapeMultiSphere::getNumPlanes() const
    {
        return 0;
    }
    
    void PhysicsShapeMultiSphere::getPlane(btVector3& planeNormal,btVector3& planeSupport,int i ) const
    {
        
    }
    
    bool PhysicsShapeMultiSphere::isInside(const btVector3& pt, f32 tolerance) const
    {
        return false;
    }

    
    void PhysicsShapeMultiSphere::addSphere(const btVector3 &position, const f32 radius)
    {
        DEBUG_ASSERT(radius >= 0.0f);
        
        removeSphere(position, radius);
        
        m_localPositionArray.push_back(position);
        m_radiArray.push_back(radius);
        
        *m_btMultiSphereShape = btMultiSphereShape(&m_localPositionArray[0], &m_radiArray[0], m_localPositionArray.size());
    }
    
    void PhysicsShapeMultiSphere::removeSphere(const btVector3 &position, const f32 radius)
    {
        int posIndex = m_localPositionArray.findLinearSearch(position);
        int radIndex = m_radiArray.findLinearSearch(radius);
        
        if (posIndex != m_localPositionArray.size() &&
            radIndex != m_radiArray.size())
        {
            if (posIndex == radIndex)
            {
                m_localPositionArray.remove(position);
                m_radiArray.remove(radius);
            }
        }
        
        *m_btMultiSphereShape = btMultiSphereShape(&m_localPositionArray[0], &m_radiArray[0], m_localPositionArray.size());
    }
//    void PhysicsShapeMultiSphere::setup (const btVector3* positions,const btScalar* radi,int numSpheres)
//    {
//        *m_btMultiSphereShape = btMultiSphereShape(positions, radi, numSpheres);
//    }
    
    void PhysicsShapeMultiSphere::calculateLocalInertia(btScalar mass,btVector3& inertia) const
    {
        const btMultiSphereShape *multisphere = dynamic_cast<const btMultiSphereShape*>(getCollisionShape());
        multisphere->calculateLocalInertia(mass, inertia);
    }
    
    int	PhysicsShapeMultiSphere::getSphereCount() const
    {
        const btMultiSphereShape *multisphere = dynamic_cast<const btMultiSphereShape*>(getCollisionShape());
        return multisphere->getSphereCount();
    }
    
    const btVector3& PhysicsShapeMultiSphere::getSpherePosition(int index) const
    {
        const btMultiSphereShape *multisphere = dynamic_cast<const btMultiSphereShape*>(getCollisionShape());
        return multisphere->getSpherePosition(index);
    }
    
    btScalar PhysicsShapeMultiSphere::getSphereRadius(int index) const
    {
        const btMultiSphereShape *multisphere = dynamic_cast<const btMultiSphereShape*>(getCollisionShape());
        return multisphere->getSphereRadius(index);
    }
    
    const btCollisionShape*	PhysicsShapeMultiSphere::getCollisionShape() const
    {
        return m_btMultiSphereShape;
    }
    
    btCollisionShape* PhysicsShapeMultiSphere::getCollisionShape()
    {
        return m_btMultiSphereShape;
    }
    
    void PhysicsShapeMultiSphere::setCollisionShape(const btCollisionShape &shape)
    {
        DEBUG_ASSERT(shape.getShapeType() == m_btMultiSphereShape->getShapeType());
        const btMultiSphereShape *multisphere = dynamic_cast<const btMultiSphereShape*>(&shape);
        m_localPositionArray.resize(multisphere->getSphereCount());
        m_radiArray.resize(multisphere->getSphereCount());
        
        for (s32 i = 0; i < multisphere->getSphereCount(); ++i)
        {
            m_localPositionArray.push_back(multisphere->getSpherePosition(i));
            m_radiArray.push_back(multisphere->getSphereRadius(i));
        }
        
        *m_btMultiSphereShape = btMultiSphereShape(&m_localPositionArray[0], &m_radiArray[0], m_localPositionArray.size());
    }
}
