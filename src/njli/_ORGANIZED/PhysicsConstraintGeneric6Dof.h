//
//  PhysicsConstraintGeneric6Dof.h
//  JLIGameEngineTest
//
//  Created by James Folk on 6/19/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsConstraintGeneric6Dof__
#define __JLIGameEngineTest__PhysicsConstraintGeneric6Dof__

#pragma mark Header

#include "AbstractFactoryObject.h"
#include "AbstractBuilder.h"
#include "lua.hpp"
#include "Log.h"

#include "PhysicsConstraint.h"

class btGeneric6DofConstraint;
class btRotationalLimitMotor;
class btTranslationalLimitMotor;

namespace njli
{
    class PhysicsConstraintGeneric6DofBuilder;
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) PhysicsConstraintGeneric6Dof:
    public PhysicsConstraint
    {
        friend class WorldFactory;
    protected:
        PhysicsConstraintGeneric6Dof();
        PhysicsConstraintGeneric6Dof(const AbstractBuilder&);
        PhysicsConstraintGeneric6Dof(const PhysicsConstraintGeneric6Dof &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~PhysicsConstraintGeneric6Dof();
        PhysicsConstraintGeneric6Dof &operator=(const PhysicsConstraintGeneric6Dof &);
    public:
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual	s32	calculateSerializeBufferSize() const;
        
        /**
         *  @author James Folk, 16-02-11 15:02:41
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
        static PhysicsConstraintGeneric6Dof **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(PhysicsConstraintGeneric6Dof **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintGeneric6Dof *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintGeneric6Dof *create(const PhysicsConstraintGeneric6DofBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintGeneric6Dof *clone(const PhysicsConstraintGeneric6Dof &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintGeneric6Dof *copy(const PhysicsConstraintGeneric6Dof &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(PhysicsConstraintGeneric6Dof *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(PhysicsConstraintGeneric6Dof &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
        
    public:
        //TODO: fill in specific methods for PhysicsConstraintGeneric6Dof
        
        /**
         *  <#Description#>
         *
         *  @param nodeA                    <#nodeA description#>
         *  @param nodeB                    <#nodeB description#>
         *  @param frameInA                 <#frameInA description#>
         *  @param frameInB                 <#frameInB description#>
         *  @param useLinearReferenceFrameA <#useLinearReferenceFrameA description#>
         */
        void setNodes(Node *nodeA, Node *nodeB, const btTransform& frameInA = btTransform::getIdentity(), const btTransform& frameInB = btTransform::getIdentity() ,bool useLinearReferenceFrameA = true);
        /**
         *  <#Description#>
         *
         *  @param nodeB                    <#nodeB description#>
         *  @param frameInB                 <#frameInB description#>
         *  @param useLinearReferenceFrameB <#useLinearReferenceFrameB description#>
         */
        void setNodes(Node *nodeB, const btTransform& frameInB = btTransform::getIdentity(), bool useLinearReferenceFrameB = true);
        
        /**
         *  <#Description#>
         */
        void calculateTransforms();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        const btTransform & getCalculatedTransformA() const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        const btTransform & getCalculatedTransformB() const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        const btTransform & getFrameOffsetA() const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        const btTransform & getFrameOffsetB() const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        btTransform & getFrameOffsetA();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        btTransform & getFrameOffsetB();
        /**
         *  <#Description#>
         *
         *  @param axis_index <#axis_index description#>
         *
         *  @return <#return value description#>
         */
        btVector3 getAxis(int axis_index) const;
        /**
         *  <#Description#>
         *
         *  @param axis_index <#axis_index description#>
         *
         *  @return <#return value description#>
         */
        f32 getAngle(int axis_index) const;
        /**
         *  <#Description#>
         *
         *  @param axis_index <#axis_index description#>
         *
         *  @return <#return value description#>
         */
        f32 getRelativePivotPosition(int axis_index) const;
        /**
         *  <#Description#>
         *
         *  @param frameA <#frameA description#>
         *  @param frameB <#frameB description#>
         */
        void setFrames(const btTransform & frameA, const btTransform & frameB);
        /**
         *  <#Description#>
         *
         *  @param axis_index <#axis_index description#>
         *
         *  @return <#return value description#>
         */
        bool testAngularLimitMotor(int axis_index);
        /**
         *  <#Description#>
         *
         *  @param linearLower <#linearLower description#>
         */
        void setLinearLowerLimit(const btVector3& linearLower);
        /**
         *  <#Description#>
         *
         *  @param linearLower <#linearLower description#>
         */
        void getLinearLowerLimit(btVector3& linearLower);
        /**
         *  <#Description#>
         *
         *  @param linearUpper <#linearUpper description#>
         */
        void setLinearUpperLimit(const btVector3& linearUpper);
        /**
         *  <#Description#>
         *
         *  @param linearUpper <#linearUpper description#>
         */
        void getLinearUpperLimit(btVector3& linearUpper);
        /**
         *  <#Description#>
         *
         *  @param angularLower <#angularLower description#>
         */
        void setAngularLowerLimit(const btVector3& angularLower);
        /**
         *  <#Description#>
         *
         *  @param angularLower <#angularLower description#>
         */
        void getAngularLowerLimit(btVector3& angularLower);
        /**
         *  <#Description#>
         *
         *  @param angularUpper <#angularUpper description#>
         */
        void setAngularUpperLimit(const btVector3& angularUpper);
        /**
         *  <#Description#>
         *
         *  @param angularUpper <#angularUpper description#>
         */
        void getAngularUpperLimit(btVector3& angularUpper);
        /**
         *  <#Description#>
         *
         *  @param index <#index description#>
         *
         *  @return <#return value description#>
         */
        btRotationalLimitMotor * getRotationalLimitMotor(int index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        btTranslationalLimitMotor * getTranslationalLimitMotor();
        /**
         *  <#Description#>
         *
         *  @param axis <#axis description#>
         *  @param lo   <#lo description#>
         *  @param hi   <#hi description#>
         */
        void setLimit(int axis, f32 lo, f32 hi);
        /**
         *  <#Description#>
         *
         *  @param limitIndex <#limitIndex description#>
         *
         *  @return <#return value description#>
         */
        bool isLimited(int limitIndex);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        bool getUseFrameOffset();
        /**
         *  <#Description#>
         *
         *  @param frameOffsetOnOff <#frameOffsetOnOff description#>
         */
        void setUseFrameOffset(bool frameOffsetOnOff);
        /**
         *  <#Description#>
         *
         *  @param axis1 <#axis1 description#>
         *  @param axis2 <#axis2 description#>
         */
        void setAxis( const btVector3& axis1, const btVector3& axis2);
    protected:
        virtual btTypedConstraint *getConstraint();
        virtual const btTypedConstraint *getConstraint()const;
        
        virtual void removeConstraint();
    private:
        btGeneric6DofConstraint *m_btGeneric6DofConstraint;
    };
}

#endif /* defined(__JLIGameEngineTest__PhysicsConstraintGeneric6Dof__) */
