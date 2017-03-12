//
//  PhysicsBodyRigid.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsBodyRigid__
#define __JLIGameEngineTest__PhysicsBodyRigid__

#include "PhysicsBody.h"
#include "AbstractBuilder.h"
#include "lua.hpp"

class btRigidBody;
struct btDefaultMotionState;

namespace njli
{
    class PhysicsBodyRigidBuilder;
    
    /**
     *  <#Description#>
     */
    ATTRIBUTE_ALIGNED16(class) PhysicsBodyRigid:
    public PhysicsBody
    {
        friend class WorldFactory;
        friend class PhysicsWorld;
    protected:
        PhysicsBodyRigid();
        PhysicsBodyRigid(const AbstractBuilder&);
        PhysicsBodyRigid(const PhysicsBodyRigid &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~PhysicsBodyRigid();
        PhysicsBodyRigid &operator=(const PhysicsBodyRigid &);
    public:
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual	s32	calculateSerializeBufferSize() const;
        
        /**
         *  @author James Folk, 16-02-11 15:02:12
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
        static PhysicsBodyRigid **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(PhysicsBodyRigid **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsBodyRigid *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsBodyRigid *create(const PhysicsBodyRigidBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsBodyRigid *clone(const PhysicsBodyRigid &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsBodyRigid *copy(const PhysicsBodyRigid &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(PhysicsBodyRigid *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(PhysicsBodyRigid &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
    public:
        //TODO: fill in specific methods for PhysicsBodyRigid
        /**
         *  <#Description#>
         *
         *  @param transform <#transform description#>
         */
        virtual void setWorldTransform(const btTransform &transform);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual btTransform getWorldTransform()const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
//        virtual const btTransform& getWorldTransform() const;
        
        /**
         *  <#Description#>
         *
         *  @param factor <#factor description#>
         */
        virtual void setLinearFactor(const btVector3 &factor);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual const btVector3 &getLinearFactor()const;
        
        /**
         *  <#Description#>
         *
         *  @param factor <#factor description#>
         */
        virtual void setAngularFactor(const btVector3 &factor);
        /**
         *  <#Description#>
         *
         *  @param factor <#factor description#>
         */
        virtual void setAngularFactor(f32 factor);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual const btVector3 &getAngularFactor()const;
        
        /**
         *  <#Description#>
         *
         *  @param mass <#mass description#>
         */
        virtual void setMass(f32 mass);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual f32 getMass()const;
        
        /**
         *  <#Description#>
         *
         *  @param charge <#charge description#>
         */
        virtual void setCharge(f32 charge);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual f32 getCharge()const;
        
        /**
         *  <#Description#>
         *
         *  @param damping <#damping description#>
         */
        virtual void setDamping(f32 damping);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual f32 getDamping()const;
        
        /**
         *  <#Description#>
         *
         *  @param damping <#damping description#>
         */
        virtual void setAngularDamping(f32 damping);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual f32 getAngularDamping()const;
        
        /**
         *  <#Description#>
         *
         *  @param direction <#direction description#>
         *  @param impulse   <#impulse description#>
         */
        virtual void applyForce(const btVector3 &direction, bool impulse = false);
        /**
         *  <#Description#>
         *
         *  @param direction <#direction description#>
         *  @param position  <#position description#>
         *  @param impulse   <#impulse description#>
         */
        virtual void applyForce(const btVector3 &direction, const btVector3 &position, bool impulse = false);
        
        /**
         *  <#Description#>
         *
         *  @param direction <#direction description#>
         *  @param impulse   <#impulse description#>
         */
        virtual void applyAngularForce(const btVector3 &direction, bool impulse = false);
        
        /**
         *  <#Description#>
         */
        virtual void clearAllForces();
        
        /**
         *  <#Description#>
         *
         *  @param velocity <#velocity description#>
         */
        virtual void setVelocity(const btVector3 &velocity);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual const btVector3 &getVelocity()const;
        
        /**
         *  <#Description#>
         *
         *  @param velocity <#velocity description#>
         */
        virtual void setAngularVelocity(const btVector3 &velocity);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual const btVector3 &getAngularVelocity()const;
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual bool isInWorld()const;
    protected:
        virtual const btCollisionObject* getCollisionObject() const;
        virtual btCollisionObject* getCollisionObject();
        virtual void setCollisionObject(const btCollisionObject &obj, PhysicsShape *shape);
        
        virtual const btRigidBody* getBody() const;
        virtual btRigidBody* getBody();
        
        virtual void applyFinalForce();
        virtual void applyFinalAngularForce();
        
        virtual bool setTransform(const btTransform &transform = btTransform::getIdentity());
        virtual bool removePhysicsBody();
    private:
        f32 m_Mass;
        btDefaultMotionState *m_btDefaultMotionState;
        btRigidBody *m_btRigidBody;
        
        
        
        ATTRIBUTE_ALIGNED16(class) ForceAndPosition
        {
        public:
            ForceAndPosition();
            ForceAndPosition(const ForceAndPosition &copy);
            BT_DECLARE_ALIGNED_ALLOCATOR();
            ForceAndPosition &operator=(const ForceAndPosition &rhs);
            
            void set(const btVector3 &force, const btVector3 &position);
            const btVector3 &getForce()const;
            const btVector3 &getPosition()const;
            void clear();
        private:
            btVector3 *m_Force;
            btVector3 *m_Position;
        };
    
        btAlignedObjectArray<ForceAndPosition*> m_LinearForceAndPositionArray;
        s32 m_LinearForceAndPositionArrayIndex;
        btAlignedObjectArray<ForceAndPosition*> m_AngularForceAndPositionArray;
        s32 m_AngularForceAndPositionArrayIndex;
        btTransform *m_btTransform;
        f32 m_Charge;
    };
}

#endif /* defined(__JLIGameEngineTest__PhysicsBodyRigid__) */
