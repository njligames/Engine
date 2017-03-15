//
//  PhysicsShapeMultiSphere.h
//  JLIGameEngineTest
//
//  Created by James Folk on 6/22/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsShapeMultiSphere__
#define __JLIGameEngineTest__PhysicsShapeMultiSphere__

#pragma mark Header

#include "AbstractFactoryObject.h"
#include "AbstractBuilder.h"
#include "lua.hpp"
#include "Log.h"
#include "PhysicsShape.h"

class btMultiSphereShape;

namespace njli
{
    class PhysicsShapeMultiSphereBuilder;
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) PhysicsShapeMultiSphere:
    public PhysicsShape
    {
        friend class WorldFactory;
    protected:
        PhysicsShapeMultiSphere();
        PhysicsShapeMultiSphere(const AbstractBuilder&);
        PhysicsShapeMultiSphere(const PhysicsShapeMultiSphere &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~PhysicsShapeMultiSphere();
        PhysicsShapeMultiSphere &operator=(const PhysicsShapeMultiSphere &);
    public:
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual	s32	calculateSerializeBufferSize() const;
        /**
         *  <#Description#>
         *
         *  @param btSerializer <#btSerializer description#>
         */
        virtual	void serialize(void*, btSerializer*) const;
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual const char *getClassName()const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual s32 getType()const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        operator std::string() const;
        
        /**
         *  <#Description#>
         *
         *  @param size <#size description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeMultiSphere **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(PhysicsShapeMultiSphere **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeMultiSphere *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeMultiSphere *create(const PhysicsShapeMultiSphereBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeMultiSphere *clone(const PhysicsShapeMultiSphere &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeMultiSphere *copy(const PhysicsShapeMultiSphere &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(PhysicsShapeMultiSphere *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(PhysicsShapeMultiSphere &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
        
    public:
        //TODO: fill in specific methods for PhysicsShapeMultiSphere
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual int	getNumVertices() const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual int getNumEdges() const;
        /**
         *  <#Description#>
         *
         *  @param i  <#i description#>
         *  @param pa <#pa description#>
         *  @param pb <#pb description#>
         */
        virtual void getEdge(int i,btVector3& pa,btVector3& pb) const;
        /**
         *  <#Description#>
         *
         *  @param i   <#i description#>
         *  @param vtx <#vtx description#>
         */
        virtual void getVertex(int i,btVector3& vtx) const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual int	getNumPlanes() const;
        /**
         *  <#Description#>
         *
         *  @param planeNormal  <#planeNormal description#>
         *  @param planeSupport <#planeSupport description#>
         *  @param i            <#i description#>
         */
        virtual void getPlane(btVector3& planeNormal,btVector3& planeSupport,int i ) const;
        
        /**
         *  <#Description#>
         *
         *  @param pt        <#pt description#>
         *  @param tolerance <#tolerance description#>
         *
         *  @return <#return value description#>
         */
        virtual	bool isInside(const btVector3& pt, f32 tolerance) const;
        
        /**
         *  <#Description#>
         *
         *  @param position <#position description#>
         *  @param radius   <#radius description#>
         */
        void addSphere(const btVector3 &position, const f32 radius);
        /**
         *  <#Description#>
         *
         *  @param position <#position description#>
         *  @param radius   <#radius description#>
         */
        void removeSphere(const btVector3 &position, const f32 radius);
        
        /**
         *  <#Description#>
         *
         *  @param mass    <#mass description#>
         *  @param inertia <#inertia description#>
         */
        void calculateLocalInertia(btScalar mass,btVector3& inertia) const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        int	getSphereCount() const;
        /**
         *  <#Description#>
         *
         *  @param index <#index description#>
         *
         *  @return <#return value description#>
         */
        const btVector3& getSpherePosition(int index) const;
        /**
         *  <#Description#>
         *
         *  @param index <#index description#>
         *
         *  @return <#return value description#>
         */
        btScalar getSphereRadius(int index) const;
    protected:
//        virtual void getAabb(const btTransform& t,btVector3& aabbMin,btVector3& aabbMax) const;
        virtual const btCollisionShape*	getCollisionShape() const;
        virtual btCollisionShape* getCollisionShape();
        virtual void setCollisionShape(const btCollisionShape &shape);
        
    private:
        btMultiSphereShape *m_btMultiSphereShape;
        btAlignedObjectArray<btVector3> m_localPositionArray;
        btAlignedObjectArray<btScalar>  m_radiArray;
    };
}

#endif /* defined(__JLIGameEngineTest__PhysicsShapeMultiSphere__) */
