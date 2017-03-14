//
//  PhysicsConstraintSlider.h
//  JLIGameEngineTest
//
//  Created by James Folk on 6/19/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsConstraintSlider__
#define __JLIGameEngineTest__PhysicsConstraintSlider__

#pragma mark Header

#include "AbstractFactoryObject.h"
#include "AbstractBuilder.h"
#include "lua.hpp"
#include "Log.h"

#include "PhysicsConstraint.h"

class btSliderConstraint;


namespace njli
{
    class PhysicsConstraintSliderBuilder;
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) PhysicsConstraintSlider:
    public PhysicsConstraint
    {
        friend class WorldFactory;
    protected:
        PhysicsConstraintSlider();
        PhysicsConstraintSlider(const AbstractBuilder&);
        PhysicsConstraintSlider(const PhysicsConstraintSlider &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~PhysicsConstraintSlider();
        PhysicsConstraintSlider &operator=(const PhysicsConstraintSlider &);
    public:
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual	s32	calculateSerializeBufferSize() const;
        
        /**
         *  @author James Folk, 16-02-11 15:02:40
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
        static PhysicsConstraintSlider **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(PhysicsConstraintSlider **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintSlider *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintSlider *create(const PhysicsConstraintSliderBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintSlider *clone(const PhysicsConstraintSlider &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsConstraintSlider *copy(const PhysicsConstraintSlider &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(PhysicsConstraintSlider *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(PhysicsConstraintSlider &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
        
    public:
        //TODO: fill in specific methods for PhysicsConstraintSlider
        
        // constructors
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
        /**
         *  <#Description#>
         *
         *  @param nodeB                    <#nodeB description#>
         *  @param frameInB                 <#frameInB description#>
         *  @param useLinearReferenceFrameA <#useLinearReferenceFrameA description#>
         */
        void setNodes(Node *nodeB, const btTransform& frameInB = btTransform::getIdentity(), bool useLinearReferenceFrameA = true);
        
        
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
         *  @return <#return value description#>
         */
        f32 getLowerLinLimit();
        /**
         *  <#Description#>
         *
         *  @param lowerLimit <#lowerLimit description#>
         */
        void setLowerLinLimit(f32 lowerLimit);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getUpperLinLimit();
        /**
         *  <#Description#>
         *
         *  @param upperLimit <#upperLimit description#>
         */
        void setUpperLinLimit(f32 upperLimit);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getLowerAngLimit();
        /**
         *  <#Description#>
         *
         *  @param lowerLimit <#lowerLimit description#>
         */
        void setLowerAngLimit(f32 lowerLimit);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getUpperAngLimit();
        /**
         *  <#Description#>
         *
         *  @param upperLimit <#upperLimit description#>
         */
        void setUpperAngLimit(f32 upperLimit);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        bool getUseLinearReferenceFrameA();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getSoftnessDirLin();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getRestitutionDirLin();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getDampingDirLin();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getSoftnessDirAng();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getRestitutionDirAng();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getDampingDirAng();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getSoftnessLimLin();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getRestitutionLimLin();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getDampingLimLin();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getSoftnessLimAng();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getRestitutionLimAng();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getDampingLimAng();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getSoftnessOrthoLin();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getRestitutionOrthoLin();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getDampingOrthoLin();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getSoftnessOrthoAng();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getRestitutionOrthoAng();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getDampingOrthoAng();
        /**
         *  <#Description#>
         *
         *  @param softnessDirLin <#softnessDirLin description#>
         */
        void setSoftnessDirLin(f32 softnessDirLin);
        /**
         *  <#Description#>
         *
         *  @param restitutionDirLin <#restitutionDirLin description#>
         */
        void setRestitutionDirLin(f32 restitutionDirLin);
        /**
         *  <#Description#>
         *
         *  @param dampingDirLin <#dampingDirLin description#>
         */
        void setDampingDirLin(f32 dampingDirLin);
        /**
         *  <#Description#>
         *
         *  @param softnessDirAng <#softnessDirAng description#>
         */
        void setSoftnessDirAng(f32 softnessDirAng);
        /**
         *  <#Description#>
         *
         *  @param restitutionDirAng <#restitutionDirAng description#>
         */
        void setRestitutionDirAng(f32 restitutionDirAng);
        /**
         *  <#Description#>
         *
         *  @param dampingDirAng <#dampingDirAng description#>
         */
        void setDampingDirAng(f32 dampingDirAng);
        /**
         *  <#Description#>
         *
         *  @param softnessLimLin <#softnessLimLin description#>
         */
        void setSoftnessLimLin(f32 softnessLimLin);
        /**
         *  <#Description#>
         *
         *  @param restitutionLimLin <#restitutionLimLin description#>
         */
        void setRestitutionLimLin(f32 restitutionLimLin);
        /**
         *  <#Description#>
         *
         *  @param dampingLimLin <#dampingLimLin description#>
         */
        void setDampingLimLin(f32 dampingLimLin);
        /**
         *  <#Description#>
         *
         *  @param softnessLimAng <#softnessLimAng description#>
         */
        void setSoftnessLimAng(f32 softnessLimAng);
        /**
         *  <#Description#>
         *
         *  @param restitutionLimAng <#restitutionLimAng description#>
         */
        void setRestitutionLimAng(f32 restitutionLimAng);
        /**
         *  <#Description#>
         *
         *  @param dampingLimAng <#dampingLimAng description#>
         */
        void setDampingLimAng(f32 dampingLimAng);
        /**
         *  <#Description#>
         *
         *  @param softnessOrthoLin <#softnessOrthoLin description#>
         */
        void setSoftnessOrthoLin(f32 softnessOrthoLin);
        /**
         *  <#Description#>
         *
         *  @param restitutionOrthoLin <#restitutionOrthoLin description#>
         */
        void setRestitutionOrthoLin(f32 restitutionOrthoLin);
        /**
         *  <#Description#>
         *
         *  @param dampingOrthoLin <#dampingOrthoLin description#>
         */
        void setDampingOrthoLin(f32 dampingOrthoLin);
        /**
         *  <#Description#>
         *
         *  @param softnessOrthoAng <#softnessOrthoAng description#>
         */
        void setSoftnessOrthoAng(f32 softnessOrthoAng);
        /**
         *  <#Description#>
         *
         *  @param restitutionOrthoAng <#restitutionOrthoAng description#>
         */
        void setRestitutionOrthoAng(f32 restitutionOrthoAng);
        /**
         *  <#Description#>
         *
         *  @param dampingOrthoAng <#dampingOrthoAng description#>
         */
        void setDampingOrthoAng(f32 dampingOrthoAng);
        /**
         *  <#Description#>
         *
         *  @param onOff <#onOff description#>
         */
        void setPoweredLinMotor(bool onOff);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        bool getPoweredLinMotor();
        /**
         *  <#Description#>
         *
         *  @param targetLinMotorVelocity <#targetLinMotorVelocity description#>
         */
        void setTargetLinMotorVelocity(f32 targetLinMotorVelocity);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getTargetLinMotorVelocity();
        /**
         *  <#Description#>
         *
         *  @param maxLinMotorForce <#maxLinMotorForce description#>
         */
        void setMaxLinMotorForce(f32 maxLinMotorForce);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getMaxLinMotorForce();
        /**
         *  <#Description#>
         *
         *  @param onOff <#onOff description#>
         */
        void setPoweredAngMotor(bool onOff);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        bool getPoweredAngMotor();
        /**
         *  <#Description#>
         *
         *  @param targetAngMotorVelocity <#targetAngMotorVelocity description#>
         */
        void setTargetAngMotorVelocity(f32 targetAngMotorVelocity);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getTargetAngMotorVelocity();
        /**
         *  <#Description#>
         *
         *  @param maxAngMotorForce <#maxAngMotorForce description#>
         */
        void setMaxAngMotorForce(f32 maxAngMotorForce);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getMaxAngMotorForce();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getLinearPos() const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getAngularPos() const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        bool getSolveLinLimit();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getLinDepth();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        bool getSolveAngLimit();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        f32 getAngDepth();
        /**
         *  <#Description#>
         *
         *  @param frameA <#frameA description#>
         *  @param frameB <#frameB description#>
         */
        void setFrames(const btTransform& frameA, const btTransform& frameB);
    protected:
        virtual btTypedConstraint *getConstraint();
        virtual const btTypedConstraint *getConstraint()const;
        
        virtual void removeConstraint();
    private:
        btSliderConstraint *m_btSliderConstraint;
    };
}

#endif /* defined(__JLIGameEngineTest__PhysicsConstraintSlider__) */
