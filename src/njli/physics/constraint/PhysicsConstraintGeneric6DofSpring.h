//
//  PhysicsConstraintGeneric6DofSpring.h
//  JLIGameEngineTest
//
//  Created by James Folk on 6/19/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsConstraintGeneric6DofSpring__
#define __JLIGameEngineTest__PhysicsConstraintGeneric6DofSpring__

#pragma mark Header

#include "AbstractFactoryObject.h"
#include "AbstractBuilder.h"
#include "lua.hpp"
#include "Log.h"

#include "PhysicsConstraintGeneric6Dof.h"

class btGeneric6DofSpringConstraint;
class btRotationalLimitMotor;
class btTranslationalLimitMotor;

namespace njli
{
    class PhysicsConstraintGeneric6DofSpringBuilder;
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) PhysicsConstraintGeneric6DofSpring:
    public PhysicsConstraintGeneric6Dof
    {
        friend class WorldFactory;
    protected:
        PhysicsConstraintGeneric6DofSpring();
        PhysicsConstraintGeneric6DofSpring(const AbstractBuilder&);
        PhysicsConstraintGeneric6DofSpring(const PhysicsConstraintGeneric6DofSpring &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~PhysicsConstraintGeneric6DofSpring();
        PhysicsConstraintGeneric6DofSpring &operator=(const PhysicsConstraintGeneric6DofSpring &);
    public:
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual	s32	calculateSerializeBufferSize() const;
        
        /**
         *  @author James Folk, 16-02-11 15:02:56
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
        static PhysicsConstraintGeneric6DofSpring **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(PhysicsConstraintGeneric6DofSpring **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintGeneric6DofSpring *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintGeneric6DofSpring *create(const PhysicsConstraintGeneric6DofSpringBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintGeneric6DofSpring *clone(const PhysicsConstraintGeneric6DofSpring &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintGeneric6DofSpring *copy(const PhysicsConstraintGeneric6DofSpring &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(PhysicsConstraintGeneric6DofSpring *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(PhysicsConstraintGeneric6DofSpring &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
        
    public:
        //TODO: fill in specific methods for PhysicsConstraintGeneric6DofSpring
        /**
         *  <#Description#>
         *
         *  @param nodeA                    <#nodeA description#>
         *  @param nodeB                    <#nodeB description#>
         *  @param frameInA                 <#frameInA description#>
         *  @param frameInB                 <#frameInB description#>
         *  @param useLinearReferenceFrameA <#useLinearReferenceFrameA description#>
         */
        void setNodes(Node *nodeA, Node *nodeB, const btTransform& frameInA = btTransform::getIdentity(), const btTransform& frameInB = btTransform::getIdentity(), bool useLinearReferenceFrameA = true);
        void setNodes(Node *nodeB, const btTransform& frameInB = btTransform::getIdentity(), bool useLinearReferenceFrameB = true);
        /**
         *  <#Description#>
         *
         *  @param index <#index description#>
         *  @param onOff <#onOff description#>
         */
        void enableSpring(int index, bool onOff);
        /**
         *  <#Description#>
         *
         *  @param index     <#index description#>
         *  @param stiffness <#stiffness description#>
         */
        void setStiffness(int index, f32 stiffness);
        /**
         *  <#Description#>
         *
         *  @param index   <#index description#>
         *  @param damping <#damping description#>
         */
        void setDamping(int index, f32 damping);
        /**
         *  <#Description#>
         */
        void setEquilibriumPoint(); // set the current constraint position/orientation as an equilibrium point for all DOF
        /**
         *  <#Description#>
         *
         *  @param index <#index description#>
         */
        void setEquilibriumPoint(int index);  // set the current constraint position/orientation as an equilibrium point for given DOF
        /**
         *  <#Description#>
         *
         *  @param index <#index description#>
         *  @param val   <#val description#>
         */
        void setEquilibriumPoint(int index, f32 val);
        
        /**
         *  <#Description#>
         *
         *  @param axis1 <#axis1 description#>
         *  @param axis2 <#axis2 description#>
         */
        virtual void setAxis( const btVector3& axis1, const btVector3& axis2);
    protected:
        virtual btTypedConstraint *getConstraint();
        virtual const btTypedConstraint *getConstraint()const;
        
        virtual void removeConstraint();
    private:
        btGeneric6DofSpringConstraint *m_btGeneric6DofSpringConstraint;
    };
}

#endif /* defined(__JLIGameEngineTest__PhysicsConstraintGeneric6DofSpring__) */
