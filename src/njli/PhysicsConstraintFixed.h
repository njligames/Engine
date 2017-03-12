//
//  PhysicsConstraintFixed.h
//  JLIGameEngineTest
//
//  Created by James Folk on 6/19/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsConstraintFixed__
#define __JLIGameEngineTest__PhysicsConstraintFixed__

#pragma mark Header

#include "AbstractFactoryObject.h"
#include "AbstractBuilder.h"
#include "lua.hpp"
#include "Log.h"

#include "PhysicsConstraint.h"

class btFixedConstraint;

namespace njli
{
    class PhysicsConstraintFixedBuilder;
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) PhysicsConstraintFixed:
    public PhysicsConstraint
    {
        friend class WorldFactory;
    protected:
        PhysicsConstraintFixed();
        PhysicsConstraintFixed(const AbstractBuilder&);
        PhysicsConstraintFixed(const PhysicsConstraintFixed &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~PhysicsConstraintFixed();
        PhysicsConstraintFixed &operator=(const PhysicsConstraintFixed &);
    public:
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual	s32	calculateSerializeBufferSize() const;
        
        /**
         *  @author James Folk, 16-02-11 15:02:27
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
        static PhysicsConstraintFixed **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(PhysicsConstraintFixed **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintFixed *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintFixed *create(const PhysicsConstraintFixedBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintFixed *clone(const PhysicsConstraintFixed &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintFixed *copy(const PhysicsConstraintFixed &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(PhysicsConstraintFixed *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(PhysicsConstraintFixed &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
        
    public:
        //TODO: fill in specific methods for PhysicsConstraintFixed
        /**
         *  <#Description#>
         *
         *  @param nodeA    <#nodeA description#>
         *  @param nodeB    <#nodeB description#>
         *  @param frameInA <#frameInA description#>
         *  @param frameInB <#frameInB description#>
         */
        void setNodes(Node *nodeA, Node *nodeB, const btTransform& frameInA = btTransform::getIdentity(),const btTransform& frameInB = btTransform::getIdentity());
    protected:
        virtual btTypedConstraint *getConstraint();
        virtual const btTypedConstraint *getConstraint()const;
        
        virtual void removeConstraint();
    private:
        btFixedConstraint *m_btFixedConstraint;
    };
}

#endif /* defined(__JLIGameEngineTest__PhysicsConstraintFixed__) */
