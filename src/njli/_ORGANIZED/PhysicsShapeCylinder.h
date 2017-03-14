//
//  PhysicsShapeCylinder.h
//  JLIGameEngineTest
//
//  Created by James Folk on 6/22/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsShapeCylinder__
#define __JLIGameEngineTest__PhysicsShapeCylinder__

#pragma mark Header

#include "AbstractFactoryObject.h"
#include "AbstractBuilder.h"
#include "lua.hpp"
#include "Log.h"
#include "PhysicsShape.h"

class btCylinderShape;

namespace njli
{
    class PhysicsShapeCylinderBuilder;
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) PhysicsShapeCylinder:
    public PhysicsShape
    {
        friend class WorldFactory;
    protected:
        PhysicsShapeCylinder();
        PhysicsShapeCylinder(const AbstractBuilder&);
        PhysicsShapeCylinder(const PhysicsShapeCylinder &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~PhysicsShapeCylinder();
        PhysicsShapeCylinder &operator=(const PhysicsShapeCylinder &);
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
        static PhysicsShapeCylinder **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(PhysicsShapeCylinder **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeCylinder *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeCylinder *create(const PhysicsShapeCylinderBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeCylinder *clone(const PhysicsShapeCylinder &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeCylinder *copy(const PhysicsShapeCylinder &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(PhysicsShapeCylinder *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(PhysicsShapeCylinder &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
        
    public:
        //TODO: fill in specific methods for PhysicsShapeCylinder
        
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
        virtual	bool isInside(const btVector3& pt,f32 tolerance) const;
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        btVector3 getHalfExtentsWithMargin() const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        const btVector3& getHalfExtentsWithoutMargin() const;
        
        /**
         *  <#Description#>
         *
         *  @param halfExtents <#halfExtents description#>
         */
        void setHalfExtentsX (const btVector3& halfExtents);
        
        /**
         *  <#Description#>
         *
         *  @param halfExtents <#halfExtents description#>
         */
        void setHalfExtentsY (const btVector3& halfExtents);
        
        /**
         *  <#Description#>
         *
         *  @param halfExtents <#halfExtents description#>
         */
        void setHalfExtentsZ (const btVector3& halfExtents);
        
        /**
         *  <#Description#>
         *
         *  @param mass    <#mass description#>
         *  @param inertia <#inertia description#>
         */
        void calculateLocalInertia(f32 mass,btVector3& inertia) const;
        /**
         *  <#Description#>
         *
         *  @param collisionMargin <#collisionMargin description#>
         */
        void setMargin(f32 collisionMargin);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        int	getUpAxis() const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        btVector3 getAnisotropicRollingFrictionDirection() const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getRadius() const;
    protected:
//        virtual void getAabb(const btTransform& t,btVector3& aabbMin,btVector3& aabbMax) const;
        virtual const btCollisionShape*	getCollisionShape() const;
        virtual btCollisionShape* getCollisionShape();
        virtual void setCollisionShape(const btCollisionShape &shape);
        
    private:
        btCylinderShape *m_btCylinderShape;
    };
}

#endif /* defined(__JLIGameEngineTest__PhysicsShapeCylinder__) */
