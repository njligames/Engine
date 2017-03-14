//
//  PhysicsConstraintConeTwist.h
//  JLIGameEngineTest
//
//  Created by James Folk on 6/19/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsConstraintConeTwist__
#define __JLIGameEngineTest__PhysicsConstraintConeTwist__

#pragma mark Header

#include "AbstractFactoryObject.h"
#include "AbstractBuilder.h"
#include "lua.hpp"
#include "Log.h"

#include "PhysicsConstraint.h"

class btConeTwistConstraint;

namespace njli
{
    class PhysicsConstraintConeTwistBuilder;
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) PhysicsConstraintConeTwist:
    public PhysicsConstraint
    {
        friend class WorldFactory;
    protected:
        PhysicsConstraintConeTwist();
        PhysicsConstraintConeTwist(const AbstractBuilder&);
        PhysicsConstraintConeTwist(const PhysicsConstraintConeTwist &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~PhysicsConstraintConeTwist();
        PhysicsConstraintConeTwist &operator=(const PhysicsConstraintConeTwist &);
    public:
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual	s32	calculateSerializeBufferSize() const;
        
        /**
         *  @author James Folk, 16-02-11 15:02:15
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
        static PhysicsConstraintConeTwist **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(PhysicsConstraintConeTwist **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintConeTwist *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintConeTwist *create(const PhysicsConstraintConeTwistBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintConeTwist *clone(const PhysicsConstraintConeTwist &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintConeTwist *copy(const PhysicsConstraintConeTwist &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(PhysicsConstraintConeTwist *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(PhysicsConstraintConeTwist &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
        
    public:
        //TODO: fill in specific methods for PhysicsConstraintConeTwist
        /**
         *  <#Description#>
         *
         *  @param nodeA    <#nodeA description#>
         *  @param rbAFrame <#rbAFrame description#>
         */
        void setNodes(Node *nodeA, const btTransform& rbAFrame = btTransform::getIdentity());
        /**
         *  <#Description#>
         *
         *  @param nodeA    <#nodeA description#>
         *  @param nodeB    <#nodeB description#>
         *  @param rbAFrame <#rbAFrame description#>
         *  @param rbBFrame <#rbBFrame description#>
         */
        void setNodes(Node *nodeA, Node *nodeB, const btTransform& rbAFrame = btTransform::getIdentity(), const btTransform& rbBFrame = btTransform::getIdentity());
        
        /**
         *  <#Description#>
         *
         *  @param angularOnly <#angularOnly description#>
         */
        void setAngularOnly(bool angularOnly);
        /**
         *  <#Description#>
         *
         *  @param limitIndex <#limitIndex description#>
         *  @param limitValue <#limitValue description#>
         */
        void setLimit(int limitIndex,f32 limitValue);
        /**
         *  <#Description#>
         *
         *  @param _swingSpan1 <#_swingSpan1 description#>
         *  @param _swingSpan2 <#_swingSpan2 description#>
         *  @param _twistSpan  <#_twistSpan description#>
         *  @param _softness          <#.f description#>
         *  @param _biasFactor         <#.3f description#>
         *  @param _relaxationFactor         <#.0f description#>
         */
        void setLimit(f32 _swingSpan1,f32 _swingSpan2,f32 _twistSpan, f32 _softness = 1.f, f32 _biasFactor = 0.3f, f32 _relaxationFactor = 1.0f);
        const btTransform& getAFrame();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        const btTransform& getBFrame();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        int getSolveTwistLimit();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        int getSolveSwingLimit();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getTwistLimitSign();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getSwingSpan1();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getSwingSpan2();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getTwistSpan();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getTwistAngle();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        bool isPastSwingLimit();
        /**
         *  <#Description#>
         *
         *  @param damping <#damping description#>
         */
        void setDamping(f32 damping);
        /**
         *  <#Description#>
         *
         *  @param b <#b description#>
         */
        void enableMotor(bool b);
        /**
         *  <#Description#>
         *
         *  @param maxMotorImpulse <#maxMotorImpulse description#>
         */
        void setMaxMotorImpulse(f32 maxMotorImpulse);
        /**
         *  <#Description#>
         *
         *  @param maxMotorImpulse <#maxMotorImpulse description#>
         */
        void setMaxMotorImpulseNormalized(f32 maxMotorImpulse);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getFixThresh();
        /**
         *  <#Description#>
         *
         *  @param fixThresh <#fixThresh description#>
         */
        void setFixThresh(f32 fixThresh);
        /**
         *  <#Description#>
         *
         *  @param q <#q description#>
         */
        void setMotorTarget(const btQuaternion &q);
        /**
         *  <#Description#>
         *
         *  @param q <#q description#>
         */
        void setMotorTargetInConstraintSpace(const btQuaternion &q);
        /**
         *  <#Description#>
         *
         *  @param fAngleInRadians <#fAngleInRadians description#>
         *  @param fLength         <#fLength description#>
         *
         *  @return <#return value description#>
         */
        btVector3 getPointForAngle(f32 fAngleInRadians, f32 fLength) const;
        /**
         *  <#Description#>
         *
         *  @param frameA <#frameA description#>
         *  @param frameB <#frameB description#>
         */
        void setFrames(const btTransform& frameA, const btTransform& frameB);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        const btTransform& getFrameOffsetA() const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        const btTransform& getFrameOffsetB() const;
    protected:
        virtual btTypedConstraint *getConstraint();
        virtual const btTypedConstraint *getConstraint()const;
        
        virtual void removeConstraint();
    private:
        btConeTwistConstraint *m_btConeTwistConstraint;
    };
}

#endif /* defined(__JLIGameEngineTest__PhysicsConstraintConeTwist__) */
