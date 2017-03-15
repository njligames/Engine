//
//  PhysicsWorld.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "PhysicsWorld.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "Camera.h"
#include "PhysicsWorldBuilder.h"

#include "btVector3.h"
#include "btDefaultCollisionConfiguration.h"
#include "btCollisionDispatcher.h"
#include "btDbvtBroadphase.h"
#include "btSequentialImpulseConstraintSolver.h"
#include "btDiscreteDynamicsWorld.h"
#include "btBox2dBox2dCollisionAlgorithm.h"
#include "btConvex2dConvex2dAlgorithm.h"
#include "btMinkowskiPenetrationDepthSolver.h"

#include "btGhostObject.h"

#include "PhysicsBody.h"
#include "PhysicsBodyRigid.h"

#ifdef BT_DEBUG
#include "btQuickprof.h"
#endif

#include "btCollisionAlgorithm.h"
#include "Node.h"

#include "btCollisionWorld.h"
#include "PhysicsRayContact.h"

#include "Log.h"
#define TAG "PhysicsWorld.cpp"
#define FORMATSTRING "{\"njli::PhysicsWorld\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "PhysicsConstraint.h"

#include "btQuickprof.h"

namespace njli
{
    
    
    void DefaultCustomPreTickCallback (btDynamicsWorld *world, btScalar timeStep)
    {
//        CustomGhostObjectCollisionTest();
//        WorldPhysics::getInstance()->ghostObjectCollisionTest();
    }
    
    
    void DefaultCustomPostTickCallback (btDynamicsWorld *world, btScalar timeStep)
    {
    }
    
//    void MyNearCallback(btBroadphasePair& collisionPair,
//                        btCollisionDispatcher& dispatcher, const btDispatcherInfo& dispatchInfo) {
//        
//        // Do your collision logic here
//        // Only dispatch the Bullet collision information if you want the physics to continue
//        dispatcher.defaultNearCallback(collisionPair, dispatcher, dispatchInfo);
//    }

    
    static void CustomNearCallback(btBroadphasePair& collisionPair, btCollisionDispatcher& dispatcher, const btDispatcherInfo& dispatchInfo)
    {
//        BT_PROFILE("CustomNearCallback");
        btCollisionObject *pCollisionObject0 = (btCollisionObject *)collisionPair.m_pProxy0->m_clientObject;
        btCollisionObject *pCollisionObject1 = (btCollisionObject *)collisionPair.m_pProxy1->m_clientObject;
        
        if (dispatcher.needsCollision(pCollisionObject0,pCollisionObject1))
        {
            const btCollisionObjectWrapper* parent = 0;
            btCollisionObjectWrapper obj0Wrap(parent,
                                              pCollisionObject0->getCollisionShape(),
                                              pCollisionObject0,
                                              pCollisionObject0->getWorldTransform(), 0, 0);
            btCollisionObjectWrapper obj1Wrap(parent,
                                              pCollisionObject1->getCollisionShape(),
                                              pCollisionObject1,
                                              pCollisionObject1->getWorldTransform(), 0, 0);
            
            
            //dispatcher will keep algorithms persistent in the collision pair
            if (!collisionPair.m_algorithm)
            {
                collisionPair.m_algorithm = dispatcher.findAlgorithm(&obj0Wrap,&obj1Wrap);
            }
            
            if (collisionPair.m_algorithm)
            {
                btManifoldResult contactPointResult(&obj0Wrap,&obj1Wrap);
                
                if (dispatchInfo.m_dispatchFunc == 		btDispatcherInfo::DISPATCH_DISCRETE)
                {
                    //discrete collision detection query
                    
                    if(collisionPair.m_algorithm != NULL)
                        collisionPair.m_algorithm->processCollision(&obj0Wrap,&obj1Wrap,dispatchInfo,&contactPointResult);
                } else
                {
                    //continuous collision detection query, time of impact (toi)
                    btScalar toi = collisionPair.m_algorithm->calculateTimeOfImpact(pCollisionObject0,pCollisionObject1,dispatchInfo,&contactPointResult);
                    if (dispatchInfo.m_timeOfImpact > toi)
                        dispatchInfo.m_timeOfImpact = toi;
                    
                }
                
                Node *node0 = static_cast<Node*>(pCollisionObject0->getUserPointer());
                Node *node1 = static_cast<Node*>(pCollisionObject1->getUserPointer());
                PhysicsBody *body0 = NULL;
                PhysicsBody *body1 = NULL;
                
                if (node0)
                    body0 = node0->getPhysicsBody();
                
                if (node1)
                    body1 = node1->getPhysicsBody();
                
                
                if(body0 && body1)
                {
                    body0->handleCollisionNear(body1, dispatchInfo);
                    body1->handleCollisionNear(body0, dispatchInfo);
                }
            }
        }
//        dispatcher.defaultNearCallback(collisionPair, dispatcher, dispatchInfo);
    }
    
    static inline btScalar	CustomCalculateCombinedFriction(float friction0,float friction1)
    {
        btScalar friction = friction0 * friction1;
        
        const btScalar MAX_FRICTION  = 10.f;
        if (friction < -MAX_FRICTION)
            friction = -MAX_FRICTION;
        if (friction > MAX_FRICTION)
            friction = MAX_FRICTION;
        return friction;
        
    }
    
    static inline btScalar	CustomCalculateCombinedRestitution(float restitution0,float restitution1)
    {
        return restitution0 * restitution1;
    }
    
    static bool CustomContactAddedCallback(btManifoldPoint& cp,
                                      const btCollisionObjectWrapper* colObj0Wrap,
                                      int partId0,
                                      int index0,
                                      const btCollisionObjectWrapper* colObj1Wrap,
                                      int partId1,
                                      int index1)
    {
        btCollisionObject *pCollisionObject0 = const_cast<btCollisionObject *>(colObj0Wrap->getCollisionObject());
        btCollisionObject *pCollisionObject1 = const_cast<btCollisionObject *>(colObj1Wrap->getCollisionObject());
        
        cp.m_combinedFriction = CustomCalculateCombinedFriction(pCollisionObject0->getFriction(),pCollisionObject1->getFriction());
        cp.m_combinedRestitution = CustomCalculateCombinedRestitution(pCollisionObject0->getRestitution(),pCollisionObject1->getRestitution());
        cp.m_combinedRollingFriction = CustomCalculateCombinedFriction(pCollisionObject0->getRollingFriction(), pCollisionObject1->getRollingFriction());
        
//        Node *node0 = static_cast<Node*>(pCollisionObject0->getUserPointer());
//        Node *node1 = static_cast<Node*>(pCollisionObject1->getUserPointer());
//        PhysicsBody *body0 = node0->getPhysicsBody();
//        PhysicsBody *body1 = node1->getPhysicsBody();
//        
//        if (node0 && node1 && body0 && body1)
//        {
//            body0->handleCollide(body1, cp);
//            body1->handleCollide(body0, cp);
//        }
        
        Node *node0 = static_cast<Node*>(pCollisionObject0->getUserPointer());
        Node *node1 = static_cast<Node*>(pCollisionObject1->getUserPointer());
        PhysicsBody *body0 = NULL;
        PhysicsBody *body1 = NULL;
        
        if (node0)
            body0 = node0->getPhysicsBody();
        
        if (node1)
            body1 = node1->getPhysicsBody();
        
        
        if(body0 && body1)
        {
            body0->handleCollide(body1, cp);
            body1->handleCollide(body0, cp);
        }
        
        
        
        
        //this return value is currently ignored, but to be on the safe side: return false if you don't calculate friction
        return true;
    }
    
    static bool CustomContactProcessedCallback(btManifoldPoint& cp,
                                               void* body0,void* body1)
    {
        return true;
    }
    
    static bool CustomContactDestroyedCallback(void* userPersistentData)
    {
        return true;
    }
    
    
    
    PhysicsWorld::CustomFilterCallback::CustomFilterCallback()
    {
        
    }
    PhysicsWorld::CustomFilterCallback::~CustomFilterCallback()
    {
        
    }
    
    // return true when pairs need collision
    bool PhysicsWorld::CustomFilterCallback::needBroadphaseCollision(btBroadphaseProxy* proxy0,btBroadphaseProxy* proxy1) const
    {
        //BaseEntity *pBaseEntity0 = getEntity(proxy0);
        //BaseEntity *pBaseEntity1 = getEntity(proxy1);
        
        //    bool shouldObjectCollide = true;
        //
        //    if(pBaseEntity0 && pBaseEntity1)
        //    {
        //        shouldObjectCollide = (pBaseEntity1->shouldCollide(pBaseEntity0)
        //                                    || pBaseEntity0->shouldCollide(pBaseEntity1));
        //    }
        
        bool collides = (proxy0->m_collisionFilterGroup & proxy1->m_collisionFilterMask) != 0;
        collides = collides && (proxy1->m_collisionFilterGroup & proxy0->m_collisionFilterMask);
        //collides = collides && shouldObjectCollide;
        
        return collides;
    }
    
    
    
//    PhysicsWorld::PhysicsWorld():
//    AbstractFactoryObject(this),
//    m_SimulationSpeed(1.0f),
//    m_TimeStep(0.0f),
//    m_collisionConfiguration(new btDefaultCollisionConfiguration()),
//    m_dispatcher(new btCollisionDispatcher(m_collisionConfiguration)),
//    m_overlappingPairCache(new btDbvtBroadphase()),
//    m_solver(new btSequentialImpulseConstraintSolver),
//    m_dynamicsWorld(new btDiscreteDynamicsWorld(m_dispatcher,
//                                                m_overlappingPairCache,
//                                                m_solver,
//                                                m_collisionConfiguration)),
//    m_btOverlapFilterCallback(new CustomFilterCallback()),
//    m_btGhostPairCallback(new btGhostPairCallback()),
//    m_GhostObjects(new btAlignedObjectArray<btPairCachingGhostObject*>()),
//    m_Paused(false)
//    {
//        m_dynamicsWorld->setGravity(btVector3(0,0,0));
//        
//        m_dispatcher->setNearCallback(CustomNearCallback);
//        m_dynamicsWorld->getPairCache()->setOverlapFilterCallback(m_btOverlapFilterCallback);
//        m_dynamicsWorld->setInternalTickCallback(DefaultCustomPreTickCallback,NULL,true);
//        m_dynamicsWorld->setInternalTickCallback(DefaultCustomPostTickCallback,NULL,false);
//        m_dynamicsWorld->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(m_btGhostPairCallback);
//    }
    
    
    PhysicsWorld::PhysicsWorld():
    AbstractFactoryObject(this),
    m_SimulationSpeed(1.0f),
    m_TimeStep(0.0f),
    m_collisionConfiguration(new btDefaultCollisionConfiguration()),
    m_dispatcher(new btCollisionDispatcher(m_collisionConfiguration)),
    m_overlappingPairCache(new btDbvtBroadphase()),
    m_solver(new btSequentialImpulseConstraintSolver),
    m_dynamicsWorld(new btDiscreteDynamicsWorld(m_dispatcher,
                                                m_overlappingPairCache,
                                                m_solver,
                                                m_collisionConfiguration)),
    m_btOverlapFilterCallback(new CustomFilterCallback()),
    m_btGhostPairCallback(new btGhostPairCallback()),
    m_GhostObjects(new btAlignedObjectArray<btPairCachingGhostObject*>()),
    m_Paused(false)//,
//    m_simplexSolver(new btVoronoiSimplexSolver()),
//    m_pdSolver(new btMinkowskiPenetrationDepthSolver())
    {
//        m_dynamicsWorld ->getSolverInfo().m_splitImpulse = true;
        
        m_dynamicsWorld->setGravity(btVector3(0,0,0));
        
        m_dispatcher->setNearCallback(CustomNearCallback);
        m_dynamicsWorld->getPairCache()->setOverlapFilterCallback(m_btOverlapFilterCallback);
        m_dynamicsWorld->setInternalTickCallback(DefaultCustomPreTickCallback,NULL,true);
        m_dynamicsWorld->setInternalTickCallback(DefaultCustomPostTickCallback,NULL,false);
        m_dynamicsWorld->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(m_btGhostPairCallback);
        
//        btConvex2dConvex2dAlgorithm::CreateFunc* convexAlgo2d = new btConvex2dConvex2dAlgorithm::CreateFunc(m_simplexSolver,m_pdSolver);
//        
//        m_dispatcher->registerCollisionCreateFunc(CONVEX_2D_SHAPE_PROXYTYPE,CONVEX_2D_SHAPE_PROXYTYPE,convexAlgo2d);
//        m_dispatcher->registerCollisionCreateFunc(BOX_2D_SHAPE_PROXYTYPE,CONVEX_2D_SHAPE_PROXYTYPE,convexAlgo2d);
//        m_dispatcher->registerCollisionCreateFunc(CONVEX_2D_SHAPE_PROXYTYPE,BOX_2D_SHAPE_PROXYTYPE,convexAlgo2d);
//        m_dispatcher->registerCollisionCreateFunc(BOX_2D_SHAPE_PROXYTYPE,BOX_2D_SHAPE_PROXYTYPE,new btBox2dBox2dCollisionAlgorithm::CreateFunc());
        
        m_dynamicsWorld->setDebugDrawer(njli::World::getInstance()->getDebugDrawer());
    }
    
    PhysicsWorld::PhysicsWorld(const AbstractBuilder &builder):
    AbstractFactoryObject(this),
    m_SimulationSpeed(1.0f),
    m_TimeStep(0.0f),
    m_collisionConfiguration(new btDefaultCollisionConfiguration()),
    m_dispatcher(new btCollisionDispatcher(m_collisionConfiguration)),
    m_overlappingPairCache(new btDbvtBroadphase()),
    m_solver(new btSequentialImpulseConstraintSolver),
    m_dynamicsWorld(new btDiscreteDynamicsWorld(m_dispatcher,
                                                m_overlappingPairCache,
                                                m_solver,
                                                m_collisionConfiguration)),
    m_btOverlapFilterCallback(new CustomFilterCallback()),
    m_btGhostPairCallback(new btGhostPairCallback()),
    m_GhostObjects(new btAlignedObjectArray<btPairCachingGhostObject*>()),
    m_Paused(false),
    m_simplexSolver(new btVoronoiSimplexSolver()),
    m_pdSolver(new btMinkowskiPenetrationDepthSolver())
    {
        m_dynamicsWorld ->getSolverInfo().m_splitImpulse = true;
        
        m_dynamicsWorld->setGravity(btVector3(0,0,0));
        
        m_dispatcher->setNearCallback(CustomNearCallback);
        m_dynamicsWorld->getPairCache()->setOverlapFilterCallback(m_btOverlapFilterCallback);
        m_dynamicsWorld->setInternalTickCallback(DefaultCustomPreTickCallback,NULL,true);
        m_dynamicsWorld->setInternalTickCallback(DefaultCustomPostTickCallback,NULL,false);
        m_dynamicsWorld->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(m_btGhostPairCallback);
        
//        btConvex2dConvex2dAlgorithm::CreateFunc* convexAlgo2d = new btConvex2dConvex2dAlgorithm::CreateFunc(m_simplexSolver,m_pdSolver);
//        
//        m_dispatcher->registerCollisionCreateFunc(CONVEX_2D_SHAPE_PROXYTYPE,CONVEX_2D_SHAPE_PROXYTYPE,convexAlgo2d);
//        m_dispatcher->registerCollisionCreateFunc(BOX_2D_SHAPE_PROXYTYPE,CONVEX_2D_SHAPE_PROXYTYPE,convexAlgo2d);
//        m_dispatcher->registerCollisionCreateFunc(CONVEX_2D_SHAPE_PROXYTYPE,BOX_2D_SHAPE_PROXYTYPE,convexAlgo2d);
//        m_dispatcher->registerCollisionCreateFunc(BOX_2D_SHAPE_PROXYTYPE,BOX_2D_SHAPE_PROXYTYPE,new btBox2dBox2dCollisionAlgorithm::CreateFunc());
        
        m_dynamicsWorld->setDebugDrawer(njli::World::getInstance()->getDebugDrawer());
        
    }
    
    PhysicsWorld::PhysicsWorld(const PhysicsWorld &copy):
    AbstractFactoryObject(this),
    m_SimulationSpeed(1.0f),
    m_TimeStep(0.0f),
    m_collisionConfiguration(new btDefaultCollisionConfiguration()),
    m_dispatcher(new btCollisionDispatcher(m_collisionConfiguration)),
    m_overlappingPairCache(new btDbvtBroadphase()),
    m_solver(new btSequentialImpulseConstraintSolver),
    m_dynamicsWorld(new btDiscreteDynamicsWorld(m_dispatcher,
                                                m_overlappingPairCache,
                                                m_solver,
                                                m_collisionConfiguration)),
    m_btOverlapFilterCallback(new CustomFilterCallback()),
    m_btGhostPairCallback(new btGhostPairCallback()),
    m_GhostObjects(new btAlignedObjectArray<btPairCachingGhostObject*>()),
    m_Paused(false),
    m_simplexSolver(new btVoronoiSimplexSolver()),
    m_pdSolver(new btMinkowskiPenetrationDepthSolver())
    {
        m_dynamicsWorld ->getSolverInfo().m_splitImpulse = true;
        
        m_dynamicsWorld->setGravity(btVector3(0,0,0));
        
        m_dispatcher->setNearCallback(CustomNearCallback);
        m_dynamicsWorld->getPairCache()->setOverlapFilterCallback(m_btOverlapFilterCallback);
        m_dynamicsWorld->setInternalTickCallback(DefaultCustomPreTickCallback,NULL,true);
        m_dynamicsWorld->setInternalTickCallback(DefaultCustomPostTickCallback,NULL,false);
        m_dynamicsWorld->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(m_btGhostPairCallback);
        
//        btConvex2dConvex2dAlgorithm::CreateFunc* convexAlgo2d = new btConvex2dConvex2dAlgorithm::CreateFunc(m_simplexSolver,m_pdSolver);
//        
//        m_dispatcher->registerCollisionCreateFunc(CONVEX_2D_SHAPE_PROXYTYPE,CONVEX_2D_SHAPE_PROXYTYPE,convexAlgo2d);
//        m_dispatcher->registerCollisionCreateFunc(BOX_2D_SHAPE_PROXYTYPE,CONVEX_2D_SHAPE_PROXYTYPE,convexAlgo2d);
//        m_dispatcher->registerCollisionCreateFunc(CONVEX_2D_SHAPE_PROXYTYPE,BOX_2D_SHAPE_PROXYTYPE,convexAlgo2d);
//        m_dispatcher->registerCollisionCreateFunc(BOX_2D_SHAPE_PROXYTYPE,BOX_2D_SHAPE_PROXYTYPE,new btBox2dBox2dCollisionAlgorithm::CreateFunc());
        
        m_dynamicsWorld->setDebugDrawer(njli::World::getInstance()->getDebugDrawer());
    }
    
    PhysicsWorld::~PhysicsWorld()
    {
        delete m_pdSolver;m_pdSolver=NULL;
        delete m_simplexSolver;m_simplexSolver=NULL;
        
        delete m_GhostObjects;m_GhostObjects=NULL;
        delete m_btGhostPairCallback;m_btGhostPairCallback=NULL;
        delete m_btOverlapFilterCallback;m_btOverlapFilterCallback=NULL;
        
        for (s32 i=m_dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
        {
            btCollisionObject* obj =
            m_dynamicsWorld->getCollisionObjectArray()[i];
            btRigidBody* body = btRigidBody::upcast(obj);
            if (body && body->getMotionState())
            {
                btMotionState *ms = body->getMotionState();
                delete ms;ms=NULL;
            }
            m_dynamicsWorld->removeCollisionObject( obj );
            delete obj;obj=NULL;
        }
        
        delete m_dynamicsWorld;m_dynamicsWorld=NULL;
        delete m_solver;m_solver=NULL;
        delete m_overlappingPairCache;m_overlappingPairCache=NULL;
        delete m_dispatcher;m_dispatcher=NULL;
        delete m_collisionConfiguration;m_collisionConfiguration=NULL;
    }
    
    PhysicsWorld &PhysicsWorld::operator=(const PhysicsWorld &rhs)
    {
        if(this != &rhs)
        {
            //TODO:implement...
        }
        return *this;
    }
    
    s32	PhysicsWorld::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void PhysicsWorld::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *PhysicsWorld::getClassName()const
    {
        return "PhysicsWorld";
    }
    
    s32 PhysicsWorld::getType()const
    {
        return PhysicsWorld::type();
    }
    
    PhysicsWorld::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    PhysicsWorld **PhysicsWorld::createArray(const u32 size)
    {
        return (PhysicsWorld**)World::getInstance()->getWorldFactory()->createArray(PhysicsWorld::type(), size);
    }
    
    void PhysicsWorld::destroyArray(PhysicsWorld **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    PhysicsWorld *PhysicsWorld::create()
    {
        return dynamic_cast<PhysicsWorld*>(World::getInstance()->getWorldFactory()->create(PhysicsWorld::type()));
    }
    
    PhysicsWorld *PhysicsWorld::create(const PhysicsWorldBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<PhysicsWorld*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    PhysicsWorld *PhysicsWorld::clone(const PhysicsWorld &physics)
    {
        return dynamic_cast<PhysicsWorld*>(World::getInstance()->getWorldFactory()->clone(physics, false));
    }
    
    PhysicsWorld *PhysicsWorld::copy(const PhysicsWorld &object)
    {
        return dynamic_cast<PhysicsWorld*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void PhysicsWorld::destroy(PhysicsWorld *object)
    {
        if(object)
        {
            World::getInstance()->getWorldFactory()->destroy(object);
        }
    }
    
    void PhysicsWorld::load(PhysicsWorld &object, lua_State *L, int index)
    {
        // Push another reference to the table on top of the stack (so we know
        // where it is, and this function can work for negative, positive and
        // pseudo indices
        lua_pushvalue(L, index);
        // stack now contains: -1 => table
        lua_pushnil(L);
        // stack now contains: -1 => nil; -2 => table
        while (lua_next(L, -2))
        {
            // stack now contains: -1 => value; -2 => key; -3 => table
            // copy the key so that lua_tostring does not modify the original
            lua_pushvalue(L, -2);
            // stack now contains: -1 => key; -2 => value; -3 => key; -4 => table
            const char *key = lua_tostring(L, -1);
            const char *value = lua_tostring(L, -2);
            if(lua_istable(L, -2))
            {
                PhysicsWorld::load(object, L, -2);
            }
            else
            {
                if(lua_isnumber(L, index))
                {
                    double number = lua_tonumber(L, index);
                    printf("%s => %f\n", key, number);
                }
                else if(lua_isstring(L, index))
                {
                    const char *v = lua_tostring(L, index);
                    printf("%s => %s\n", key, v);
                }
                else if(lua_isboolean(L, index))
                {
                    bool v = lua_toboolean(L, index);
                    printf("%s => %d\n", key, v);
                }
                else if(lua_isuserdata(L, index))
                {
//                    swig_lua_userdata *usr;
//                    swig_type_info *type;
//                    assert(lua_isuserdata(L,index));
//                    usr=(swig_lua_userdata*)lua_touserdata(L,index);  /* get data */
//                    type = usr->type;
//                    njli::AbstractFactoryObject *object = static_cast<njli::AbstractFactoryObject*>(usr->ptr);
//                    printf("%s => %d:%s\n", key, object->getType(), object->getClassName());
                    
                }
            }
            // pop value + copy of key, leaving original key
            lua_pop(L, 2);
            // stack now contains: -1 => key; -2 => table
        }
        // stack now contains: -1 => table (when lua_next returns 0 it pops the key
        // but does not push anything.)
        // Pop table
        lua_pop(L, 1);
        // Stack is now the same as it was on entry to this function
    }
    
    u32 PhysicsWorld::type()
    {
        return JLI_OBJECT_TYPE_PhysicsWorld;
    }
    
    void PhysicsWorld::update(f32 timeStep)
    {
        BT_PROFILE("PhysicsWorld::update");
        
        gContactAddedCallback = CustomContactAddedCallback;
        gContactProcessedCallback = CustomContactProcessedCallback;
        gContactDestroyedCallback = CustomContactDestroyedCallback;
        
        m_TimeStep = timeStep;
        
        if(!m_Paused)
            m_dynamicsWorld->stepSimulation(m_TimeStep * m_SimulationSpeed);//, 32);
    }
    
    void PhysicsWorld::render(Camera *camera)
    {
        camera->cull((btDbvtBroadphase*)m_overlappingPairCache);
    }
    
    void PhysicsWorld::setGravity(const btVector3 &gravity)
    {
        m_dynamicsWorld->setGravity(gravity);
    }
    btVector3 PhysicsWorld::getGravity()const
    {
        return m_dynamicsWorld->getGravity();
    }
    
    void PhysicsWorld::setSimulationSpeed(const f32 speed)
    {
        m_SimulationSpeed = speed;
    }
    
    f32 PhysicsWorld::getSimulationSpeed()const
    {
        return m_SimulationSpeed;
    }
    
    f32 PhysicsWorld::getTimeStep()const
    {
        return m_TimeStep;
    }
    
    void PhysicsWorld::setPreTickCallback(btInternalTickCallback callback)
    {
        m_dynamicsWorld->setInternalTickCallback(callback,NULL,true);
    }
    
    void PhysicsWorld::setPostTickCallback(btInternalTickCallback callback)
    {
        m_dynamicsWorld->setInternalTickCallback(callback,NULL,false);
    }
    
    bool PhysicsWorld::rayTestClosest(const btVector3 &rayFromWorld,
                                      const btVector3 &rayToWorld,
                                      PhysicsRayContact &rayContact,
                                      njliBitCategories collisionGroup,
                                      njliBitCategories collisionMask)const
    {
        btCollisionWorld::ClosestRayResultCallback rayCallback(rayFromWorld, rayToWorld);
        rayCallback.m_collisionFilterGroup = collisionGroup;
        rayCallback.m_collisionFilterMask = collisionMask;
        rayCallback.m_flags = 0;
        
        m_dynamicsWorld->rayTest(rayFromWorld, rayToWorld, rayCallback);
        
        if(rayCallback.hasHit())
        {
//            Node *😀 = NULL;
            Node *node = static_cast<Node*>(rayCallback.m_collisionObject->getUserPointer());
            node->enableTouched();
            rayContact.set(rayCallback.m_closestHitFraction,
                           rayCallback.m_hitNormalWorld,
                           rayCallback.m_hitPointWorld,
                           node);
            return true;
        }
        return false;
    }
    
    bool PhysicsWorld::rayTestAll(const btVector3 &rayFromWorld,
                                  const btVector3 &rayToWorld,
                                  btAlignedObjectArray<PhysicsRayContact*> &rayContacts,
                                  s32 &numContacts,
                                  njliBitCategories collisionGroup,
                                  njliBitCategories collisionMask)const
    {
        btAlignedObjectArray<Node*> collisionNodes;
        
        btCollisionWorld::AllHitsRayResultCallback rayCallback(rayFromWorld, rayToWorld);
        rayCallback.m_collisionFilterGroup = collisionGroup;
        rayCallback.m_collisionFilterMask = collisionMask;
        rayCallback.m_flags = 0;
        
        m_dynamicsWorld->rayTest(rayFromWorld, rayToWorld, rayCallback);
        
        if(rayCallback.hasHit())
        {
            numContacts = rayCallback.m_collisionObjects.size();
            for (s32 i = 0; i < numContacts; ++i)
            {
                if (i < rayContacts.size())
                {
                    rayContacts.at(i)->set(rayCallback.m_hitFractions[i],
                                           rayCallback.m_hitNormalWorld[i],
                                           rayCallback.m_hitPointWorld[i],
                                           static_cast<Node*>(rayCallback.m_collisionObjects[i]->getUserPointer()));
                }
                else
                {
                    DEBUG_LOG_PRINT_E(TAG, "The btAlignedObjectArray is not large enough (%d of %d)", i, rayContacts.size());
                }
            }
            return true;
        }
        return false;
    }
    
    void PhysicsWorld::enablePause(bool enable)
    {
        m_Paused = enable;
    }
    
    bool PhysicsWorld::isPaused()const
    {
        return m_Paused;
    }
    
    void PhysicsWorld::debugDrawWorld()
    {
        m_dynamicsWorld->debugDrawWorld();
    }
    
    bool PhysicsWorld::addRigidBody(PhysicsBodyRigid *body)
    {
        if(body)
        {
            if(!body->isInWorld())
            {
                m_dynamicsWorld->addRigidBody(body->getBody(),
                                              body->getCollisionGroup(),
                                              body->getCollisionMask());
                
                body->getCollisionObject()->setUserPointer(body->getParent());
            }
            return true;
        }
        return false;
        
    }
    bool PhysicsWorld::removeRigidBody(PhysicsBodyRigid *body)
    {
        if(body && body->getBody())
        {
            if (body->isInWorld())
            {
                m_dynamicsWorld->removeRigidBody(body->getBody());
                body->getCollisionObject()->setUserPointer(NULL);
                
                return true;
            }
        }
        return false;
    }
    
    bool PhysicsWorld::addConstraint(PhysicsConstraint *constraint, bool disableCollisionsBetweenLinkedBodies)
    {
        if(constraint && constraint->getConstraint())
        {
            m_dynamicsWorld->addConstraint(constraint->getConstraint(), disableCollisionsBetweenLinkedBodies);
            return true;
        }
        return false;
    }
    
    bool PhysicsWorld::removeConstraint(PhysicsConstraint *constraint)
    {
        if(constraint && constraint->getConstraint())
        {
            m_dynamicsWorld->removeConstraint(constraint->getConstraint());
            return true;
        }
        return false;
    }
    
    void PhysicsWorld::ghostObjectCollisionTest()
    {
        if(NULL == m_GhostObjects)
            return;
        
        int size = m_GhostObjects->size();
        
        for(int ghostIndex = 0; ghostIndex < size; ghostIndex++)
        {
            btPairCachingGhostObject *pCurrentGhostObject = (*m_GhostObjects)[ghostIndex];
            
            // Prepare for getting all the contact manifolds for one Overlapping Pair
            btManifoldArray   manifoldArray;
            // Get all the Overlapping Pair
            btBroadphasePairArray& pairArray = pCurrentGhostObject->getOverlappingPairCache()->getOverlappingPairArray();
            int numPairs = pairArray.size();
            
            
            
            for (int pairIndex=0;pairIndex<numPairs;pairIndex++)
            {
                manifoldArray.clear();
                
                const btBroadphasePair& pair = pairArray[pairIndex];
                
                //unless we manually perform collision detection on this pair, the contacts are in the dynamics world paircache:
                //The next line fetches the collision information for this Pair
                btBroadphasePair* collisionPair = m_dynamicsWorld->getPairCache()->findPair(pair.m_pProxy0,pair.m_pProxy1);
                if (!collisionPair)
                    continue;
                
                // Read out the all contact manifolds for this Overlapping Pair
                if (collisionPair->m_algorithm)
                    collisionPair->m_algorithm->getAllContactManifolds(manifoldArray);
                
                for (int j=0;j<manifoldArray.size();j++)
                {
                    btPersistentManifold* manifold = manifoldArray[j];
                    
                    const btCollisionObject *pCollisionObject0 = (const btCollisionObject *)manifold->getBody0();
                    const btCollisionObject *pCollisionObject1 = (const btCollisionObject *)manifold->getBody1();
                    
                    Node *node0 = static_cast<Node*>(pCollisionObject0->getUserPointer());
                    Node *node1 = static_cast<Node*>(pCollisionObject1->getUserPointer());
                    
                    for (int p=0;p<manifold->getNumContacts();p++)
                    {
                        const btManifoldPoint&pt = manifold->getContactPoint(p);
                        if (pt.getDistance()<0.f)
                        {
                            if(pCollisionObject0 == pCurrentGhostObject)
                                node0->getPhysicsBody()->handleCollide(node1->getPhysicsBody(),
                                                                       pt);
                            else
                                node1->getPhysicsBody()->handleCollide(node0->getPhysicsBody(),
                                                                       pt);
                        }
                    }
                }
            }
        }
    }
}