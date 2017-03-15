//
//  PhysicsShapeStaticPlane.h
//  JLIGameEngineTest
//
//  Created by James Folk on 6/22/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsShapeStaticPlane__
#define __JLIGameEngineTest__PhysicsShapeStaticPlane__

#pragma mark Header

#include "AbstractFactoryObject.h"
#include "AbstractBuilder.h"
#include "lua.hpp"
#include "Log.h"
#include "PhysicsShape.h"

class btStaticPlaneShape;

namespace njli
{
    class PhysicsShapeStaticPlaneBuilder;
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) PhysicsShapeStaticPlane:
    public PhysicsShape
    {
        friend class WorldFactory;
    protected:
        PhysicsShapeStaticPlane();
        PhysicsShapeStaticPlane(const AbstractBuilder&);
        PhysicsShapeStaticPlane(const PhysicsShapeStaticPlane &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~PhysicsShapeStaticPlane();
        PhysicsShapeStaticPlane &operator=(const PhysicsShapeStaticPlane &);
    public:
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual	s32	calculateSerializeBufferSize() const;
        
        /**
         *  @author James Folk, 16-02-11 15:02:48
         *
         *  @brief <#Description#>
         *
         *  @param dataBuffer   <#dataBuffer description#>
         *  @param btSerializer <#btSerializer description#>
         */
        virtual	void serialize(void*dataBuffer, btSerializer*) const;
        
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
        static PhysicsShapeStaticPlane **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(PhysicsShapeStaticPlane **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeStaticPlane *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeStaticPlane *create(const PhysicsShapeStaticPlaneBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeStaticPlane *clone(const PhysicsShapeStaticPlane &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsShapeStaticPlane *copy(const PhysicsShapeStaticPlane &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(PhysicsShapeStaticPlane *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(PhysicsShapeStaticPlane &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
        
    public:
        //TODO: fill in specific methods for PhysicsShapeStaticPlane
        
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
        
        void setPlaneNormal(const btVector3 &normal);
        /**
         *  <#Description#>
         *
         *  @param planeConstant <#planeConstant description#>
         */
        void setPlaneConstant(f32 planeConstant);
        
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
         *  @param scaling <#scaling description#>
         */
        void setLocalScaling(const btVector3& scaling);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        const btVector3& getPlaneNormal() const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        const btScalar&	getPlaneConstant() const;
    protected:
//        virtual void getAabb(const btTransform& t,btVector3& aabbMin,btVector3& aabbMax) const;
        virtual const btCollisionShape*	getCollisionShape() const;
        virtual btCollisionShape* getCollisionShape();
        virtual void setCollisionShape(const btCollisionShape &shape);
        
    private:
        btStaticPlaneShape *m_btStaticPlaneShape;
    };
}

#endif /* defined(__JLIGameEngineTest__PhysicsShapeStaticPlane__) */
