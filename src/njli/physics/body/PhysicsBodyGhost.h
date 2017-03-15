//
//  PhysicsBodyGhost.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsBodyGhost__
#define __JLIGameEngineTest__PhysicsBodyGhost__

#include "PhysicsBody.h"
#include "AbstractBuilder.h"
#include "lua.hpp"

class btPairCachingGhostObject;

namespace njli
{
    class PhysicsBodyGhostBuilder;
    class Node;
    
    ATTRIBUTE_ALIGNED16(class) PhysicsBodyGhost:
    public PhysicsBody
    {
        friend class WorldFactory;
    protected:
        PhysicsBodyGhost();
        PhysicsBodyGhost(const AbstractBuilder&);
        PhysicsBodyGhost(const PhysicsBodyGhost &);
        BT_DECLARE_ALIGNED_ALLOCATOR();
        virtual ~PhysicsBodyGhost();
        PhysicsBodyGhost &operator=(const PhysicsBodyGhost &);
    public:
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual	s32	calculateSerializeBufferSize() const;
        
        /**
         *  @author James Folk, 16-02-11 15:02:57
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
        static PhysicsBodyGhost **createArray(const u32 size);
        /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
        static void destroyArray(PhysicsBodyGhost **array, const u32 size = 0);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsBodyGhost *create();
        /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsBodyGhost *create(const PhysicsBodyGhostBuilder &builder);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsBodyGhost *clone(const PhysicsBodyGhost &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
        static PhysicsBodyGhost *copy(const PhysicsBodyGhost &object);
        /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
        static void destroy(PhysicsBodyGhost *object);
        /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
        static void load(PhysicsBodyGhost &object, lua_State *L, int stack_index);
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        static u32 type();
    public:
        //TODO: fill in specific methods for PhysicsBodyGhost
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
        virtual bool isInWorld()const;
        
        virtual void setMass(f32 mass);
        virtual f32 getMass()const;
        
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual const btVector3 &getVelocity()const;
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual const btVector3 &getAngularVelocity()const;
    protected:
        
        virtual const btCollisionObject* getCollisionObject() const;
        virtual btCollisionObject* getCollisionObject();
        virtual void setCollisionObject(const btCollisionObject &obj, PhysicsShape *shape);
        
        virtual bool setTransform(const btTransform &transform = btTransform::getIdentity());
        virtual bool removePhysicsBody();
        
        virtual const btPairCachingGhostObject* getBody() const;
        virtual btPairCachingGhostObject* getBody();
    private:
        btPairCachingGhostObject *m_btPairCachingGhostObject;
    };
}

#endif /* defined(__JLIGameEngineTest__PhysicsBodyGhost__) */
