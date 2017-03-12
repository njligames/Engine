//
//  PhysicsConstraintHinge.h
//  JLIGameEngineTest
//
//  Created by James Folk on 6/18/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsConstraintHinge__
#define __JLIGameEngineTest__PhysicsConstraintHinge__

#pragma mark Header

#include "AbstractFactoryObject.h"
#include "AbstractBuilder.h"
#include "lua.hpp"
#include "Log.h"

#include "PhysicsConstraint.h"

class btHingeConstraint;

namespace njli
{
    class PhysicsConstraintHingeBuilder;
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) PhysicsConstraintHinge:
    public PhysicsConstraint
    {
        friend class WorldFactory;
    protected:
        PhysicsConstraintHinge();
        PhysicsConstraintHinge(const AbstractBuilder&);
        PhysicsConstraintHinge(const PhysicsConstraintHinge &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~PhysicsConstraintHinge();
        PhysicsConstraintHinge &operator=(const PhysicsConstraintHinge &);
    public:
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual	s32	calculateSerializeBufferSize() const;
        
        /**
         *  @author James Folk, 16-02-11 15:02:13
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
        static PhysicsConstraintHinge **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(PhysicsConstraintHinge **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintHinge *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintHinge *create(const PhysicsConstraintHingeBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintHinge *clone(const PhysicsConstraintHinge &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintHinge *copy(const PhysicsConstraintHinge &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(PhysicsConstraintHinge *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(PhysicsConstraintHinge &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
        
    public:
        //TODO: fill in specific methods for PhysicsConstraintHinge
        /**
         *  <#Description#>
         *
         *  @param nodeA              <#nodeA description#>
         *  @param nodeB              <#nodeB description#>
         *  @param pivotInA           <#pivotInA description#>
         *  @param pivotInB           <#pivotInB description#>
         *  @param axisInA            <#axisInA description#>
         *  @param axisInB            <#axisInB description#>
         *  @param useReferenceFrameA <#useReferenceFrameA description#>
         */
        void setNodes(Node *nodeA, Node *nodeB,
                      const btVector3& pivotInA,
                      const btVector3& pivotInB,
                      const btVector3& axisInA,
                      const btVector3& axisInB,
                      bool useReferenceFrameA = false);
        /**
         *  <#Description#>
         *
         *  @param nodeA              <#nodeA description#>
         *  @param pivotInA           <#pivotInA description#>
         *  @param axisInA            <#axisInA description#>
         *  @param useReferenceFrameA <#useReferenceFrameA description#>
         */
        void setNodes(Node *nodeA,
                      const btVector3& pivotInA,
                      const btVector3& axisInA,
                      bool useReferenceFrameA = false);
        /**
         *  <#Description#>
         *
         *  @param nodeA              <#nodeA description#>
         *  @param nodeB              <#nodeB description#>
         *  @param rbAFrame           <#rbAFrame description#>
         *  @param rbBFrame           <#rbBFrame description#>
         *  @param useReferenceFrameA <#useReferenceFrameA description#>
         */
        void setNodes(Node *nodeA, Node *nodeB,
                      const btTransform& rbAFrame = btTransform::getIdentity(),
                      const btTransform& rbBFrame = btTransform::getIdentity(),
                      bool useReferenceFrameA = false);
        /**
         *  <#Description#>
         *
         *  @param nodeA              <#nodeA description#>
         *  @param rbAFrame           <#rbAFrame description#>
         *  @param useReferenceFrameA <#useReferenceFrameA description#>
         */
        void setNodes(Node *nodeA,
                      const btTransform& rbAFrame = btTransform::getIdentity(),
                      bool useReferenceFrameA = false);
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        btTransform& getFrameOffsetA();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        btTransform& getFrameOffsetB();
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
         *  @param angularOnly <#angularOnly description#>
         */
        void setAngularOnly(bool angularOnly);
        
        /**
         *  <#Description#>
         *
         *  @param enableMotor     <#enableMotor description#>
         *  @param targetVelocity  <#targetVelocity description#>
         *  @param maxMotorImpulse <#maxMotorImpulse description#>
         */
        void enableAngularMotor(bool enableMotor, f32 targetVelocity, f32 maxMotorImpulse);
        
        // extra motor API, including ability to set a target rotation (as opposed to angular velocity)
        // note: setMotorTarget sets angular velocity under the hood, so you must call it every tick to
        //       maintain a given angular target.
        /**
         *  <#Description#>
         *
         *  @param enableMotor <#enableMotor description#>
         */
        void enableMotor(bool enableMotor);
        /**
         *  <#Description#>
         *
         *  @param maxMotorImpulse <#maxMotorImpulse description#>
         */
        void setMaxMotorImpulse(f32 maxMotorImpulse);
        /**
         *  <#Description#>
         *
         *  @param qAinB <#qAinB description#>
         *  @param dt    <#dt description#>
         */
        void setMotorTarget(const btQuaternion& qAinB, f32 dt); // qAinB is rotation of body A wrt body B.
        /**
         *  <#Description#>
         *
         *  @param targetAngle <#targetAngle description#>
         *  @param dt          <#dt description#>
         */
        void setMotorTarget(f32 targetAngle, f32 dt);
        
        /**
         *  <#Description#>
         *
         *  @param low  <#low description#>
         *  @param high <#high description#>
         *  @param _softness  <#.9f description#>
         *  @param _biasFactor  <#.3f description#>
         *  @param _relaxationFactor  <#.0f description#>
         */
        void setLimit(f32 low, f32 high, f32 _softness = 0.9f, f32 _biasFactor = 0.3f, f32 _relaxationFactor = 1.0f);
        
        /**
         *  <#Description#>
         *
         *  @param axisInA <#axisInA description#>
         */
        void setAxis(btVector3& axisInA);
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32	getLowerLimit() const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32	getUpperLimit() const;
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getHingeAngle();
        /**
         *  <#Description#>
         *
         *  @param transA <#transA description#>
         *  @param transB <#transB description#>
         *
         *  @return <#return value description#>
         */
        f32 getHingeAngle(const btTransform& transA,const btTransform& transB);
        
        /**
         *  <#Description#>
         *
         *  @param transA <#transA description#>
         *  @param transB <#transB description#>
         */
        void testLimit(const btTransform& transA,const btTransform& transB);
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        const btTransform& getAFrame() const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        const btTransform& getBFrame() const;
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        btTransform& getAFrame();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        btTransform& getBFrame();
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        int getSolveLimit();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getLimitSign();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        bool getAngularOnly();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        bool getEnableAngularMotor();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getMotorTargetVelocity();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getMaxMotorImpulse();
    protected:
        virtual btTypedConstraint *getConstraint();
        virtual const btTypedConstraint *getConstraint()const;
        
        virtual void removeConstraint();
    private:
        btHingeConstraint *m_btHingeConstraint;
    };
}

#endif /* defined(__JLIGameEngineTest__PhysicsConstraintHinge__) */
