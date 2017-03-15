//
//  PhysicsWorld.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsWorld__
#define __JLIGameEngineTest__PhysicsWorld__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "Util.h"
#include "btAlignedObjectArray.h"

#include "btOverlappingPairCache.h"
#include "lua.hpp"

class btVector3;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
struct btOverlapFilterCallback;
class btGhostPairCallback;
class btPairCachingGhostObject;
struct btBroadphaseProxy;

class btVoronoiSimplexSolver;
class btMinkowskiPenetrationDepthSolver;

#include "btDynamicsWorld.h"

#include "JLIFactoryTypes.h"

namespace njli {
typedef void (*ghostCallback)();

extern void DefaultCustomPreTickCallback(btDynamicsWorld* world, btScalar timeStep);
extern void DefaultCustomPostTickCallback(btDynamicsWorld* world, btScalar timeStep);

class Camera;
class PhysicsWorldBuilder;
class PhysicsBody;
class PhysicsBodyRigid;
class Node;
class PhysicsRayContact;
class PhysicsConstraint;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
PhysicsWorld : public AbstractFactoryObject
{
    friend class WorldFactory;
    friend class World;

protected:
    PhysicsWorld();
    PhysicsWorld(const AbstractBuilder&);
    PhysicsWorld(const PhysicsWorld&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~PhysicsWorld();
    PhysicsWorld& operator=(const PhysicsWorld&);

public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
    using AbstractFactoryObject::create;
//    using AbstractFactoryObject::clone;
    using AbstractFactoryObject::getPointer;
    using AbstractFactoryObject::getPointerValue;
    using AbstractFactoryObject::serializeObject;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 calculateSerializeBufferSize() const;

    /**
         *  @author James Folk, 16-02-11 15:02:19
         *
         *  @brief <#Description#>
         *
         *  @param dataBuffer   <#dataBuffer description#>
         *  @param btSerializer <#btSerializer description#>
         */
    virtual void serialize(void* dataBuffer, btSerializer*) const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual const char* getClassName() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 getType() const;
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
    static PhysicsWorld** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(PhysicsWorld * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static PhysicsWorld* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static PhysicsWorld* create(const PhysicsWorldBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param physics <#physics description#>
         *
         *  @return <#return value description#>
         */
    static PhysicsWorld* clone(const PhysicsWorld& physics);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static PhysicsWorld* copy(const PhysicsWorld& object);
    /**
         *  <#Description#>
         *
         *  @param physicsWorld <#physicsWorld description#>
         */
    static void destroy(PhysicsWorld * physicsWorld);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(PhysicsWorld & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

public:
    //TODO: fill in specific methods for PhysicsWorld

    /// <#Description#>
    class CustomFilterCallback : public btOverlapFilterCallback {
    public:
        /**
             *  <#Description#>
             */
        CustomFilterCallback();
        /**
             *  <#Description#>
             *
             *  @return <#return value description#>
             */
        virtual ~CustomFilterCallback();

        /**
             *  <#Description#>
             *
             *  @param proxy0 <#proxy0 description#>
             *  @param proxy1 <#proxy1 description#>
             *
             *  @return <#return value description#>
             */
        virtual bool needBroadphaseCollision(btBroadphaseProxy* proxy0, btBroadphaseProxy* proxy1) const;
    };

    /**
         *  <#Description#>
         *
         *  @param timeStep <#timeStep description#>
         */
    void update(f32 timeStep);
    /**
         *  <#Description#>
         *
         *  @param camera <#camera description#>
         */
    void render(Camera * camera);

    /**
         *  <#Description#>
         *
         *  @param gravity <#gravity description#>
         */
    void setGravity(const btVector3& gravity);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    btVector3 getGravity() const;

    /**
         *  <#Description#>
         *
         *  @param speed <#speed description#>
         */
    void setSimulationSpeed(const f32 speed);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    f32 getSimulationSpeed() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    f32 getTimeStep() const;

    /**
         *  <#Description#>
         *
         *  @param callback <#callback description#>
         */
    void setPreTickCallback(btInternalTickCallback callback);
    /**
         *  <#Description#>
         *
         *  @param callback <#callback description#>
         */
    void setPostTickCallback(btInternalTickCallback callback);

    /**
         *  <#Description#>
         *
         *  @param rayFromWorld   <#rayFromWorld description#>
         *  @param rayToWorld     <#rayToWorld description#>
         *  @param rayContact     <#rayContact description#>
         *  @param collisionGroup <#collisionGroup description#>
         *  @param collisionMask  <#collisionMask description#>
         *
         *  @return <#return value description#>
         */
    bool rayTestClosest(const btVector3& rayFromWorld,
        const btVector3& rayToWorld,
        PhysicsRayContact& rayContact,
        njliBitCategories collisionGroup = JLI_BIT_CATEGORY_DefaultFilter,
        njliBitCategories collisionMask = JLI_BIT_CATEGORY_AllFilter) const;

    /**
         *  <#Description#>
         *
         *  @param rayFromWorld   <#rayFromWorld description#>
         *  @param rayToWorld     <#rayToWorld description#>
         *  @param rayContacts    <#rayContacts description#>
         *  @param numContacts    <#numContacts description#>
         *  @param collisionGroup <#collisionGroup description#>
         *  @param collisionMask  <#collisionMask description#>
         *
         *  @return <#return value description#>
         */
    bool rayTestAll(const btVector3& rayFromWorld,
        const btVector3& rayToWorld,
        btAlignedObjectArray<PhysicsRayContact*>& rayContacts,
        s32& numContacts,
        njliBitCategories collisionGroup = JLI_BIT_CATEGORY_DefaultFilter,
        njliBitCategories collisionMask = JLI_BIT_CATEGORY_AllFilter) const;

    void enablePause(bool enable = true);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    bool isPaused() const;

protected:
    void debugDrawWorld();

public:
    /**
         *  <#Description#>
         *
         *  @param body <#body description#>
         *
         *  @return <#return value description#>
         */
    bool addRigidBody(PhysicsBodyRigid * body);
    /**
         *  <#Description#>
         *
         *  @param body <#body description#>
         *
         *  @return <#return value description#>
         */
    bool removeRigidBody(PhysicsBodyRigid * body);

    /**
         *  <#Description#>
         *
         *  @param constraint                           <#constraint description#>
         *  @param disableCollisionsBetweenLinkedBodies <#disableCollisionsBetweenLinkedBodies description#>
         *
         *  @return <#return value description#>
         */
    bool addConstraint(PhysicsConstraint * constraint, bool disableCollisionsBetweenLinkedBodies = true);
    /**
         *  <#Description#>
         *
         *  @param constraint <#constraint description#>
         *
         *  @return <#return value description#>
         */
    bool removeConstraint(PhysicsConstraint * constraint);

private:
    void ghostObjectCollisionTest();

    f32 m_SimulationSpeed;
    f32 m_TimeStep;

    btDefaultCollisionConfiguration* m_collisionConfiguration;
    btCollisionDispatcher* m_dispatcher;

    btBroadphaseInterface* m_overlappingPairCache;

    btSequentialImpulseConstraintSolver* m_solver;
    btDiscreteDynamicsWorld* m_dynamicsWorld;
    btOverlapFilterCallback* m_btOverlapFilterCallback;
    btGhostPairCallback* m_btGhostPairCallback;

    btAlignedObjectArray<btPairCachingGhostObject*>* m_GhostObjects;

    btBroadphaseInterface* m_broadphase;
    btAlignedObjectArray<struct btBroadphaseProxy*> m_proxies;

    btAlignedObjectArray<Node*> m_collisionNodes;

    bool m_Paused;

    btVoronoiSimplexSolver* m_simplexSolver;
    btMinkowskiPenetrationDepthSolver* m_pdSolver;
};
}

#endif /* defined(__JLIGameEngineTest__PhysicsWorld__) */
