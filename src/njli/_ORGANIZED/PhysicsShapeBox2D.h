//
//  PhysicsShapeBox2D.h
//  JLIGameEngineTest
//
//  Created by James Folk on 3/14/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsShapeBox2D__
#define __JLIGameEngineTest__PhysicsShapeBox2D__

#include "PhysicsShape.h"
#include "AbstractBuilder.h"
#include "lua.hpp"

class btBox2dShape;
class btTransform;
class btVector2;

namespace njli
{
    class PhysicsShapeBox2DBuilder;
    
    ATTRIBUTE_ALIGNED16(class) PhysicsShapeBox2D:
    public PhysicsShape
    {
        friend class WorldFactory;
    protected:
        PhysicsShapeBox2D();
        PhysicsShapeBox2D(const AbstractBuilder&);
        PhysicsShapeBox2D(const PhysicsShapeBox2D &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~PhysicsShapeBox2D();
        PhysicsShapeBox2D &operator=(const PhysicsShapeBox2D &);
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
        static PhysicsShapeBox2D **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(PhysicsShapeBox2D **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeBox2D *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeBox2D *create(const PhysicsShapeBox2DBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeBox2D *clone(const PhysicsShapeBox2D &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeBox2D *copy(const PhysicsShapeBox2D &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(PhysicsShapeBox2D *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(PhysicsShapeBox2D &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
        
    public:
        //TODO: fill in specific methods for PhysicsShapeBox2D
        /**
         *  <#Description#>
         *
         *  @param extends <#extends description#>
         */
        void setHalfExtends(const btVector2 &extends);
        
        /**
         *  <#Description#>
         *
         *  @param collisionMargin <#collisionMargin description#>
         */
        virtual void setMargin(btScalar collisionMargin);
        
        /**
         *  <#Description#>
         *
         *  @param mass    <#mass description#>
         *  @param inertia <#inertia description#>
         */
        virtual void calculateLocalInertia(btScalar mass,btVector3& inertia) const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        int	getVertexCount() const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual int getNumVertices()const;
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
         *  @return <#return value description#>
         */
        const btVector3& getCentroid() const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual int getNumPlanes() const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual int getNumEdges() const;
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
         *  @param plane <#plane description#>
         *  @param i     <#i description#>
         */
        virtual void	getPlaneEquation(btVector4& plane,int i) const;
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
         *  @param pt        <#pt description#>
         *  @param tolerance <#tolerance description#>
         *
         *  @return <#return value description#>
         */
        virtual	bool isInside(const btVector3& pt,btScalar tolerance) const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual int getNumPreferredPenetrationDirections() const;
        /**
         *  <#Description#>
         *
         *  @param index             <#index description#>
         *  @param penetrationVector <#penetrationVector description#>
         */
        virtual void getPreferredPenetrationDirection(int index, btVector3& penetrationVector) const;
    protected:
//        virtual void getAabb(const btTransform& t,btVector3& aabbMin,btVector3& aabbMax) const;
        virtual const btCollisionShape* getCollisionShape() const;
        virtual btCollisionShape* getCollisionShape();
        virtual void setCollisionShape(const btCollisionShape &shape);
        
        virtual const btBox2dShape* getShape() const;
        virtual btBox2dShape* getShape();
    private:
        btBox2dShape *m_btBox2dShape;
    };
}

#endif /* defined(__JLIGameEngineTest__PhysicsShapeBox2D__) */
