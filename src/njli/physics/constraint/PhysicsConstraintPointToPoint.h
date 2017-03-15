//
//  PhysicsConstraintPointToPoint.h
//  JLIGameEngineTest
//
//  Created by James Folk on 6/15/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsConstraintPointToPoint__
#define __JLIGameEngineTest__PhysicsConstraintPointToPoint__

#pragma mark Header

#include "AbstractFactoryObject.h"
#include "AbstractBuilder.h"
#include "lua.hpp"
#include "Log.h"
#include "PhysicsConstraint.h"

class btPoint2PointConstraint;

namespace njli
{
    class PhysicsConstraintPointToPointBuilder;
    class Node;
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) PhysicsConstraintPointToPoint:
    public PhysicsConstraint
    {
        friend class WorldFactory;
    protected:
        PhysicsConstraintPointToPoint();
        PhysicsConstraintPointToPoint(const AbstractBuilder&);
        PhysicsConstraintPointToPoint(const PhysicsConstraintPointToPoint &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~PhysicsConstraintPointToPoint();
        PhysicsConstraintPointToPoint &operator=(const PhysicsConstraintPointToPoint &);
    public:
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual	s32	calculateSerializeBufferSize() const;
        
        /**
         *  @author James Folk, 16-02-11 15:02:26
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
        static PhysicsConstraintPointToPoint **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(PhysicsConstraintPointToPoint **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintPointToPoint *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintPointToPoint *create(const PhysicsConstraintPointToPointBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintPointToPoint *clone(const PhysicsConstraintPointToPoint &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintPointToPoint *copy(const PhysicsConstraintPointToPoint &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(PhysicsConstraintPointToPoint *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(PhysicsConstraintPointToPoint &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
        
    public:
        /**
         *  <#Description#>
         *
         *  @param nodeA <#nodeA description#>
         *  @param nodeB <#nodeB description#>
         */
        void setNodes(Node *nodeA, Node *nodeB, const btVector3& pivotInA = btVector3(0,0,0),const btVector3& pivotInB = btVector3(0,0,0));
        /**
         *  <#Description#>
         *
         *  @param nodeA <#nodeA description#>
         */
        void setNodes(Node *nodeA, const btVector3& pivotInA = btVector3(0,0,0));
        
        
        
        
        
        //TODO: fill in specific methods for PhysicsConstraintPointToPoint
        /**
         *  <#Description#>
         *
         *  @param pivot <#pivot description#>
         */
        void setPivotInA(const btVector3 &pivot);
        /**
         *  <#Description#>
         *
         *  @param pivot <#pivot description#>
         */
        void setPivotInB(const btVector3 &pivot);
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        const btVector3 &getPivotInA()const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        const btVector3 &getPivotInB()const;
    protected:
        virtual btTypedConstraint *getConstraint();
        virtual const btTypedConstraint *getConstraint()const;
        
        virtual void removeConstraint();
    private:
        btPoint2PointConstraint *m_btPoint2PointConstraint;
    };
}

#endif /* defined(__JLIGameEngineTest__PhysicsConstraintPointToPoint__) */
