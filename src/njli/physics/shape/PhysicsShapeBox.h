//
//  PhysicsShapeBox.h
//  JLIGameEngineTest
//
//  Created by James Folk on 1/1/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsShapeBox__
#define __JLIGameEngineTest__PhysicsShapeBox__

#include "PhysicsShape.h"
#include "AbstractBuilder.h"
#include "lua.hpp"

class btCollisionShape;
class btBoxShape;
class btVector3;
class btVector4;
class btTransform;



namespace njli
{
    class PhysicsShapeBoxBuilder;
    
    ATTRIBUTE_ALIGNED16(class) PhysicsShapeBox:
    public PhysicsShape
    {
        friend class WorldFactory;
    protected:
        PhysicsShapeBox();
        PhysicsShapeBox(const AbstractBuilder&);
        PhysicsShapeBox(const PhysicsShapeBox &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~PhysicsShapeBox();
        PhysicsShapeBox &operator=(const PhysicsShapeBox &);
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
        static PhysicsShapeBox **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(PhysicsShapeBox **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeBox *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeBox *create(const PhysicsShapeBoxBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeBox *clone(const PhysicsShapeBox &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeBox *copy(const PhysicsShapeBox &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(PhysicsShapeBox *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(PhysicsShapeBox &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
        
    public:
        //TODO: fill in specific methods for PhysicsShapeBox
        
        /**
         *  <#Description#>
         *
         *  @param extends <#extends description#>
         */
        void setHalfExtends(const btVector3 &extends);
        
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
         *  @param vec <#vec description#>
         *
         *  @return <#return value description#>
         */
        btVector3 localGetSupportingVertex(const btVector3& vec) const;
        /**
         *  <#Description#>
         *
         *  @param vec <#vec description#>
         *
         *  @return <#return value description#>
         */
        btVector3 localGetSupportingVertexWithoutMargin(const btVector3& vec)const;
        /**
         *  <#Description#>
         *
         *  @param vectors            <#vectors description#>
         *  @param supportVerticesOut <#supportVerticesOut description#>
         *  @param numVectors         <#numVectors description#>
         */
        void batchedUnitVectorGetSupportingVertexWithoutMargin(const btVector3* vectors,btVector3* supportVerticesOut,int numVectors) const;
        /**
         *  <#Description#>
         *
         *  @param collisionMargin <#collisionMargin description#>
         */
        void setMargin(btScalar collisionMargin);
        
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
         *  @param planeNormal  <#planeNormal description#>
         *  @param planeSupport <#planeSupport description#>
         *  @param i            <#i description#>
         */
        void getPlane(btVector3& planeNormal,btVector3& planeSupport,int i ) const;
        /**
         *  <#Description#>
         *
         *  @param i <#i description#>
         *
         *  @return <#return value description#>
         */
        btVector3 getPlane(int i)const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        int getNumPlanes() const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        int getNumVertices() const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        int getNumEdges() const;
        /**
         *  <#Description#>
         *
         *  @param i   <#i description#>
         *  @param vtx <#vtx description#>
         */
        void getVertex(int i,btVector3& vtx) const;
        /**
         *  <#Description#>
         *
         *  @param plane <#plane description#>
         *  @param i     <#i description#>
         */
        void getPlaneEquation(btVector4& plane,int i) const;
        /**
         *  <#Description#>
         *
         *  @param i  <#i description#>
         *  @param pa <#pa description#>
         *  @param pb <#pb description#>
         */
        void getEdge(int i,btVector3& pa,btVector3& pb) const;
        /**
         *  <#Description#>
         *
         *  @param pt        <#pt description#>
         *  @param tolerance <#tolerance description#>
         *
         *  @return <#return value description#>
         */
        bool isInside(const btVector3& pt,btScalar tolerance) const;
        
        
    protected:
//        void getAabb(const btTransform& t,btVector3& aabbMin,btVector3& aabbMax) const;
        
        virtual const btCollisionShape* getCollisionShape() const;
        virtual btCollisionShape* getCollisionShape();
        virtual void setCollisionShape(const btCollisionShape &shape);
        
        virtual const btBoxShape* getShape() const;
        virtual btBoxShape* getShape();
    private:
        btBoxShape *m_btBoxShape;
    };
}

#endif /* defined(__JLIGameEngineTest__PhysicsShapeBox__) */
