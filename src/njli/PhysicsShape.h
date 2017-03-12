//
//  PhysicsShape.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsShape__
#define __JLIGameEngineTest__PhysicsShape__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "btVector3.h"
#include "lua.hpp"

class btCollisionShape;
class btRigidBody;
class btMotionState;
class btTransform;

namespace njli {
class PhysicsBody;
class PhysicsShapeBuilder;

ATTRIBUTE_ALIGNED16(class)
PhysicsShape : public AbstractFactoryObject
{
    friend class WorldFactory;
    friend class PhysicsBody;
    friend class PhysicsBodyRigid;
    friend class Node;

protected:
    PhysicsShape();
    PhysicsShape(const AbstractBuilder&);
    PhysicsShape(const PhysicsShape&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~PhysicsShape();
    PhysicsShape& operator=(const PhysicsShape&);

public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
    using AbstractFactoryObject::create;
//    using AbstractFactoryObject::clone;
    using AbstractFactoryObject::getPointer;
    using AbstractFactoryObject::getPointerValue;
    using AbstractFactoryObject::serializeObject;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 calculateSerializeBufferSize() const = 0;
    /**
         *  <#Description#>
         *
         *  @param btSerializer <#btSerializer description#>
         */
    virtual void serialize(void*, btSerializer*) const = 0;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual const char* getClassName() const = 0;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 getType() const = 0;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    operator std::string() const = 0;

    /**
         *  <#Description#>
         *
         *  @param type <#type description#>
         *
         *  @return <#return value description#>
         */
    static PhysicsShape* create(u32 type);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(PhysicsShape * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(PhysicsShape & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

public:
    //TODO: fill in specific methods for PhysicsShape
    /**
         *  <#Description#>
         *
         *  @param mass        <#mass description#>
         *  @param motionState <#motionState description#>
         *  @param localInertia           <#0 description#>
         *
         *  @return <#return value description#>
         */
    btRigidBody* createRigidBodyWithShape(f32 mass, btMotionState * motionState, const btVector3& localInertia = btVector3(0, 0, 0));
    /**
         *  <#Description#>
         *
         *  @param mass <#mass description#>
         *
         *  @return <#return value description#>
         */
    btVector3 calculateLocalInertia(f32 mass) const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual int getNumVertices() const = 0;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual int getNumEdges() const = 0;
    /**
         *  <#Description#>
         *
         *  @param i  <#i description#>
         *  @param pa <#pa description#>
         *  @param pb <#pb description#>
         */
    virtual void getEdge(int i, btVector3& pa, btVector3& pb) const = 0;
    /**
         *  <#Description#>
         *
         *  @param i   <#i description#>
         *  @param vtx <#vtx description#>
         */
    virtual void getVertex(int i, btVector3& vtx) const = 0;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual int getNumPlanes() const = 0;
    /**
         *  <#Description#>
         *
         *  @param planeNormal  <#planeNormal description#>
         *  @param planeSupport <#planeSupport description#>
         *  @param i            <#i description#>
         */
    virtual void getPlane(btVector3 & planeNormal, btVector3 & planeSupport, int i) const = 0;

    /**
         *  <#Description#>
         *
         *  @param pt        <#pt description#>
         *  @param tolerance <#tolerance description#>
         *
         *  @return <#return value description#>
         */
    virtual bool isInside(const btVector3& pt, btScalar tolerance) const = 0;

    /**
         *  <#Description#>
         *
         *  @param scaling <#scaling description#>
         */
    virtual void setLocalScaling(const btVector3& scaling);
    /**
         *  <#Description#>
         *
         *  @param t       <#t description#>
         *  @param aabbMin <#aabbMin description#>
         *  @param aabbMax <#aabbMax description#>
         */
    virtual void getAabb(const btTransform& t, btVector3& aabbMin, btVector3& aabbMax) const;

protected:
    virtual const btCollisionShape* getCollisionShape() const = 0;
    virtual btCollisionShape* getCollisionShape() = 0;
    virtual void setCollisionShape(const btCollisionShape& shape) = 0;

    //        void applyPhysicsShape();

    PhysicsBody* getParent();
    const PhysicsBody* getParent() const;
    //        virtual void enablePropertyChange(bool enable = true);
    //        virtual bool isPropertyChanged()const;
private:
    //        bool m_PropertyChanged;
};
}

#endif /* defined(__JLIGameEngineTest__PhysicsShape__) */
