//
//  Scene.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__Scene__
#define __JLIGameEngineTest__Scene__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "btAlignedObjectArray.h"
//#include "AbstractTransform.h"
#include "JLIFactoryTypes.h"
#include "lua.hpp"

#include <string>
#include <vector>

class btTransform;
class btVector2;

namespace njli {
class SceneState;
class SceneBuilder;
class Node;
class Camera;
class Light;
class SceneStateMachine;
class ParticleEmitter;
class Material;
class PhysicsWorld;
class PhysicsRayContact;
class Clock;
class Geometry;
    class DeviceTouch;

/**
     *  <#Description#>
     */
ATTRIBUTE_ALIGNED16(class)
Scene : public AbstractFactoryObject
{
    friend class WorldFactory;
    friend class World;
    friend class Node;
    friend class WorldInput;
    friend class WorldState;
    friend class SceneState;

protected:
    Scene();
    Scene(const AbstractBuilder&);
    Scene(const Scene&);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~Scene();
    Scene& operator=(const Scene&);

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
         *  <#Description#>
         *
         *  @param btSerializer <#btSerializer description#>
         */
    virtual void serialize(void*, btSerializer*) const;

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
    static Scene** createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(Scene * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static Scene* create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static Scene* create(const SceneBuilder& builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static Scene* clone(const Scene& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static Scene* copy(const Scene& object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(Scene * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(Scene & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

protected:
    //TODO: fill in specific methods for Scene

    void update(f32 timeStep, const u32 numSubSteps = 2);
    void render();

public:
    /**
         *  <#Description#>
         *
         *  @param node <#node description#>
         */
    void setRootNode(Node * node);
    /**
         *  <#Description#>
         */
    void removeRootNode();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    Node* getRootNode();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const Node* getRootNode() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    SceneStateMachine* getStateMachine();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const SceneStateMachine* getStateMachine() const;

    void removeStateMachine();

    /**
         *  <#Description#>
         *
         *  @param emitter <#emitter description#>
         *
         *  @return <#return value description#>
         */
    //        s32 addParticleEmitter(ParticleEmitter *emitter);
    /**
         *  <#Description#>
         *
         *  @param emitter <#emitter description#>
         *
         *  @return <#return value description#>
         */
    //        bool removeParticleEmitter(ParticleEmitter *emitter);
    /**
         *  <#Description#>
         */
    //        void removeAllParticleEmitters();
    /**
         *  <#Description#>
         *
         *  @param particleEmitters <#particleEmitters description#>
         */
    //        void getParticleEmitters(std::vector<ParticleEmitter*> &particleEmitters)const;
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    //        s32 getParticleEmitterIndex(ParticleEmitter *object)const;
    /**
         *  <#Description#>
         *
         *  @param index <#index description#>
         *
         *  @return <#return value description#>
         */
    //        ParticleEmitter *getParticleEmitter(const u32 index);
    /**
         *  <#Description#>
         *
         *  @param index <#index description#>
         *
         *  @return <#return value description#>
         */
    //        const ParticleEmitter *getParticleEmitter(const u32 index)const;

    /**
         *  @author James Folk, 16-02-11 17:02:26
         *
         *  @brief <#Description#>
         *
         *  @param material <#material description#>
         */
    void addBackground(Material * material);
    /**
         *  <#Description#>
         */
    void removeBackground();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    Material* getBackground();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const Material* getBackground() const;

    /**
         *  <#Description#>
         *
         *  @param world <#world description#>
         */
    void setPhysicsWorld(PhysicsWorld * world);
    /**
         *  <#Description#>
         */
    void removePhysicsWorld();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    PhysicsWorld* getPhysicsWorld();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const PhysicsWorld* getPhysicsWorld() const;

    /**
         *  <#Description#>
         *
         *  @param clock <#clock description#>
         *
         *  @return <#return value description#>
         */
    s32 addClock(Clock * clock);
    /**
         *  <#Description#>
         *
         *  @param clock <#clock description#>
         *
         *  @return <#return value description#>
         */
    bool removeClock(Clock * clock);
    /**
         *  <#Description#>
         */
    void removeAllClocks();
    /**
         *  <#Description#>
         *
         *  @param clocks <#clocks description#>
         */
    void getClocks(std::vector<Clock*> & clocks) const;
    /**
         *  <#Description#>
         *
         *  @param clock <#clock description#>
         *
         *  @return <#return value description#>
         */
    s32 getClockIndex(Clock * clock) const;
    /**
         *  <#Description#>
         *
         *  @param index <#index description#>
         *
         *  @return <#return value description#>
         */
    Clock* getClock(const u32 index);
    /**
         *  <#Description#>
         *
         *  @param index <#index description#>
         *
         *  @return <#return value description#>
         */
    const Clock* getClock(const u32 index) const;

    /**
         *  <#Description#>
         */
    //        void pause();
    /**
         *  <#Description#>
         */
    //        void unPause();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    //        bool isPaused()const;
    
    /**
     *  <#Description#>
     *
     *  @param m_CurrentTouches <#m_CurrentTouches description#>
     */
    void touchDown(DeviceTouch** m_CurrentTouches);
    /**
     *  <#Description#>
     *
     *  @param m_CurrentTouches <#m_CurrentTouches description#>
     */
    void touchUp(DeviceTouch** m_CurrentTouches);
    /**
     *  <#Description#>
     *
     *  @param m_CurrentTouches <#m_CurrentTouches description#>
     */
    void touchMove(DeviceTouch** m_CurrentTouches);
    /**
     *  <#Description#>
     *
     *  @param m_CurrentTouches <#m_CurrentTouches description#>
     */
    void touchCancelled(DeviceTouch** m_CurrentTouches);
    
    void keyboardShow();
    void keyboardCancel();
    void keyboardReturn(const char* text);
    
    void renderHUD();
    
    void pauseGame();
    void unPauseGame();
    
    void willResignActive();
    void didBecomeActive();
    void didEnterBackground();
    void willEnterForeground();
    void willTerminate();
    void interrupt();
    void resumeInterrupt();
    
    void receivedMemoryWarning();
    
    void updateViewSize();
    
    void addCameraNode(Node *cameraNode, bool touchCamera = false);
    
    /**
     *  <#Description#>
     *
     *  @param camera <#camera description#>
     */
    void setTouchCamera(Camera* camera);
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    Camera* getTouchCamera();
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    const Camera* getTouchCamera() const;
protected:
    void addActiveCamera(Camera * camera);
    void removeActiveCamera(Camera * camera);

    void addActiveNode(Node * node);
    void removeActiveNode(Node * node);
    void getActiveNodes(btAlignedObjectArray<Node*> &activeNodes)const;

    void addActiveParticleEmitter(ParticleEmitter * particleEmitter);
    void removeActiveParticleEmitter(ParticleEmitter * particleEmitter);

    void addActiveClock(Clock * clock);
    void removeActiveClock(Clock * clock);

    void addActiveGeometry(Geometry * clock);
    void removeActiveGeometry(Geometry * clock);

    void clearNodeTouches();

    void clearAllStates();

private:
    Node* m_RootNode;
    
    SceneStateMachine* m_SceneStateMachine;
    //        std::vector<ParticleEmitter*> m_ParticleEmitterList;
    Material* m_BackgroundMaterial;
    PhysicsWorld* m_PhysicsWorld;
    std::vector<Clock*> m_ClockList;
    //        bool m_isPaused;

    std::vector<Geometry*> m_ActiveGeometries;

    btAlignedObjectArray<Camera*>* m_ActiveCameras;
    btAlignedObjectArray<Node*>* m_ActiveNodes;

    btAlignedObjectArray<ParticleEmitter*>* m_ActiveParticleEmitters;
    btAlignedObjectArray<Clock*>* m_ActiveClocks;
    btAlignedObjectArray<Geometry*>* m_ActiveGeometry;
    
    Camera* m_TouchCamera;
};
}

#endif /* defined(__JLIGameEngineTest__Scene__) */
