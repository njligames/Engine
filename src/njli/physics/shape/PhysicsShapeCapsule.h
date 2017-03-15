//
//  PhysicsShapeCapsule.h
//  JLIGameEngineTest
//
//  Created by James Folk on 6/22/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsShapeCapsule__
#define __JLIGameEngineTest__PhysicsShapeCapsule__

#pragma mark Header

#include "AbstractFactoryObject.h"
#include "AbstractBuilder.h"
#include "lua.hpp"
#include "Log.h"
#include "PhysicsShape.h"

class btCapsuleShape;

namespace njli
{
    class PhysicsShapeCapsuleBuilder;
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) PhysicsShapeCapsule:
    public PhysicsShape
    {
        friend class WorldFactory;
    protected:
        PhysicsShapeCapsule();
        PhysicsShapeCapsule(const AbstractBuilder&);
        PhysicsShapeCapsule(const PhysicsShapeCapsule &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~PhysicsShapeCapsule();
        PhysicsShapeCapsule &operator=(const PhysicsShapeCapsule &);
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
        static PhysicsShapeCapsule **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(PhysicsShapeCapsule **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeCapsule *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeCapsule *create(const PhysicsShapeCapsuleBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeCapsule *clone(const PhysicsShapeCapsule &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeCapsule *copy(const PhysicsShapeCapsule &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(PhysicsShapeCapsule *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(PhysicsShapeCapsule &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
        
    public:
        //TODO: fill in specific methods for PhysicsShapeCapsule
        
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
         *  @param radius <#radius description#>
         */
        void setRadiusX(f32 radius);
        
        /**
         *  <#Description#>
         *
         *  @param height <#height description#>
         */
        void setHeightX(f32 height);
        
        /**
         *  <#Description#>
         *
         *  @param radius <#radius description#>
         */
        void setRadiusY(f32 radius);
        
        /**
         *  <#Description#>
         *
         *  @param height <#height description#>
         */
        void setHeightY(f32 height);
        
        /**
         *  <#Description#>
         *
         *  @param radius <#radius description#>
         */
        void setRadiusZ(f32 radius);
        
        /**
         *  <#Description#>
         *
         *  @param height <#height description#>
         */
        void setHeightZ(f32 height);
        
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
         *  @param t       <#t description#>
         *  @param aabbMin <#aabbMin description#>
         *  @param aabbMax <#aabbMax description#>
         */
        void getAabb (const btTransform& t, btVector3& aabbMin, btVector3& aabbMax) const;
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
        f32	getRadius() const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32	getHalfHeight() const;
        /**
         *  <#Description#>
         *
         *  @param scaling <#scaling description#>
         */
        void setLocalScaling(const btVector3& scaling);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        btVector3 getAnisotropicRollingFrictionDirection() const;
    protected:
        virtual const btCollisionShape*	getCollisionShape() const;
        virtual btCollisionShape* getCollisionShape();
        virtual void setCollisionShape(const btCollisionShape &shape);
        
    private:
        btCapsuleShape *m_btCapsuleShape;
    };
}

#endif /* defined(__JLIGameEngineTest__PhysicsShapeCapsule__) */
