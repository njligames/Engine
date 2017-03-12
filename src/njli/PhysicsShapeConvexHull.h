//
//  PhysicsShapeConvexHull.h
//  JLIGameEngineTest
//
//  Created by James Folk on 6/22/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsShapeConvexHull__
#define __JLIGameEngineTest__PhysicsShapeConvexHull__

#pragma mark Header

#include "AbstractFactoryObject.h"
#include "AbstractBuilder.h"
#include "lua.hpp"
#include "Log.h"
#include "PhysicsShape.h"

class btConvexHullShape;

namespace njli
{
    class PhysicsShapeConvexHullBuilder;
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) PhysicsShapeConvexHull:
    public PhysicsShape
    {
        friend class WorldFactory;
    protected:
        PhysicsShapeConvexHull();
        PhysicsShapeConvexHull(const AbstractBuilder&);
        PhysicsShapeConvexHull(const PhysicsShapeConvexHull &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~PhysicsShapeConvexHull();
        PhysicsShapeConvexHull &operator=(const PhysicsShapeConvexHull &);
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
        static PhysicsShapeConvexHull **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(PhysicsShapeConvexHull **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeConvexHull *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeConvexHull *create(const PhysicsShapeConvexHullBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeConvexHull *clone(const PhysicsShapeConvexHull &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeConvexHull *copy(const PhysicsShapeConvexHull &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(PhysicsShapeConvexHull *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(PhysicsShapeConvexHull &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
        
    public:
        //TODO: fill in specific methods for PhysicsShapeConvexHull
        
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
         *  @param point                <#point description#>
         *  @param recalculateLocalAabb <#recalculateLocalAabb description#>
         */
        void addPoint(const btVector3& point, bool recalculateLocalAabb = true);
        
        /**
         *  <#Description#>
         *
         *  @param points <#points description#>
         */
        void getUnscaledPoints(std::vector<btVector3> &points)const;
        /**
         *  <#Description#>
         *
         *  @param i <#i description#>
         *
         *  @return <#return value description#>
         */
        btVector3 getScaledPoint(int i) const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        int getNumPoints() const;
        /**
         *  <#Description#>
         *
         *  @param trans       <#trans description#>
         *  @param dir         <#dir description#>
         *  @param minProj     <#minProj description#>
         *  @param maxProj     <#maxProj description#>
         *  @param witnesPtMin <#witnesPtMin description#>
         *  @param witnesPtMax <#witnesPtMax description#>
         */
        void project(const btTransform& trans, const btVector3& dir, btScalar& minProj, btScalar& maxProj, btVector3& witnesPtMin,btVector3& witnesPtMax) const;
    protected:
//        virtual void getAabb(const btTransform& t,btVector3& aabbMin,btVector3& aabbMax) const;
        virtual const btCollisionShape*	getCollisionShape() const;
        virtual btCollisionShape* getCollisionShape();
        virtual void setCollisionShape(const btCollisionShape &shape);
        
    private:
        btConvexHullShape *m_btConvexHullShape;
    };
}

#endif /* defined(__JLIGameEngineTest__PhysicsShapeConvexHull__) */
